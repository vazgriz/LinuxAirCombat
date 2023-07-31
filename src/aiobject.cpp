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

/* This file includes all AI objects instancing models. */

#include "aiobject.h"
#include "glland.h"
#include "land.h"
#include "main.h"
#include "mathtab.h"
#include "mission.h"
#include "NetworkApi.h"

extern bool ClearSpeedHistoryArrayFlag;
extern bool GearUpDamageAlreadyInflicted;
extern bool LandedAtSafeSpeed;
extern bool LandingLogged;
extern bool OnTheGround;
extern bool MissileFired;
extern bool NetworkMissionIsActiveWithDataFlow;
extern bool NewSystemMessageNeedsScrolling;
extern bool PlayerCollidedWithAircraftCarrier;
extern bool RadarReflectorBlueHasBeenDestroyedAtLeastOnce;
extern bool RadarReflectorRedHasBeenDestroyedAtLeastOnce;
extern bool RecoveredFromStall;
extern bool TakeoffLogged;
extern bool WindNoiseOn;

extern char CurrentMissionNumber;

extern char DebugBuf[];
extern char SystemMessageBufferA[];

extern unsigned char MissionHeadToHead00State;

extern unsigned char AirfieldChosenForLanding;
extern unsigned char AirfieldRequested;
extern unsigned char BattleshipSunkAlertCountBlue;
extern unsigned char BattleshipSunkAlertCountRed;
extern unsigned char DefaultAircraft;
extern unsigned char GoodMenuBehavior;
extern unsigned char HighestRecentMyNetworkId;
extern unsigned char MissionObjectHqBlue;
extern unsigned char MissionObjectHqRed;
extern unsigned char MaxPlayersInCurrentMission;
extern unsigned char MissionHeadToHead00State;
extern unsigned char MissionCommander;
extern unsigned char MissionCommanderCandidate;
extern unsigned char MissionIdNegotiationCount;
extern unsigned char MissionObjectAirfieldBlue1;
extern unsigned char MissionObjectAirfieldRed1;
extern unsigned char MissionObjectAirfieldBlue2;
extern unsigned char MissionObjectAirfieldRed2;
extern unsigned char MissionObjectAirfieldBlue3;
extern unsigned char MissionObjectAirfieldRed3;
extern unsigned char MissionObjectAirfieldBlue4;
extern unsigned char MissionObjectAirfieldRed4;
extern unsigned char MissionObjectBatteryBlue1;
extern unsigned char MissionObjectBatteryRed1;
extern unsigned char MissionObjectBatteryBlue2;
extern unsigned char MissionObjectBatteryRed2;
extern unsigned char MissionObjectBatteryBlue3;
extern unsigned char MissionObjectBatteryRed3;
extern unsigned char MissionObjectBatteryBlue4;
extern unsigned char MissionObjectBatteryRed4;
extern unsigned char MissionObjectBattleshipBlue1;
extern unsigned char MissionObjectBattleshipRed1;
extern unsigned char MissionObjectBattleshipBlue2;
extern unsigned char MissionObjectBattleshipRed2;
extern unsigned char MissionObjectBattleshipBlue3;
extern unsigned char MissionObjectBattleshipRed3;
extern unsigned char MissionObjectBattleshipBlue4;
extern unsigned char MissionObjectBattleshipRed4;
extern unsigned char MissionObjectBunkerBlue1;
extern unsigned char MissionObjectBunkerRed1;
extern unsigned char MissionObjectBunkerBlue2;
extern unsigned char MissionObjectBunkerRed2;
extern unsigned char MissionObjectBunkerBlue3;
extern unsigned char MissionObjectBunkerRed3;
extern unsigned char MissionObjectBunkerBlue4;
extern unsigned char MissionObjectBunkerRed4;
extern unsigned char MissionObjectCarrierBlue1;
extern unsigned char MissionObjectCarrierRed1;
extern unsigned char MissionObjectCarrierBlue2;
extern unsigned char MissionObjectCarrierRed2;
extern unsigned char MissionObjectCarrierBlue3;
extern unsigned char MissionObjectCarrierRed3;
extern unsigned char MissionObjectCarrierBlue4;
extern unsigned char MissionObjectCarrierRed4;
extern unsigned char MissionObjectDestroyerBlue1;
extern unsigned char MissionObjectDestroyerRed1;
extern unsigned char MissionObjectDestroyerBlue2;
extern unsigned char MissionObjectDestroyerRed2;
extern unsigned char MissionObjectDestroyerBlue3;
extern unsigned char MissionObjectDestroyerRed3;
extern unsigned char MissionObjectDestroyerBlue4;
extern unsigned char MissionObjectDestroyerRed4;
extern unsigned char MissionObjectRadarBlue1;
extern unsigned char MissionObjectRadarRed1;
extern unsigned char MissionObjectRadarBlue2;
extern unsigned char MissionObjectRadarRed2;
extern unsigned char MissionObjectRadarBlue3;
extern unsigned char MissionObjectRadarRed3;
extern unsigned char MissionObjectRadarBlue4;
extern unsigned char MissionObjectRadarRed4;
extern unsigned char MissionOutPacketCount;
extern unsigned char MissionStateNetworkBattle;
extern unsigned char MyNetworkId;
extern unsigned char NetworkApiVersion;
extern unsigned char NetworkOpponent;
extern unsigned char NewestInPacketId;

extern unsigned char MyNetworkId;
extern unsigned char NetworkOpponent;
extern unsigned char RecentVictim;

extern unsigned int DisplayedAirSpeed;

extern int AirfieldXMax;
extern int AirfieldXMin;
extern int AirfieldYMax;
extern int AirfieldYMin;
extern int IffOnOff;
extern int MissionEndingTimer;
extern int MissionEndingTimer2;
extern int MissionNumber;
extern int NetworkMode;
extern int RadarOnOff;

extern Uint32 DeltaTime;
extern Uint32 LandingTimer;
extern Uint32 Me163LandingTimer;
extern Uint32 ViewResetTimer;

extern float BlackoutSensitivity;
extern float BombCompressibilitySpeed;
extern float CompressibilityRollFactor;
extern float ConfiguredViewDistance;
extern float RecentVictimAltitude;
extern float RecentVictimGamma;
extern float RecentVictimPhi;
extern float RecentVictimTheta;
extern float RecentVictimVelocity;
extern float RecentVictimXPosition;
extern float RecentVictimZPosition;
extern float RegulatedForceX;
extern float RegulatedForceY;
extern float RegulatedForceZ;
extern float SeaLevel;
extern float TrueAirSpeed;

extern LacUdpApiPacket InPacket;

extern FILE* OnlineScoreLogFile;

/*
*
* Function Prototypes:
*/

void CalculateTrueAirspeed();
void event_targetNext();
void RegulateGamma();
void RegulateXYZForces(float forcex, float forcey, float forcez);
void TestAltitudeAirDensity();
void TestDiveSpeedStructuralLimit();
void TestForExcessGamma();
void TestForFlapEffects();
void TestForLoopBeyondVertical();
void TestForSpeedBrakeDrag();
void TestForUndercarriageEffects();
void TestForWindNoise();

extern void RearmRefuelRepair();
extern void UpdateOnlineScoreLogFileWithCrashes();
extern void UpdateOnlineScoreLogFileWithLandings();
extern void UpdateOnlineScoreLogFileWithTakeoffs();

