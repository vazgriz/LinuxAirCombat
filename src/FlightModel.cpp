/*
    LAC (Linux Air combat)
    Copyright 2015 by Robert J. Bosen. Major portions of
    this code were derived from "gl-117", by Thomas A. Drexl and
    other contributors, who are mentioned in the "Credits" menu.

    This file is part of LAC.

    LAC is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    LAC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LAC; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <ctype.h>

#include "cockpit.h"
#include "common.h"
#include "conf.h"
#include "dirs.h"
#include "gl.h"
#include "glland.h"
#include "land.h"
#include "main.h"
#include "mathtab.h"
#include "menu.h"
#include "mission.h"

// External Variables, alphabetically within increasingly complex data type groups:
//

extern bool ClimbAngleExceedsMaxSustainable;
extern bool LandedAtSafeSpeed;
extern bool OnTheGround;
extern bool RecoveredFromStall;
extern bool SpeedBrakeRequested;
extern bool WindNoiseOn;

extern char CurrentMissionNumber;
extern char DebugBuf[];

extern unsigned char DefaultAircraft;

extern unsigned int DisplayedAirSpeed;

extern int FlapsLevelElevatorEffectNow;
extern int JustLandedTimer;
extern int NetworkMode;
extern int PlayerAircraftType;
extern int PlayerEngineType;
extern int SkipCount;
extern int ThrottleReference;
extern int TrimElevatorSetting;
extern int TrimRudderSetting;
extern int WindNoiseLevel;

extern Uint32 DeltaTime;
extern Uint32 SpeedBrakeTimer;
extern Uint32 StallTimer;
extern Uint32 MissionNetworkBattle01Timer;

extern float AirDensityAtThisAltitude;
extern float AirspeedManeuverabilityFactor;
extern float CompressibilityElevatorFactor;
extern float CompressibilityRollFactor;
extern float DamageRatio;
extern float DegreesToRadiansFactor;
extern float MaxFullPowerAltitude;
extern float MaxGammaPenaltyPerWeapon;
extern float PlayerAltitude;
extern float PlayersOriginalMaxGamma;
extern float redout;
extern float RegulatedForceX;
extern float RegulatedForceY;
extern float RegulatedForceZ;
extern float SeaLevel;
extern float StallRatio;
extern float TrueAirSpeed;
extern float Turbulence;

extern void setPlaneVolume();

///////////////////////////////////////////
//
// Functions related to Flight Model tuning,
// Alphabetically by name:
//
///////////////////////////////////////////

//
// AileronSettings()
//
void AileronSettings(int x, int y) {
    float TorqueOffset = 0;
    float SpeedEffect;
    float FinalTorqueOffset;
    float aileron = x / 32768.0;
    if (difficulty <= 2) { // Get here if ignoring Torque roll
        aileron *= fabs(aileron);
    } else { // Get here if the player has configured us to consider Torque roll
        aileron *= fabs(aileron);
        // Adjust TorqueOffset in proportion to direction of prop rotation and thrust:

        TorqueOffset += 0.1 * (fplayer->thrust / 0.856137);
        TorqueOffset -= 0.1;
        TorqueOffset *= 2.1;
        if (TorqueOffset < 0.0) {
            TorqueOffset = 0.0;
        }

        //
        // OK. TorqueOffset now ranges from 0.0 at idle to 0.2 at full throttle.
        //
        // Now adjust SpeedEffect in inverse proportion to speed:
        //
        SpeedEffect = 1.0 - (((float)DisplayedAirSpeed) / 160.0);
        if (SpeedEffect < 0.0) {
            SpeedEffect = 0.0;
        }
        SpeedEffect *= 3.0;
        //
        // OK. SpeedEffect is 0.0 at any speed above 100MPH. As we slow down below 100 MPH
        // SpeedEffect gradually increases until it is about 1.0 when stopped.
        //

        //
        // Now calculate FinalTorqueOffset by combining TorqueOffset and SpeedEffect:
        FinalTorqueOffset = TorqueOffset * SpeedEffect;
        // Now compensate for different aircraft and engine configurations through
        // an aircraft-specifific "TorqueMultiplier" as configured in aiotject.cpp:
        FinalTorqueOffset *= fplayer->TorqueMultiplier;

        //
        // Now adjust aileron according to accumulated TorqueOffset and SpeedEffect:
        //
        aileron -= FinalTorqueOffset;

    }

    fplayer->rolleffect = (float)-aileron + Turbulence;
    fplayer->rolleffect *= CompressibilityRollFactor;
    AirspeedManeuverabilityFactor = ((fplayer->realspeed) / ((fplayer->StallSpeed) * 1.15));
    if (AirspeedManeuverabilityFactor > 1.0 || difficulty < 4) {
        AirspeedManeuverabilityFactor = 1.0;
    }
    fplayer->rolleffect *= AirspeedManeuverabilityFactor;
}

void CalculateTrueAirspeed() {
    static int SpeedInstrumentTimer = 1;
    float CurrentClimbSpeed;
    float CurrentGroundSpeed;
    float CurrentXPosition;
    float CurrentYPosition;
    float CurrentZPosition;
    float DeltaXPosition;
    float DeltaYPosition;
    float DeltaZPosition;
    static float PriorXPosition;
    static float PriorYPosition;
    static float PriorZPosition;
    SpeedInstrumentTimer -= DeltaTime;
    if (SpeedInstrumentTimer <= 0) {
        SpeedInstrumentTimer = 120000;
        CurrentXPosition = fplayer->tl->x;
        CurrentYPosition = fplayer->tl->y;
        CurrentZPosition = fplayer->tl->z;
        DeltaXPosition = CurrentXPosition - PriorXPosition;
        DeltaYPosition = CurrentYPosition - PriorYPosition;
        DeltaZPosition = CurrentZPosition - PriorZPosition;
        CurrentGroundSpeed = sqrt((DeltaXPosition * DeltaXPosition) + (DeltaZPosition * DeltaZPosition));
        CurrentGroundSpeed *= 35.00;
        CurrentClimbSpeed = fabs(DeltaYPosition) * 15.00;
        if (!OnTheGround) {
            TrueAirSpeed = (CurrentGroundSpeed + CurrentClimbSpeed) * 1.75;
        } else {
            TrueAirSpeed = CurrentGroundSpeed;
        }
        if (TrueAirSpeed > 500) {
            TrueAirSpeed = 500;
        }
        PriorXPosition = CurrentXPosition;
        PriorYPosition = CurrentYPosition;
        PriorZPosition = CurrentZPosition;
    }
}

//
// CompressibilityEffects()
//
void CompressibilityEffects() {
    if (fplayer->InertiallyDampenedPlayerSpeed > fplayer->CompressibilitySpeed) {

        float CompressibilityFactor0;
        float CompressibilityFactor1;
        float CompressibilityFactor2;
        float CompressibilityFactor3;
        CompressibilityFactor0 = (fplayer->InertiallyDampenedPlayerSpeed / fplayer->CompressibilitySpeed);
        if (difficulty >= 4) {
            CompressibilityFactor1 = 1.03 * CompressibilityFactor0 * CompressibilityFactor0;
            CompressibilityFactor2 = CompressibilityFactor1 * CompressibilityFactor1;
            CompressibilityFactor3 = CompressibilityFactor2 * CompressibilityFactor2;
        } else {
            CompressibilityFactor1 = CompressibilityFactor0 * CompressibilityFactor0;
            CompressibilityFactor2 = CompressibilityFactor1 * CompressibilityFactor0;
            CompressibilityFactor3 = CompressibilityFactor2 * CompressibilityFactor2 * CompressibilityFactor2;
        }
        switch (DefaultAircraft) {
        case FIGHTER_P38L:
        {
            if (fplayer->SpeedBrake) {
                CompressibilityElevatorFactor = 1.0 / CompressibilityFactor2;
                CompressibilityRollFactor = 1.2 / CompressibilityFactor2;
            } else {
                CompressibilityElevatorFactor = 1 / (CompressibilityFactor3);
                CompressibilityRollFactor = 0.5 / (CompressibilityFactor3);
            }
            break;
        }
        case FIGHTER_P38F:
        {
            CompressibilityElevatorFactor = 1 / (CompressibilityFactor3);
            CompressibilityRollFactor = 0.66 / (CompressibilityFactor3);
            break;
        }
        case FIGHTER_A6M2:
        {
            CompressibilityElevatorFactor = 1.0 / (CompressibilityFactor2 * CompressibilityFactor1 * 1.2);
            CompressibilityRollFactor = 1.0 / (CompressibilityFactor2 * CompressibilityFactor1 * 1.2);
            break;
        }
        case FIGHTER_A6M5:
        {
            CompressibilityElevatorFactor = 1.0 / (CompressibilityFactor2 * CompressibilityFactor1 * 1.2);
            CompressibilityRollFactor = 1.0 / (CompressibilityFactor2 * CompressibilityFactor1 * 1.2);
            break;
        }
        case BOMBER_B17:
        {
            CompressibilityElevatorFactor = 1.0 / (CompressibilityFactor2 * CompressibilityFactor1);
            CompressibilityRollFactor = 1.0 / (CompressibilityFactor3);
            break;
        }
        case FIGHTER_ME163:
        {
            CompressibilityElevatorFactor = 1.0 / (CompressibilityFactor2 * CompressibilityFactor1);
            CompressibilityRollFactor = 1.0 / (CompressibilityFactor3);
            break;
        }
        default:
        {
            CompressibilityElevatorFactor = 1.0 / (CompressibilityFactor2);
            CompressibilityRollFactor = 1.0 / (CompressibilityFactor2);
        }
        }
    } else {
        CompressibilityElevatorFactor += DeltaTime;
        if (CompressibilityElevatorFactor > 1.0) {
            CompressibilityElevatorFactor = 1.0;
        }
        CompressibilityRollFactor += DeltaTime;
        if (CompressibilityRollFactor > 1.0) {
            CompressibilityRollFactor = 1.0;
        }
    }
}

//
//  CompressibilityTurbulenceEffects()
//
//
void CompressibilityTurbulenceEffects() {
    if (fplayer->InertiallyDampenedPlayerSpeed > fplayer->DiveSpeedLimit1) {

        Turbulence *= 1.2;
    } else if (fplayer->InertiallyDampenedPlayerSpeed > fplayer->CompressibilitySpeed) {
        Turbulence *= 1.1;
    }
}

void DegradeFlightModelDueToOrdnanceLoad() {
    PlayersOriginalMaxGamma = fplayer->maxgamma;
    sprintf(DebugBuf, "DegradeFlightModelDueToOrdnanceLoad() 001 PlayersOriginalMaxGamma = %f", PlayersOriginalMaxGamma);
    display(DebugBuf, LOG_MOST);
    unsigned int TotalMissileLoad = 0;
    int HardPoint;
    for (HardPoint = 0; HardPoint < missiletypes; HardPoint++) {
        TotalMissileLoad += fplayer->missiles[HardPoint];
    }
    display((char*)"DegradeFlightModelDueToOrdnanceLoad() TotalMissileLoad =", LOG_MOST);
    sprintf(DebugBuf, "%d", TotalMissileLoad);
    display(DebugBuf, LOG_MOST);
    if (TotalMissileLoad > 22) {
        TotalMissileLoad = 22;
    }
    sprintf(DebugBuf, "DegradeFlightModelDueToOrdnanceLoad() (float)TotalMissileLoad = %f", (float)TotalMissileLoad);
    display(DebugBuf, LOG_MOST);
    sprintf(DebugBuf, "DegradeFlightModelDueToOrdnanceLoad() PlayersOriginalMaxGamma = %f", PlayersOriginalMaxGamma);
    display(DebugBuf, LOG_MOST);
    sprintf(DebugBuf, "DegradeFlightModelDueToOrdnanceLoad() (float)TotalMissileLoad / 7.0 = %f", (TotalMissileLoad / 7.0));
    display(DebugBuf, LOG_MOST);
    fplayer->maxgamma -= (float)(TotalMissileLoad / 7.0);
    sprintf(DebugBuf, "DegradeFlightModelDueToOrdnanceLoad() adjusted maxgamma = %f", fplayer->maxgamma);
    display(DebugBuf, LOG_MOST);
    MaxGammaPenaltyPerWeapon = (PlayersOriginalMaxGamma - fplayer->maxgamma);
    if (TotalMissileLoad != 0) {
        MaxGammaPenaltyPerWeapon /= TotalMissileLoad;
    }
    if (MaxGammaPenaltyPerWeapon < 0) {
        MaxGammaPenaltyPerWeapon *= -1.0;
    }
    sprintf(DebugBuf, "DegradeFlightModelDueToOrdnanceLoad() MaxGammaPenaltyPerWeapon = %f", MaxGammaPenaltyPerWeapon);
    display(DebugBuf, LOG_MOST);
    unsigned int i;
    for (i = 0; i < TotalMissileLoad; i++) {
        fplayer->maxthrust -= 0.002;
    }
    display((char*)"DegradeFlightModelDueToOrdnanceLoad() has completed.", LOG_MOST);
}

//
// DragEffects()
//
void DragEffects() {
    fplayer->DragEffect = fplayer->StaticDrag;
    float SpeedRatio = fplayer->InertiallyDampenedPlayerSpeed * fplayer->InertiallyDampenedPlayerSpeed / fplayer->SeaLevelSpeedLimitThreshold * fplayer->SeaLevelSpeedLimitThreshold;
    SpeedRatio *= 0.4;
    fplayer->forcex *= (1.0 - SpeedRatio);
    fplayer->forcey *= (1.0 - SpeedRatio);
    fplayer->forcez *= (1.0 - SpeedRatio);
}

//
// ElevatorSettings()
//
void ElevatorSettings(int x, int y) {
    if (SkipCount > 5) {

        fplayer->elevatoreffect = ((float)(y + TrimElevatorSetting + FlapsLevelElevatorEffectNow) / 30000) + 2.0 * Turbulence;
    } else {

        fplayer->elevatoreffect = ((float)(y + TrimElevatorSetting + FlapsLevelElevatorEffectNow) / 30000) - 2.0 * Turbulence;
    }
    fplayer->elevatoreffect *= CompressibilityElevatorFactor;
    fplayer->elevatoreffect *= AirspeedManeuverabilityFactor;
}

//
// RegulateGamma();
//
void RegulateGamma() {
    float GammaRegulation = SIN(fplayer->theta) * (float)DeltaTime * 0.0004;
    fplayer->gamma -= fabs(GammaRegulation);
}

//
// RegulateXYZForces();
//
void RegulateXYZForces(float forcex, float forcey, float forcez) {
    Uint32 OverSpeedTimer = 0;
    static float ForceXRegulator = 0.0;
    static float ForceYRegulator = 0.0;
    static float ForceZRegulator = 0.0;
    if (fplayer->InertiallyDampenedPlayerSpeed > (fplayer->SeaLevelSpeedLimitThreshold + (PlayerAltitude / 1018000))) {

        OverSpeedTimer += DeltaTime; // How much time has accumulated since we entered overspeed condition?

        ForceXRegulator += ((float)DeltaTime / (fplayer->DragEffect * 10));
        ForceZRegulator = ForceYRegulator = ForceXRegulator;

        forcex = forcex / (ForceXRegulator + 1.0);
        forcey = forcey / (ForceYRegulator + 1.0);
        forcez = forcez / (ForceZRegulator + 1.0);
    } else {
        OverSpeedTimer = 0; // Stop accumulating time in OverSpeed condition.
        ForceXRegulator -= ((float)DeltaTime / (fplayer->DragEffect * 20));
        if (ForceXRegulator < 0) {
            ForceXRegulator = 0;
        }
        ForceZRegulator = ForceYRegulator = ForceXRegulator;
    }
    // Now export our regulated forces for external use:
    RegulatedForceX = forcex;
    RegulatedForceY = forcey;
    RegulatedForceZ = forcez;
}

//
// Rudder Settings()
//
void RudderSettings(int rudder) {
    fplayer->ruddereffect = (float)(rudder + TrimRudderSetting) / 30000;
    if (fplayer->ruddereffect > 1.0) {
        fplayer->ruddereffect = 1.0;
    } else if (fplayer->ruddereffect < -1.0) {
        fplayer->ruddereffect = -1.0;
    }

    fplayer->rolleffect += ((fplayer->ruddereffect) / 30);
}

//
// SpeedBrakeEffects()
//
void SpeedBrakeEffects() {
    if (fplayer->SpeedBrakePower == 1.0) {
        fplayer->SpeedBrake = 0;
        return;
    }
    if (SpeedBrakeRequested) {
        SpeedBrakeTimer += DeltaTime;
        if (SpeedBrakeTimer > 2000) {
            fplayer->SpeedBrake = 1;
        }
    } else {
        SpeedBrakeTimer = 0;
        fplayer->SpeedBrake = 0;
    }
}

//
// StallEffects()
//
void StallEffects() {
    if (fplayer->InertiallyDampenedPlayerSpeed < (fplayer->StallSpeed - (float)(fplayer->FlapsLevel / 80.0))) {
        StallRatio = (fplayer->InertiallyDampenedPlayerSpeed / fplayer->StallSpeed);
        fplayer->elevatoreffect *= 0.25;
        fplayer->elevatoreffect *= StallRatio;
        fplayer->rolleffect *= 0.25;
        fplayer->rolleffect *= StallRatio;
        if (fplayer->gamma > 167) {
            StallTimer += DeltaTime;
            if (StallTimer > 25) {
                float height = fplayer->tl->y - l->getExactHeight(fplayer->tl->x + 1, fplayer->tl->z);
                if (height > 0.9) {
                    fplayer->gamma -= 0.7; // Drop the nose..... Was 1.5
                }
                StallTimer = 0;
            }
        } else {
            StallTimer = 0;

            RecoveredFromStall = true;
        }
    }
    if (fplayer->elevatoreffect > 1.0) {
        fplayer->elevatoreffect = 1.0;
    } else if (fplayer->elevatoreffect < -0.5) {
        fplayer->elevatoreffect = -0.5;
    }
}

//
//   TestAltitudeAirDensity()
//
//
void TestAltitudeAirDensity() {
    float LowAltitudeDragFactor = 1.0;
    float DragDissipationAsAltitudeIncreases = 0.137;
    switch (DefaultAircraft) {
    case BOMBER_B17:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.15;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_B24:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.15;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_B25:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.139;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_B26:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.16;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_B29:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.30;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_B5N:
    {
        LowAltitudeDragFactor = 1.0;
        DragDissipationAsAltitudeIncreases = 0.002;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_DORNIER:
    {
        LowAltitudeDragFactor = 1.2;
        DragDissipationAsAltitudeIncreases = 0.750;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_HE111:
    {
        LowAltitudeDragFactor = 1.3;
        DragDissipationAsAltitudeIncreases = 0.550;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_JU87:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.22;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_JU88:
    {
        LowAltitudeDragFactor = 1.4;
        DragDissipationAsAltitudeIncreases = 0.550;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_LANCASTER:
    {
        LowAltitudeDragFactor = 1.3;
        DragDissipationAsAltitudeIncreases = 0.880;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_MOSQUITOB:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.550;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_SB2C:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.170;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case BOMBER_TBF:
    {
        LowAltitudeDragFactor = 1.2;
        DragDissipationAsAltitudeIncreases = 0.170;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_A6M2:
    {
        LowAltitudeDragFactor = 1.07;
        DragDissipationAsAltitudeIncreases = 0.130;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_A6M5:
    {
        LowAltitudeDragFactor = 1.07;
        DragDissipationAsAltitudeIncreases = 0.130;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_MACCIC202:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.16;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_D3A:
    {
        LowAltitudeDragFactor = 1.0;
        DragDissipationAsAltitudeIncreases = 0.1;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_F4U:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.210;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_F4F:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.10;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_F6F:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.18;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_FW190:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.18;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_LA5:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.185;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_LA7:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.185;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_ME109F:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.21;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_ME109G:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.21;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_N1K1:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.16;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P38F:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.190;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P38L:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.192;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P39:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.095;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P40:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.25;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P47D:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.20;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P51B:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.188;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_P51D:
    {
        LowAltitudeDragFactor = 1.1;
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.210;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_SPIT5:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.135;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_SPIT9:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.16;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_TEMPEST:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.16;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_YAK1:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.130;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    case FIGHTER_YAK9:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.137;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
        break;
    }
    default:
    {
        LowAltitudeDragFactor = 1.1;
        DragDissipationAsAltitudeIncreases = 0.16;
        fplayer->AirDensityDrag = LowAltitudeDragFactor - ((fplayer->tl->y / MAXALTITUDE) * DragDissipationAsAltitudeIncreases);
    }
    }
}

//
// TestDiveSpeedStructuralLimit()
//
void TestDiveSpeedStructuralLimit() {
    if (fplayer->InertiallyDampenedPlayerSpeed > fplayer->DiveSpeedStructuralLimit) {
        fplayer->SpeedBeyondStructuralLimitsTimer += DeltaTime;
        fplayer->SpeedBeyondStructuralLimitsDrag = 1.0 + ((float)fplayer->SpeedBeyondStructuralLimitsTimer / 1000.0);
        if (fplayer->SpeedBeyondStructuralLimitsTimer > 3000) {
            if (fplayer->SpeedBeyondStructuralLimitsTimer > 8000) {
                fplayer->Durability -= 80;
                fplayer->SpeedBeyondStructuralLimitsTimer = 0;
            }
        }
    } else {
        fplayer->SpeedBeyondStructuralLimitsTimer = 0;
        fplayer->SpeedBeyondStructuralLimitsDrag = 1.0;
    }
} // End TestDiveSpeedStructuralLimit()

//
//  TestForExcessGamma()
//
void TestForExcessGamma() {
    float ExcessGamma1 = (fplayer->gamma - 180) - fplayer->maxgamma; // How much steeper is our climb angle than our maxgamma?
    float ExcessGamma;
    if (fplayer->maxDurability < 17000) {
        ExcessGamma = ExcessGamma1 + (fplayer->tl->y / 150);
    } else {
        ExcessGamma = ExcessGamma1 + (fplayer->tl->y / 600);
    }
    if (ExcessGamma > 0.0) {
        ClimbAngleExceedsMaxSustainable = true;
        if (fplayer->id == FIGHTER_P38L || fplayer->id == FIGHTER_P38F) {
            fplayer->GammaDrag += (ExcessGamma * DeltaTime / 240000.0);
        } else if (fplayer->id == FIGHTER_P51D) {
            fplayer->GammaDrag += (ExcessGamma * DeltaTime / 220000.0);
        } else if (fplayer->id == FIGHTER_A6M2) {
            fplayer->GammaDrag += (ExcessGamma * DeltaTime / 200000.0);
        }

        else { // Fine-tune default aircraft performance here
            fplayer->GammaDrag += (ExcessGamma * DeltaTime / 210000.0);
        }
    } else {
        ClimbAngleExceedsMaxSustainable = false;
        if (fplayer->GammaDrag > 5.0) {
            fplayer->GammaDrag = 5.0;
        }
        fplayer->GammaDrag -= DeltaTime * .0002;
        if (fplayer->GammaDrag < 1.0) {
            fplayer->GammaDrag = 1.0;
        }
    }
}

//
// TestForFlapEffects()
//
void TestForFlapEffects() {
    if (fplayer->FlapsLevel > 0) {
        fplayer->FlapDrag = 1.0 + (float)FlapsLevelElevatorEffectNow / 16000.0;
    } else {
        fplayer->FlapDrag = 1.0;
    }
}

//
// TestForLoopBeyondVertical()
//
void TestForLoopBeyondVertical() {
    if (fplayer->checkLooping()) { //Get here Once every time we loop beyond the vertical.
        // Set "LoopedBeyondVertical" flag:
        fplayer->LoopedBeyondVertical = true;
    }
    if (fplayer->LoopedBeyondVertical) {
        if ((((fplayer->gamma - 180) > 30) || (fplayer->theta > 35)) && (fplayer->LoopedBeyondVerticalTime < 3000)) {

            fplayer->LoopedBeyondVerticalTime += DeltaTime;
            fplayer->LoopedBeyondVerticalDrag = 1.0 + ((float)fplayer->LoopedBeyondVerticalTime / 10000.0);
        } else {
            fplayer->LoopedBeyondVertical = false;
            fplayer->LoopedBeyondVerticalTime = 0;
            fplayer->LoopedBeyondVerticalDrag = 1.0;
        }
    }
} // End TestForLoopBeyondVertical()

//
// TestForSpeedBrakeDrag
//
void TestForSpeedBrakeDrag() {
    if (fplayer->SpeedBrake) {
        fplayer->SpeedBrakeDrag = fplayer->SpeedBrakePower;
    } else {
        fplayer->SpeedBrakeDrag = 1.0;
    }
}

//
// TestForUndercarriageEffects()
//
void TestForUndercarriageEffects() {
    if (fplayer->UndercarriageLevel > 0) {
        fplayer->UndercarriageDrag = 1.30;
    } else {
        fplayer->UndercarriageDrag = 1.0;
    }
} // End TestForUndercarriageEffects()

void TestForWindNoise() {
    static int PriorWindNoiseLevel;
    float WindNoiseLevel1 = 0;
    float WindNoiseLevel2 = 0;
    WindNoiseLevel1 = (128.0 * (fplayer->thrust / fplayer->maxthrust)) - 80.0;
    WindNoiseLevel2 = (128.0 * (fplayer->InertiallyDampenedPlayerSpeed / fplayer->DiveSpeedStructuralLimit));
    WindNoiseLevel = (int)(WindNoiseLevel1 + WindNoiseLevel2) / 2.0;
    if (WindNoiseLevel > 126) {
        WindNoiseLevel = 126;
    }
    if (WindNoiseLevel != PriorWindNoiseLevel) {
        sound->setVolume(SOUND_WINDNOISE, WindNoiseLevel);
        PriorWindNoiseLevel = WindNoiseLevel;
    }
    if ((WindNoiseOn == false) && (CurrentMissionNumber != MISSION_DEMO) && (game == GAME_PLAY)) {
        WindNoiseOn = true;
        sound->playLoop(SOUND_WINDNOISE);
    }
}

//
// ThrottleSettings()
//
void ThrottleSettings(int throttleinput) {
    static short int PriorThrottleReference = 0;
    static short int ThrottleTemp = 0;
    float AirDensityPowerOffset = 1.0;
    ThrottleReference = (throttleinput - 32768);
    fplayer->FuelLevel += ((float)ThrottleReference / 100000000.0) * fplayer->FuelBurnRate;

    // Note that "throttle" ranges from about -32768 (max throttle) to about +32768 (min throttle)
    // and that when the throttle is exactly half-way between min and max then the value of
    // "throttle" is about 0.
    //
    // Now determine whether the user has configured the throttle for the usual "absolute mode"
    // (best for traditional joysticks with a dedicated throttle lever) or for "relative mode"
    // (best for game-console controllers whose throttle lever has a spring that always
    // returns it to the center point). We use the "32" bit of "NetworkMode" for that
    // as follows:
    //
    if (NetworkMode & 32) { // Get here if our throttle level is configured for "relative mode"
        if (throttleinput == PriorThrottleReference) { // Get here if, due to some mysterious quirk, throttleinput gets corrupted by PriorThrottleReference.
            throttleinput = 0; // Discard this quirky little problem.
        }
        if ((throttleinput > -4000) && (throttleinput < 4000)) { // Get here when throttle is at or near spring-loaded center position. Ignore it.
            ThrottleTemp = PriorThrottleReference;
        } // End logic for centered joystick
        else { // Get here if throttle is NOT centered.
            if (throttleinput < -4000) { // Get here when throttle lever is higher than center.
                ThrottleTemp -= 300;
                if (ThrottleTemp < -32000) { // Prevent it from asserting too much throttle
                    ThrottleTemp = -32000;
                }
                PriorThrottleReference = ThrottleTemp;
            }
            if (throttleinput > 4000) { // Get here when throttle lever is lower than center.
                ThrottleTemp += 300;
                if (ThrottleTemp > 32000) { // Prevent it from diminishing throttle too far.
                    ThrottleTemp = 32000;
                }
                PriorThrottleReference = ThrottleTemp;
            }
        } // End logic for UnCentered joystick
        ThrottleReference = ThrottleTemp - 32768;
    }// End relative-mode throttle processing.

    if (DefaultAircraft == FIGHTER_ME163) {
        if (fplayer->Durability < fplayer->maxDurability) {
            fplayer->FuelLevel += ((float)(ThrottleReference - 25000) / 5000000.0) * fplayer->FuelBurnRate;
        }
    }
    if (fplayer->WEPLevel) { // Burn additional fuel
        fplayer->FuelLevel += ((float)ThrottleReference / 39000000.0);
    }
    if (fplayer->FuelLevel < 0) {
        fplayer->FuelLevel = 0;
    }
    if (fplayer->FuelLevel > 0) {

        if (DefaultAircraft == FIGHTER_SPIT5 || DefaultAircraft == FIGHTER_SPIT9) {
            if ((redout > 60.0) || (blackout == 0.0 && (fplayer->theta < -140 || fplayer->theta > 140))) {
                //Cut throttle due to Spitfire's well-known carburator flow problems
                ThrottleReference = 0;
            }
        }
        MaxFullPowerAltitude = fplayer->MaxFullPowerAltRatio * MAXALTITUDE;

        fplayer->recthrust = fplayer->maxthrust * ThrottleReference / 65536 * -1;
        if (ThrottleReference > -32) {
            fplayer->recthrust = 0.0;
            fplayer->thrustDown();
        }

        float DescentAngle = fplayer->gamma - 180.0;
        float SinOfDescentAngle = sin(DescentAngle * DegreesToRadiansFactor);
        if (difficulty > 3) {
            if (fplayer->gamma < 180) {
                fplayer->recthrust += (2.0 * SinOfDescentAngle); // increase thrust per steepness
            } else {
                fplayer->recthrust += (1.0 * SinOfDescentAngle); // decrease thrust per steepness
            }
        }

        DamageRatio = fplayer->Durability / fplayer->maxDurability;
        if (DamageRatio < 0.6) {
            fplayer->recthrust *= DamageRatio;
            fplayer->recthrust *= 1.3;
        }
        if (fplayer->tl->y > MaxFullPowerAltitude) {

            AirDensityAtThisAltitude = (MaxFullPowerAltitude / fplayer->tl->y);

            switch (DefaultAircraft) {
            case FIGHTER_HAWK:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            case FIGHTER_P47D:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case FIGHTER_P38L:
            {
                AirDensityPowerOffset = 1.1;
                break;
            }
            case FIGHTER_P38F:
            {
                AirDensityPowerOffset = 1.1;
                break;
            }
            case FIGHTER_P51D:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case FIGHTER_FIATG55:
            {
                AirDensityPowerOffset = 0.81;
                break;
            }
            case FIGHTER_F4F:
            {
                AirDensityPowerOffset = 1.1;
                break;
            }
            case FIGHTER_F6F:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case FIGHTER_F4U:
            {
                AirDensityPowerOffset = 1.21;
                break;
            }
            case FIGHTER_FW190:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case BOMBER_B17:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            case FIGHTER_P39:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            case FIGHTER_P40:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            case BOMBER_B24:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            case FIGHTER_A6M2:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case FIGHTER_IL16:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case FIGHTER_KI43:
            {
                AirDensityPowerOffset = 1.22;
                break;
            }
            case BOMBER_JU87:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case BOMBER_G5M:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case BOMBER_B25:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case BOMBER_B26:
            {
                AirDensityPowerOffset = 1.2;
                break;
            }
            case FIGHTER_SPIT5:
            {
                AirDensityPowerOffset = 1.25;
                break;
            }
            case FIGHTER_SPIT9:
            {
                AirDensityPowerOffset = 1.25;
                break;
            }
            case FIGHTER_ME109G:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case FIGHTER_LA5:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case FIGHTER_LA7:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case FIGHTER_IL2:
            {
                AirDensityPowerOffset = 1.15;
                break;
            }
            case FIGHTER_TEMPEST:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            default:
            {
                AirDensityPowerOffset = 1.0;
            }
            }
            fplayer->recthrust *= AirDensityAtThisAltitude * AirDensityPowerOffset;
            if (fplayer->tl->y > fplayer->ServiceCeilingAltitude) {
                fplayer->tl->y = fplayer->ServiceCeilingAltitude;
            }
        } else {

            switch (DefaultAircraft) {
            case FIGHTER_P51D:
            {
                AirDensityPowerOffset = 1.0;
                break;
            }
            case FIGHTER_ME163:
            {
                fplayer->FuelLevel += 5.0 * ((float)ThrottleReference / 100000000.0);
                break;
            }
            default:
            {
                AirDensityPowerOffset = 1.0;
            }
            }
            AirDensityAtThisAltitude = 1.0;
            if (!OnTheGround) {
                if (fplayer->recthrust < 0.55) {
                    fplayer->recthrust = 0.55;
                }
            }
        }
        if (fplayer->WEPLevel) {

            fplayer->recthrust *= 1.2;
        }
    } else {
        if (!LandedAtSafeSpeed) {
            fplayer->recthrust = (fplayer->maxthrust * 0.16 - 0.154696) * 2.5;
        }
        if (OnTheGround) {
            fplayer->recthrust = -0;
        }
        if (PlayerEngineType == 0) {
            sound->stop(SOUND_PLANE1);
        } else if (PlayerEngineType == 1) {
            sound->stop(SOUND_PLANE2);
        }
    }
    if (PriorThrottleReference != ThrottleReference) {
        setPlaneVolume();
    }
}

//
//   ZeroSpeedCorrection()
//
void ZeroSpeedCorrection() {
    // Prevent extremely low speed because it triggers graphical errors somehow.
    if (fplayer->realspeed < 0.01) {
        fplayer->realspeed = 0.0001;
    }
}