// core AI method
void AIObj::aiAction(Uint32 dt, AIObj** f, AIObj** m, DynamicObj** c, DynamicObj** flare, DynamicObj** chaff) {
    int i;
    timer += dt;
    if (!active && !draw)   // not active, not drawn, then exit
    {
        return;
    }

    if (firecannonttl > 0) {
        firecannonttl -= dt;    // time to fire the next cannon
    }
    if (firemissilettl > 0) {
        firemissilettl -= dt;    // time to fire the next missile
    }
    if (fireflarettl > 0) {
        fireflarettl -= dt;    // time to fire the next flare
    }
    if (firechaffttl > 0) {
        firechaffttl -= dt;    // time to fire the next chaff
    }
    if (smokettl > 0) {
        smokettl -= dt;        // time to activate next smoke element
    }
    // move this object according to our physics model:
    move(dt);

    if (id >= STATIC_PASSIVE)   // no AI for static ground objects (buildings)
    {

        return; // Static ground objects have no need for AI treatment
    }

    if (haveMissile()) {
        if ((missiletype == BOMB01 - MISSILE1) || (missiletype == MISSILE_DF1 - MISSILE1)) {
            ttf = 0;
        }
    }
    // set smoke for objects in motion:
    if ((id >= MISSILE1 && id < MISSILE_MINE1) || (id >= FIGHTER1 && id <= FIGHTER_HAWK)) { // Get here whenever a rocket is in flight.
        // display ((char *) "AI230405AD.", LOG_MOST); 
        float sz = COS(gamma) * COS(phi) * zoom * 1.1; // polar (spherical) coordinates
        float sy = -SIN(gamma) * zoom * 1.1;
        float sx = COS(gamma) * SIN(phi) * zoom * 1.1;
        // some smoke elements per discrete movement
        float fg = sqrt(forcex * forcex + forcey * forcey + forcez * forcez) * 1.5;
        if (fg >= MAXSMOKEELEM) {
            fg = (float)MAXSMOKEELEM - 0.5;
        }
        for (i = 0; i < (int)fg; i++) {
            float fac = (float)i / fg;
            smoke->setSmoke(tl->x - sx - forcex * fac, tl->y - sy - forcey * fac, tl->z - sz - forcez * fac, (int)phi, 39 - i);
        }
        smoke->move(dt, (int)fg + 1);
    }
    if (!active)   // not active, then exit
    {
        return;
    }
    if (explode > 0 || sink > 0)   // exploding or sinking, then exit
    {
        thrust = 0;
        return;
    }

    float pulljoystick = 0.01;
    float nocorrection = 0.1;
    if (recrolleffect > rolleffect + nocorrection) {

        rolleffect += pulljoystick * timestep;
    } else if (recrolleffect < rolleffect - nocorrection) {

        rolleffect -= pulljoystick * timestep;
    }
    if (recelevatoreffect > elevatoreffect + nocorrection) {

        elevatoreffect += pulljoystick * timestep;
    } else if (recelevatoreffect < elevatoreffect - nocorrection) {

        elevatoreffect -= pulljoystick * timestep;
    }

    if (NetworkMissionIsActiveWithDataFlow) {
        if (this->MyMissionPlayerNumber == 2) {

        }
        manoeverstate = 100;

    }

    // do expensive calculations only once
    float TerrainHeightBelowMe = l->getExactHeight(tl->x, tl->z);

    if (target != NULL) {
        if (this->MyMissionPlayerNumber == 2) {
            // display ((char *) "AI230329AH.", LOG_MOST);
        }
        disttarget = distance(target);    // distance to target
    } else {
        disttarget = 1;
        if (this->MyMissionPlayerNumber == 2) {

            // display ((char *) "AI230329AI.", LOG_MOST);
        }
    }
    // We never get here if packets are flowing.
    if (id >= MISSILE1 && id <= MISSILE2) {
        if (target == NULL) {
            ttl = 0; // "time to live". Set to 0 to sink with gravity
        } else if (!target->active) {
            ttl = 0;// "time to live". Set to 0 to sink with gravity
        }
    }
    if (target == NULL) {
        if (this->MyMissionPlayerNumber == 2) {

            // display ((char *) "AI230329AK.", LOG_MOST);
        }
        if (bomber) {
            targetNearestGroundEnemy(f);
        } else {
            targetNearestEnemy(f);
        }
    }

    if (!ai) {
        return; // Not an AI object. We are done!
    }

    if (id >= FIGHTER1 && id <= FIGHTER2)   // for fighters do the following
    {

        if (this->MyMissionPlayerNumber == 2 && manoeverstate > 218) {
            sprintf(
                DebugBuf,
                "AIObj::aiAction PlayerId=%d, Aircraft=%d, CombatMode=%d, TacticalManoever=%d, PriorManoeverState=%d, manoeverstate=%d, ManoeverStateTimer = %d, gamma=%3.1f, phi=%3.1f, theta=%3.1f, tl->y=%3.1f, recrolleffect=%3.1f, recelevatoreffect=%3.1f, thrust=%3.1f, realspeed=%3.3f, recheight = %3.1f, TerrainHeightBelowMe = %3.1f",
                this->MyMissionPlayerNumber,
                this->id,
                CombatMode,
                TacticalManoever,
                PriorManoeverState,
                manoeverstate,
                ManoeverStateTimer,
                gamma,
                phi,
                theta,
                tl->y,
                recrolleffect,
                recelevatoreffect,
                thrust,
                realspeed,
                recheight,
                TerrainHeightBelowMe
            );
            display(DebugBuf, LOG_MOST);
            if (manoeverstate != PriorManoeverState) {
                switch (manoeverstate) {
                case 0:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"0 \"", "r");
                    break;
                }
                case 1:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"1 \"", "r");
                    break;
                }
                case 2:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"2 \"", "r");
                    break;
                }
                case 3:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"3 \"", "r");
                    break;
                }
                case 4:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"4 \"", "r");
                    break;
                }
                case 5:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"5 \"", "r");
                    break;
                }
                case 6:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"6 \"", "r");
                    break;
                }
                case 7:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"7 \"", "r");
                    break;
                }
                case 8:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"8 \"", "r");
                    break;
                }
                case 9:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"9 \"", "r");
                    break;
                }
                case 10:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"10 \"", "r");
                    break;
                }
                case 11:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"11 \"", "r");
                    break;
                }
                case 12:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"12 \"", "r");
                    break;
                }
                case 13:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"13 \"", "r");
                    break;
                }
                case 14:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"14 \"", "r");
                    break;
                }
                case 15:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"15 \"", "r");
                    break;
                }
                case 16:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"16 \"", "r");
                    break;
                }
                case 17:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"17 \"", "r");
                    break;
                }
                case 18:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"18 \"", "r");
                    break;
                }
                case 19:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"19 \"", "r");
                    break;
                }
                case 20:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"20 \"", "r");
                    break;
                }
                case 21:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"21 \"", "r");
                    break;
                }
                case 100:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"100 \"", "r");
                    break;
                }
                case 200:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"200 \"", "r");
                    break;
                }
                case 201:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"201 \"", "r");
                    break;
                }
                case 202:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"202 \"", "r");
                    break;
                }
                case 203:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"203 \"", "r");
                    break;
                }
                case 204:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"204 \"", "r");
                    break;
                }
                case 205:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"205 \"", "r");
                    break;
                }
                case 206:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"206 \"", "r");
                    break;
                }
                case 207:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"207 \"", "r");
                    break;
                }
                case 208:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"208 \"", "r");
                    break;
                }
                case 209:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"209 \"", "r");
                    break;
                }
                case 210:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"210 \"", "r");
                    break;
                }
                case 211:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"211 \"", "r");
                    break;
                }
                case 212:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"212 \"", "r");
                    break;
                }
                case 213:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"213 \"", "r");
                    break;
                }
                case 214:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"214 \"", "r");
                    break;
                }
                case 215:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"215 \"", "r");
                    break;
                }
                case 216:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"216 \"", "r");
                    break;
                }
                case 217:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"217 \"", "r");
                    break;
                }
                default:
                {
                    //popen ("espeak -p 80 -a 120  -s 200 \"Undefined. \"", "r");
                    break;
                }
                }
            }
            PriorManoeverState = manoeverstate;
        }
    }
    //
    // Bot maneuvers are managed by the following sequence of "manoeverstate" logic:
    //
    if (tl->y > 200 && manoeverstate != 100) {
        if (this->MyMissionPlayerNumber == 2) {

            display((char*)"AI230329AW.", LOG_MOST);
        }
        manoeverstate = 11;
    }
    if (active && draw) {
        if (manoeverstate == 0) {

            if (fabs(theta) > 20) {
                recrolleffect = -0.5;
            } else {
                recrolleffect = 0.0;
            }
            recruddereffect = 0.7;
            // Gradually adjust elevators toward -0.6:
            if (recelevatoreffect > -0.6) { // Get here if elevator pressure is higher than we want
                recelevatoreffect -= (0.25 / ((float)dt));
            } else { // Get here if elevator pressure is NOT higher than we want
                recelevatoreffect += (0.25 / ((float)dt));
            }
            // Get here after adjusting elevators toward about -0.6.
            if (fabs(tl->y - TerrainHeightBelowMe) < 50) {
                manoeverstate = 1;
            }
        }
        if (manoeverstate == 1) {

            // Gradually bring elevator pressure to 0.1:
            if (recelevatoreffect > 0.1) {
                recelevatoreffect -= (0.25 / ((float)dt));
            } else {
                recelevatoreffect += (0.25 / ((float)dt));
            }
            // Get here after adjusting elevators toward 0.1

            if (fabs(theta) > 10) {
                recrolleffect = -1;
            } else {
                recrolleffect = 0;
                manoeverstate = 2;
            }
        }
        if (manoeverstate == 2) {
            if (fabs(theta) <= 150) {

                recrolleffect = 0;
                // Gradually adjust elevator pressure to 1.0:
                if (recelevatoreffect < 1.0) { // If elevatore pressure is less than we want
                    recelevatoreffect += (0.25 / ((float)dt)); // Increase it a bit
                } else { // Otherwise, if it might be too much:
                    recelevatoreffect = 1.0;
                }
            } else {
                manoeverstate = 3;
            }
        }
        if (manoeverstate == 3) {
            if (gamma > 190) { // Get here if still in a climb
                recrolleffect = 0;
                // Gradually adjust elevator pressure to 1.0:
                if (recelevatoreffect < 1.0) {
                    recelevatoreffect += (0.25 / ((float)dt));
                }
                if (recelevatoreffect > 1.0) {
                    elevatoreffect = 1.0;
                }
                // Get here after adjusting elevator pressure toward 1.0
            } else {
                if (myrandom(100) < 50) {
                    manoeverstate = 4;
                } else {
                    if (fabs(tl->y - TerrainHeightBelowMe) > 50) {
                        manoeverstate = 10;
                    } else {
                        manoeverstate = 1;
                    }
                }
            }
        }
        if (manoeverstate == 4) {
            // Gradually adjust elevator pressure to 0.1:
            if (recelevatoreffect > 0.1) { // Get here if elevator pressure is higher than we want
                recelevatoreffect -= (0.25 / ((float)dt)); // diminish it a bit.
            } else { // Get here if elevator might be lower than we want
                recelevatoreffect += (0.25 / ((float)dt)); // increase it a bit.
            }
            // Roll wings level
            if (fabs(theta) > 20) {
                recrolleffect = 1; // Assert strong roll
            } else {
                recrolleffect = 0; // Stop rolling.
                if (InertiallyDampenedPlayerSpeed < StallSpeed * 1.5) {
                    manoeverstate = 0;
                } else {
                    if (myrandom(100) > 70) {
                        manoeverstate = 16;
                    } else {
                        manoeverstate = 0;
                    }
                }
            }
        }
        if (manoeverstate == 10)   // Shallow Dive. No roll.
        {

            //
            // First, level wings until more-or-less flat:
            if ((fabs)(theta) > 15) {
                recrolleffect = 1.0;
            } else {
                recrolleffect = 0;
            }
            // Get here after asserting a roll if our wings are not level yet.
            //
            // Now gradually adjust our elevator pressure to 0.5:
            if (recelevatoreffect < 0.5) { // Get here if elevator pressure is lower than we like
                recelevatoreffect += (0.25 / ((float)dt)); // Increase it a bit
            } else { // Get here if elevator pressure might be higher than we like
                recelevatoreffect -= (0.25 / ((float)dt)); // Decrease it a bit
            }
            // Get here after adjustting elevator pressure toward 0.5.
            if (gamma > 260 || gamma < 75) {
                manoeverstate = 11;
            }
        }
        if (manoeverstate == 11) {
            if (fabs(tl->y) > 100) {
                manoeverstate = 12;
            } else {

                manoeverstate = 1;
            }
        }

        if (manoeverstate == 12) {
            //
            // To start this state off, roll inverted:
            //
            if (fabs(theta) < 170) {

                if (rolleffect > -1.0) { // Get here if we need more neg aileron pressure rolling to our liking
                    rolleffect -= (0.25 / ((float)dt));
                } else { // Get here if we might already have more neg aileron pressure than we like
                    rolleffect = -1.0; // Assert max neg aileron pressure. Keep rolling
                }
                // Get here after adjusting aileron pressure toward 0.6
            } else {
                rolleffect = 0;
            }
            if (tl->y > 100) {
                // Adjust our nose into a dive:
                if (gamma > 150) {

                    if (recelevatoreffect < 1.0) {
                        recelevatoreffect += (0.25 / ((float)dt));
                    } else {
                        recelevatoreffect = 1.0;
                    }
                    // Get here while nose is high after adjusting elevator pressure toward 1.0
                } else { // Get here while rolled upside down, altitude is too high, but nose has descended into a nice dive

                    if (recelevatoreffect > 0) {
                        recelevatoreffect -= (0.25 / ((float)dt)); // Diminish elevator pull a bit more
                    } else {
                        recelevatoreffect += (0.25 / ((float)dt)); // Increase it a bit.
                    }
                    // Still flying upside down, up too high, nose downward, elevator pressure near zero,
                }
            } else {
                if (gamma > 150) {

                    if (recelevatoreffect > -0.5) {
                        recelevatoreffect -= (0.25 / ((float)dt)); // Diminish elevator pressure a little
                    } else {
                        recelevatoreffect += (0.25 / ((float)dt)); // Adjust elevator pressure up a bit
                    }
                    // Get here flying upside down while altitude is nice, with moderate diving pressure on elevators
                } else { // Get here flying upside down while altitude is too high but nose has descended into a nice dive
                    // Adjust elevator pressure to hold current dive angle:
                    if (recelevatoreffect > 0) {
                        recelevatoreffect -= (0.25 / ((float)dt));
                    } else {
                        recelevatoreffect += (0.25 / ((float)dt));
                    }
                }
                // Get here flying upside down while altitude is moderate.
            }
            if (fabs(tl->y - TerrainHeightBelowMe) < 80) {
                manoeverstate = 20;
            }
        }

        if (manoeverstate == 16) {
            if (gamma > 240) {
                // Release elevator pressure
                if (recelevatoreffect > 0) { // Get here if elevator pressure is higher than we like
                    recelevatoreffect -= (0.25 / ((float)dt)); // Decrease it a bit
                } else { // Get here if elevator pressure is negative
                    recelevatoreffect += (0.25 / ((float)dt)); // Increase it a bit
                }
                // Get here after adjusting elevator pressure toward zero.
                recthrust = 0.4;
                if (myrandom(1000) < 2) {
                    manoeverstate = 12;
                }
            } else {
                if (fabs(theta) > 90) { // Get here if our roll is generally upward
                    // Adjust elevatoreffect toward -1.
                    if (recelevatoreffect > -1.0) {  // Get here if we have too much elevatoreffect
                        recelevatoreffect -= (0.25 / ((float)dt)); // Diminish it a bit
                    } else { // Get here if elevatoreffect has gone too far negative
                        recelevatoreffect = -1.0; // Stabilize at -1.0;
                    }
                } else {
                    // Adjust elevatoreffect toward 1.0
                    if (recelevatoreffect < 1.0) {  // Get here if we have too little elevatoreffect
                        recelevatoreffect += (0.25 / ((float)dt)); // Increase it a bit
                    } else { // Get here if elevatoreffect has gone too far positive
                        recelevatoreffect = 1.0; // Stabilize at 1.0;
                    }
                }
            }
            if (InertiallyDampenedPlayerSpeed < StallSpeed * 1.7) {
                recrolleffect = 1.0;
                if (gamma > 240) { // Get here if we are in a steep climb
                    if (recelevatoreffect < 1.0) {
                        recelevatoreffect += (0.25 / ((float)dt));
                    } else {
                        recelevatoreffect = 1.0;
                    }
                }
            }
            if (InertiallyDampenedPlayerSpeed < StallSpeed * 1.4) {
                recthrust = 1.0;
                manoeverstate = 12;
            }
        }

        if (manoeverstate == 20) {
            if (recelevatoreffect < 1.0) {
                recelevatoreffect += (0.25 / ((float)dt));
            } else {
                recelevatoreffect = 1.0;
            }
            // Get here with elevator pull at or approaching 1.0
            recrolleffect = 1;
            if (theta > 80 && theta < 90) {
                manoeverstate = 21;
            }
        }
        if (manoeverstate == 21) {

            if (theta > -10 && theta < 10) { // Get here after wings roll more-or-less level.
                // Gradually diminish elevatoreffect toward 0.0
                if (recelevatoreffect > 0) { // Get here if elevator effect is higher than we like
                    recelevatoreffect -= (0.25 / ((float)dt));
                } else { // Get here if elevator effect is lower than we like
                    recelevatoreffect += (0.25 / ((float)dt)); // Gradually increase elevator effect
                }
                rectheta = 0.0; // Wings have rolled level. Stop rolling.
                NextManoeverStateDuration = 3000;
                manoeverstate = 201;
            }
        }

        if (manoeverstate == 100) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 204;
                NextManoeverStateDuration = 1000;
            }
            if (id >= FIGHTER1 && id <= FIGHTER2) { // Don't get here unless object is an aircraft
                rolleffect = AileronFromPriorInPacket;
                recrolleffect = rolleffect;
                elevatoreffect = ElevatorFromPriorInPacket;
                recelevatoreffect = elevatoreffect;
                ruddereffect = RudderFromPriorInPacket;
                recruddereffect = ruddereffect;
                thrust = ThrustFromPriorInPacket;
                recthrust = thrust;
            }
        }

        //
        // Come to straight and level flight
        //
        if (manoeverstate == 201) {
            if (NextManoeverStateDuration != 0) {
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            ManoeverStateTimer -= dt;
            // Roll Level:
            if ((fabs)(theta) > 10) {
                // Get here if wings NOT rolled level.
                rolleffect = 1; // Keep rolling while wings not level
            } else {
                // Wings are rolled more-or-less level
                rolleffect = 0; // Stop rolling because wings are more-or-less level
            }
            // Begin a gentle climb:
            if (gamma > 190) {
                // Wings rolled level,
                // Climb is steeper than we like.
                if (recelevatoreffect >= -1.0) {
                    // Wings rolled level,
                    // Climb is steeper than we like,
                    // and elevators are NOT working hard to diminish climb
                    recelevatoreffect -= (0.25 / ((float)dt)); // Push elevator down a bit.
                } else {
                    // Wings level,
                    // Climb is steeper than we like,
                    // But elevators are working hard to diminish climb
                    recelevatoreffect = -1.0; // Push elevators to limit of descent.
                }
            } else if (gamma < 180) {
                // Wings rolled level.
                // Nose is lower than level.
                if (recelevatoreffect < 1.0) {
                    // Wings rolled level.
                    // Nose is lower than level.
                    // Elevators are NOT working hard to raise nose.
                    recelevatoreffect += (0.25 / ((float)dt)); // Increase elevator pressure a bit (up)
                } else {
                    // Wings rolled level
                    // Nose is lower than level
                    // Elevators are working hard to raise our nose.
                    recelevatoreffect = 1.0; // Don't let elevator go too high.
                }
            }
            if (ManoeverStateTimer < 0) { // This state expires according to "NextManoeverStateDuration".
                // By now we should be flying more-or-less straight and level.
                recrolleffect = 0; // Set ailerons neutral
                recelevatoreffect = 0; // Set elevators neutral
                rectheta = 0; // Recommend no roll.
                // Set up parameters for next manoeverstate according to current mission:
                switch (CurrentMissionNumber) {
                case MISSION_TUTORIAL:
                {
                    ManoeverStateTargetAltitude = 90; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 11000; // And reset the timer in preparation for next state.
                }
                case MISSION_TUTORIAL3:
                {
                    ManoeverStateTargetAltitude = 95; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 12000; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE01:
                {
                    ManoeverStateTargetAltitude = 96; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 13000; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE02:
                {
                    ManoeverStateTargetAltitude = 97; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 14000; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE03:
                {
                    ManoeverStateTargetAltitude = 98; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 15000; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE04:
                {
                    ManoeverStateTargetAltitude = 99; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 16000; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE05:
                {
                    ManoeverStateTargetAltitude = 100; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 17000; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE06:
                {
                    ManoeverStateTargetAltitude = 101; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 17100; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE07:
                {
                    ManoeverStateTargetAltitude = 102; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 17200; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE08:
                {
                    ManoeverStateTargetAltitude = 103; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 17300; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE09:
                {
                    ManoeverStateTargetAltitude = 104; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 17400; // And reset the timer in preparation for next state.
                }
                case MISSION_NETWORKBATTLE10:
                {
                    ManoeverStateTargetAltitude = 105; // Next state will try to climb to this tl->y altitude.
                    NextManoeverStateDuration = 17500; // And reset the timer in preparation for next state.
                }
                default:
                {
                    display((char*)"AIObj::aiAction() manoeverstate 201: Error: Cannot load parameters for invalid mission.", LOG_MOST);
                    ManoeverStateTargetAltitude = 95; // Next state will try to climb to tl->y = 95.
                    NextManoeverStateDuration = 12000; // And reset the timer in preparation for next state.
                }
                }
                manoeverstate = 202; // Proceedto next manoeverstate
            }
        }

        //
        // Try to adjust altitude to about the level of "ManoeverStateTargetAltitude". At conclusion
        // of this state, wings will be rolled level, but nose could be slightly high or
        // slightly low, as this state oscillates between climbing UP that level or
        // descending DOWN to that level. If this state times out before reaching the desired
        // altitude, it will terminate with wings rolled level but nose high, still climbing.
        // This is the usual termination result if this state 202 is invoked with a setting for
        // "NextManoeverStateDuration" set too low.
        if (manoeverstate == 202) {
            // Get here in straight and level flight.
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 203; // Try for straight and level flight
                NextManoeverStateDuration = 4000; // Allow 4 state 203 4 seconds
            }
            //
            // Climb at best angle (or descend if already higher) to tl->y of 70.
            //
            if (tl->y < ManoeverStateTargetAltitude) { // Get here if we need to climb to reach altitude goal.
                if (gamma < 220) {
                    if (recelevatoreffect < 1.0) {
                        // Wings level,
                        // Need to climb
                        // Climb angle is not too steep
                        // Elevators not yet pulling us up as hard as they can
                        recelevatoreffect += (0.25 / ((float)dt)); // Pull elevators up a little more
                    } else {
                        // Wings level,
                        // Need to climb,
                        // Climb angle is not too steep
                        // Up elevator is maxed out or beyond
                        recelevatoreffect = 1.0; // Prevent overflow
                    }
                } else {
                    if (recelevatoreffect > 0) { // Get here if We have not yet fully relaxed our elevators to prevent excess climb angle
                        recelevatoreffect -= (0.25 / ((float)dt)); // Diminish up elevators a bit
                    } else { // Get here if up elevators are minimized or a bit too low
                        recelevatoreffect = 0.0; // Assert neutral elevators
                    }
                }
            } else { // Get here if we need to descend to reach altitude goal.
                if (gamma > 120) {
                    if (recelevatoreffect > -1.0) {
                        // Wings level,
                        // Need to descend,
                        // Descent angle is not too steep,
                        // Down elevator not yet working hard to help us descend
                        recelevatoreffect -= (0.25 / ((float)dt)); // A tad more down elevator
                    } else {
                        recelevatoreffect = -1.0;
                    }
                } else {
                    if (recelevatoreffect < 1.0) {
                        // Wingslevel
                        // Need to descend,
                        // Descent angle is dangerously steep,
                        // Up elevator is not yet working hard to diminish our descent
                        recelevatoreffect += (0.25 / ((float)dt)); // A tad more up elevator
                    } else {
                        recelevatoreffect = 1.0; // Don't let it get too high.
                    }
                }
            }
        }

        //
        // Restore straight and level flight and throttle up
        //
        if (manoeverstate == 203) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Spending too much time here. Set up for the next state:
                NextManoeverStateDuration = 4000;
                manoeverstate = 204; // Try to roll clockwise to 90 degrees
            }
            // Keep throttle up:
            recthrust = 1.0;
            // Roll Level:
            if ((fabs)(theta) > 10) {
                // Get here if wings NOT rolled level.
                rolleffect = 1; // Keep rolling while wings not level
            } else {
                // Wings are rolled more-or-less level. Go tonext state.
                rolleffect = 0; // Stop rolling because wings are more-or-less level
            }
            // Bring and keep nose to straight-and-level. 192 degrees is a nice
            // climb-rate compromise because our wings might not be rolled
            // completely level, and the constant up/down adjustments cost climb
            // energy.
            if (gamma < 192) { // Get here if nose is not pointed slightly upward
                // Gradually adjust elevator pressure to 1.0:
                if (recelevatoreffect < 1.0) {
                    recelevatoreffect += (0.25 / ((float)dt));
                }
                if (recelevatoreffect > 1.0) {
                    elevatoreffect = 1.0;
                }
                // Get here after adjusting elevator pressure toward 1.0
            } else {
                if (recelevatoreffect > -1.0) {
                    recelevatoreffect -= (0.25 / ((float)dt));
                }
                if (recelevatoreffect < -1.0) {
                    elevatoreffect = -1.0;
                }
            }
        }

        //
        // Get here flying straight and level. We have 4 seconds to roll our
        // wings CCW to 90 degrees in preparation for a flat left turn.
        //
        if (manoeverstate == 204) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Out of time. Set up for the next state:
                manoeverstate = 205;
                NextManoeverStateDuration = 12000;
            }
            if (theta < 90) { // Get here if we haven't rolled to 90 degrees yet
                recrolleffect += (0.25 / ((float)dt)); // Increase CCW aileron roll force
            } else { // Get here after rolling CCW on our side
                recrolleffect = 0; // Stop rolling
                manoeverstate = 205;
                NextManoeverStateDuration = 10000;
            }
        }

        //
        // Get here rolled on our left side. Now pull back on joystick
        // to assert up elevator pressure so we go into a flat turn for
        // a maximum of 10 seconds:
        //
        if (manoeverstate == 205) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 206;
                NextManoeverStateDuration = 3000;
            }
            if (recelevatoreffect < 0.8) {
                recelevatoreffect += (0.25 / ((float)dt)); // Increase elevator pressure a bit
            } else {
                recelevatoreffect = 0.5; // Prevent too much elevator pressure.
            }
            if (myrandom(4096) > 4093) { // For the sake of variety, sometimes we branch back to state 201...
                ManoeverStateTargetAltitude = 85;
                NextManoeverStateDuration = 8000;
                manoeverstate = 201;
            }
        }

        //
        // Get here rolled on our side, just coming out of a flat turn.
        // Roll back into straight and level flight: We have 3 seconds.
        //
        if (manoeverstate == 206) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 207;
                NextManoeverStateDuration = 2000;
            }
            if ((fabs)(theta) > 5) { // Get here if we haven't completed rolling back flat yet
                recrolleffect -= (0.25 / ((float)dt)); // Decrease elevator pressure a bit
            } else { // Get here after we've rolled back flat
                recrolleffect = 0;
                manoeverstate = 207;
            }
        }

        //
        // Continue straight and level. Accelerate. Exit pulling nose-high,
        // wings level
        //
        if (manoeverstate == 207) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                if (recelevatoreffect > 0.25) {
                    // Timer has expired AND elevator is pulling us upward
                    // Go to next manoeverstate:
                    manoeverstate = 208; // Restart the bot state machine
                }
                NextManoeverStateDuration = 3000;
            }
            // Keep throttle up:
            recthrust = 1.0;
            // Roll Level:
            if ((fabs)(theta) > 10) {
                // Get here if wings NOT rolled level.
                rolleffect = 1; // Keep rolling while wings not level
            } else {
                // Wings are rolled more-or-less level.
                rolleffect = 0; // Stop rolling because wings are more-or-less level
            }
            // Bring and keep nose to straight-and-level. 192 degrees is a nice
            // climb-rate compromise because our wings might not be rolled
            // completely level, and the constant up/down adjustments cost climb
            // energy.
            if (gamma < 192) { // Get here if nose is not pointed slightly upward
                // Gradually adjust elevator pressure to 1.0:
                if (recelevatoreffect < 1.0) {
                    recelevatoreffect += (0.25 / ((float)dt));
                }
                if (recelevatoreffect > 1.0) {
                    elevatoreffect = 1.0;
                }
                // Get here after adjusting elevator pressure toward 1.0
            } else {
                if (recelevatoreffect > -1.0) {
                    recelevatoreffect -= (0.25 / ((float)dt));
                }
                if (recelevatoreffect < -1.0) {
                    elevatoreffect = -1.0;
                }
            }
        }

        //
        // Roll Clockwise to -90 degrees in preparation for a hard
        // left turn:
        //
        if (manoeverstate == 208) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 209;
                NextManoeverStateDuration = 1000;
            }
            // Relax elevator pressure:
            recelevatoreffect = 0;
            if (theta > -90) { // Get here if we haven't rolled to -90 degrees yet
                recrolleffect -= (0.25 / ((float)dt)); // Increase CW aileron roll force
            } else { // Get here after rolling CW on our side
                recrolleffect = 0; // Stop rolling
                manoeverstate = 209;
                NextManoeverStateDuration = 11000;
            }
        }

        //
        // Get here rolled on right side (theta about -90 degrees).
        //
        // Pull back on joystick for up elevator pressure resulting
        // in a flat turn to the right:
        //
        if (manoeverstate == 209)
            //
            // Commence with the usual boilerplate:
            //
        {
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 210;
                NextManoeverStateDuration = 5000;
            }
            if (recelevatoreffect < 0.8) {
                recelevatoreffect += (0.25 / ((float)dt)); // Increase elevator pressure a bit
            } else {
                recelevatoreffect = 0.5; // Prevent too much elevator pressure.
            }
        }

        //
        // Resume straight-and level flight
        //
        if (manoeverstate == 210) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 211;
                NextManoeverStateDuration = 1000;
            }
            // Keep throttle up:
            recthrust = 1.0;
            // Roll Level:
            if ((fabs)(theta) > 10) {
                // Get here if wings NOT rolled level.
                rolleffect = 1; // Keep rolling while wings not level
            } else {
                // Wings are rolled more-or-less level.
                rolleffect = 0; // Stop rolling because wings are more-or-less level
            }
            // Bring and keep nose to straight-and-level. 192 degrees is a nice
            // climb-rate compromise because our wings might not be rolled
            // completely level, and the constant up/down adjustments cost climb
            // energy.
            if (gamma < 192) { // Get here if nose is not pointed slightly upward
                // Gradually adjust elevator pressure to 1.0:
                if (recelevatoreffect < 1.0) {
                    recelevatoreffect += (0.25 / ((float)dt));
                }
                if (recelevatoreffect > 1.0) {
                    elevatoreffect = 1.0;
                }
                // Get here after adjusting elevator pressure toward 1.0
            } else {
                if (recelevatoreffect > -1.0) {
                    recelevatoreffect -= (0.25 / ((float)dt));
                }
                if (recelevatoreffect < -1.0) {
                    elevatoreffect = -1.0;
                }
            }
        }

        //
        // Check to see if we are dangerously low and if so, branch back to
        // manoeverstate "10": Otherwise continue with manoeverstate 212:
        //
        if (manoeverstate == 211) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 212;
                NextManoeverStateDuration = 1000;
            }
            // Check to see if we are below minimum safe altitude
            if (fabs(tl->y - TerrainHeightBelowMe) < 75) {
                NextManoeverStateDuration = 9000;
                manoeverstate = 10; // Branch to state "10" which will stabilize and climb us...
            }
        }

        //
        // Do Nothing. (This manoeverstate handler has not yet been coded
        // beyond its standardized, skeletal form.)
        //
        if (manoeverstate == 212) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 213;
                NextManoeverStateDuration = 1000;
            }
        }

        //
        // Do Nothing. (This manoeverstate handler has not yet been coded
        // beyond its standardized, skeletal form.)
        //
        if (manoeverstate == 213) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 214;
                NextManoeverStateDuration = 1000;
            }
        }

        //
        // Do Nothing. (This manoeverstate handler has not yet been coded
        // beyond its standardized, skeletal form.)
        //
        if (manoeverstate == 214) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 215;
                NextManoeverStateDuration = 1000;
            }
        }

        //
        // Do Nothing. (This manoeverstate handler has not yet been coded
        // beyond its standardized, skeletal form.)
        //
        if (manoeverstate == 215) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 216;
                NextManoeverStateDuration = 1000;
            }
        }

        //
        // Do Nothing. (This manoeverstate handler has not yet been coded
        // beyond its standardized, skeletal form.)
        //
        if (manoeverstate == 216) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 217;
                NextManoeverStateDuration = 1000;
            }
        }

        //
        // Do Nothing. (This manoeverstate handler has not yet been coded
        // beyond its standardized, skeletal form.)
        //
        if (manoeverstate == 217) {
            //
            // Commence with the usual boilerplate:
            //
            if (NextManoeverStateDuration != 0) { // Initialize ManoeverStateTimer:
                ManoeverStateTimer = NextManoeverStateDuration;
                NextManoeverStateDuration = 0;
            }
            // Check for timer expiration
            ManoeverStateTimer -= dt;
            if (ManoeverStateTimer < 0) { // Set up for the next state:
                manoeverstate = 0;
                NextManoeverStateDuration = 1000;
            }
        }
    }
}

void AIObj::aiinit() {
    int i;
    acttype = 0;
    dualshot = false;
    intelligence = 100;
    aggressivity = 100;
    precision = 100;
    Durability = 0.01F;
    ai = true;
    active = true;
    draw = true;
    target = NULL;
    dtheta = 0;
    dgamma = 0;
    id = MISSILE1;
    impact = 30;
    manoevertheta = 0;
    manoeverheight = 0;
    manoeverthrust = 0;
    idle = 0;
    smokettl = 0;
    firecannonttl = 0;
    firemissilettl = 0;
    fireflarettl = 0;
    firechaffttl = 0;
    flares = 0;
    aw = 0;
    source = NULL;
    points = 0;
    elevatoreffect = 0;
    ruddereffect = 0;
    gamma = 180;
    recgamma = 180;
    dgamma = 0;
    theta = 0;
    maxgamma = 70;
    maxtheta = 90;
    missiletype = 0;
    autofire = false;
    ttl = -1;
    ttf = 30 * timestep;
    for (i = 0; i < missiletypes; i++) {
        missiles[i] = 0;
    }
    for (i = 0; i < missileracks; i++) {
        missilerack[i] = -1;
        missilerackn[i] = 0;
    }
    bomber = 0;
    timer = 0;
    ammo = -1;
    manoeverstate = 11;
    rectheta = 90;
}

AIObj::AIObj() {
    o = NULL;
    zoom = 1.0;
    aiinit();
    smoke = new CSmoke(0);
}

AIObj::~AIObj() {
    delete smoke;
}

AIObj::AIObj(Space* space2, CModel* o2, float zoom2) {
    this->space = space2;
    o = o2;
    zoom = zoom2;
    aiinit();
    smoke = new CSmoke(0);
    space->addObject(this);
}

void AIObj::decreaseMissile(int id) {
    char buf[STDSIZE];
    int i;
    id -= MISSILE1;
    if (id < 0 || id >= missiletypes) {
        sprintf(buf, "Wrong missile ID in %s, line %d", __FILE__, __LINE__);
        display(buf, LOG_ERROR);
    }
    missiles[id]--;
    int ptrrack = 0, maxrack = 0;
    for (i = 0; i < missileracks; i++)
        if (missilerack[i] == id)
            if (missilerackn[i] > maxrack) {
                ptrrack = i;
                maxrack = missilerackn[i];
            }
    if (maxrack > 0) {
        missilerackn[ptrrack]--;
        refscale[ptrrack * 3 + 2 - missilerackn[ptrrack]] = 0;
    }
}

void AIObj::fireCannon(DynamicObj* MachineGunBullet, float phi) {
    if (firecannonttl > 0) {
        return;
    }

    if (ammo == 0) {
        return;
    }
    ammo--;
    MachineGunBullet->zoom = 0.05; // Bullets look better when visually scaled to 0.05.
    MachineGunBullet->thrust = 0;
    MachineGunBullet->recthrust = MachineGunBullet->thrust;
    MachineGunBullet->manoeverability = 0.0;
    MachineGunBullet->maxthrust = 0;
    if (target != NULL && ai) {
        if (target->active) {
            // exact calculation to hit enemy (non-static turret!)
            if (id >= FIGHTER1 && id <= FIGHTER2) {
                MachineGunBullet->gamma = gamma;
            } else {
                MachineGunBullet->gamma = 180.0 + atan((target->tl->y - tl->y) / distance(target)) * 180.0 / pitab;
            }
        }
    } else {
        MachineGunBullet->gamma = gamma;
    }
    MachineGunBullet->party = party;
    MachineGunBullet->ttl = 80 * timestep;
    MachineGunBullet->Durability = 1;
    MachineGunBullet->immunity = (int)(zoom * 9) * timestep;
    MachineGunBullet->source = this;
    MachineGunBullet->phi = phi;
    MachineGunBullet->theta = theta;
    initValues(MachineGunBullet, phi);
    float fac = 0.7F;
    MachineGunBullet->forcex += COS(MachineGunBullet->gamma) * SIN(MachineGunBullet->phi) * fac;
    MachineGunBullet->forcey -= SIN(MachineGunBullet->gamma) * fac;
    MachineGunBullet->forcez += COS(MachineGunBullet->gamma) * COS(MachineGunBullet->phi) * fac;
    MachineGunBullet->activate();
    firecannonttl += 45;
    if (day) {
        if (dualshot) {
            MachineGunBullet->o = &model_cannon1b;
        } else {
            MachineGunBullet->o = &model_cannon1;
        }
    } else {
        if (dualshot) {
            MachineGunBullet->o = &model_cannon2b;
        } else {
            MachineGunBullet->o = &model_cannon2;
        }
    }
}

void AIObj::fireCannon(DynamicObj** MachineGunBullet, float phi) {
    int i;
    if (firecannonttl > 0) {
        return;
    }
    if (ammo == 0) {
        return;
    }
    for (i = 0; i < maxMachineGunBullet; i++) {
        if (!MachineGunBullet[i]->active) {
            break;
        }
    }
    if (i < maxMachineGunBullet) {
        fireCannon(MachineGunBullet[i], phi);
    }
}

void AIObj::fireCannon(DynamicObj** MachineGunBullet) {
    if (firecannonttl > 0) {
        return;
    }
    if (ammo == 0) {
        return;
    }
    fireCannon(MachineGunBullet, phi);
}

bool AIObj::fireChaff(DynamicObj** chaff, AIObj** missile) {
    int i, i2;
    if (chaffs <= 0) {
        return false;
    }
    if (firechaffttl > 0) {
        return false;
    }
    for (i = 0; i < maxchaff; i++) {
        if (chaff[i]->ttl <= 0) {
            break;
        }
    }
    if (i < maxchaff) {
        fireChaff2(chaff[i]);
        chaffs--;
        firechaffttl = 8 * timestep;
        for (i2 = 0; i2 < maxmissile; i2++) {
            if (missile[i2]->ttl > 0) {
                if (missile[i2]->id > MISSILE_AIR3) // only radar seeking missiles
                    if (missile[i2]->target == this)   // only change target if angle is good
                    {
                        bool hit = false;
                        if (myrandom((int)(fabs(elevatoreffect) * 90 + 20)) > 50) {
                            hit = true;
                        }
                        if (hit) {
                            if (DebugLevel == LOG_ALL) {
                                display((char*)"AIObj::fireChaff() Missile to chaff", LOG_ALL);
                            }

                            missile[i2]->target = chaff[i];
                        }
                    }
            }
        }
        return true;
    }
    return false;
}

void AIObj::fireChaff2(DynamicObj* chaff) {
    char buf[STDSIZE];
    if (debug == LOG_ALL) {
        sprintf(buf, "Chaff: party=%d", party);
        display(buf, LOG_ALL);
    }
    chaff->dinit();
    chaff->thrust = 0;
    chaff->realspeed = 0;
    chaff->recthrust = 0;
    chaff->manoeverability = 0.0;
    chaff->maxthrust = 1.0;
    chaff->gamma = 0;
    chaff->party = party;
    chaff->ttl = 80 * timestep;
    chaff->Durability = 1;
    chaff->immunity = (int)(zoom * 12) * timestep;
    chaff->source = this;
    chaff->phi = phi;
    chaff->id = CHAFF1;
    initValues(chaff, phi);
    chaff->activate();
    chaff->explode = 0;
    chaff->zoom = 0.12F;
}

bool AIObj::fireFlare(DynamicObj** flare, AIObj** missile) {
    int i, i2;
    if (flares <= 0) {
        return false;
    }
    if (fireflarettl > 0) {
        return false;
    }
    for (i = 0; i < maxflare; i++) {
        if (flare[i]->ttl <= 0) {
            break;
        }
    }
    if (i < maxflare) {
        fireFlare2(flare[i]);
        flares--;
        fireflarettl = 8 * timestep;
        for (i2 = 0; i2 < maxmissile; i2++) {
            if (missile[i2]->ttl > 0) {
                if (missile[i2]->id >= MISSILE_AIR2 && missile[i2]->id <= MISSILE_AIR3) // only heat seeking missiles
                    if (missile[i2]->target == this)   // only change target if angle is good
                    {
                        bool hit = false;
                        if (myrandom((int)(fabs(elevatoreffect) * 90 + 20)) > 50) {
                            hit = true;
                        }
                        if (hit) {
                            if (DebugLevel == LOG_ALL) {
                                display((char*)"AIObj::fireFlare() Missile to flare", LOG_ALL);
                            }
                            missile[i2]->target = flare[i];
                        }
                    }
            }
        }
        return true;
    }
    return false;
}

void AIObj::fireFlare2(DynamicObj* flare) {
    char buf[STDSIZE];
    if (DebugLevel == LOG_ALL) {
        sprintf(buf, "Flare: party=%d", party);
        display(buf, DebugLevel);
    }
    flare->dinit();
    flare->thrust = 0;
    flare->realspeed = 0;
    flare->recthrust = 0;
    flare->manoeverability = 0.0;
    flare->maxthrust = 1.0;
    flare->gamma = 0;
    flare->party = party;
    flare->ttl = 80 * timestep;
    flare->Durability = 1;
    flare->immunity = (int)(zoom * 12) * timestep;
    flare->source = this;
    flare->phi = phi;
    flare->id = FLARE1;
    initValues(flare, phi);
    flare->activate();
    flare->explode = 0;
}

bool AIObj::fireMissile(int id, AIObj** missile, AIObj* target) {
    display((char*)"AIObj::fireMissile (int id, AIObj **missile, AIObj *target)", LOG_MOST);
    int i;
    if (!haveMissile(id)) {
        return false;
        display((char*)"AIObj::fireMissile (int id, AIObj **missile, AIObj *target) returned false due to !haveMissile(id).", LOG_MOST);
    }
    if (ttf > 0) {
        return false;
        display((char*)"AIObj::fireMissile (int id, AIObj **missile, AIObj *target) returned false due to ttf>0.", LOG_MOST);
    }
    for (i = 0; i < maxmissile; i++) {
        if (missile[i]->ttl <= 0) {
            display((char*)"AIObj::fireMissile (int id, AIObj **missile, AIObj *target) breaking out due to missile [i]->ttl <= 0.", LOG_MOST);
            break;
        }
    }
    if (i < maxmissile) {
        fireMissile2(id, missile[i], target);
        decreaseMissile(id);
        firemissilettl = 20 * timestep;
        display((char*)"AIObj::fireMissile (int id, AIObj **missile, AIObj *target) returned true as expected.", LOG_MOST);
        return true;
    }
    return false;
    display((char*)"AIObj::fireMissile (int id, AIObj **missile, AIObj *target) returned false by default.", LOG_MOST);
}

bool AIObj::fireMissile(AIObj** missile, AIObj* target) {
    display((char*)"AIObj::fireMissile (AIObj **missile, AIObj *target)", LOG_MOST);
    if (ttf > 0) {
        return false;
    }
    return fireMissile(missiletype + MISSILE1, missile, (AIObj*)target);
}

bool AIObj::fireMissile(int id, AIObj** missile) {
    display((char*)"AIObj::fireMissile (int id, AIObj **missile)", LOG_MOST);
    if (ttf > 0) {
        display((char*)"AIObj::fireMissile (int id, AIObj **missile) returned false due to ttf >0.", LOG_MOST);
        return false;
    }
    display((char*)"AIObj::fireMissile (int id, AIObj **missile) returning true as expected.", LOG_MOST);
    return fireMissile(id, missile, (AIObj*)target);
}

bool AIObj::fireMissile(AIObj** missile) {
    display((char*)"AIObj::fireMissile (AIObj **missile)", LOG_MOST);
    if (ttf > 0) {
        return false;
    }
    return fireMissile(missiletype + MISSILE1, missile);
}
void AIObj::fireMissile2(int id, AIObj* missile, AIObj* target) { // Get here when pilot launches an air-to-ground rocket
    sprintf(DebugBuf, "Rocket: party=%d, id=%d", party, id);
    display(DebugBuf, LOG_MOST);
    ttf = 50 * timestep;
    missile->dinit();
    missile->aiinit();
    missile->newinit(id, party, 0);
    initValues(missile, phi);
    missile->id = id;
    missile->explode = 0;
    missile->thrust = thrust + 0.001;
    missile->recthrust = missile->maxthrust;
    missile->gamma = gamma;
    missile->target = target;
    missile->recgamma = gamma;
    missile->Durability = 1;
    missile->party = party;
    missile->immunity = (45 + (int)(zoom * 6.0)) * timestep;
    missile->dtheta = 0;
    missile->dgamma = 0;
    missile->source = this;
    if (missile->id == MISSILE_DF1) {
        display((char*)"AIObj::fireMissile2() dropped MISSILE_DF1", LOG_MOST);
        float RocketLaunchGammaDelta = 0.0;
        RocketLaunchGammaDelta = fabs(fplayer->gamma - 180) / -2.7;
        RocketLaunchGammaDelta -= 5.0;
        missile->gamma = fplayer->gamma + RocketLaunchGammaDelta;
        missile->tl->x = fplayer->tl->x;
        missile->tl->z = fplayer->tl->z;
        missile->tl->y = fplayer->tl->y - 0.01; // This is the "drop distance" that rockets fall down before their motors ignite.
        missile->realspeed = fplayer->realspeed * 1.1;
        missile->immunity = (60 + (int)(zoom * 6.0)) * timestep; // Avoid blowing ourselves up
        sprintf(DebugBuf, "AIObj::fireMissile2() (Rocket). fplayer->gamma =%f", fplayer->gamma);
        display(DebugBuf, LOG_MOST);
        sprintf(DebugBuf, "AIObj::fireMissile2() (Rocket). RocketLaunchGammaDelta =%f", RocketLaunchGammaDelta);
        display(DebugBuf, LOG_MOST);
        sprintf(DebugBuf, "AIObj::fireMissile2() (Rocket). missile->gamma =%f", missile->gamma);
        display(DebugBuf, LOG_MOST);
    }
    if (missile->id == BOMB01) {
        display((char*)"AIObj::fireMissile2() dropped BOMB02", LOG_MOST);
        missile->BombReleaseVelocity = fplayer->realspeed; // Bomb gets player's velocity when dropped
        missile->immunity = (60 + (int)(zoom * 6.0)) * timestep; // Avoid blowing ourselves up
        missile->gamma -= 10;
        missile->recgamma -= 10;
        if (missile->gamma < 0) {
            missile->gamma = 0;
            missile->recgamma = 0;
        }
    }
    if (missile->id > BOMB01 && missile->id < FIGHTER1) {
        MissileFired = true;
    }
    missile->activate();
    if (id >= FIGHTER1 && id <= FIGHTER2) {
        missile->manoeverheight = 30 * timestep;
        missile->recheight = missile->tl->y - l->getHeight(missile->tl->x, missile->tl->z) - 4;
    }
}

bool AIObj::fireMissileAir(AIObj** missile, AIObj* target) {
    if (ttf > 0) {
        return false;
    }
    if (target->id >= MOVING_GROUND) {
        return false;
    }
    if (haveMissile(MISSILE_AIR3)) {
        return fireMissile(MISSILE_AIR3, missile, (AIObj*)target);
    } else if (haveMissile(MISSILE_AIR2)) {
        return fireMissile(MISSILE_AIR2, missile, (AIObj*)target);
    } else if (haveMissile(BOMB01)) {
        return fireMissile(BOMB01, missile, (AIObj*)target);
    }
    return false;
}

bool AIObj::fireMissileAirFF(AIObj** missile, AIObj* target) {
    if (ttf > 0) {
        return false;
    }
    if (target->id >= MOVING_GROUND) {
        return false;
    }
    if (haveMissile(MISSILE_FF2)) {
        return fireMissile(MISSILE_FF2, missile, (AIObj*)target);
    } else if (haveMissile(MISSILE_FF1)) {
        return fireMissile(MISSILE_FF1, missile, (AIObj*)target);
    }
    return false;
}

bool AIObj::fireMissileGround(AIObj** missile) {
    if (ttf > 0) {
        return false;
    }
    if (target->id < MOVING_GROUND) {
        return false;
    }
    if (haveMissile(MISSILE_GROUND2)) {
        return fireMissile(MISSILE_GROUND2, missile, (AIObj*)target);
    } else if (haveMissile(MISSILE_GROUND1)) {
        return fireMissile(MISSILE_GROUND1, missile, (AIObj*)target);
    }
    return false;
}

int AIObj::firstMissile() {
    int i = 0;
    while (!missiles[i]) {
        i++;
        if (i >= missiletypes) {
            return 0;
        }
    }

    ttf = 50 * timestep;
    return i;
}

bool AIObj::haveMissile(int id) {
    char buf[STDSIZE];
    id -= MISSILE1;
    if (id < 0 || id >= missiletypes) {
        sprintf(buf, "Wrong missile ID in %s, line %d", __FILE__, __LINE__);
        display(buf, LOG_ERROR);
    }
    if (missiles[id] > 0) {
        return true;
    }
    return false;
}

bool AIObj::haveMissile() // due to missiletype
{
    if (missiles[missiletype] > 0) {
        return true;
    }
    return false;
}

void AIObj::initValues(DynamicObj* dobj, float phi) {
    float fac = zoom / 8;
    if (dobj->id == FLARE1 || dobj->id == CHAFF1) {
        fac = -fac;
    }
    // use the exact polar coordinates because of gamma and theta
    float cgamma = gamma;
    dobj->tl->x = tl->x + COS(cgamma) * SIN(phi) * fac;
    dobj->tl->y = tl->y - SIN(cgamma) * fac;
    if ((id >= FLAK1 && id <= FLAK2) || (id >= TANK1 && id <= TANK2)) {
        dobj->tl->y += fac;
    }
    dobj->tl->z = tl->z + COS(cgamma) * COS(phi) * fac;
    dobj->phi = phi;
    dobj->rectheta = dobj->theta;
    dobj->forcex = forcex;
    dobj->forcey = forcey;
    dobj->forcez = forcez;
    dobj->rot->setAngles((short)(90 + dobj->gamma - 180), (short)dobj->theta + 180, (short)-dobj->phi);
}

void AIObj::missileCount() {
    if (id < FIGHTER1 || id > FIGHTER2) {
        return;
    }
    int i;
    for (i = 0; i < missiletypes; i++) {
        missiles[i] = 0;
    }
    for (i = 0; i < missileracks; i++) {
        if (missilerackn[i] > 0) {
            missiles[missilerack[i]] += missilerackn[i];
        }
    }
}

void AIObj::newinit(int id, int party, int intelligence, int precision, int aggressivity) {
    int i;
    ai = true;
    this->id = id;
    this->party = party;
    manoeverstate = 2;
    activate();
    for (i = 0; i < missileracks; i++) {
        missilerackn[i] = 0;
    }
    ammo = -1;
    bomber = 0;
    dualshot = false;
    //
    // Adjust the size of the "hit bubble" around aircraft, tanks,
    // and etc. for people with poor eyesight or otherwise requesting
    // enhanced video handling if they are also lacking a real
    // joystick:
    //
    float cubefac;  // Hit bubble size multiplier for aircraft
    float cubefac1; // Hit bubble size multiplier for tanks, rockets, etc.
    if ((NetworkMode & 128) && (NetworkMode & 32)) { // Get here if configured for enhanced video and console game controller
        // Expanded hit bubble multiplier
        cubefac = 0.9F; // aircraft
        cubefac1 = 0.9F; // tanks, rockets, etc.
    } else { // Normal hit bubble multiplier
        cubefac = 0.6F; // aircraft
        cubefac1 = 0.7F; // tanks, rockets, etc.
    }
    float missilethrustbase = 6.5F;
    o = getModel(id);
    o->cubex = zoom;
    o->cubey = zoom;
    o->cubez = zoom;
    if (id == STATIC_AIRFIELD00) {
        o->cubex *= 90.0;
        o->cubey *= 4.0;
        o->cubez *= 28.0;
        maxDurability = AIRFIELDMAXDURABILITY;
        Durability = AIRFIELDMAXDURABILITY;
    }
    if (id == CANNON1) {
        statLethality = 2;
        impact = 2;
    }
    if (id == STATIC_RADARREFLECTOR) {
        statLethality = 0;
        impact = 00;
        maxDurability = 65000;
        Durability = 65000;
        o->cubex *= 5.0;
        o->cubey *= 1.0;
        o->cubez *= 5.0;
    }
    if (id == FIGHTER_P38L) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.68;
        RollRate = 0.70;
        manoeverability = 0.1685;
        maxDurability = 510;
        zoom = 0.39;
        maxtheta = 90.0;
        maxgamma = 28.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.0;
        ammo = 2450;
        impact = 1000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 100.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 4000;
        FlapsLevelElevatorEffect4 = 11000;
        SpeedBrakePower = 1.01;
        MaxFullPowerAltRatio = 0.68;
        inertia = 3.5;
        deadweight = 0.13;
        if (difficulty <= 3) {
            CompressibilitySpeed = 0.31; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        } else {
            CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        }
        CompressibilitySpeedWithSpeedBrakes = 0.43; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.369565217391;
        DiveSpeedLimit1 = 0.42; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.504; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 0.0;
    }
    if (id == FIGHTER_FIATG55) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.58;
        RollRate = 0.65;
        manoeverability = 0.1541;
        maxDurability = 420;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 23.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 9.6;
        ammo = 1600;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.4;
        deadweight = 0.13;
        CompressibilitySpeed = 0.34; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.34; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.371; // Faster than begins to regulate overspeed. 0.36 ~= 414 MPH
        DiveSpeedLimit1 = 0.38; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.43; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.140;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_A6M2) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.56;
        RollRate = 0.50;
        manoeverability = 0.1987;
        maxDurability = 210;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 22.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 3.8;
        ammo = 1600;
        impact = 300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 2400;
        FlapsLevelElevatorEffect2 = 2400;
        FlapsLevelElevatorEffect3 = 2400;
        FlapsLevelElevatorEffect4 = 2400;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.51;
        inertia = 2.0;
        deadweight = 0.07;
        CompressibilitySpeed = 0.290; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.290; // Replaces above setting when SpeedBrakes are active.
        DiveSpeedLimit1 = 0.290; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.370; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.110;
        ServiceCeilingAltitude = 1500;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 1.0;
    }
    if (id == FIGHTER_KI43) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.75;
        RollRate = 0.50;
        manoeverability = 0.2000;
        maxDurability = 180;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 29;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 1.860;
        ammo = 1600;
        impact = 280;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 2400;
        FlapsLevelElevatorEffect2 = 2400;
        FlapsLevelElevatorEffect3 = 2400;
        FlapsLevelElevatorEffect4 = 2400;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.51;
        inertia = 1.6712;
        deadweight = 0.07;
        CompressibilitySpeed = 0.20; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.20; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.291501976285; // Ki43: Faster than begins to regulate overspeed. 0.291501976285 ~= 295 MPH
        DiveSpeedLimit1 = 0.23; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.31; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.110;
        ServiceCeilingAltitude = 1500;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 1.0;
    }
    if (id == FIGHTER_IL16) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.4;
        RollRate = 0.50;
        manoeverability = 0.2016;
        maxDurability = 300;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 21;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.6;
        ammo = 1600;
        impact = 300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 2400;
        FlapsLevelElevatorEffect2 = 2400;
        FlapsLevelElevatorEffect3 = 2400;
        FlapsLevelElevatorEffect4 = 2400;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.51;
        inertia = 2.2;
        deadweight = 0.07;
        CompressibilitySpeed = 0.21;
        CompressibilitySpeedWithSpeedBrakes = 0.21; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.2421;
        DiveSpeedLimit1 = 0.24; // Faster than this induces extra turbulence. IL16: 263
        DiveSpeedStructuralLimit = 0.3063; // Faster than this will induce severe airframe damage. IL16: 310MPH
        WepCapable = false;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1500;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_F4F) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.48;
        RollRate = 0.55;
        manoeverability = 0.1872;
        maxDurability = 480;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 19.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.1;
        ammo = 1600;
        impact = 800;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.7;
        deadweight = 0.13;
        CompressibilitySpeed = 0.27; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.27; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.287549407115;
        DiveSpeedLimit1 = 0.3010; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.40; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_F6F) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.842;
        RollRate = 0.57;
        manoeverability = 0.1857;
        maxDurability = 540;
        zoom = 0.36;
        maxtheta = 90.0;
        maxgamma = 27;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.2;
        ammo = 1600;
        impact = 800;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.7;
        deadweight = 0.13;
        CompressibilitySpeed = 0.31; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.31; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.3468;
        DiveSpeedLimit1 = 0.35; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.44; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_F4U) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.90;
        RollRate = 0.70;
        manoeverability = 0.1332;
        maxDurability = 550;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 26.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.2;
        ammo = 1600;
        impact = 750;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 109.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.67;
        inertia = 2.557;
        deadweight = 0.13;
        CompressibilitySpeed = 0.31255; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.31; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.386363636364;
        DiveSpeedLimit1 = 0.379; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.49; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.135;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.3;
    }
    if (id == FIGHTER_P47D) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.84;
        RollRate = 0.72;
        manoeverability = 0.1267;
        maxDurability = 1200;
        zoom = 0.36;
        maxtheta = 90.0;
        maxgamma = 20;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.8;
        ammo = 1600;
        impact = 1000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.685;
        inertia = 3.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.35; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.35; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.388339920949;
        DiveSpeedLimit1 = 0.43; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.55; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.135;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_FW190) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.6;
        RollRate = 0.72;
        manoeverability = 0.1350;
        maxDurability = 570;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 22;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 9.55;
        ammo = 1600;
        impact = 750;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 108.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.67;
        inertia = 2.55;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.363636363636;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.45; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_P51D) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.67;
        RollRate = 0.55;
        manoeverability = 0.1440;
        maxDurability = 510;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 20;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.2;
        ammo = 1600;
        impact = 750;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.67;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.33; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.33; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.397233201581;
        DiveSpeedLimit1 = 0.3873; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.45; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.135;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_HAWK) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 3;
        DefensiveLethality = 0;
        maxthrust = 3.5;
        RollRate = 0.70;
        manoeverability = 0.1440;
        maxDurability = 510;
        zoom = 0.39;
        maxtheta = 90.0;
        maxgamma = 28;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 12.0;
        ammo = 2450;
        impact = 1000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.5;
        MaxFullPowerAltRatio = 0.68;
        inertia = 3.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.56; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.56; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.6916; // Faster than begins to regulate overspeed. 0.36 ~= 414 MPH
        DiveSpeedLimit1 = 0.71; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.88; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.165;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 0.0;
    } else if (id == BOMBER_B17) {
        o->cubex = zoom * cubefac * 2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 2;
        HistoricPeriod = 1;
        DefensiveLethality = 39;
        maxthrust = 1.70;
        RollRate = 0.28;
        manoeverability = 0.1125;
        maxDurability = 8400;
        zoom = 1.0;
        maxtheta = 90.0;
        maxgamma = 22.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.0;
        ammo = 2450;
        impact = 5000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 2400;
        FlapsLevelElevatorEffect4 = 2400;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = .69;
        inertia = 4.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.25; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.249011857708;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.35; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.110;
        ServiceCeilingAltitude = 1360;
        FuelBurnRate = 0.5;
        TorqueMultiplier = -0.5;
    } else if (id == BOMBER_B24) {
        o->cubex = zoom * cubefac * 2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 2;
        HistoricPeriod = 2;
        DefensiveLethality = 30;
        maxthrust = 1.69;
        RollRate = 0.26;
        manoeverability = 0.1080;
        maxDurability = 7800;
        zoom = 1.0;
        maxtheta = 90.0;
        maxgamma = 22.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.0;
        ammo = 2450;
        impact = 4000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 2400;
        FlapsLevelElevatorEffect4 = 2400;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = .69;
        inertia = 4.2;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.25; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.247035573123;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.35; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1360;
        FuelBurnRate = 0.5;
        TorqueMultiplier = -0.5;
    } else if (id == FIGHTER_SPIT9) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.66;
        RollRate = 0.58;
        manoeverability = 0.1699;
        maxDurability = 420;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 27.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.33;
        ammo = 2450;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1700;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.35; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.35; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.370553359684;
        DiveSpeedLimit1 = 0.3806; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.46; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_ME109G) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.69;
        RollRate = 0.55;
        manoeverability = 0.1512;
        maxDurability = 390;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 26;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.0;
        ammo = 2450;
        impact = 500;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 1.8;
        deadweight = 0.13;
        CompressibilitySpeed = 0.28; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.28; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.353754940711;
        DiveSpeedLimit1 = 0.38; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.44; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 2.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_HURRICANE) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.54;
        RollRate = 0.50;
        manoeverability = 0.1863;
        maxDurability = 450;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 22.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.5;
        ammo = 1600;
        impact = 700;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 105.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.33; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.296442687747;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_P40) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.35;
        RollRate = 0.50;
        manoeverability = 0.1449;
        maxDurability = 480;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 14;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.24;
        ammo = 2450;
        impact = 700;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.8;
        deadweight = 0.13;
        CompressibilitySpeed = 0.29; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.29; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.3162055336;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.49; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_P39) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.64;
        RollRate = 0.55;
        manoeverability = 0.1418;
        maxDurability = 480;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 26;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 36.000000;
        ammo = 2450;
        impact = 700;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 103.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.48;
        inertia = 2.9;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.334980237154;
        DiveSpeedLimit1 = 0.38; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.45; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_YAK9) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.56;
        RollRate = 0.55;
        manoeverability = 0.1282;
        maxDurability = 375;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 26;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.2;
        ammo = 1600;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 1600;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.60;
        inertia = 2.4;
        deadweight = 0.13;
        CompressibilitySpeed = 0.28; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.28; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.369565217391;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    } else if (id == FIGHTER_N1K1) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.9;
        RollRate = 0.55;
        manoeverability = 0.1483;
        maxDurability = 450;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 29.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 3.64;
        ammo = 2450;
        impact = 700;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.26; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.26; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.363636363636;
        DiveSpeedLimit1 = 0.375; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.46; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 1.0;
    }
    if (id == BOMBER_JU87) {
        o->cubex = zoom * cubefac * 1.2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.2;
        HistoricPeriod = 1;
        DefensiveLethality = 6;
        maxthrust = 1.68;
        RollRate = 0.33;
        manoeverability = 0.1183;
        maxDurability = 2000;
        zoom = 0.4;
        maxtheta = 90.0;
        maxgamma = 14;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 3.2;
        ammo = 2450;
        impact = 1300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1770;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 3200;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 2.60;
        MaxFullPowerAltRatio = 0.48;
        inertia = 3.8904;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.25; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.212450592885; // Ju87: 0.212450592885=215MPH
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.34; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.110;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == BOMBER_G5M) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 1;
        DefensiveLethality = 10;
        maxthrust = 1.56;
        RollRate = 0.32;
        manoeverability = 0.1161;
        maxDurability = 601;
        zoom = 0.70;
        maxtheta = 90.0;
        maxgamma = 20;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.6;
        ammo = 2450;
        impact = 2500;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .160;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 4.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.17; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.17; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.22233201581;
        DiveSpeedLimit1 = 0.20; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.34; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == BOMBER_B25) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 1;
        DefensiveLethality = 12;
        maxthrust = 1.43;
        RollRate = 0.33;
        manoeverability = 0.1246;
        maxDurability = 2200;
        zoom = 0.70;
        maxtheta = 90.0;
        maxgamma = 18;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 56.64;
        ammo = 2450;
        impact = 2000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 4.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.21; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.21; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.227272727273;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.38; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1200;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == BOMBER_B26) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 2;
        DefensiveLethality = 12;
        maxthrust = 1.60;
        RollRate = 0.35;
        manoeverability = 0.1252;
        maxDurability = 1800;
        zoom = 0.70;
        maxtheta = 90.0;
        maxgamma = 22;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 22.82;
        ammo = 2450;
        impact = 2000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 4.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.24; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.24; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.255928853755;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.39; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1200;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == FIGHTER_LA5) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.74;
        RollRate = 0.60;
        manoeverability = 0.1433;
        maxDurability = 425;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 25.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 5.23;
        ammo = 2450;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1770;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.60;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.31; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.31; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.358695652174;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_LA7) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.77;
        RollRate = 0.62;
        manoeverability = 0.1400;
        maxDurability = 425;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 23.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 7.84;
        ammo = 2450;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1770;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.60;
        inertia = 2.40;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.366600790514;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.131;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_IL2) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 2;
        DefensiveLethality = 3;
        maxthrust = 1.45;
        RollRate = 0.40;
        manoeverability = 0.125;
        maxDurability = 3500;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 18;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.0;
        ammo = 1600;
        impact = 1300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 2400;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 2.10;
        MaxFullPowerAltRatio = 0.45;
        inertia = 2.7;
        deadweight = 0.13;
        CompressibilitySpeed = 0.210; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.210; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.21442687747;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.37; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.131;
        ServiceCeilingAltitude = 1280;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_MACCIC202) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.57;
        RollRate = 0.55;
        manoeverability = 0.1555;
        maxDurability = 410;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 26;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 1.8;
        ammo = 2450;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1700;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.29; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.29; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.328063241107;
        DiveSpeedLimit1 = 0.33; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == BOMBER_LANCASTER) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 1;
        DefensiveLethality = 7;
        maxthrust = 1.74;
        RollRate = 0.30;
        manoeverability = 0.0990;
        maxDurability = 6000;
        zoom = 1.0;
        maxtheta = 90.0;
        maxgamma = 13;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.0;
        ammo = 2450;
        impact = 5000;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .140;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 5.5;
        deadweight = 0.13;
        CompressibilitySpeed = 0.220; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.220; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.217391304348;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.37; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1200;
        FuelBurnRate = 0.5;
        TorqueMultiplier = -0.5;
    }
    if (id == BOMBER_MOSQUITOB) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.55;
        RollRate = 0.38;
        manoeverability = 0.1166;
        maxDurability = 1310;
        zoom = 0.70;
        maxtheta = 90.0;
        maxgamma = 20.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 32.0; // 4x20mm and 4x30cal, all in nose, forward-firing, fixed. Lethality bonus for optimal aiming.
        ammo = 2450;
        impact = 1700;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 108.0;
        ClipDistance = 0.03;
        FlapSpeed = .177;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 4.1;
        deadweight = 0.13;
        CompressibilitySpeed = 0.34; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.34; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.362;
        DiveSpeedLimit1 = 0.41; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.45; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == FIGHTER_TYPHOON) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.5;
        RollRate = 0.55;
        manoeverability = 0.1404;
        maxDurability = 610;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 18;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 9.600000;
        ammo = 2450;
        impact = 700;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1770;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.5;
        deadweight = 0.13;
        CompressibilitySpeed = 0.32; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.32; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.367588932806;
        DiveSpeedLimit1 = 0.39; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.44; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.135;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_YAK1) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.6;
        RollRate = 0.55;
        manoeverability = 0.1389;
        maxDurability = 370;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 23.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.2;
        ammo = 1600;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .177;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 1600;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.60;
        inertia = 2.1;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.324110671937;
        DiveSpeedLimit1 = 0.32; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = false;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == BOMBER_B29) {
        o->cubex = zoom * cubefac * 3;
        o->cubey = zoom * cubefac * 2;
        o->cubez = zoom * cubefac * 3;
        HistoricPeriod = 2;
        DefensiveLethality = 30;
        maxthrust = 1.6;
        RollRate = 0.28;
        manoeverability = 0.0900;
        maxDurability = 17550;
        zoom = 1.25;
        maxtheta = 90.0;
        maxgamma = 9.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.0;
        ammo = 2450;
        impact = 7000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = .69;
        inertia = 5.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.313241106719;
        DiveSpeedLimit1 = 0.33; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.38; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1400;
        FuelBurnRate = 0.33;
        TorqueMultiplier = -0.3;
    }
    if (id == FIGHTER_DW520) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.56;
        RollRate = 0.58;
        manoeverability = 0.1584;
        maxDurability = 390;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 21.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.0;
        ammo = 2450;
        impact = 500;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.303359683794;
        DiveSpeedLimit1 = 0.32; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.40; // Faster than this will induce severe airframe damage.
        WepCapable = false;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == BOMBER_SB2C) {
        o->cubex = zoom * cubefac * 1.2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.2;
        HistoricPeriod = 2;
        DefensiveLethality = 6;
        maxthrust = 1.7;
        RollRate = 0.33;
        manoeverability = 0.1260;
        maxDurability = 2500;
        zoom = 0.4;
        maxtheta = 90.0;
        maxgamma = 18.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.0;
        ammo = 2450;
        impact = 1400;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 3200;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 2.60;
        MaxFullPowerAltRatio = 0.48;
        inertia = 3.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.25; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.251976284585;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -0.8;
    }
    if (id == BOMBER_TBF) {
        o->cubex = zoom * cubefac * 1.2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.2;
        HistoricPeriod = 1;
        DefensiveLethality = 7;
        maxthrust = 1.85;
        RollRate = 0.33;
        manoeverability = 0.1278;
        maxDurability = 3000;
        zoom = 0.4;
        maxtheta = 90.0;
        maxgamma = 20.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 3.2;
        ammo = 2450;
        impact = 1300;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 3200;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 2.50;
        MaxFullPowerAltRatio = 0.48;
        inertia = 4.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.23; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.23; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.232213438735;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.39; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -0.8;
    }
    if (id == FIGHTER_ME163) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 3.80;
        RollRate = 0.65;
        manoeverability = 0.1620;
        maxDurability = 600;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 55;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 48.0;
        ammo = 120;
        impact = 400;
        BlackoutSensitivity = 24.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 95.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 1.00;
        inertia = 1.7;
        deadweight = 0.13;
        CompressibilitySpeed = 0.44; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.44; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.533596837945;
        DiveSpeedLimit1 = 0.55; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.66; // Faster than this will induce severe airframe damage.
        WepCapable = false;
        StallSpeed = 0.175;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 0.0;
    }
    if (id == FIGHTER_TEMPEST) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.85;
        RollRate = 0.50;
        manoeverability = 0.127;
        maxDurability = 450;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 29;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 10.9;
        ammo = 2450;
        impact = 700;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1770;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1200;
        FlapsLevelElevatorEffect3 = 1600;
        FlapsLevelElevatorEffect4 = 2000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.39; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.39; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.387351778656;
        DiveSpeedLimit1 = 0.38; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.46; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.140;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_D3A) {
        o->cubex = zoom * cubefac * 1.2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.2;
        HistoricPeriod = 1;
        DefensiveLethality = 1;
        maxthrust = 1.5;
        RollRate = 0.40;
        manoeverability = 0.1181;
        maxDurability = 1300;
        zoom = 0.4;
        maxtheta = 90.0;
        maxgamma = 17.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 1.8;
        ammo = 2450;
        impact = 1300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 3200;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 1.90;
        MaxFullPowerAltRatio = 0.66;
        inertia = 3.5;
        deadweight = 0.13;
        CompressibilitySpeed = 0.21; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.21;
        SeaLevelSpeedLimitThreshold = 0.2243083004;
        DiveSpeedLimit1 = 0.27; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.37; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 1.0;
    }
    if (id == BOMBER_B5N) {
        o->cubex = zoom * cubefac * 1.2;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.2;
        HistoricPeriod = 1;
        DefensiveLethality = 1;
        maxthrust = 1.4;
        RollRate = 0.33;
        manoeverability = 0.1422;
        maxDurability = 1650;
        zoom = 0.4;
        maxtheta = 90.0;
        maxgamma = 16.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 1.8;
        ammo = 2450;
        impact = 1400;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 3200;
        FlapsLevelElevatorEffect2 = 3200;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 3200;
        SpeedBrakePower = 1.90;
        MaxFullPowerAltRatio = 0.48;
        inertia = 4.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.200; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.200; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.192687747036;
        DiveSpeedLimit1 = 0.210; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.260; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == BOMBER_DAUNTLESS) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 6;
        maxthrust = 1.5;
        RollRate = 0.40;
        manoeverability = 0.1382;
        maxDurability = 2000;
        zoom = 0.39;
        maxtheta = 90.0;
        maxgamma = 19.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.1;
        ammo = 2450;
        impact = 1000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 2.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.75;
        deadweight = 0.13;
        CompressibilitySpeed = 0.225; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.225; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.212450592885;
        DiveSpeedLimit1 = 0.29; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.40; // Faster than this will induce severe airframe damage.
        WepCapable = false;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_ME110) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 2;
        maxthrust = 1.8;
        RollRate = 0.47;
        manoeverability = 0.1195;
        maxDurability = 480;
        zoom = 0.39;
        maxtheta = 90.0;
        maxgamma = 17.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 10.9;
        ammo = 2450;
        impact = 1000;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 3.5;
        deadweight = 0.13;
        CompressibilitySpeed = 0.30; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.30; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.326086956522;
        DiveSpeedLimit1 = 0.35; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == BOMBER_DORNIER) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 1;
        DefensiveLethality = 6;
        maxthrust = 1.55;
        RollRate = 0.33;
        manoeverability = 0.1170;
        maxDurability = 1850;
        zoom = 0.70;
        maxtheta = 90.0;
        maxgamma = 18;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.6;
        ammo = 2450;
        impact = 1600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 3.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.20; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.20; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.212450592885;
        DiveSpeedLimit1 = 0.24; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.32; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == BOMBER_HE111) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 1;
        DefensiveLethality = 7;
        maxthrust = 1.6;
        RollRate = 0.33;
        manoeverability = 0.1139;
        maxDurability = 2200;
        zoom = 0.75;
        maxtheta = 90.0;
        maxgamma = 11;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.6;
        ammo = 2450;
        impact = 2000;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 4.7;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.25; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.23023715415;
        DiveSpeedLimit1 = 0.28; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.300; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == BOMBER_JU88) {
        o->cubex = zoom * cubefac * 1.4;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac * 1.4;
        HistoricPeriod = 1;
        DefensiveLethality = 6;
        maxthrust = 2.1;
        RollRate = 0.33;
        manoeverability = 0.1224;
        maxDurability = 1250;
        zoom = 0.70;
        maxtheta = 90.0;
        maxgamma = 8;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.6;
        ammo = 2450;
        impact = 1300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .180;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 6400;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.61;
        inertia = 4.2;
        deadweight = 0.13;
        CompressibilitySpeed = 0.25; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.25; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.27371541502;
        DiveSpeedLimit1 = 0.30; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.37; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.125;
        ServiceCeilingAltitude = 1026;
        FuelBurnRate = 0.75;
        TorqueMultiplier = -0.7;
    }
    if (id == FIGHTER_KI84) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.99;
        RollRate = 0.60;
        manoeverability = 0.1656;
        maxDurability = 480;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 29;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.500000;
        ammo = 2450;
        impact = 700;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.2;
        deadweight = 0.13;
        CompressibilitySpeed = 0.340; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.340; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.3814229249;
        DiveSpeedLimit1 = 0.378; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.44; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 1.0;
    }
    if (id == FIGHTER_KI61) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.55;
        RollRate = 0.55;
        manoeverability = 0.1454;
        maxDurability = 480;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 20;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.500;
        ammo = 2450;
        impact = 800;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.29; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.29; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.324110671937;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_GENERIC01) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 2;
        DefensiveLethality = 0;
        maxthrust = 1.55;
        RollRate = 0.55;
        manoeverability = 0.1454;
        maxDurability = 480;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 20;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.5000;
        ammo = 2450;
        impact = 800;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.29; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.29; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.324110671937;
        DiveSpeedLimit1 = 0.34; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.42; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_A6M5) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.58;
        RollRate = 0.50;
        manoeverability = 0.195;
        maxDurability = 210;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 22.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 2.80;
        ammo = 1600;
        impact = 300;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .166;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 2400;
        FlapsLevelElevatorEffect2 = 2400;
        FlapsLevelElevatorEffect3 = 2400;
        FlapsLevelElevatorEffect4 = 2400;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.51;
        inertia = 1.0;
        deadweight = 0.07;
        CompressibilitySpeed = 0.280; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active.
        CompressibilitySpeedWithSpeedBrakes = 0.280; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.311264822134; // A6M5: 0.311264822134 yields 315MPH.
        DiveSpeedLimit1 = 0.290; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.370; // Faster than this will induce severe airframe damage
        WepCapable = false;
        StallSpeed = 0.110;
        ServiceCeilingAltitude = 1500;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 1.0;
    }
    if (id == FIGHTER_SPIT5) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.60;
        RollRate = 0.58;
        manoeverability = 0.172;
        maxDurability = 420;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 27.5;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 4.3;
        ammo = 2450;
        impact = 600;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1700;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 2.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.35; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.35; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.370553359684;
        DiveSpeedLimit1 = 0.3806; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.46; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_P51B) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.60;
        RollRate = 0.55;
        manoeverability = 0.150;
        maxDurability = 510;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 19;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 6.220;
        ammo = 1600;
        impact = 750;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.67;
        inertia = 2.3;
        deadweight = 0.13;
        CompressibilitySpeed = 0.33; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.33; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.3814229249;
        DiveSpeedLimit1 = 0.3873; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.45; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.135;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_P47B) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.70;
        RollRate = 0.72;
        manoeverability = 0.1267;
        maxDurability = 1200;
        zoom = 0.36;
        maxtheta = 90.0;
        maxgamma = 16;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.8;
        ammo = 1600;
        impact = 1000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 110.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.685;
        inertia = 3.0;
        deadweight = 0.13;
        CompressibilitySpeed = 0.35; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.35; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.357707509881;
        DiveSpeedLimit1 = 0.43; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.55; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.135;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_ME109F) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.64;
        RollRate = 0.55;
        manoeverability = 0.1512;
        maxDurability = 390;
        zoom = 0.35;
        maxtheta = 90.0;
        maxgamma = 26;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.0;
        ammo = 2450;
        impact = 500;
        BlackoutSensitivity = 22.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 104.0;
        ClipDistance = 0.03;
        FlapSpeed = .170;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 3200;
        FlapsLevelElevatorEffect4 = 8000;
        SpeedBrakePower = 1.0;
        MaxFullPowerAltRatio = 0.68;
        inertia = 1.8;
        deadweight = 0.13;
        CompressibilitySpeed = 0.28; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.28; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.340909090909;
        DiveSpeedLimit1 = 0.38; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.44; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.130;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.5;
        TorqueMultiplier = -1.0;
    }
    if (id == FIGHTER_P38F) {
        o->cubex = zoom * cubefac;
        o->cubey = zoom * cubefac;
        o->cubez = zoom * cubefac;
        HistoricPeriod = 1;
        DefensiveLethality = 0;
        maxthrust = 1.60;
        RollRate = 0.70;
        manoeverability = 0.175;
        maxDurability = 510;
        zoom = 0.39;
        maxtheta = 90.0;
        maxgamma = 26.0;
        missilerackn[0] = 0;
        missilerackn[1] = 0;
        missilerackn[2] = 0;
        missilerackn[3] = 0;
        missilerack[0] = 0;
        missilerack[1] = 0;
        missilerack[2] = 0;
        missilerack[3] = 0;
        flares = 0;
        chaffs = 0;
        statLethality = 8.0;
        ammo = 2450;
        impact = 1000;
        BlackoutSensitivity = 20.0F;
        RedoutSensitivity = 40.0F;
        StaticDrag = 100.0;
        ClipDistance = 0.03;
        FlapSpeed = .1778;
        FlapsLevelElevatorEffect0 = 0;
        FlapsLevelElevatorEffect1 = 800;
        FlapsLevelElevatorEffect2 = 1600;
        FlapsLevelElevatorEffect3 = 4000;
        FlapsLevelElevatorEffect4 = 11000;
        SpeedBrakePower = 1.00;
        MaxFullPowerAltRatio = 0.68;
        inertia = 3.5;
        deadweight = 0.13;
        CompressibilitySpeed = 0.31; // Faster than this degrades elevator and aileron response unless SpeedBrakes are available and active. Was .29
        CompressibilitySpeedWithSpeedBrakes = 0.31; // Replaces above setting when SpeedBrakes are active.
        SeaLevelSpeedLimitThreshold = 0.363636363636;
        DiveSpeedLimit1 = 0.42; // Faster than this induces extra turbulence
        DiveSpeedStructuralLimit = 0.504; // Faster than this will induce severe airframe damage.
        WepCapable = true;
        StallSpeed = 0.120;
        ServiceCeilingAltitude = 1760;
        FuelBurnRate = 1.0;
        TorqueMultiplier = 0.0;
    }
    if (id >= FIGHTER1 && id <= FIGHTER2) {
        recthrust = maxthrust;
        Durability = maxDurability;
        thrust = recthrust = maxthrust;
        smoke->type = 1;
        impact = 2;
        forcez = recthrust;
    }
    if (id == FLAK_AIR1) {
        maxthrust = 0;
        thrust = 0;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 12.0;
        Durability = maxDurability = 240;
        zoom = 0.35;
    }
    if (id == FLARAK_AIR1) {
        maxthrust = 0;
        thrust = 0;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 6.0;
        Durability = maxDurability = 210;
        zoom = 0.3;
        missiles[6] = 100;
    }
    if (id >= FLAK1 && id <= FLAK2) {
        o->cubex = zoom * cubefac1;
        o->cubey = zoom * cubefac1;
        o->cubez = zoom * cubefac1;
    }
    if (id == TANK_AIR1) {
        maxthrust = 0.04;
        thrust = 0;
        gamma = 180;
        theta = 0;
        phi = 0;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 8.0;
        Durability = maxDurability = 600;
        zoom = 0.35;
        o->cubex = zoom * 0.7;
        o->cubey = zoom * 0.45;
        o->cubez = zoom * 0.7;
    } else if (id == TANK_GROUND1) {
        maxthrust = 0.04;
        thrust = 0;
        gamma = 180;
        theta = 0;
        phi = 0;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 8.0;
        Durability = maxDurability = 600;
        zoom = 0.4;
        o->cubex = zoom * 0.7;
        o->cubey = zoom * 0.5;
        o->cubez = zoom * 0.7;
    } else if (id == TANK_PICKUP1) {
        maxthrust = 0;
        thrust = 0.02;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 0;
        Durability = maxDurability = 90;
        zoom = 0.25;
        o->cubex = zoom * 0.7;
        o->cubey = zoom * 0.55;
        o->cubez = zoom * 0.7;
    } else if (id == TANK_TRUCK1) {
        maxthrust = 0;
        thrust = 0.02;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 0;
        Durability = maxDurability = 60;
        zoom = 0.45;
        o->cubex = zoom * 0.6;
        o->cubey = zoom * 0.35;
        o->cubez = zoom * 0.6;
    } else if (id == TANK_TRUCK2) {
        maxthrust = 0;
        thrust = 0.02;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 0;
        Durability = maxDurability = 120;
        zoom = 0.4;
        o->cubex = zoom * 0.6;
        o->cubey = zoom * 0.35;
        o->cubez = zoom * 0.6;
    } else if (id == TANK_TRSAM1) {
        maxthrust = 0;
        thrust = 0.02;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 0;
        Durability = maxDurability = 150;
        zoom = 0.35;
        missiles[6] = 200;
        o->cubex = zoom * 0.7;
        o->cubey = zoom * 0.6;
        o->cubez = zoom * 0.7;
    }
    if (id >= TANK1 && id <= TANK2) {
    }
    if (id == SHIP_CRUISER) {
        zoom = 5.0;
        maxthrust = 0.05;
        thrust = 0.05;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 4.0;
        impact = 200;
        Durability = maxDurability = 30000;
        missiles[6] = 200;
        o->cubex = zoom * 0.35;
        o->cubey = zoom * 0.1;
        o->cubez = zoom * 0.35;
    } else if (id == SHIP_DESTROYER1) {
        zoom = 2.5;
        maxthrust = 0.05;
        thrust = 0.05;
        maxgamma = 0;
        maxtheta = 0.03;
        manoeverability = 6.0;
        impact = 300;
        Durability = maxDurability = 15000;
        o->cubex = zoom * 0.4;
        o->cubey = zoom * 0.12;
        o->cubez = zoom * 0.4;
    }
    if (id == BOMB01) {
        intelligence = 0;
        maxthrust = 0.01 * missilethrustbase;
        RollRate = 0.0;
        manoeverability = 0.0;
        ai = true;
        StaticDrag = 3000;
        ttl = 2000 * timestep;
        impact = 30000;
        CompressibilitySpeed = BombCompressibilitySpeed;
    } else if (id == MISSILE_AIR2) {
        intelligence = 100;
        maxthrust = 0.5 * missilethrustbase;
        RollRate = 3.5;
        manoeverability = 4.5;
        StaticDrag = 8;
        ttl = 320 * timestep;
        impact = 2100;
    } else if (id == MISSILE_AIR3) {
        intelligence = 100;
        maxthrust = 0.65 * missilethrustbase;
        RollRate = 4.5;
        manoeverability = 5.5;
        StaticDrag = 8;
        ttl = 340 * timestep;
        impact = 2200;
    } else if (id == MISSILE_GROUND1) {
        intelligence = 10;
        maxthrust = 0.60 * missilethrustbase;
        RollRate = 1.2;
        manoeverability = 1.0;
        ai = true;
        StaticDrag = 8;
        ttl = 300 * timestep;
        impact = 3000;
    } else if (id == MISSILE_GROUND2) {
        intelligence = 10;
        maxthrust = 0.75 * missilethrustbase;
        RollRate = 1.5;
        manoeverability = 1.0;
        ai = true;
        StaticDrag = 8;
        ttl = 400 * timestep;
        impact = 4000;
    } else if (id == MISSILE_DF1) {
        intelligence = 1;
        maxthrust = 0.90 * missilethrustbase;
        RollRate = 0.0;
        manoeverability = 0.0;
        ai = true;
        StaticDrag = 1;
        ttl = 350 * timestep;
        impact = 8000;
        CompressibilitySpeed = 0.9;
        inertia = 0.01;
    } else if (id == MISSILE_FF1) {
        intelligence = 100;
        maxthrust = 0.85 * missilethrustbase;
        RollRate = 2.0;
        manoeverability = 5.0;
        StaticDrag = 10;
        ttl = 300 * timestep;
        impact = 2100;
    } else if (id == MISSILE_FF2) {
        intelligence = 100;
        maxthrust = 0.90 * missilethrustbase;
        RollRate = 3.0;
        manoeverability = 6.0;
        StaticDrag = 10;
        ttl = 320 * timestep;
        impact = 2200;
    } else if (id == MISSILE_MINE1) {
        intelligence = 0;
        maxthrust = 0.1;
        RollRate = 1.0;
        manoeverability = 1.0;
        ai = true;
        StaticDrag = 8;
        ttl = -1;
        impact = 500;
        zoom = 0.3;
    }
    if (id >= MISSILE1 && id <= MISSILE2) {
        o->cubex = zoom;
        o->cubey = zoom;
        o->cubez = zoom;
    }
    if (id >= STATIC_PASSIVE) {
        intelligence = 0;
        maxthrust = 0;
        RollRate = 0;
        manoeverability = 0;
        impact = 5;
        maxtheta = 0;
        maxgamma = 0;
    }
    if (id == STATIC_CONTAINER1) {
        Durability = maxDurability = 90;
        zoom = 1.0;
        impact = 20;
        o->cubex = zoom * 0.4;
        o->cubey = zoom * 0.35;
        o->cubez = zoom * 0.9;
    }
    if (id == STATIC_BATTERY) {
        Durability = maxDurability = AIRFIELDMAXDURABILITY / 2.0;
        zoom = 6.0;
        impact = 2000;
        o->cubex = zoom * 0.20;
        o->cubey = zoom * 0.16;
        o->cubez = zoom * 1.05;
    }
    if (id == STATIC_BATTLESHIP) {
        Durability = maxDurability = 120000;
        zoom = 12.0;
        impact = 9000;
        o->cubex = zoom * 1.00;
        o->cubey = zoom * 0.16;
        o->cubez = zoom * 1.00;
    }
    if (id == STATIC_DESTROYER) {
        Durability = maxDurability = 20000;
        zoom = 6.0;
        impact = 1000;
        o->cubex = zoom * 0.55;
        o->cubey = zoom * 0.08;
        o->cubez = zoom * 0.55;
    }
    if (id == STATIC_CARRIER00) {
        Durability = maxDurability = 120000;
        zoom = 12.0;
        impact = 7000;
        o->cubex = zoom * 1.00;
        o->cubey = zoom * 0.01;
        o->cubez = zoom * 1.00;
    }
    if (id == STATIC_HALL2) {
        Durability = maxDurability = 900;
        zoom = 2.5;
        impact = 20;
        o->cubex = zoom;
        o->cubey = zoom * 0.45;
        o->cubez = zoom;
    }
    if (id == STATIC_OILRIG1) {
        Durability = maxDurability = 1400;
        zoom = 3.5;
        impact = 20;
        o->cubex = zoom * 0.95;
        o->cubey = zoom * 0.5;
        o->cubez = zoom * 0.95;
    }
    if (id == STATIC_COMPLEX1) {
        Durability = maxDurability = 5000;
        zoom = 2.0;
        impact = 20;
        o->cubex = zoom * 0.75;
        o->cubey = zoom * 0.6;
        o->cubez = zoom * 0.75;
    }
    if (id == STATIC_RADAR1) {
        Durability = maxDurability = 500;
        zoom = 1.3;
        impact = 20;
        o->cubex = zoom * 0.5;
        o->cubey = zoom * 0.7;
        o->cubez = zoom * 0.5;
    }
    if (id == STATIC_BASE1) {
        Durability = maxDurability = 5500;
        zoom = 4.0;
        impact = 20;
        o->cubex = zoom * 0.7;
        o->cubey = zoom * 0.5;
        o->cubez = zoom * 0.7;
    }
    if (id == STATIC_DEPOT1) {
        Durability = maxDurability = 3000;
        zoom = 1.5;
        impact = 20;
        o->cubex = zoom;
        o->cubey = zoom * 0.5;
        o->cubez = zoom;
    }
    if (id == STATIC_BARRIER1) {
        Durability = maxDurability = 1000;
        zoom = 12.0;
        impact = 2000;
        o->cubex = 0.8;
        o->cubey = 11;
        o->cubez = 11;
    }
    this->intelligence = intelligence;
    this->precision = precision;
    this->aggressivity = aggressivity;
    missileCount();
}

void AIObj::newinit(int id, int party, int intelligence) {
    newinit(id, party, intelligence, intelligence, intelligence);
}

int AIObj::nextMissile(int from) {
    int i = from + 1;
    if (i >= missiletypes) {
        i = 0;
    }
    while (!missiles[i]) {
        i++;
        if (i >= missiletypes) {
            i = 0;
        }
        if (i == from) {
            break;
        }
    }
    ttf = 50 * timestep;
    return i;
}

bool AIObj::selectMissileAir(AIObj** missile) {
    bool sel = false;
    if (haveMissile(MISSILE_AIR3)) {
        missiletype = MISSILE_AIR3 - MISSILE1;
        sel = true;
    } else if (haveMissile(MISSILE_AIR2)) {
        missiletype = MISSILE_AIR2 - MISSILE1;
        sel = true;
    } else if (haveMissile(BOMB01)) {
        missiletype = BOMB01 - MISSILE1;
        sel = true;
    }
    return sel;
}

bool AIObj::selectMissileAirFF(AIObj** missile) {
    bool sel = false;
    if (haveMissile(MISSILE_FF2)) {
        missiletype = MISSILE_FF2 - MISSILE1;
        sel = true;
    } else if (haveMissile(MISSILE_FF1)) {
        missiletype = MISSILE_FF1 - MISSILE1;
        sel = true;
    }
    return sel;
}

bool AIObj::selectMissileGround(AIObj** missile) {
    bool sel = false;
    if (haveMissile(MISSILE_GROUND2)) {
        missiletype = MISSILE_GROUND2 - MISSILE1;
        sel = true;
    } else if (haveMissile(MISSILE_GROUND1)) {
        missiletype = MISSILE_GROUND1 - MISSILE1;
        sel = true;
    }
    return sel;
}

void AIObj::targetNearestEnemy(AIObj** f) {
    int i;
    float d = 1E12;
    ttf = 50 * timestep;
    for (i = 0; i < maxfighter; i++) {
        if (this != f[i] && party != f[i]->party && f[i]->active) {
            float phi = getAngle(f[i]);
            float d2 = distance(f[i]) * (60 + fabs(phi)); // prefer enemies in front

            if (d2 < d) {
                d = d2;
                target = f[i];
            }
        }
    }
    if (!ai && target)
        if (distance(target) > 400) {
            target = NULL;
        }
}

void AIObj::targetNearestGroundEnemy(AIObj** f) {
    int i;
    float d = 1E12;
    ttf = 50 * timestep;
    for (i = 0; i < maxfighter; i++) {
        if (this != f[i] && party != f[i]->party && f[i]->active) {
            float phi = getAngle(f[i]);
            float d2 = distance(f[i]) * (60 + fabs(phi)); // prefer enemies in front
            if (bomber)
                if (f[i]->id < MOVING_GROUND) {
                    d2 += 1E10;    // only use this target if no ground targets exist
                }
            if (d2 < d) {
                d = d2;
                target = f[i];
            }
        }
    }
    if (target)
        if (distance(target) > 400) {
            target = NULL;
        }
}

void AIObj::targetNext(AIObj** f) {
    int i;
    ttf = 50 * timestep;
    if (target == ThreeDObjects[0]) {

        target = f[0]; // Special case. Select NOTHING.
        return; // and keep it that way!
    }
    for (i = 0; i < maxfighter; i++)
        if (target == f[i]) {
            break;
        }
    int z = 0;
    do {
        i++;
        if (i >= maxfighter) {
            i = 0;
        }
        if (f[i] == this) {
            i++;
            z++;
        }
        if (i >= maxfighter) {
            i = 0;
        }
    }
    while ((!f[i]->active || distance(f[i]) > 11000) && z <= 1);
    target = f[i];
    if (z > 1 && !ai) {
        target = NULL;
    }
}

void AIObj::targetPrevious(AIObj** f) {
    int i;
    ttf = 50 * timestep;
    if (target == NULL) {
        target = f[0];
    }
    for (i = 0; i < maxfighter; i++)
        if (target == f[i]) {
            break;
        }
    int z = 0;
    do {
        i--;
        if (i < 0) {
            i = maxfighter - 1;
        }
        if (f[i] == this) {
            i--;
            z++;
        }
        if (i < 0) {
            i = maxfighter - 1;
        }
    }
    while ((!f[i]->active || distance(f[i]) > 11000) && z <= 1);
    target = f[i];
    if (z > 1 && !ai) {
        target = NULL;
    }
}

void DynamicObj::activate() {
    active = true;
    draw = true;
}

// check the objects Durability value for damage. Explode/sink if necessary. Start
// Mission-ending flags and timers if airfields are destroyed or nearly destroyed.
//
void DynamicObj::checkDurability() {
    if ((id == CANNON1) || (id == CANNON2)) {
        return; // Bullets don't need any special treatment.
    }
    if (id == STATIC_AIRFIELD00) {
        if ((Durability < (maxDurability * 0.25)) && (active)) { // Get here if the examined object is alive but so damaged it must die.
            //display ((char *)"checkDurability(): Detected heavily damaged airfield.", LOG_MOST);
            //

            if (Durability) {
                Durability = 0.0;
            }
            if (!explode) {
                //display ((char *)"DynamicObj::checkDurability(): explode attribute is FALSE.", LOG_MOST);
                explode = 1;
            }
            if (active) {
                active = false;
            }
            if ((!MissionEndingTimer) && (!MissionEndingTimer2)) {
                display((char*)"checkDurability(): Setting MissionEndingTimer to 13000.", LOG_MOST);
                MissionEndingTimer = 13000;
            }
            // After destroying that airfield, we should also destroy any surviving, associated
            // RADAR antenna. But in order to do that we must first determine WHICH airfield was
            // destroyed. We will do that by examining the XZ position within each possible mission:
            display((char*)"DynamicObj::checkDurability: Destroyed an airfield.", LOG_MOST);
            sprintf(DebugBuf, "DynamicObj::Destroyed airfield XZ position = %f, %f.", tl->x, tl->z);
            display(DebugBuf, LOG_MOST);
            switch (CurrentMissionNumber) {
            case (MISSION_NETWORKBATTLE01):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE01.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[MissionObjectRadarBlue1]->Durability = 0.0;
                    ThreeDObjects[MissionObjectRadarBlue1]->explode = 1;
                    ThreeDObjects[MissionObjectRadarBlue1]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[MissionObjectRadarRed1]->Durability = 0.0;
                    ThreeDObjects[MissionObjectRadarRed1]->explode = 1;
                    ThreeDObjects[MissionObjectRadarRed1]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE02):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE02.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[MissionObjectRadarBlue1]->Durability = 0.0;
                    ThreeDObjects[MissionObjectRadarBlue1]->explode = 1;
                    ThreeDObjects[MissionObjectRadarBlue1]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[MissionObjectRadarRed1]->Durability = 0.0;
                    ThreeDObjects[MissionObjectRadarRed1]->explode = 1;
                    ThreeDObjects[MissionObjectRadarRed1]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE03):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE03.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[MissionObjectRadarBlue1]->Durability = 0.0;
                    ThreeDObjects[MissionObjectRadarBlue1]->explode = 1;
                    ThreeDObjects[MissionObjectRadarBlue1]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[MissionObjectRadarRed1]->Durability = 0.0;
                    ThreeDObjects[MissionObjectRadarRed1]->explode = 1;
                    ThreeDObjects[MissionObjectRadarRed1]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE04):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE04.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE05):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE05.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE06):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE06.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE07):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE07.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE08):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE08.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE09):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE09.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            case (MISSION_NETWORKBATTLE10):
            {
                display((char*)"DynamicObj::checkDurability: Destroyed an airfield within MISSION_NETWORKBATTLE10.", LOG_MOST);
                if (tl->x == -304) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 28.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[26]->Durability = 0.0;
                    ThreeDObjects[26]->explode = 1;
                    ThreeDObjects[26]->active = 0;
                }
                if (tl->x == 207.5) {
                    display((char*)"DynamicObj::checkDurability: Destroyed airfield 29.", LOG_MOST);
                    // Destroy associated RADAR antenna:
                    ThreeDObjects[27]->Durability = 0.0;
                    ThreeDObjects[27]->explode = 1;
                    ThreeDObjects[27]->active = 0;
                }
                break;
            }
            default:
            {
                display((char*)"DynamicObj::checkDurability: CurrentMissionNumber is Invalid.", LOG_MOST);
            }
            }
            return;
        }
    }
    if (Durability <= 0 && active) {
        explode = 1;
        active = false;
    }
}

// check whether the object is exploding or sinking and deactivate if necessary
void DynamicObj::checkExplosion(Uint32 dt) {
    if (explode > 0) {
        if (explode == 1) {
            ttl = -1;
            if (
                id == STATIC_CONTAINER1 ||
                id == STATIC_RADAR1 ||
                id == STATIC_COMPLEX1 ||
                id == STATIC_DEPOT1 ||
                id == TANK1 ||
                id == STATIC_AIRFIELD00
                ) {

                setExplosion(2.0, 100 * timestep);
                setBlackSmoke(14.0, 600 * timestep);
            } else if (id == STATIC_OILRIG1) {
                setExplosion(3.0, 40 * timestep);
                setBlackSmoke(5.5, 80 * timestep);
            } else {
                float zoom2 = zoom * 2;

                if (zoom2 > 2) {
                    zoom2 = 2;
                }
                setExplosion(zoom2, 35 * timestep);
                setBlackSmoke(1.0, 60 * timestep);
            }
        }
        if (id >= STATIC_GROUND || (id >= MOVING_GROUND && id <= MOVING_WATER)) {
            if (explode >= 25 * timestep && ttl == -1) {
                setExplosion(zoom * 2, 35 * timestep);
                setBlackSmoke(1.0, 60 * timestep);
                ttl = -2;
            }
            if (explode >= 30 * timestep && ttl == -2) {
                setExplosion(zoom * 2, 35 * timestep);
                setBlackSmoke(1.0, 60 * timestep);
                ttl = -3;
            }
        }
        if (explode >= 35 * timestep) {
            deactivate();
            ttl = -1;
            explode += dt;
            setBlackSmoke(18.0, 600 * timestep);
            if (id == STATIC_RADARREFLECTOR) {

                if (tl->x > 0) {
                    if (ThreeDObjects[MissionObjectHqRed]->Durability > (ThreeDObjects[MissionObjectHqRed]->maxDurability * 0.4)) {
                        ThreeDObjects[MissionObjectHqRed]->Durability = ThreeDObjects[MissionObjectHqRed]->maxDurability * 0.39;
                        RadarReflectorRedHasBeenDestroyedAtLeastOnce = true;
                    }
                } else {
                    if (ThreeDObjects[MissionObjectHqBlue]->Durability > (ThreeDObjects[MissionObjectHqBlue]->maxDurability * 0.4)) {
                        ThreeDObjects[MissionObjectHqBlue]->Durability = ThreeDObjects[MissionObjectHqBlue]->maxDurability * 0.39;
                        RadarReflectorBlueHasBeenDestroyedAtLeastOnce = true;
                    }
                }
            }
            if (((id != STATIC_AIRFIELD00) && (id != STATIC_RADARREFLECTOR) && (id >= STATIC_GROUND)) || ((id >= MOVING_GROUND) && (id <= MOVING_WATER))) {
                explode = 0;
                draw = true;
                id = STATIC_PASSIVE;
                Durability = 100000;
                o = &model_rubble1;
                zoom *= 0.7F;
                if (zoom > 1) {
                    zoom = 1;
                }

                tl->y = l->getExactHeight(tl->x, tl->z) + zoom / 4;
            }
        } else {
            explode += dt;
        }
    }
    if (sink) {
        sink += dt;
        if (sink > 100 * timestep) {
            deactivate();
            ttl = -1;
        }
    }
}

// check for a looping, this is tricky :-)
bool DynamicObj::checkLooping() {
    if (gamma > 270) {
        gamma = 540 - gamma;
        theta += 180;
        phi += 180;
        rectheta += 180;
        if (theta >= 360) {
            theta -= 360;
        }

        if (rectheta >= 360) {
            rectheta -= 360;
        }

        if (phi >= 360) {
            phi -= 360;
        }
        return true;
    } else if (gamma < 90) {
        gamma = 180 - gamma;
        theta += 180;
        phi += 180;
        rectheta += 180;
        if (theta >= 360) {
            theta -= 360;
        }
        if (rectheta >= 360) {
            rectheta -= 360;
        }
        if (phi >= 360) {
            phi -= 360;
        }
        return true;
    }
    return false;
} // end DynamicObj::checkLooping ()

//
// check for collision between two mission objects. All attributes of one of the two objects
// can be directly referenced, and all of the attributes of the other object can be indirectly
// referenced through "d", with syntax like "d->id".
//
// Simplified model, each model is surrounded by a cube. This works pretty well, but we must
// use more than one model for complex models or scenes
//
void DynamicObj::collide(DynamicObj* d, Uint32 dt) // d must be the medium (MachineGunBullet, missile)
{

    if (immunity > 0 || d->immunity > 0) {
        return;
    }
    if (explode > 0 || sink > 0) {
        return;
    }
    bool collide = false;
    if (tl->x + o->cubex >= d->tl->x - d->o->cubex && tl->x - o->cubex <= d->tl->x + d->o->cubex &&
        tl->y + o->cubey >= d->tl->y - d->o->cubey && tl->y - o->cubey <= d->tl->y + d->o->cubey &&
        tl->z + o->cubez >= d->tl->z - d->o->cubez && tl->z - o->cubez <= d->tl->z + d->o->cubez) {
        collide = true;
    }
    if (collide) {
        if (id == STATIC_BATTERY) {
            if (d == (DynamicObj*)fplayer) {
                display((char*)"DynamicObj::collide() player collided with an artillery battery", LOG_MOST);
                fplayer->Durability -= 12;
            }
        }
        if (id == STATIC_BATTLESHIP) {
            if (d == (DynamicObj*)fplayer) {
                display((char*)"DynamicObj::collide() player collided with a Battleship", LOG_MOST);
                fplayer->Durability -= 12;
            }
        }
        if (id == STATIC_DESTROYER) {
            if (d == (DynamicObj*)fplayer) {
                display((char*)"DynamicObj::collide() player collided with a Destroyer", LOG_MOST);
                fplayer->Durability -= 12;
            }
        }
        if (id == STATIC_AIRFIELD00) {
            if (d->id > FIGHTER1 && d->id < FIGHTER2) {
                if (
                    tl->x + 1 >= d->tl->x - 1 && tl->x - 1 <= d->tl->x + 1 &&
                    tl->y + 1 >= d->tl->y - 1 && tl->y - 1 <= d->tl->y + 1 &&
                    tl->z + 1 >= d->tl->z - 1 && tl->z - 1 <= d->tl->z + 1
                    ) {
                    if (d == (DynamicObj*)fplayer) {
                        fplayer->Durability -= 4.0F;
                    }
                } else {
                    return;
                }
            } else if (d->id == BOMB01) {
                d->Durability -= 30000.0;
                DamageInNetQueue += 30000.0;
                display((char*)"DynamicObj::collide() bomb hit. DamageInNetQueue += 30000.0", LOG_MOST);
            } else if (d->id == MISSILE_DF1) {
                d->Durability -= 8000;
                DamageInNetQueue += 8000.0;
                display((char*)"DynamicObj::collide() missile hit. DamageInNetQueue += 8000.0", LOG_MOST);
            }
        }
        if (this == (DynamicObj*)fplayer && d->id >= AIR && d->id < MOVING_GROUND) { // Get here if the player has collided with another aircraft
            Durability = -1.0F; // Damage the player
            d->Durability = -1.0F; // Damage the other aircraft with which we collided
            fplayer->target = NULL;
            display((char*)"DynamicObj::collide() reset player target to 0 due to collision with aircraft.", LOG_MOST);
        }
        if (id < STATIC_PASSIVE || (id >= STATIC_PASSIVE && d->id >= MISSILE1 && d->id <= MISSILE2)) {
            Durability -= (float)d->impact;

            if (
                CurrentMissionNumber == MISSION_NETWORKBATTLE01 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE02 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE03 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE04 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE05 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE06 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE07 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE08 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE09 ||
                CurrentMissionNumber == MISSION_NETWORKBATTLE10 ||
                CurrentMissionNumber == MISSION_TUTORIAL3
                ) {
                d->Durability -= 500;
            }
            DamageInNetQueue += (float)d->impact;
            sprintf(DebugBuf, "DynamicObj::collide() impact. DamageInNetQueue += d->impact or %f", d->impact);
            display(DebugBuf, LOG_MOST);
        }
        if (d->id == CANNON1) {
            Durability -= fplayer->statLethality;
            if ((difficulty > 3) && (myrandom(100) < 5)) {
                Durability -= ((fplayer->statLethality) * 40);
                DamageInNetQueue += ((fplayer->statLethality) * 40);
            }
        }
        if (d->id == CANNON2) {
            Durability -= fplayer->statLethality;
            if ((difficulty > 3) && (myrandom(100) < 5)) {
                Durability -= ((fplayer->statLethality) * 40);
                DamageInNetQueue += ((fplayer->statLethality) * 40);
            }
        }
        if (d->source->party == party) { // Somebody is attempting fratricide
            if (d->source == (DynamicObj*)fplayer) { // player is shooting his own team
                if (id == STATIC_AIRFIELD00) {
                    //sprintf (SystemMessageBufferA, "YOU ARE SHOOTING YOUR OWN AIRFIELD!");
                    //NewSystemMessageNeedsScrolling = true;
                    //fplayer->Durability -= 0.02;
                }
            }
        }
        if ((d->id != BOMB01) && (d->id != MISSILE_DF1)) {
            // display ("DynamicObj::collide()1: Two mission objects collided.", LOG_MOST);
            // sprintf (DebugBuf, "DynamicObj::collide()2: d->id = %d", d->id);
            // display (DebugBuf, LOG_MOST);
            // sprintf (DebugBuf, "DynamicObj::collide()3: id = %d", id);
            // display (DebugBuf, LOG_MOST);
            if (id == STATIC_CARRIER00) {

                if (d->id == fplayer->id) {

                    if (d->phi == fplayer->phi) { // Get here if the player has collided with an aircraft carrier.

                        PlayerCollidedWithAircraftCarrier = true;
                    }
                }
            }
            if (!PlayerCollidedWithAircraftCarrier) {
                DamageInNetQueue += fplayer->statLethality; // Inflict damage from unfortunate collision
            }
        }
        if (d->source != NULL && active)   // only for missiles/cannons
        {
            if (Durability <= 0) {
                if (active && draw && !killed) {
                    if (d->source->id >= FIGHTER1 && d->source->id <= FIGHTER2) {
                        killed = true;
                        DamageInNetQueue += 500000;
                        display((char*)"DynamicObj::collide() Fighter killed something. DamageInNetQueue += 500000.0", LOG_MOST);
                        if (id >= FIGHTER1 && id <= FIGHTER2) {
                            Sentient = 0;
                            d->source->fighterkills++;
                            fplayer->target = NULL;

                            RecentVictim = id;
                            RecentVictimAltitude = tl->y;
                            RecentVictimXPosition = tl->x;
                            RecentVictimZPosition = tl->z;
                            RecentVictimGamma = gamma;
                            RecentVictimPhi = phi;
                            RecentVictimTheta = theta;
                            RecentVictimVelocity = realspeed * 0.8;
                        } else if (id >= SHIP1 && id <= SHIP2) {
                            d->source->shipkills++;
                        } else if ((id >= FLAK1 && id <= FLAK2) || (id >= TANK1 && id <= TANK2)) {
                            d->source->tankkills++;
                        }
                        if (id == STATIC_DEPOT1) {
                            if (tl->x > 0) {
                                display((char*)"DynamicObj::collide() RedTeam Bunker Destroyed.", LOG_MOST);

                                ThreeDObjects[MissionObjectHqRed]->Durability -= 2400;
                            } else {
                                display((char*)"DynamicObj::collide() BlueTeam Bunker Destroyed.", LOG_MOST);

                                ThreeDObjects[MissionObjectHqBlue]->Durability -= 2400;
                            }
                        }
                    }
                }
            }
        }

        if (!PlayerCollidedWithAircraftCarrier) {
            int DamageTemp = (int)DamageInNetQueue;
            if (DamageTemp > 4000) {
                DamageTemp = 4000;
            }
            setExplosion(0.2, 20 * timestep * DamageTemp / 500);
            setBlackSmoke(0.5, 30 * timestep * DamageTemp / 20);
        }
    }
}

// check whether the object collides on the ground and alter gamma and y-translation
void DynamicObj::crashGround(Uint32 dt) {
    static bool NoseWheelDamageInflicted;
    static bool TireSqueakSounded;
    static bool LandingDamageSounded;
    static bool OceanCrashSounded;
    static bool BellyScrapeSounded;
    static bool WheelRolloutSounded;
    if (id >= MOVING_GROUND) {
        return;
    }
    float TerrainHeightHere = l->getExactHeight(tl->x, tl->z);
    float height = tl->y - TerrainHeightHere;
    if (id >= CANNON1 && id <= CANNON2) {
        if (tl->y < TerrainHeightHere) {
            setExplosion(3.0, 30 * timestep);
            deactivate();
        }
    }
    if (height < zoom || (height < 4 && PlayerCollidedWithAircraftCarrier)) {
        if (this == (DynamicObj*)fplayer) {
            RearmRefuelRepair();
            tl->y -= (height - zoom);
            if (height < 4 && PlayerCollidedWithAircraftCarrier) {
                tl->y += 1.0;  // Raise player aircraft to height of carrier deck.
            }
        } else {
            if (Sentient > 3) {
                tl->y -= (height - zoom * 0.3);
            } else {

                if ((CurrentMissionNumber == MISSION_FREEFLIGHTWW2) || (CurrentMissionNumber == MISSION_TUTORIAL) || (this->id != 0)) {
                    sprintf(
                        DebugBuf,
                        "crashGround(): Bot #%d destroyed due to impact with ground. Type =%d.",
                        this->MyMissionPlayerNumber,
                        this->id
                    );
                    display(DebugBuf, LOG_MOST);
                    setExplosion(3.0, 30 * timestep);
                    deactivate();
                    float Xdistance;
                    float Zdistance;
                    float XZdistance;
                    Xdistance = (fabs)(fplayer->tl->x - tl->x);
                    Zdistance = (fabs)(fplayer->tl->z - tl->z);
                    XZdistance = (Xdistance + Zdistance) * 1.5;
                    if (XZdistance > 126) {
                        XZdistance = 126;
                    }
                    sound->setVolume(SOUND_EXPLOSION1, (126 - (int)XZdistance));
                    sound->play(SOUND_EXPLOSION1, false);
                }
            }
        }
        if (realspeed < StallSpeed * 0.5) {
            if (gamma > 180) {
                gamma -= (.005 * timestep);
            }
            if (gamma < 180) {
                gamma = 180;
            }
            theta = 0;
        } else {
            PlayerCollidedWithAircraftCarrier = false;
        }
        if (Durability > 0) {
            if (id >= MISSILE1 && id <= MISSILE2) {
                setExplosion(1.2, 30 * timestep);
                setBlackSmoke(1.2, 30 * timestep);
            }
        }
        float decfac = 200.0F;
        if (realism && this == (DynamicObj*)fplayer && game == GAME_PLAY) {
            OnTheGround = true;
            WindNoiseOn = false;
            if (fplayer->realspeed < (fplayer->StallSpeed * 1.0)) {
                if (gamma < 174.0 && !NoseWheelDamageInflicted) {
                    Durability -= ((fplayer->realspeed * decfac * dt / timestep) * 7);
                    NoseWheelDamageInflicted = true;
                }
                float height2 = tl->y - l->getExactHeight(tl->x + 1, tl->z);
                float height3 = tl->y - l->getExactHeight(tl->x - 1, tl->z);
                float height4 = tl->y - l->getExactHeight(tl->x, tl->z + 1);
                float height5 = tl->y - l->getExactHeight(tl->x, tl->z - 1);
                float diff1 = (fabs)(height2 - height3);
                float diff2 = (fabs)(height3 - height4);
                float diff3 = (fabs)(height4 - height5);
                if (diff1 < 0.4 && diff2 < 0.4 && diff3 < 0.4) {

                    if (fabs(l->getExactHeight(tl->x, tl->z) + SeaLevel) < 0.1) {
                        if (!OceanCrashSounded) {
                            float TempTest1 = fabs(l->getExactHeight(tl->x, tl->z));
                            sprintf(DebugBuf, "CrashGround(): Ocean Landing Impact. Altitude = %f,  SeaLevel = %f", TempTest1, SeaLevel);
                            display(DebugBuf, LOG_MOST);
                            sound->setVolume(SOUND_CRASHOCEAN00, 90);
                            sound->play(SOUND_CRASHOCEAN00, false);
                            Durability -= ((fplayer->realspeed * decfac * dt / timestep) * 15.0);
                            if (fplayer->UndercarriageLevel) {
                                Durability -= ((fplayer->realspeed * decfac * dt / timestep) * 190.0);
                            }
                            OceanCrashSounded = true;
                            LandedAtSafeSpeed = true;
                        }
                        // Stop player forward motion:
                        accx = 0;
                        accy = 0;
                        accz = 0;
                        fplayer->maxthrust *= 0.999;
                        //fplayer->thrust = 0.0;
                        fplayer->FuelLevel = 0.0;
                        fplayer->realspeed *= 0.99;
                        LandedAtSafeSpeed = true;
                    } else if (fplayer->UndercarriageLevel) {
                        if ((fabs(fplayer->theta)) < 5.0) {
                            Durability -= 0;
                            if (fplayer->thrust < 0.01) {

                                ClearSpeedHistoryArrayFlag = true;
                                fplayer->realspeed *= 0.9;
                                if (fplayer->realspeed < 0.04) {
                                    fplayer->realspeed = 0;
                                }
                                fplayer->thrust *= 0.9999;
                                fplayer->recthrust *= 0.9999;
                            }
                            if (TrueAirSpeed < 50.00 && (
                                fplayer->id == BOMBER_B17 ||
                                fplayer->id == BOMBER_B24 ||
                                fplayer->id == BOMBER_JU87 ||
                                fplayer->id == BOMBER_G5M ||
                                fplayer->id == BOMBER_B25 ||
                                fplayer->id == BOMBER_B26 ||
                                fplayer->id == BOMBER_B29 ||
                                fplayer->id == BOMBER_JU88 ||
                                fplayer->id == BOMBER_DORNIER ||
                                fplayer->id == BOMBER_HE111 ||
                                fplayer->id == BOMBER_LANCASTER
                                )
                                ) {
                                LandedAtSafeSpeed = true;
                                UpdateOnlineScoreLogFileWithLandings();

                                if (TakeoffLogged == true) {
                                    TakeoffLogged = false;
                                }
                            } else if (TrueAirSpeed < 29) {
                                LandedAtSafeSpeed = true;
                                fplayer->InertiallyDampenedPlayerSpeed = 0;
                                fplayer->accx = 0;
                                fplayer->accy = 0;
                                fplayer->accz = 0;
                                UpdateOnlineScoreLogFileWithLandings();

                                if (TakeoffLogged == true) {
                                    TakeoffLogged = false;
                                }
                            }
                            if (!TireSqueakSounded) {
                                sound->setVolume(SOUND_TIRESQUEAK1, 90);
                                sound->play(SOUND_TIRESQUEAK1, false);
                                TireSqueakSounded = true;
                                display((char*)"crashGround(): TireSqueakSounded.", LOG_MOST);
                            }
                        }
                        if ((fabs(fplayer->theta)) > 10.0 && (fplayer->realspeed > 0.03 && !LandedAtSafeSpeed)) {
                            Durability = -15;
                            fplayer->theta = 0;
                            sound->setVolume(SOUND_BELLYSCRAPE00, 90);
                            sound->play(SOUND_BELLYSCRAPE00, false);
                            display((char*)"crashGround(): BellyScrape Sounded due to sideways landing attempt.", LOG_MOST);
                        } else {
                            if (!WheelRolloutSounded) {
                                sound->setVolume(SOUND_WHEELROLLOUT00, 90);
                                sound->play(SOUND_WHEELROLLOUT00, false);
                                WheelRolloutSounded = true;
                                display((char*)"crashGround(): WheelRollout Sounded.", LOG_MOST);
                            }
                        }

                        if (fplayer->thrust > 1.0) {
                            unsigned char HistoryArrayPointer;

                            for (HistoryArrayPointer = 0; HistoryArrayPointer <= 9; HistoryArrayPointer++) {
                                SpeedHistoryArray[HistoryArrayPointer] = (fplayer->StallSpeed) * 0.6;
                            }
                        }
                    } else {
                        if (!BellyScrapeSounded) {
                            sound->setVolume(SOUND_BELLYSCRAPE00, 90);
                            sound->play(SOUND_BELLYSCRAPE00, false);
                            BellyScrapeSounded = true;
                            display((char*)"crashGround(): BellyScrape Sounded due to gear-up landing attempt.", LOG_MOST);
                        }
                        if (!GearUpDamageAlreadyInflicted) {
                            Durability -= fplayer->realspeed * decfac * dt * 28.0 / timestep;;
                            GearUpDamageAlreadyInflicted = true;
                            display((char*)"crashGround(): inflicting crash damage due to gear-up landing attempt.", LOG_MOST);
                        }
                        if (fplayer->gamma > 0) {
                            fplayer->gamma -= 2.0;
                            display((char*)"crashGround(): dropping gamma due to gear-up landing attempt.", LOG_MOST);
                            LandedAtSafeSpeed = true;
                            accx = 0;
                            accy = 0;
                            accz = 0;
                            fplayer->realspeed *= 0.99;
                        }

                    }
                } else {

                    Durability -= fplayer->realspeed * decfac * dt / timestep;
                    if (!LandingDamageSounded) {
                        sound->setVolume(SOUND_DAMAGE00, 90);
                        sound->play(SOUND_DAMAGE00, false);
                        LandingDamageSounded = true;
                        display((char*)"crashGround(): LandingDamage Sounded due to non-flat ground.", LOG_MOST);
                    }
                }
            } else {

                if (!LandedAtSafeSpeed) {
                    Durability -= fplayer->realspeed * decfac * dt / timestep;
                    if (!LandingDamageSounded) {
                        sound->setVolume(SOUND_DAMAGE00, 90);
                        sound->play(SOUND_DAMAGE00, false);
                        LandingDamageSounded = true;
                        display((char*)"crashGround(): LandingDamageSounded due to excessive landing speed.", LOG_MOST);
                    }
                }
                if (Durability < 0.5) {
                    setExplosion(0.2, 25 * timestep);
                    setBlackSmoke(0.5, 25 * timestep);
                    UpdateOnlineScoreLogFileWithCrashes();
                }
            }
        } else {

            if (id == BOMB01) {
                Durability -= decfac * dt / timestep;
            }
            if (realspeed > 0.33) {
                if (id != BOMB01) {
                    Durability -= decfac * dt / timestep;
                }
                if (Durability < 0 && (id >= FIGHTER1 && id <= FIGHTER2)) {
                    setExplosion(0.2, 25 * timestep);
                    setBlackSmoke(0.5, 25 * timestep);
                    active = false;
                }
            }
        }
    } else {
        if (this == (DynamicObj*)fplayer && ((height > zoom + 1.0))) {
            OnTheGround = false;
            PlayerCollidedWithAircraftCarrier = false;
            if (LandedAtSafeSpeed) {

                UpdateOnlineScoreLogFileWithTakeoffs();

                LandedAtSafeSpeed = false;
                Me163LandingTimer = 90000;
                LandingTimer = 0;
            }

            LandingLogged = false;
            GearUpDamageAlreadyInflicted = false;
            NoseWheelDamageInflicted = false;
            TireSqueakSounded = false;
            LandingDamageSounded = false;
            OceanCrashSounded = false;
            BellyScrapeSounded = false;
            WheelRolloutSounded = false;
        }
    }
}

void DynamicObj::deactivate() {
    active = false;
    draw = false;
}

void DynamicObj::dinit() {
    rot->a = 90;
    phi = 0;
    theta = 0;
    gamma = 180;
    rectheta = 0;
    tl->z = 0;
    tl->x = 0;
    forcex = 0;
    forcez = 0;
    forcey = 0;
    maxthrust = 0.3;
    braking = 0;
    manoeverability = 0.5;
    thrust = maxthrust;
    recthrust = thrust;
    recheight = 5.0;
    ttl = -1;
    Durability = 0.01F;
    maxDurability = 0.01F;
    immunity = 0;
    recgamma = 180;
    id = CANNON1;
    impact = 7;
    source = NULL;
    points = 0;
    party = 0;
    elevatoreffect = 0;
    ruddereffect = 0;
    rolleffect = 0;
    maxgamma = 70;
    maxtheta = 90;
    gamma = 180;
    theta = 0;
    explode = 0;
    sink = 0;
    RollRate = 1.0;
    fighterkills = 0;
    shipkills = 0;
    tankkills = 0;
    otherkills = 0;
    killed = false;
    realism = physics;
    accx = accy = accz = 0;
    DragEffect = 1.0;
}

float DynamicObj::distance(DynamicObj* target) {
    float dx = target->tl->x - tl->x;
    float dz = target->tl->z - tl->z;
    float dy = target->tl->y - tl->y;
    return sqrt(dx * dx + dz * dz + dy * dy);
}

float DynamicObj::distanceXZ(DynamicObj* target) {
    float dx = target->tl->x - tl->x;
    float dz = target->tl->z - tl->z;
    return sqrt(dx * dx + dz * dz);
}

DynamicObj::DynamicObj() {
    dinit();
}

DynamicObj::DynamicObj(Space* space2, CModel* o2, float zoom2) {
    this->space = space2;
    o = o2;
    zoom = zoom2;
    dinit();
    space->addObject(this);
}

// return heading difference towards enemy
int DynamicObj::getAngle(DynamicObj* o) {
    float dx2 = o->tl->x - tl->x, dz2 = o->tl->z - tl->z;
    int a, w = (int)phi;
    if (dz2 > -0.0001 && dz2 < 0.0001) {
        dz2 = 0.0001;
    }
    a = (int)(atan(dx2 / dz2) * 180 / PI);
    if (dz2 > 0) {
        if (dx2 > 0) {
            a -= 180;
        } else {
            a += 180;
        }
    }
    int aw = a - w;

    if (aw < -180) {
        aw += 360;
    }
    if (aw > 180) {
        aw -= 360;
    }
    return aw;
}

// return elevation difference towards enemy
int DynamicObj::getAngleH(DynamicObj* o) {
    float disttarget = distance(o);
    return (int)(atan((o->tl->y - tl->y) / disttarget) * 180 / PI - (gamma - 180));
}

void DynamicObj::move(Uint32 dt) {
    float DegreesToRadiansFactor = 0.01745333;
    float SpeedHistoryAccumulator = 0;
    unsigned char HistoryArrayPointer;
    if (dt <= 0) {
        return;
    }
    if (OnTheGround) {
        CalculateTrueAirspeed();
    }

    if (ViewResetTimer > 0) {
        ViewResetTimer += dt;
        if (ViewResetTimer > 2000) {
            view = ConfiguredViewDistance;
            ViewResetTimer = 0;
        }
    }
    if (realspeed <= 0) {
        realspeed = 1.0F;
    }
    float brakepower = 1.0F;
    float timefac = (float)dt / (float)timestep;
    checkExplosion(dt); // check if this object is exploding
    if (sink > 0)   // only ships (they will not explode)
    {
        tl->y -= 0.02 * timefac; // sink down
        gamma = recgamma = 180.0 + 0.5 * (float)sink / timestep; // change angle when sinking
        return; // and exit move()
    }
    if (!active && !draw) {
        return;    // exit if not active
    }
    if (id == BOMB01) {

        unsigned char CycleLimit = 11;
        if (tl->y < 410) // 17,000 feet
        {
            CycleLimit = 7;
        } else if (337.0) {
            CycleLimit = 10;
        } else if (265.0) {
            CycleLimit = 15;
        } else if (193.0) {
            CycleLimit = 19;
        } else if (120.0) {
            CycleLimit = 30;
        } else if (83.0) {
            CycleLimit = 48;
        } else if (41.5) {
            CycleLimit = 130;
        }
        static unsigned char Cycle = 0;
        Cycle++;
        if (Cycle == CycleLimit) {
            tl->y -= dt / 10;
            Cycle = 0;
        }
        recgamma -= dt / 12;
        gamma -= dt / 12;
        if (recgamma < 108) {
            recgamma = 108;
        }
        if (gamma < 108) {
            gamma = 108;
        }
    }
    if (id >= STATIC_PASSIVE)   // only buildings, static objects
    {
        // set the correct angles to diplay
        rot->setAngles((short)(90 + gamma - 180), (short)theta + 180, (short)-phi);
        checkDurability();
        return; // and exit this function
    }
    if (id == FLARE1)   // only flares
    {
        tl->y -= 0.04 * timefac; // fall down (gravity, constant)
        zoom = 0.12F + 0.03F * sin((float)ttl / (float)timestep / 15); // blink (high frequency)
        phi = camphi; // angles to viewer (player)
        theta = 0;
        gamma = camgamma;
    }
    if (id == CHAFF1)   // only chaff
    {
        tl->y -= 0.04 * timefac; // fall down (gravity, constant)
        zoom = 0.12F + 0.01F * (80 * timestep - ttl) / timestep; // spread out
        phi = camphi; // angles to viewer (player)
        theta = 0;
        gamma = camgamma;
    }
    (void)checkLooping();
    // The core of directional alterations and force calculations:
    int vz = 1;
    if (gamma < 90 || gamma > 270) {
        vz = -1;
    }

    if (maxthrust + thrust <= -0.00001 || maxthrust + thrust >= 0.00001) {

        if ((id != BOMB01) && (id != MISSILE_DF1)) {
            phi += vz * SIN(theta) * elevatoreffect * manoeverability * (3.33 + 15.0 * realspeed) * timefac;
            gamma += COS(theta) * elevatoreffect * manoeverability * (3.33 + 15.0 * realspeed) * timefac;
            phi += -vz * COS(theta) * ruddereffect * manoeverability * (0.66 + 3.0 * realspeed) * timefac;
            gamma += SIN(theta) * ruddereffect * manoeverability * (0.66 + 3.0 * realspeed) * timefac;
            // change roll due to roll ;-)
            if (rolleffect) {
                theta += rolleffect * (RollRate * (1.0 + realspeed)) * timefac * 5.0F;
                rectheta = theta;
            }
        }
    }
    if (phi < 0) {
        phi += 360.0;    // validate heading
    } else if (phi >= 360.0) {
        phi -= 360.0;
    }
    if (theta < -180 && rectheta < -180) {
        rectheta += 360;
        theta += 360;
    } else if (theta >= 180 && rectheta >= 180) {
        rectheta -= 360;
        theta -= 360;
    }
    if ((recthrust > maxthrust) && (gamma > 180.0) && (difficulty < 3)) { // Prevent recthrust exceeding maxthrust unless descending
        recthrust = maxthrust;
    }
    //
    // Now adjust thrust upward if the requested value is higher
    // than the actual value, and downward if the requested value
    // is lower than the actual value. The size of the adjustment
    // is inversely proportional to our inertia, so it takes longer
    // for heavier aircraft to accumulate or dissipate thrust than
    // for less massive aircraft.
    //
    float throttlechange;
    if ((difficulty > 3) && (id > FIGHTER1)) {
        throttlechange = maxthrust / (100 * inertia) * timefac;
    } else {
        throttlechange = maxthrust / 100 * timefac;
    }
    if (throttlechange < (maxthrust / 100)) {
        if (OnTheGround) {
            throttlechange = maxthrust / 100;
        }
    }

    if (recthrust > thrust + throttlechange) {
        thrust += (throttlechange);
    } else if (recthrust < thrust - throttlechange) {
        thrust -= (throttlechange);
    }

    if (NetworkOpponent && (MissionNumber == MISSION_HEADTOHEAD00)) {

        ThreeDObjects[MissionHeadToHead00State]->realspeed = InPacket.UdpObjSpeed;
        ThreeDObjects[MissionHeadToHead00State]->thrust = InPacket.UdpObjThrust;
        ThreeDObjects[MissionHeadToHead00State]->recthrust = InPacket.UdpObjThrust;
    }
    // PHYSICS (simplified model)
    CVector3 vaxis, uaxis, utemp, utemp2, utemp3;
    float gammaup, phiup, thetaup, RealSpeedTemp2;
    bool stop;
    float gravityforce;
    if (id <= CANNON2) {
        tl->x += forcex * timefac; // add our vector to the translation
        tl->z += forcez * timefac;
        tl->y += forcey * timefac;
        goto cannondone; // jump down to decrease ttl and test collision
    }

    vaxis.set(COS(gamma) * SIN(phi), SIN(gamma), COS(gamma) * COS(phi));
    if (realism) {

        gammaup = gamma + 90;
        thetaup = -theta;
        phiup = phi;
        uaxis.set(COS(gammaup) * SIN(phiup), SIN(gammaup), COS(gammaup) * COS(phiup)); // upward axis (theta = 0)

        utemp.take(&uaxis);
        utemp.mul(COS(thetaup));
        utemp2.take(&vaxis);
        utemp2.mul((1 - COS(thetaup)) * uaxis.dotproduct(&vaxis));
        utemp3.take(&uaxis);
        utemp3.crossproduct(&vaxis);
        utemp3.mul(SIN(thetaup));
        utemp.add(&utemp2);
        utemp.add(&utemp3);
        uaxis.take(&utemp);

        braking = (fabs(ruddereffect * 20.0) + fabs(elevatoreffect * 35.0) + fabs(rolleffect * 18.0) + fplayer->DragEffect) / 200;
        brakepower = pow(0.93 - braking, timefac);

        accx *= brakepower;
        accy *= brakepower;
        accz *= brakepower;

        accz += thrust * vaxis.z * 0.3 * timefac;
        accx += thrust * vaxis.x * 0.3 * timefac;
        accy -= thrust * vaxis.y * 0.1 * timefac;

        accz += thrust * uaxis.z * 0.067 * timefac;
        accx += thrust * uaxis.x * 0.067 * timefac;
        accy -= thrust * uaxis.y * 0.067 * timefac * cos((fplayer->theta) * DegreesToRadiansFactor);

        accy -= 0.015 * timefac;

        accy -= fplayer->deadweight * timefac;

        if (this == (DynamicObj*)fplayer) {
            accy += sin((gamma - 180) * DegreesToRadiansFactor) * ((fplayer->InertiallyDampenedPlayerSpeed) / 0.8);
        } else if (id == BOMB01) {

            accy += sin((gamma - 180) * DegreesToRadiansFactor) * (BombReleaseVelocity);
            tl->y += accy / 3.0;
        } else {
            accy += sin(((gamma - 180) * DegreesToRadiansFactor) * (realspeed / 0.8));
        }

        if (this == (DynamicObj*)fplayer) {
            accx -= sin(fplayer->phi * DegreesToRadiansFactor) * ((fplayer->realspeed));
            accz -= cos(fplayer->phi * DegreesToRadiansFactor) * ((fplayer->realspeed));
        } else {
            accx -= sin(phi * DegreesToRadiansFactor) * ((realspeed));
            accz -= cos(phi * DegreesToRadiansFactor) * ((realspeed));
        }
        float stepfac = 0.24;
        tl->x += accx * timefac * stepfac;
        tl->z += accz * timefac * stepfac;
        tl->y += accy * timefac * stepfac;
        float scalef = 1.1;
        forcex = accx * stepfac * scalef;
        forcey = accy * stepfac * scalef;
        forcez = accz * stepfac * scalef;

        gravityforce = sqrt(realspeed) * vaxis.y * 1.10 * timefac;
        forcez += gravityforce * vaxis.z;
        forcex += gravityforce * vaxis.x;
        forcey += gravityforce * vaxis.y;

        forcey -= gravityforce * vaxis.y * 2.2;
    }
    stop = false;
    if (id >= TANK1 && id <= TANK2)   // tanks cannot climb steep faces
    {
        float newy = l->getExactHeight(tl->x + forcex, tl->z + forcez) + zoom / 2;

        if (fabs(newy - tl->y) > 0.05) {
            stop = true;
        } else if (fabs(newy - tl->y) > 2) {
            stop = false;
        }
    }
    //
    //  InertiaEffects
    //

    InertiaTimer += DeltaTime;

    unsigned static char InertiaPhase;

    if (InertiaTimer < (1000 * inertia)) {
        InertiaPhase = 0;
    } else if (InertiaTimer < (2000 * inertia)) {
        InertiaPhase = 1;
    } else if (InertiaTimer < (3000 * inertia)) {
        InertiaPhase = 2;
    } else if (InertiaTimer < (4000 * inertia)) {
        InertiaPhase = 3;
    } else if (InertiaTimer < (5000 * inertia)) {
        InertiaPhase = 4;
    } else if (InertiaTimer < (6000 * inertia)) {
        InertiaPhase = 5;
    } else if (InertiaTimer < (7000 * inertia)) {
        InertiaPhase = 6;
    } else if (InertiaTimer < (8000 * inertia)) {
        InertiaPhase = 7;
    } else if (InertiaTimer < (9000 * inertia)) {
        InertiaPhase = 8;
    } else if (InertiaTimer < (10000 * inertia)) {
        InertiaPhase = 9; // Last of 10 phases is phase "9".
    }

    SpeedHistoryArray[InertiaPhase] = (fplayer->realspeed);

    if (RecoveredFromStall) {
        for (HistoryArrayPointer = 0; HistoryArrayPointer <= 9; HistoryArrayPointer++) {
            SpeedHistoryArray[HistoryArrayPointer] = fplayer->StallSpeed;
            RecoveredFromStall = false;
        }
    }

    if (ClearSpeedHistoryArrayFlag) {
        for (HistoryArrayPointer = 0; HistoryArrayPointer <= 9; HistoryArrayPointer++) {
            SpeedHistoryArray[HistoryArrayPointer] = fplayer->StallSpeed / 1000.0;
            ClearSpeedHistoryArrayFlag = false;
        }
    }

    for (HistoryArrayPointer = 0; HistoryArrayPointer <= 9; HistoryArrayPointer++) {
        SpeedHistoryAccumulator += SpeedHistoryArray[HistoryArrayPointer];
    }

    InertiallyDampenedPlayerSpeed = SpeedHistoryAccumulator / 10;

    if (InertiaTimer > (int)(10000.0 * inertia)) {
        InertiaTimer = 0;
    }

    if (!fplayer->ai) {
        TestAltitudeAirDensity();
        forcex /= AirDensityDrag;
        forcey /= AirDensityDrag;
        forcez /= AirDensityDrag;

        TestForExcessGamma();
        forcex /= GammaDrag;
        forcey /= GammaDrag;
        forcez /= GammaDrag;

        TestForLoopBeyondVertical();
        forcex /= LoopedBeyondVerticalDrag;
        forcey /= LoopedBeyondVerticalDrag;
        forcez /= LoopedBeyondVerticalDrag;
        TestDiveSpeedStructuralLimit();
        forcex /= SpeedBeyondStructuralLimitsDrag;
        forcey /= SpeedBeyondStructuralLimitsDrag;
        forcez /= SpeedBeyondStructuralLimitsDrag;
        TestForFlapEffects();
        forcex /= FlapDrag;
        forcey /= FlapDrag;
        forcez /= FlapDrag;
        TestForUndercarriageEffects();
        forcex /= UndercarriageDrag;
        forcey /= UndercarriageDrag;
        forcez /= UndercarriageDrag;
        TestForSpeedBrakeDrag();
        forcex /= SpeedBrakeDrag;
        forcey /= SpeedBrakeDrag;
        forcez /= SpeedBrakeDrag;
        RegulateXYZForces(forcex, forcey, forcez);
        forcex = RegulatedForceX;
        forcey = RegulatedForceY;
        forcez = RegulatedForceZ;
        RegulateGamma();

    }
    RealSpeedTemp2 = ((forcex * forcex) + (forcez * forcez) + (forcey * forcey));
    if (RealSpeedTemp2 == 0) {
        RealSpeedTemp2 = 0.001;
    }
    realspeed = sqrt(RealSpeedTemp2);
    if (!fplayer->ai) {

        realspeed = (realspeed + InertiallyDampenedPlayerSpeed) / 2;
        TestForWindNoise();
    }
    // objects moving on the ground should always change their elevation due to the surface
    if (id >= TANK1 && id <= TANK2 && thrust > 0 && !stop) {
        float newy = l->getExactHeight(tl->x, tl->z) + zoom / 2;
        float dy = newy - tl->y + forcey;
        float dx = fabs(forcex) + fabs(forcez);
        float gamma2 = 0;
        if (fabs(dx) > 0.0001) {
            gamma2 = atan(dy / dx);
        }
        gamma = 180.0 + 180.0 / PI * gamma2;
        tl->y = newy;
    }
    // set angles to correctly display the object
    rot->setAngles((short)(90 + gamma - 180), (short)theta + 180, (short)-phi);
cannondone:
    ;
    if (ttl > 0) {
        ttl -= dt;
        if (ttl <= 0) {
            ttl = -1;
            if (id >= MISSILE1 && id <= MISSILE2) {
                recheight = -10;    // missiles drop
            } else {
                deactivate();    // cannon shots vanish
            }
        }
    }

    checkDurability(); // check Durability issues
    crashGround(dt); // check ground collision
    if (immunity > 0) {
        immunity -= dt;
    }
}

void DynamicObj::setBlackSmoke(float maxzoom, int len) {
    int i;
    for (i = 0; i < maxblacksmoke; i++) // search a free blacksmoke instance
        if (blacksmoke[i]->ttl <= 0) {
            break;
        }
    if (i >= maxblacksmoke) {
        i = 0;
    }
    blacksmoke[i]->setBlackSmoke(tl->x, tl->y, tl->z, phi, maxzoom, len);
}

void DynamicObj::setExplosion(float maxzoom, int len) {
    int i;
    for (i = 0; i < maxexplosion; i++) // search a free explosion instance
        if (explosion[i]->ttl <= 0) {
            break;
        }
    if (i >= maxexplosion) {
        i = 0;
    }
    if (id >= CANNON1 && id <= CANNON2) {

        explosion[i]->setExplosion(tl->x, tl->y + 1.0, tl->z, forcex, forcey, forcez, maxzoom / 2, len);
    } else if (id == MISSILE_DF1) {
        explosion[i]->setExplosion(tl->x, tl->y, tl->z, forcex, forcey, forcez, tl->y * 0.4, len);
    } else if (id == BOMB01) {
        explosion[i]->setExplosion(tl->x, tl->y, tl->z, forcex, forcey, forcez, tl->y * 0.9, len);
    } else if (id == STATIC_AIRFIELD00) {
        ;
    } else {
        explosion[i]->setExplosion(tl->x, tl->y, tl->z, forcex, forcey, forcez, maxzoom, len);
    }
}

void DynamicObj::thrustDown() {
    recthrust -= maxthrust / 12;
    if (recthrust < maxthrust / 100) {
        recthrust = maxthrust / 100;
    }
    //sprintf (DebugBuf, "DynamicObj::thrustDown(): recthrust = %f.", recthrust);
    //display (DebugBuf, LOG_MOST);
}

void DynamicObj::thrustUp() {
    recthrust += maxthrust / 12;
    if ((recthrust > maxthrust) && (gamma > 180.0) && (difficulty < 3)) {
        recthrust = maxthrust;
    }
}

