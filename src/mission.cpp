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

#include <stdio.h>
#include <string.h>

#include "aiobject.h"
#include "common.h"
#include "conf.h"
#include "glland.h"
#include "mission.h"
#include "main.h"
#include "mathtab.h"
#include "NetworkApi.h"

extern bool AirfieldRepairRateNormalForBlueTeam;
extern bool AirfieldRepairRateNormalForRedTeam;
extern bool AirfieldRepairsAcceleratedForBlueTeam;
extern bool AirfieldRepairsAcceleratedForRedTeam;
extern bool AirfieldRepairsStoppedForBlueTeam;
extern bool AirfieldRepairsStoppedForRedTeam;
extern bool AllBlueTeamAirfieldsAreHeavilyDamaged;
extern bool AllRedTeamAirfieldsAreHeavilyDamaged;
extern bool AutoPilotActive;
extern bool ClearSpeedHistoryArrayFlag;
extern bool LandedAtSafeSpeed;
extern bool MissionRunning;
extern bool NetworkPlayerKilled;
extern bool NewSystemMessageNeedsScrolling;
extern bool MumbleManagement;
extern bool NoMissionHasYetCommenced;
extern bool OnTheGround;
extern bool PeerPacketReceivedInThisMissionState;
extern bool RadarReflectorBlueHasBeenDestroyedAtLeastOnce;
extern bool RadarReflectorRedHasBeenDestroyedAtLeastOnce;
extern bool ReturnedToCombat;
extern bool WindNoiseOn;

extern char DebugBuf[];
extern char MumbleStringR0Mission1Blue[128];
extern char MumbleStringR0Mission1Red[128];
extern char MumbleStringR0Mission2Blue[128];
extern char MumbleStringR0Mission2Red[128];
extern char MumbleStringR0Mission3Blue[128];
extern char MumbleStringR0Mission3Red[128];
extern char SystemMessageBufferA[];

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
extern unsigned char MissionChronoMilestone;
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
extern unsigned char MissionObjectHqBlue;
extern unsigned char MissionObjectHqRed;
extern unsigned char MissionObjectRadarBlue1;
extern unsigned char MissionObjectRadarRed1;
extern unsigned char MissionObjectRadarBlue2;
extern unsigned char MissionObjectRadarRed2;
extern unsigned char MissionObjectRadarBlue3;
extern unsigned char MissionObjectRadarRed3;
extern unsigned char MissionObjectRadarBlue4;
extern unsigned char MissionObjectRadarRed4;
extern unsigned char MissionObjectRadarHqBlue;
extern unsigned char MissionObjectRadarHqRed;
extern unsigned char MissionOutPacketCount;
extern unsigned char MissionStateNetworkBattle;
extern unsigned char MumbleChannelPresumed;
extern unsigned char MyNetworkId;
extern unsigned char NetworkApiVersion;
extern unsigned char NetworkOpponent;
extern unsigned char NewestInPacketId;
extern unsigned char PriorChronoMilestone;
extern unsigned char SelectedMissionTarget;
extern unsigned char StaticUpdateSwitcher;

extern char MorseCharacterOut[16];

extern int AirfieldXCenter;
extern int AirfieldXMax;
extern int AirfieldXMin;
extern int AirfieldYCenter;
extern int AirfieldYMax;
extern int AirfieldYMin;
extern int BattleDamageRiskTimer;
extern int HudLadderBarsOnOff;
extern int HudOnOff;
extern int IffOnOff;
extern int lastDurability;
extern int MissionAircraftDamaged;
extern int MapViewOnOff;
extern int MissionEndingTimer;
extern int MissionEndingTimer2;
extern int MissionNetworkBattle01PriorAircraft[];
extern int MissionNetworkBattle02PriorAircraft[];
extern int MissionNetworkBattle03PriorAircraft[];
extern int MissionNetworkBattle04PriorAircraft[];
extern int MissionNetworkBattle05PriorAircraft[];
extern int MissionNetworkBattle06PriorAircraft[];
extern int MissionNetworkBattle07PriorAircraft[];
extern int MissionNetworkBattle08PriorAircraft[];
extern int MissionNetworkBattle09PriorAircraft[];
extern int MissionNetworkBattle10PriorAircraft[];
extern int MissionNumber;
extern int NetworkMode; // Mode 0 = PeerToPeer. Mode 1 = ClientServer.
extern int NetworkTransmitTimer;
extern int NetworkTransmitTimerInterval;
extern int PlayerAircraftType;
extern int PlayersOriginalDurability;
extern int PriorStateEndTimer;
extern int RadarOnOff;
extern int RadarWasOn;
extern int RadarZoom;
extern int StateTransitionTimer;
extern int StaticObjectUpdateTimer;
extern int TrimElevatorSetting;
extern int TrimRudderSetting;

extern unsigned int key_DROPCHAFF;
extern unsigned int key_DROPFLARE;
extern unsigned int key_PRIMARY;
extern unsigned int key_RadarZoomIn;
extern unsigned int key_RadarZoomOut;
extern unsigned int key_SECONDARY;
extern unsigned int key_TARGETNEXT;
extern unsigned int key_TARGETPREVIOUS;
extern unsigned int key_WEAPONSELECT;
extern unsigned int MissedPacketCount;
extern unsigned int MissionTenSecondTimer;
extern unsigned int NetworkReceiveTimer;
extern unsigned int NetworkReceiveTimerInterval;
extern unsigned int RefuelRearmRepairDurationTimer;

extern Uint32 DeltaTime;
extern Uint32 LandingTimer;
extern Uint32 Me163LandingTimer;
extern Uint32 MissionNetworkBattle01Timer;
extern Uint32 MissionNetworkBattle02Timer;
extern Uint32 MissionNetworkBattle03Timer;
extern Uint32 MissionNetworkBattle04Timer;
extern Uint32 MissionNetworkBattle05Timer;
extern Uint32 MissionNetworkBattle06Timer;
extern Uint32 MissionNetworkBattle07Timer;
extern Uint32 MissionNetworkBattle08Timer;
extern Uint32 MissionNetworkBattle09Timer;
extern Uint32 MissionNetworkBattle10Timer;
extern Uint32 MissionNetworkBattleRadarTimer;
extern Uint32 MumbleCommandTimer;
extern Uint32 MumbleTimeRemainingBeforeChannelReset;
extern Uint32 NetworkApiPriorTimer[32];

extern long MilestoneCorrectionTimer;

extern float AutoPilotAltitude;
extern float blackout;
extern float CalculatedDamageDueToCurrentRisk;
extern float DamageToClaim;
extern float FratricideShameFactor;
extern float FuelLevelAtLastLanding;
extern float NetDeltaX[32];
extern float NetDeltaY[32];
extern float NetDeltaZ[32];
extern float NetXErr[32];
extern float NetYErr[32];
extern float NetZErr[32];
extern float PlayersOriginalMaxGamma;
extern float PlayersOriginalRollRate;
extern float PlayersOriginalMaxThrust;
extern float ThrustReadiness;
extern float redout;
extern float ScreenFOVx;
extern float ScreenFOVy;
extern float SeaLevel;
extern float ThrustFactor[32];

extern float NetworkApiPriorXPosition[];
extern float NetworkApiPriorYPosition[];
extern float NetworkApiPriorZPosition[];

extern LacUdpApiPacket InPacket;
extern LacUdpApiPacket OutPacket;

extern int  DiscardAnyInPacketsInQueue();
extern int  GetNetworkApiPacket();
extern int  OpenClientUdpSocket();
extern int  OpenUdpSocketForReceiving();
extern int  OpenUdpSocketForSending();

bool TestForSentience(unsigned char PlayerNumber);

extern void CleanPlayerIdStrings();
extern void event_CommsMacro01();
extern void event_CommsMacro02();
extern void event_CommsMacro03();
extern void event_CommsMacro04();
extern void event_CommsMacro05();
extern void event_CommsMacro06();
extern void event_CommsMacro07();
extern void event_CommsMacro08();
extern void event_CommsMacro09();
extern void event_CommsMacro10();
extern void event_CommsMacro17();
extern void ConfigureClientUdpSocket();
extern void ConfigureIncomingUdpSocket();
extern void ConfigureOutgoingUdpSocket();
extern void DegradeFlightModelDueToOrdnanceLoad();
extern void event_HudLadderBarsOnOff();
extern void event_IffOnOff();
extern void event_MapViewOnOff();
extern void event_MapZoomIn();
extern void event_RadarOnOff();
extern void event_RadarZoomIn();
extern void event_RadarZoomOut();
extern void event_targetNextRed();
extern void event_targetPreviousBlue();
extern void event_targetVocalize();
extern void event_thrustUp();
extern void event_ToggleUndercarriage();
extern void event_TrimElevatorDn();
extern void event_TrimElevatorUp();
extern void event_ZoomFovOut();
extern void game_quit();
extern void LoadServerIpAddress();
extern void LoadVariablesFromNetworkApiPacket();
extern void MumbleChannelChange(char MumbleUrl[]);
extern void SendNetworkApiPacket();
extern void event_UnMuteMorseAll();
extern void UpdateOnlineScoreLogFileWithCalculatedRisks();
extern void UpdateOnlineScoreLogFileWithNewSorties();
extern void VocalizeBlueHqStatus();
extern void VocalizeRedHqStatus();

bool MissionHeadToHead00RetrieveFirstDamageDescription();
bool MissionNetworkBattle01RetrieveFirstDamageDescription();
bool MissionNetworkBattle02RetrieveFirstDamageDescription();
bool MissionNetworkBattle03RetrieveFirstDamageDescription();
bool MissionNetworkBattle04RetrieveFirstDamageDescription();
bool MissionNetworkBattle05RetrieveFirstDamageDescription();
bool MissionNetworkBattle06RetrieveFirstDamageDescription();
bool MissionNetworkBattle07RetrieveFirstDamageDescription();
bool MissionNetworkBattle08RetrieveFirstDamageDescription();
bool MissionNetworkBattle09RetrieveFirstDamageDescription();
bool MissionNetworkBattle10RetrieveFirstDamageDescription();

int AirfieldRepairsAcceleratedForRedTeamTimer = 0;
int AirfieldRepairsAcceleratedForBlueTeamTimer = 0;
int AirfieldRepairsStoppedForBlueTeamTimer = 0;
int AirfieldRepairsStoppedForRedTeamTimer = 0;

float DegreesToRadiansFactor = -0.01745333;

void DetermineCurrentAirfield();
void MissionHeadToHead00LoadVariablesFromNetworkApiPacket(int);
void ProcessUdpObjFlightDetails();
void LoadVariablesFromNetworkApiPacket(int);
void RearmRefuelRepair();

void ArmPlayerAtRequestedField() {
    display((char*)"Function Entry: ArmPlayerAtRequestedField()", LOG_MOST);
    sprintf(DebugBuf, "ArmPlayerAtRequestedField() AirfieldRequested = %d\n", AirfieldRequested);
    display(DebugBuf, LOG_MOST);
    sprintf(DebugBuf, "fplayer->missiles[0] = %d\n", fplayer->missiles[0]);
    display(DebugBuf, LOG_MOST);
    if (MyNetworkId % 2) {
        display((char*)"ArmPlayerAtRequestedField() RedTeam", LOG_MOST);
        fplayer->party = 1;
        if (AirfieldRequested == 1) {
            display((char*)"ArmPlayerAtRequestedField() SPAWNING AT RED HQ", LOG_MOST);
            fplayer->tl->x = 400;
            fplayer->tl->z = 5.00;
        }
        if (AirfieldRequested == 2) {
            display((char*)"ArmPlayerAtRequestedField() SPAWNING AT RED FIELD2", LOG_MOST);
            fplayer->tl->x = 900;
            fplayer->tl->z = 5.00;
        }
        if (AirfieldRequested > 2) {
            display((char*)"ArmPlayerAtRequestedField() RedTeam Field > 2", LOG_MOST);
            if (fplayer->missiles[0] >= 6) {
                AirfieldRequested = 4;
                display((char*)"ArmPlayerAtRequestedField() SPAWNING AT RED FIELD4", LOG_MOST);
                fplayer->tl->x = 1900;
                fplayer->tl->z = 5.00;
            } else {
                AirfieldRequested = 3;
                display((char*)"ArmPlayerAtRequestedField() SPAWNING AT RED FIELD3", LOG_MOST);
                fplayer->tl->x = 1400;
                fplayer->tl->z = 5.00;
            }

            if (fplayer->id == BOMBER_B29) {
                display((char*)"ArmPlayerAtRequestedField() SPAWNING RedTeam B29 AT RED FIELD5", LOG_MOST);
                fplayer->tl->x = 2300;
                fplayer->tl->z = 5.00;
            }
        }
    } else {
        display((char*)"ArmPlayerAtRequestedField() BlueTeam", LOG_MOST);
        fplayer->party = 0;
        if (AirfieldRequested == 1) {
            display((char*)"ArmPlayerAtRequestedField() SPAWNING AT BLUE HQ", LOG_MOST);
            fplayer->tl->x = -500;
            fplayer->tl->z = 5.00;
        }
        if (AirfieldRequested == 2) {
            display((char*)"ArmPlayerAtRequestedField() SPAWNING AT BLUE FIELD2", LOG_MOST);
            fplayer->tl->x = -1000;
            fplayer->tl->z = 5.00;
        }
        if (AirfieldRequested > 2) {
            display((char*)"ArmPlayerAtRequestedField() BlueTeam Field > 2", LOG_MOST);
            if (fplayer->missiles[0] >= 6) {
                AirfieldRequested = 4;
                display((char*)"ArmPlayerAtRequestedField() SPAWNING AT BLUE FIELD4", LOG_MOST);
                fplayer->tl->x = -2000;
                fplayer->tl->z = 5.00;
            } else {
                AirfieldRequested = 3;
                display((char*)"ArmPlayerAtRequestedField() SPAWNING AT BLUE FIELD3", LOG_MOST);
                fplayer->tl->x = -1500;
                fplayer->tl->z = 5.00;
            }

            if (fplayer->id == BOMBER_B29) {
                display((char*)"SPAWNING BlueTeam B29 AT BLUE FIELD5", LOG_MOST);
                fplayer->tl->x = -2400;
                fplayer->tl->z = 5.00;
            }
        }
    }
}

void AutoPilot() {
    if (AutoPilotActive) {
        float AltitudeDifferential = ThreeDObjects[0]->tl->y - AutoPilotAltitude;
        if (fabs(AltitudeDifferential) < 10) {
            TrimElevatorSetting /= 2;
        }
        float GammaDifferential = ThreeDObjects[0]->gamma - 180;
        if (fabs(GammaDifferential) < 1) {
            TrimElevatorSetting /= 2;
        }
        if (AltitudeDifferential < 4) {
            TrimElevatorSetting += (int)(AltitudeDifferential * -20);
        }
        if (AltitudeDifferential > 4) {
            TrimElevatorSetting -= (int)(AltitudeDifferential * 20);
        }

        if (TrimElevatorSetting > 2000) {
            TrimElevatorSetting = 2000;
        }
        if (TrimElevatorSetting < -2000) {
            TrimElevatorSetting = -2000;
        }

        if (ThreeDObjects[0]->gamma > 190) {
            ThreeDObjects[0]->gamma = 190;
            TrimElevatorSetting /= 2;
        }
        if (ThreeDObjects[0]->gamma < 170) {
            ThreeDObjects[0]->gamma = 170;
            TrimElevatorSetting /= 2;
        }

        if (ThreeDObjects[0]->theta > 5) {
            ThreeDObjects[0]->theta -= 2;
        } else if (ThreeDObjects[0]->theta < -5) {
            ThreeDObjects[0]->theta += 2;
        }
        if (ThreeDObjects[0]->theta > 2) {
            ThreeDObjects[0]->theta -= 0.5;
        } else if (ThreeDObjects[0]->theta < -2) {
            ThreeDObjects[0]->theta += 0.5;
        }
        if (TrimRudderSetting != 0) {
            ThreeDObjects[0]->theta = TrimRudderSetting * -0.0005;
        }
    }
}

void CalcDamageRiskFromNearbyOpposition() {
    static float CalculatedDamageFromAirfields = 0;
    static float CalculatedDamageFromAircraft[11] = { 0 };
    static float CalculatedDamageFromBatteries = 0;
    static float CalculatedDamageFromBattleships = 0;
    static float CalculatedDamageFromDestroyers = 0;
    unsigned char Mission3dObject;
    float XDisplacementTemp;
    float YDisplacementTemp;
    float ZDisplacementTemp;
    float TotalXYZDisplacement;
    float HostileDamageState;
    float JinkingStrength = 0;
    CalculatedDamageDueToCurrentRisk = 0;
    for (Mission3dObject = 1; Mission3dObject <= 29; Mission3dObject++) {
        if (ThreeDObjects[Mission3dObject]->active == true && Mission3dObject % 2 != MyNetworkId % 2) {
            XDisplacementTemp = fabs(fplayer->tl->x - ThreeDObjects[Mission3dObject]->tl->x);
            if (XDisplacementTemp < 90.0) {
                ZDisplacementTemp = fabs(fplayer->tl->z - ThreeDObjects[Mission3dObject]->tl->z);
                if (ZDisplacementTemp < 90.0) {
                    YDisplacementTemp = fabs(fplayer->tl->y - ThreeDObjects[Mission3dObject]->tl->y);
                    if (YDisplacementTemp < 400) {
                        TotalXYZDisplacement = XDisplacementTemp + YDisplacementTemp / 2 + ZDisplacementTemp;
                        if (TotalXYZDisplacement < 5.0) {
                            TotalXYZDisplacement = 5.0;
                        }
                        if (
                            (
                                (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) ||
                                (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) ||
                                (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) ||
                                (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY)
                                )
                            &&
                            fplayer->tl->y > (SeaLevel - 30)
                            ) {

                            if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                CalculatedDamageFromAirfields = 4800 / TotalXYZDisplacement;
                                CalculatedDamageFromAirfields *= ((ThreeDObjects[Mission3dObject]->Durability) / (ThreeDObjects[Mission3dObject]->maxDurability));
                            } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                CalculatedDamageFromBatteries = 2000 / TotalXYZDisplacement;
                            } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                CalculatedDamageFromBattleships = 4800 / TotalXYZDisplacement;
                            } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                CalculatedDamageFromDestroyers = 2000 / TotalXYZDisplacement;
                            }
                            if (
                                fplayer->id == BOMBER_B17 ||
                                fplayer->id == BOMBER_B24 ||
                                fplayer->id == BOMBER_G5M ||
                                fplayer->id == BOMBER_HE111 ||
                                fplayer->id == BOMBER_LANCASTER ||
                                fplayer->id == BOMBER_B29
                                ) {
                                if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                    CalculatedDamageFromAirfields *= 20; // Big Bombers get hit more often.
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                    CalculatedDamageFromBatteries *= 20;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                    CalculatedDamageFromBattleships *= 20;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                    CalculatedDamageFromDestroyers *= 20;
                                }
                                display((char*)"CalcDamageRiskFromNearbyOpposition() 20x big target penalty.", LOG_MOST);
                            } else if (
                                fplayer->id == BOMBER_B25 ||
                                fplayer->id == BOMBER_B26 ||
                                fplayer->id == BOMBER_B5N ||
                                fplayer->id == BOMBER_DAUNTLESS ||
                                fplayer->id == BOMBER_DORNIER ||
                                fplayer->id == BOMBER_JU87 ||
                                fplayer->id == BOMBER_JU88 ||
                                fplayer->id == BOMBER_MOSQUITOB ||
                                fplayer->id == BOMBER_SB2C ||
                                fplayer->id == BOMBER_TBF
                                ) {
                                if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                    CalculatedDamageFromAirfields *= 7; // Medium bombers are also easier to hit.
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                    CalculatedDamageFromBatteries *= 7; // Medium bombers are also easier to hit.
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                    CalculatedDamageFromBattleships *= 7; // Medium bombers are also easier to hit.
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                    CalculatedDamageFromDestroyers *= 7; // Medium bombers are also easier to hit.
                                }
                                display((char*)"CalcDamageRiskFromNearbyOpposition() 7x Medium bomber penalty.", LOG_MOST);
                            }
                            int volume = (int)(
                                (
                                    CalculatedDamageFromAirfields +
                                    CalculatedDamageFromBattleships +
                                    CalculatedDamageFromDestroyers +
                                    CalculatedDamageFromBatteries
                                    ) * 18
                                ) - 110;
                            // Prevent excessive acoustic volume to avoid distortion. 127 is absolute max, but lower is safer!
                            if (volume > 80) {
                                volume = 80;
                            }
                            if (volume < 0) {
                                volume = 0;
                            }

                            HostileDamageState = ThreeDObjects[Mission3dObject]->Durability / ThreeDObjects[Mission3dObject]->maxDurability;
                            if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                CalculatedDamageFromAirfields *= HostileDamageState;
                            } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                CalculatedDamageFromBatteries *= HostileDamageState;
                            } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                CalculatedDamageFromBattleships *= HostileDamageState;
                            } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                CalculatedDamageFromDestroyers *= HostileDamageState;
                            }
                            if (HostileDamageState > 0.4) {
                                sound->setVolume(SOUND_BEEP1, volume);
                                sound->play(SOUND_BEEP1, false);
                            } else {
                                if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                    CalculatedDamageFromAirfields *= .30;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                    CalculatedDamageFromBatteries *= .30;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                    CalculatedDamageFromBattleships *= .30;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                    CalculatedDamageFromDestroyers *= .30;
                                }
                            }

                            if (blackout > 0) {
                                JinkingStrength = blackout * 5;
                                if (JinkingStrength > 10.0) {
                                    JinkingStrength = 10.0;
                                    if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                        CalculatedDamageFromAirfields = 0.0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                        CalculatedDamageFromBatteries = 0.0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                        CalculatedDamageFromBattleships = 0.0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                        CalculatedDamageFromDestroyers = 0.0;
                                    }
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() +Jinking helped.", LOG_MOST);
                                }
                                if (JinkingStrength > 1.0) {
                                    if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                        CalculatedDamageFromAirfields /= JinkingStrength;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                        CalculatedDamageFromBatteries /= JinkingStrength;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                        CalculatedDamageFromBattleships /= JinkingStrength;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                        CalculatedDamageFromDestroyers /= JinkingStrength;
                                    }
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() +Jinking helped.", LOG_MOST);
                                }
                            } else if (redout > 0) {
                                JinkingStrength = redout * 6;
                                if (JinkingStrength > 1.0) {
                                    if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                        CalculatedDamageFromAirfields /= JinkingStrength;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                        CalculatedDamageFromBatteries /= JinkingStrength;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                        CalculatedDamageFromBattleships /= JinkingStrength;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                        CalculatedDamageFromDestroyers /= JinkingStrength;
                                    }
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() -Jinking helped.", LOG_MOST);
                                }
                                if (JinkingStrength > 10.0) {
                                    JinkingStrength = 10.0;
                                    if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                        CalculatedDamageFromAirfields = 0.0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                        CalculatedDamageFromBatteries = 0.0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                        CalculatedDamageFromBattleships = 0.0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                        CalculatedDamageFromDestroyers = 0.0;
                                    }
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() -Jinking helped.", LOG_MOST);
                                }
                            }

                            if (myrandom(100) > 50) {
                                if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                    CalculatedDamageFromAirfields = 0.0;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                    CalculatedDamageFromBatteries = 0.0;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                    CalculatedDamageFromBattleships = 0.0;
                                } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                    CalculatedDamageFromDestroyers = 0.0;
                                }
                                display((char*)"CalcDamageRiskFromNearbyOpposition() myrandom() helped.", LOG_MOST);
                            }

                            if (fplayer->realspeed > .32) {
                                if (myrandom(100) > 20) {
                                    if (ThreeDObjects[Mission3dObject]->id == STATIC_AIRFIELD00) {
                                        CalculatedDamageFromAirfields = 0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTERY) {
                                        CalculatedDamageFromBatteries = 0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_BATTLESHIP) {
                                        CalculatedDamageFromBattleships = 0;
                                    } else if (ThreeDObjects[Mission3dObject]->id == STATIC_DESTROYER) {
                                        CalculatedDamageFromDestroyers = 0;
                                    }
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() Airfield guns missed due to our high speed.", LOG_MOST);
                                }
                            }
                        }

                        if (
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_B17) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_B24) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_JU87) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_G5M) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_B25) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_B26) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_LANCASTER) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_B29) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_B5N) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_DAUNTLESS) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_DORNIER) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_HE111) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_JU88) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_SB2C) ||
                            (ThreeDObjects[Mission3dObject]->id == BOMBER_TBF) ||
                            (ThreeDObjects[Mission3dObject]->id == FIGHTER_D3A) ||
                            (ThreeDObjects[Mission3dObject]->id == FIGHTER_ME110) ||
                            (ThreeDObjects[Mission3dObject]->id == FIGHTER_IL2)
                            ) {
                            sound->setVolume(SOUND_BEEP1, 40);
                            sound->play(SOUND_BEEP1, false);

                            if (XDisplacementTemp < 30 && YDisplacementTemp < 30 && ZDisplacementTemp < 30) {
                                CalculatedDamageFromAircraft[Mission3dObject] = 100 / TotalXYZDisplacement; // In range
                                int volume = (int)(CalculatedDamageFromAircraft[Mission3dObject] * 36) - 110;
                                if (volume > 126) {
                                    volume = 126;
                                }
                                sound->setVolume(SOUND_BEEP1, volume);
                                sound->play(SOUND_BEEP1, false);

                                float PhiDifferential = fabs(fplayer->phi - ThreeDObjects[Mission3dObject]->phi);
                                float GammaDifferential = fabs(fplayer->gamma - ThreeDObjects[Mission3dObject]->gamma);
                                sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Damage due to bomber proximity = %f from bomber %d", CalculatedDamageFromAircraft[Mission3dObject], Mission3dObject);
                                display(DebugBuf, LOG_MOST);
                                if (PhiDifferential < 14.0 && GammaDifferential < 6.0) {
                                    CalculatedDamageFromAircraft[Mission3dObject] *= 2.0; // Serious hits are far more likely in this circumstance!
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() 2x Damage Penalty!", LOG_MOST);
                                } else if (PhiDifferential > 80 || GammaDifferential > 20) {
                                    CalculatedDamageFromAircraft[Mission3dObject] /= 3.0;
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() Radical intercept helped.", LOG_MOST);
                                }

                                HostileDamageState = ThreeDObjects[Mission3dObject]->Durability / ThreeDObjects[Mission3dObject]->maxDurability;
                                CalculatedDamageFromAircraft[Mission3dObject] *= HostileDamageState;

                                if (blackout > 0) {
                                    JinkingStrength = blackout * 3;
                                    if (JinkingStrength > 10.0) {
                                        JinkingStrength = 10.0;
                                        CalculatedDamageFromAircraft[Mission3dObject] = 0.0;
                                    }
                                    if (JinkingStrength > 1.0) {
                                        CalculatedDamageFromAircraft[Mission3dObject] /= JinkingStrength;
                                        display((char*)"CalcDamageRiskFromNearbyOpposition() +Jinking helped.", LOG_MOST);
                                    }
                                } else if (redout > 0) {
                                    JinkingStrength = redout * 5;
                                    if (JinkingStrength > 10.0) {
                                        JinkingStrength = 10.0;
                                        CalculatedDamageFromAircraft[Mission3dObject] = 0.0;
                                    }
                                    if (JinkingStrength > 1.0) {
                                        CalculatedDamageFromAircraft[Mission3dObject] /= JinkingStrength;
                                        display((char*)"CalcDamageRiskFromNearbyOpposition() -Jinking helped.", LOG_MOST);
                                    }
                                }

                                if (myrandom(100) > 50) {
                                    CalculatedDamageFromAircraft[Mission3dObject] = 0.0;
                                    display((char*)"CalcDamageRiskFromNearbyOpposition() myrandom() helped.", LOG_MOST);
                                }

                                if (fplayer->realspeed > (ThreeDObjects[Mission3dObject]->realspeed * 1.3)) {
                                    if (myrandom(100) > 20) {
                                        CalculatedDamageFromAircraft[Mission3dObject] = 0;
                                        display((char*)"CalcDamageRiskFromNearbyOpposition() Bomber guns missed due to our high speed.", LOG_MOST);
                                    }
                                }

                                if (fplayer->realspeed > (ThreeDObjects[Mission3dObject]->realspeed * 1.5)) {
                                    if (myrandom(100) > 3) {
                                        CalculatedDamageFromAircraft[Mission3dObject] = 0;
                                        display((char*)"CalcDamageRiskFromNearbyOpposition() Bomber guns missed due to our high speed.", LOG_MOST);
                                    }
                                }
                            } else {
                                CalculatedDamageFromAircraft[Mission3dObject] = 0.0; // Out of range
                            }

                            float LethalityFactor = ((float)(ThreeDObjects[Mission3dObject]->DefensiveLethality));
                            CalculatedDamageFromAircraft[Mission3dObject] *= LethalityFactor;
                        } // end of section handling bombers in the general vicinity
                    } // end of logic checking x, y, and z displacements
                }
            }
        }
    }
    CalculatedDamageDueToCurrentRisk = CalculatedDamageFromAirfields +
        CalculatedDamageFromBattleships +
        CalculatedDamageFromDestroyers +
        CalculatedDamageFromBatteries;

    if (CalculatedDamageFromAirfields > 0.0) {
        sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Airfield damaged us by %f", CalculatedDamageFromAirfields);
        display(DebugBuf, LOG_MOST);
        CalculatedDamageFromAirfields = 0;
    }
    if (CalculatedDamageFromBatteries > 0.0) {
        sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Artillery batteries damaged us by %f", CalculatedDamageFromBatteries);
        display(DebugBuf, LOG_MOST);
        CalculatedDamageFromBatteries = 0;
    }
    if (CalculatedDamageFromBattleships > 0.0) {
        sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Battleships damaged us by %f", CalculatedDamageFromBattleships);
        display(DebugBuf, LOG_MOST);
        CalculatedDamageFromBattleships = 0;
    }
    if (CalculatedDamageFromDestroyers > 0.0) {
        sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Destroyers damaged us by %f", CalculatedDamageFromDestroyers);
        display(DebugBuf, LOG_MOST);
        CalculatedDamageFromDestroyers = 0;
    }
    for (Mission3dObject = 1; Mission3dObject <= 10; Mission3dObject++) {
        if (CalculatedDamageFromAircraft[Mission3dObject] > 0.0) {
            CalculatedDamageDueToCurrentRisk += CalculatedDamageFromAircraft[Mission3dObject];

            sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Bomber %d damaged us by %f", Mission3dObject, CalculatedDamageFromAircraft[Mission3dObject]);
            display(DebugBuf, LOG_MOST);
            CalculatedDamageFromAircraft[Mission3dObject] = 0;
        }
    }
    if (CalculatedDamageDueToCurrentRisk > 0 && CalculatedDamageDueToCurrentRisk < 0.22) {
        display((char*)"CalcDamageRiskFromNearbyOpposition() Discarding negligible value of CalculatedDamageDueToCurrentRisk.", LOG_MOST);
        CalculatedDamageDueToCurrentRisk = 0;
    }
    if (CalculatedDamageDueToCurrentRisk > 0.0) {

        for (Mission3dObject = 1; Mission3dObject <= 10; Mission3dObject++) {
            if (ThreeDObjects[Mission3dObject]->active == true) {
                if (Mission3dObject % 2 == MyNetworkId % 2) {
                    if ((ThreeDObjects[Mission3dObject]->id > FIGHTER1) && (ThreeDObjects[Mission3dObject]->id < FIGHTER2)) {
                        float XDisplacementTemp1 = fabs(fplayer->tl->x - ThreeDObjects[Mission3dObject]->tl->x);
                        float YDisplacementTemp1 = fabs(fplayer->tl->y - ThreeDObjects[Mission3dObject]->tl->y);
                        float ZDisplacementTemp1 = fabs(fplayer->tl->z - ThreeDObjects[Mission3dObject]->tl->z);
                        if (XDisplacementTemp1 < 40 && YDisplacementTemp1 < 40 && ZDisplacementTemp1 < 40) {
                            CalculatedDamageDueToCurrentRisk *= 0.5; // A nearby ally shares our damage risk.
                            display((char*)"CalcDamageRiskFromNearbyOpposition() Ally sharing helped.", LOG_MOST);
                        } else {
                            ; // Make no adjustment if this aircraft is too far away to share damage risk.
                        }
                    }
                }
            }
        }
    }
    if (CalculatedDamageDueToCurrentRisk > 0.0) {
        sprintf(DebugBuf, "CalcDamageRiskFromNearbyOpposition() Grand Total CalculatedDamageDuetoCurrentRisk = %f", CalculatedDamageDueToCurrentRisk);
        display(DebugBuf, LOG_MOST);
    }
}

void ConfigureOrdnanceForOnlineMissions() {
    int i2;
    for (i2 = 0; i2 < missiletypes; i2++) {
        fplayer->missiles[i2] = 4;
    }
    if (
        fplayer->id == FIGHTER_P38L ||
        fplayer->id == FIGHTER_A6M2 ||
        fplayer->id == FIGHTER_F4U ||
        fplayer->id == FIGHTER_F4F ||
        fplayer->id == FIGHTER_F6F ||
        fplayer->id == FIGHTER_P47D ||
        fplayer->id == FIGHTER_P51D ||
        fplayer->id == FIGHTER_FW190 ||
        fplayer->id == FIGHTER_IL16 ||
        fplayer->id == FIGHTER_FIATG55 ||
        fplayer->id == FIGHTER_ME109G ||
        fplayer->id == FIGHTER_P39 ||
        fplayer->id == FIGHTER_P40 ||
        fplayer->id == FIGHTER_HURRICANE ||
        fplayer->id == FIGHTER_SPIT9 ||
        fplayer->id == FIGHTER_KI43 ||
        fplayer->id == FIGHTER_LA5 ||
        fplayer->id == FIGHTER_LA7 ||
        fplayer->id == FIGHTER_IL2 ||
        fplayer->id == FIGHTER_MACCIC202 ||
        fplayer->id == FIGHTER_TYPHOON ||
        fplayer->id == FIGHTER_YAK1 ||
        fplayer->id == FIGHTER_N1K1 ||
        fplayer->id == FIGHTER_YAK9 ||
        fplayer->id == BOMBER_B29 ||
        fplayer->id == FIGHTER_DW520 ||
        fplayer->id == BOMBER_SB2C ||
        fplayer->id == BOMBER_TBF ||
        fplayer->id == FIGHTER_ME163 ||
        fplayer->id == FIGHTER_TEMPEST ||
        fplayer->id == FIGHTER_D3A ||
        fplayer->id == BOMBER_B5N ||
        fplayer->id == BOMBER_DAUNTLESS ||
        fplayer->id == FIGHTER_ME110 ||
        fplayer->id == BOMBER_DORNIER ||
        fplayer->id == BOMBER_HE111 ||
        fplayer->id == BOMBER_JU88 ||
        fplayer->id == FIGHTER_KI84 ||
        fplayer->id == FIGHTER_KI61 ||
        fplayer->id == BOMBER_JU87 ||
        fplayer->id == BOMBER_B17 ||
        fplayer->id == BOMBER_B24 ||
        fplayer->id == BOMBER_G5M ||
        fplayer->id == BOMBER_B25 ||
        fplayer->id == BOMBER_B26 ||
        fplayer->id == BOMBER_LANCASTER ||
        fplayer->id == BOMBER_MOSQUITOB ||
        fplayer->id == FIGHTER_GENERIC01 ||
        fplayer->id == FIGHTER_A6M5 ||
        fplayer->id == FIGHTER_SPIT5 ||
        fplayer->id == FIGHTER_P51B ||
        fplayer->id == FIGHTER_P47B ||
        fplayer->id == FIGHTER_ME109F ||
        fplayer->id == FIGHTER_P38F

        ) {
        for (i2 = 0; i2 < missiletypes; i2++) {
            fplayer->missiles[i2] = 0;
        }

        for (i2 = 0; i2 < missiletypes; i2++) {
            if (i2 == 0) {
                if (fplayer->id == FIGHTER_P38L) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_A6M2) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_F4U) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_F4F) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_F6F) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_P47D) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_P51D) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_FW190) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_IL16) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_FIATG55) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_ME109G) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_P39) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_P40) {
                    fplayer->missiles[i2] = 3;
                }
                if (fplayer->id == FIGHTER_HURRICANE) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_SPIT9) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_KI43) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_N1K1) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_YAK9) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_LA5) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_LA7) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_MACCIC202) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_TYPHOON) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_YAK1) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_DW520) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_SB2C) {
                    fplayer->missiles[i2] = 4;
                }
                if (fplayer->id == BOMBER_TBF) {
                    fplayer->missiles[i2] = 4;
                }
                if (fplayer->id == FIGHTER_ME163) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_TEMPEST) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_D3A) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == BOMBER_B5N) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == BOMBER_DAUNTLESS) {
                    fplayer->missiles[i2] = 4;
                }
                if (fplayer->id == FIGHTER_ME110) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_DORNIER) {
                    fplayer->missiles[i2] = 5;
                }
                if (fplayer->id == BOMBER_HE111) {
                    fplayer->missiles[i2] = 12;
                }
                if (fplayer->id == BOMBER_JU88) {
                    fplayer->missiles[i2] = 6;
                }
                if (fplayer->id == FIGHTER_KI84) {
                    fplayer->missiles[i2] = 3;
                }
                if (fplayer->id == FIGHTER_KI61) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_GENERIC01) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_A6M5) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_SPIT5) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_P51B) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_P47B) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_ME109F) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_P38F) {
                    fplayer->missiles[i2] = 1;
                }
                if (fplayer->id == FIGHTER_IL2) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == BOMBER_JU87) {
                    fplayer->missiles[i2] = 4;
                }
                if (fplayer->id == BOMBER_G5M) {
                    fplayer->missiles[i2] = 4;
                }
                if (fplayer->id == BOMBER_B25) {
                    fplayer->missiles[i2] = 6;
                }
                if (fplayer->id == BOMBER_B26) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == BOMBER_B17) {
                    fplayer->missiles[i2] = 15;
                }
                if (fplayer->id == BOMBER_MOSQUITOB) {
                    fplayer->ammo = 2000;
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == BOMBER_LANCASTER) {
                    fplayer->missiles[i2] = 22;
                }
                if (fplayer->id == BOMBER_B29) {
                    fplayer->missiles[i2] = 30;
                }
                if (fplayer->id == BOMBER_B24) {
                    fplayer->missiles[i2] = 16;
                }
            }
            //
            // Now degrade bombload of heavy bombers when launching
            // from forward airfields:
            //
            if (fplayer->missiles[i2] >= 6) { // Get here if we are flying a heavy bomber
                DetermineCurrentAirfield();
                if (AirfieldRequested == 1 && !LandedAtSafeSpeed) {
                    display((char*)"ConfigureOrdnanceForOnlineMissions() in-flight: Degrading bomb load to 50%", LOG_MOST);
                    fplayer->missiles[i2] /= 2;
                    sprintf(DebugBuf, "Total bomb load now %d.", fplayer->missiles[i2]);
                    display((char*)DebugBuf, LOG_MOST);
                } else if (AirfieldRequested == 2 && !LandedAtSafeSpeed) {
                    display((char*)"ConfigureOrdnamceForOnlineMissions() if-flight: Degrading bomb load to 75%", LOG_MOST);
                    fplayer->missiles[i2] *= 3;
                    fplayer->missiles[i2] /= 4;
                    sprintf(DebugBuf, "Total bomb load now %d.", fplayer->missiles[i2]);
                    display((char*)DebugBuf, LOG_MOST);
                }
                if (AirfieldChosenForLanding == 1 && LandedAtSafeSpeed) {
                    display((char*)"ConfigureOrdnanceForOnlineMissions() landed: Degrading bomb load to 50%", LOG_MOST);
                    fplayer->missiles[i2] /= 2;
                    sprintf(DebugBuf, "Total bomb load now %d.", fplayer->missiles[i2]);
                    display((char*)DebugBuf, LOG_MOST);
                } else if (AirfieldChosenForLanding == 2 && LandedAtSafeSpeed) {
                    display((char*)"ConfigureOrdnamceForOnlineMissions() landed: Degrading bomb load to 75%", LOG_MOST);
                    fplayer->missiles[i2] *= 3;
                    fplayer->missiles[i2] /= 4;
                    sprintf(DebugBuf, "Total bomb load now %d.", fplayer->missiles[i2]);
                    display((char*)DebugBuf, LOG_MOST);
                }
            }
            if (i2 == 5) {
                if (fplayer->id == FIGHTER_P38L) {
                    fplayer->missiles[i2] = 10;
                }
                if (fplayer->id == FIGHTER_A6M2) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_F4U) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == FIGHTER_F4F) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_F6F) {
                    fplayer->missiles[i2] = 6;
                }
                if (fplayer->id == FIGHTER_P47D) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == FIGHTER_P51D) {
                    fplayer->missiles[i2] = 6;
                }
                if (fplayer->id == FIGHTER_FW190) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_IL16) {
                    fplayer->missiles[i2] = 6;
                }
                if (fplayer->id == FIGHTER_FIATG55) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_ME109G) {
                    fplayer->missiles[i2] = 2;
                }
                if (fplayer->id == FIGHTER_P39) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_P40) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_HURRICANE) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_SPIT9) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_KI43) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_N1K1) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_YAK9) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_LA5) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_LA7) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_IL2) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == BOMBER_JU87) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_G5M) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_B25) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == BOMBER_B26) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_B17) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_B24) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_LANCASTER) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_MOSQUITOB) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == FIGHTER_MACCIC202) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_TYPHOON) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == FIGHTER_YAK1) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_B29) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_DW520) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_SB2C) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == BOMBER_TBF) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == FIGHTER_ME163) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_TEMPEST) {
                    fplayer->missiles[i2] = 8;
                }
                if (fplayer->id == FIGHTER_D3A) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_B5N) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_DAUNTLESS) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_ME110) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_DORNIER) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_HE111) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == BOMBER_JU88) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_KI84) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_KI61) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_GENERIC01) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_A6M5) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_SPIT5) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_P51B) {
                    fplayer->missiles[i2] = 4;
                }
                if (fplayer->id == FIGHTER_P47B) {
                    fplayer->missiles[i2] = 6;
                }
                if (fplayer->id == FIGHTER_ME109F) {
                    fplayer->missiles[i2] = 0;
                }
                if (fplayer->id == FIGHTER_P38F) {
                    fplayer->missiles[i2] = 6;
                }
            }
        }
    }
}

void DetermineCurrentAirfield() {
    if (fplayer->tl->y > (SeaLevel + 1000)) {
        AirfieldChosenForLanding = 0;
        return;
    }
    if (fplayer->tl->z > 10.0) {
        AirfieldChosenForLanding = 7;
        return;
    }
    if (fplayer->tl->z < -10.0) {
        AirfieldChosenForLanding = 7;
        return;
    }
    if (fplayer->tl->x < -1500.0) {
        AirfieldChosenForLanding = 7;
        return;
    }
    if (fplayer->tl->x > 1500.0) {
        AirfieldChosenForLanding = 7;
        return;
    }
    if (fplayer->tl->x > 1100.0) {
        AirfieldChosenForLanding = 6;
        return;
    }
    if (fplayer->tl->x > 600.0) {
        AirfieldChosenForLanding = 5;
        return;
    }
    if (fplayer->tl->x > 100.0) {
        AirfieldChosenForLanding = 4;
        return;
    }
    if (fplayer->tl->x > -500.0) {
        AirfieldChosenForLanding = 1;
        return;
    }
    if (fplayer->tl->x > -1000.0) {
        AirfieldChosenForLanding = 2;
        return;
    } else {
        AirfieldChosenForLanding = 3;
        return;
    }
}

void LoadVariablesFromNetworkApiPacket(int timer) {

    static unsigned char BlueTeamAirfieldDestroyedNotificationCount = 0.0;
    static unsigned char RedTeamAirfieldDestroyedNotificationCount = 0.0;
    unsigned char PlayerNumber;

    extern LacUdpApiPacket InPacket;
    display((char*)"LoadVariablesFromNetworkApiPacket()", LOG_NET);

    if (InPacket.NetworkApiVersion != NetworkApiVersion) {

        display((char*)"LoadVariablesFromNetworkApiPacket() discarded a UDP packet.", LOG_ERROR);
        display((char*)"Reason: Unexpected NetworkApiVersionNumber:", LOG_ERROR);
        sprintf(DebugBuf, "We are using NetworkApiVersion %d", NetworkApiVersion);
        display(DebugBuf, LOG_ERROR);
        sound->setVolume(SOUND_BEEP1, 80);
        sound->play(SOUND_BEEP1, false);
        if (NetworkApiVersion < InPacket.NetworkApiVersion) {
            sprintf(SystemMessageBufferA, "PLAYER %d HAS NEWER LAC. YOU SHOULD UPGRADE.", InPacket.UdpObjPlayerNumber);
            NewSystemMessageNeedsScrolling = true;
            sprintf(DebugBuf, "We received an InPacket using newer NetworkApiVersion %d", InPacket.NetworkApiVersion);
            display(DebugBuf, LOG_ERROR);
            display((char*)"This means that you probably need to download a newer version of LAC for compatibility.", LOG_ERROR);
        } else {
            sprintf(SystemMessageBufferA, "PLAYER %d HAS OLDER LAC. URGE HIM TO UPGRADE.", InPacket.UdpObjPlayerNumber);
            NewSystemMessageNeedsScrolling = true;
            sprintf(DebugBuf, "We received an InPacket using older NetworkApiVersion %d from player %d", InPacket.NetworkApiVersion, InPacket.UdpObjPlayerNumber);
            display(DebugBuf, LOG_ERROR);
            display((char*)"Please inform all players that you have upgraded to a newer version of LAC for compatibility.", LOG_ERROR);
        }
        return;
    }
    NetworkOpponent = 1;

    PlayerNumber = InPacket.UdpObjPlayerNumber;
    if (PlayerNumber > 10) { // If InPacket has PlayererNumber > 10 here, it is corrupt. Discard it to avoid segmentation errors.

        sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket() PlayerNumber out of range. Got: %d", PlayerNumber);
        display(DebugBuf, LOG_MOST);
        display((char*)"LoadVariablesFromNetworkApiPacket(): Corrupt InPacket discarded.", LOG_MOST);
        InPacket.UdpObjPlayerNumber = 1;
        return; // If missions are ever expanded beyond 10 players this will need to change.
    }

    NewestInPacketId = PlayerNumber;

    if (NewestInPacketId > HighestRecentMyNetworkId) {
        HighestRecentMyNetworkId = NewestInPacketId;
        MissionCommanderCandidate = HighestRecentMyNetworkId;
    }
    sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket() PlayerNumber= %d", PlayerNumber);
    display(DebugBuf, LOG_NET);
    sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket() SentientCount = %d", ThreeDObjects[PlayerNumber]->Sentient);
    display(DebugBuf, LOG_NET);
    if (ThreeDObjects[PlayerNumber]->Sentient > 0 && ThreeDObjects[PlayerNumber]->Sentient <= 10) {
        ThreeDObjects[PlayerNumber]->Sentient++;
        if (ThreeDObjects[PlayerNumber]->Sentient == 7) {

            ThreeDObjects[PlayerNumber]->newinit(ThreeDObjects[PlayerNumber]->id, 0, 1200);
        }
    }
    if (ThreeDObjects[PlayerNumber]->Sentient < 2) {
        ThreeDObjects[PlayerNumber]->Sentient = 2;
        return; // Discard the first packet.
    }

    ThreeDObjects[PlayerNumber]->AileronFromPriorInPacket = InPacket.UdpObjAileron;
    ThreeDObjects[PlayerNumber]->ElevatorFromPriorInPacket = InPacket.UdpObjElevator;
    ThreeDObjects[PlayerNumber]->RudderFromPriorInPacket = InPacket.UdpObjRudder;
    ThreeDObjects[PlayerNumber]->ThrustFromPriorInPacket = InPacket.UdpObjThrust;

    ThreeDObjects[PlayerNumber]->id = (int)InPacket.UdpObjVehicle;

    NetDeltaX[PlayerNumber] = InPacket.UdpObjXPosition - NetworkApiPriorXPosition[PlayerNumber];
    NetDeltaY[PlayerNumber] = InPacket.UdpObjYPosition - NetworkApiPriorYPosition[PlayerNumber];
    NetDeltaZ[PlayerNumber] = InPacket.UdpObjZPosition - NetworkApiPriorZPosition[PlayerNumber];

    NetXErr[PlayerNumber] = InPacket.UdpObjXPosition - ThreeDObjects[PlayerNumber]->tl->x;
    NetYErr[PlayerNumber] = InPacket.UdpObjYPosition - ThreeDObjects[PlayerNumber]->tl->y;
    NetZErr[PlayerNumber] = InPacket.UdpObjZPosition - ThreeDObjects[PlayerNumber]->tl->z;

    if (NetDeltaX[PlayerNumber] >= 0) {
        if (NetXErr[PlayerNumber] <= 0) {
            ThrustFactor[PlayerNumber] -= fabs(NetXErr[PlayerNumber]) * 0.20;
        } else {
            ThrustFactor[PlayerNumber] += fabs(NetXErr[PlayerNumber]) * 0.20;
        }
    } else {
        if (NetXErr[PlayerNumber] <= 0) {
            ThrustFactor[PlayerNumber] += fabs(NetXErr[PlayerNumber]) * 0.20;
        } else {
            ThrustFactor[PlayerNumber] -= fabs(NetXErr[PlayerNumber]) * 0.20;
        }
    }
    if (NetDeltaZ[PlayerNumber] >= 0) {
        if (NetZErr[PlayerNumber] <= 0) {
            ThrustFactor[PlayerNumber] -= fabs(NetZErr[PlayerNumber]) * 0.20;
        } else {
            ThrustFactor[PlayerNumber] += fabs(NetZErr[PlayerNumber]) * 0.20;
        }
    } else {
        if (NetZErr[PlayerNumber] <= 0) {
            ThrustFactor[PlayerNumber] += fabs(NetZErr[PlayerNumber]) * 0.20;
        } else {
            ThrustFactor[PlayerNumber] -= fabs(NetZErr[PlayerNumber]) * 0.20;
        }
    }

    if (ThrustFactor[PlayerNumber] > 2.0) {
        ThrustFactor[PlayerNumber] = 2.0;
    }
    if (ThrustFactor[PlayerNumber] < -0.5) {
        ThrustFactor[PlayerNumber] = -0.5;
    }
    ThreeDObjects[PlayerNumber]->thrust = InPacket.UdpObjThrust * (1.0 + ThrustFactor[PlayerNumber]);
    ThreeDObjects[PlayerNumber]->recthrust = InPacket.UdpObjThrust * (1.0 + ThrustFactor[PlayerNumber]);

    ThreeDObjects[PlayerNumber]->tl->x = InPacket.UdpObjXPosition;
    ThreeDObjects[PlayerNumber]->tl->y = InPacket.UdpObjYPosition;
    ThreeDObjects[PlayerNumber]->tl->z = InPacket.UdpObjZPosition;

    ThreeDObjects[PlayerNumber]->gamma = InPacket.UdpObjGamma;
    ThreeDObjects[PlayerNumber]->phi = InPacket.UdpObjPhi;
    ThreeDObjects[PlayerNumber]->theta = InPacket.UdpObjTheta;

    ThreeDObjects[PlayerNumber]->realspeed = InPacket.UdpObjSpeed;
    ThreeDObjects[PlayerNumber]->elevatoreffect = InPacket.UdpObjElevator;
    ThreeDObjects[PlayerNumber]->recelevatoreffect = InPacket.UdpObjElevator;
    ThreeDObjects[PlayerNumber]->ruddereffect = InPacket.UdpObjRudder;
    ThreeDObjects[PlayerNumber]->recruddereffect = InPacket.UdpObjRudder;
    ThreeDObjects[PlayerNumber]->rolleffect = InPacket.UdpObjAileron;
    ThreeDObjects[PlayerNumber]->recrolleffect = InPacket.UdpObjAileron;
    ProcessUdpObjFlightDetails();

    NetworkApiPriorXPosition[PlayerNumber] = InPacket.UdpObjXPosition;
    NetworkApiPriorYPosition[PlayerNumber] = InPacket.UdpObjYPosition;
    NetworkApiPriorZPosition[PlayerNumber] = InPacket.UdpObjZPosition;
    NetworkApiPriorTimer[PlayerNumber] = timer;
    if (InPacket.UdpObjDamageId == MyNetworkId) { // Get here if received damage claim addresses this human player
        ThreeDObjects[0]->Durability -= InPacket.UdpObjDamageAmount; // Damage this player
        sprintf(SystemMessageBufferA, "PLAYER %d DAMAGED YOUR AIRCRAFT.", PlayerNumber);
        NewSystemMessageNeedsScrolling = true;
    } else if (InPacket.UdpObjDamageAmount > 0.0) { // Get here if received damage claim addresses some other bot or player or mission object
        ThreeDObjects[InPacket.UdpObjDamageId]->Durability -= InPacket.UdpObjDamageAmount; // Damage addressed mission object
        if (InPacket.UdpObjDamageId > 0 && InPacket.UdpObjDamageId <= 10) { // Get here if the damaged object was an aircraft
            if (InPacket.UdpObjDamageAmount < 1000) {
                sprintf(SystemMessageBufferA, "AIRCRAFT %d DAMAGED AIRCRAFT %d.", PlayerNumber, InPacket.UdpObjDamageId);
            } else {
                sprintf(SystemMessageBufferA, "AIRCRAFT %d DESTROYED AIRCRAFT %d.", PlayerNumber, InPacket.UdpObjDamageId);
            }
            NewSystemMessageNeedsScrolling = true;
        } else if (InPacket.UdpObjDamageId >= 11) { // Get here if the damaged item was NOT an aircraft

            if (
                (InPacket.UdpObjDamageAmount < 450000) &&
                (InPacket.UdpObjDamageAmount < ThreeDObjects[InPacket.UdpObjDamageId]->Durability)
                ) {
                if (
                    (
                        ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_AIRFIELD00 ||
                        ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_BATTLESHIP
                        )
                    &&
                    (
                        !(MyNetworkId % 2)
                        )
                    ) {
                    if (InPacket.UdpObjDamageAmount > 2000) {
                        float XDistance = fabs(fplayer->tl->x - ThreeDObjects[InPacket.UdpObjDamageId]->tl->x);
                        float YDistance = fabs(fplayer->tl->y - ThreeDObjects[InPacket.UdpObjDamageId]->tl->y);
                        float ZDistance = fabs(fplayer->tl->z - ThreeDObjects[InPacket.UdpObjDamageId]->tl->z);
                        float Distance = XDistance + YDistance + ZDistance;
                        int Volume = 16384 / ((int)Distance * Distance);
                        if (Volume > 126) {
                            Volume = 126;
                        }
                        sound->setVolume(SOUND_EXPLOSION1, Volume);
                        sound->play(SOUND_EXPLOSION1, false);
                        sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): Explosion of %f claimed vs resource %d. Remaining strength = %f", InPacket.UdpObjDamageAmount, InPacket.UdpObjDamageId, ThreeDObjects[InPacket.UdpObjDamageId]->Durability);
                        display(DebugBuf, LOG_MOST);
                    }
                }
                if (
                    (
                        ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_AIRFIELD00 ||
                        ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_BATTLESHIP
                        )
                    &&
                    (
                        (MyNetworkId % 2)
                        )
                    ) {
                    if (InPacket.UdpObjDamageAmount > 2000) {
                        float XDistance = fabs(fplayer->tl->x - ThreeDObjects[InPacket.UdpObjDamageId]->tl->x);
                        float YDistance = fabs(fplayer->tl->y - ThreeDObjects[InPacket.UdpObjDamageId]->tl->y);
                        float ZDistance = fabs(fplayer->tl->z - ThreeDObjects[InPacket.UdpObjDamageId]->tl->z);
                        float Distance = XDistance + YDistance + ZDistance;
                        int Volume = 16384 / ((int)Distance * Distance);
                        if (Volume > 126) {
                            Volume = 126;
                        }
                        sound->setVolume(SOUND_EXPLOSION1, Volume);
                        sound->play(SOUND_EXPLOSION1, false);
                    }
                }
                display((char*)"Next message is from LoadVariablesFromNetworkApiPacket()", LOG_MOST);
                display(SystemMessageBufferA, LOG_MOST);
                NewSystemMessageNeedsScrolling = true;
            } else {
                if (SelectedMissionTarget == InPacket.UdpObjDamageId) {
                    event_targetNextRed();
                }
                sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket() InPacket compelled destruction of object %d", InPacket.UdpObjDamageId);
                display(DebugBuf, LOG_MOST);
                ThreeDObjects[InPacket.UdpObjDamageId]->Durability = -4000;
                if ((ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_BATTLESHIP) && (!(InPacket.UdpObjDamageId % 2))) {
                    display((char*)"LoadVariablesFromNetworkApiPacket(): BlueTeam battleship destroyed.", LOG_MOST);

                    bool Condition1 = false;
                    bool Condition2 = false;
                    sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): ThreeDObjects[MissionObjectHqBlue]->Durability = %f.", ThreeDObjects[MissionObjectHqBlue]->Durability);
                    display(DebugBuf, LOG_MOST);
                    sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): ThreeDObjects[MissionObjectHqBlue]->maxDurability = %f.", ThreeDObjects[MissionObjectHqBlue]->maxDurability);
                    display(DebugBuf, LOG_MOST);
                    if ((ThreeDObjects[MissionObjectHqBlue]->Durability) > ((ThreeDObjects[MissionObjectHqBlue]->maxDurability) * 0.70)) {
                        Condition1 = true;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition1 = true.", LOG_MOST);
                    } else {
                        Condition1 = false;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition1 = false.", LOG_MOST);
                    }
                    if (BattleshipSunkAlertCountBlue <= 2) {
                        Condition2 = true;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition2 = true.", LOG_MOST);
                    } else {
                        Condition2 = false;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition2 = false.", LOG_MOST);
                    }
                    if (Condition1 && Condition2) {
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Dropping BlueHQ durability to 69%.", LOG_MOST);
                        ThreeDObjects[MissionObjectHqBlue]->Durability = ((ThreeDObjects[MissionObjectHqBlue]->maxDurability) * 0.69);
                        sprintf(SystemMessageBufferA, "BLUE TEAM BATTLESHIP DESTROYED.");
                        NewSystemMessageNeedsScrolling = true;
                    }
                    BattleshipSunkAlertCountBlue++;
                }
                if ((ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_BATTLESHIP) && (InPacket.UdpObjDamageId % 2)) {
                    display((char*)"LoadVariablesFromNetworkApiPacket(): RedTeam battleship destroyed.", LOG_MOST);

                    bool Condition1 = false;
                    bool Condition2 = false;
                    sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): ThreeDObjects[MissionObjectHqRed]->Durability = %f.", ThreeDObjects[MissionObjectHqRed]->Durability);
                    display(DebugBuf, LOG_MOST);
                    sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): ThreeDObjects[MissionObjectHqRed]->maxDurability = %f.", ThreeDObjects[MissionObjectHqRed]->maxDurability);
                    display(DebugBuf, LOG_MOST);
                    if ((ThreeDObjects[MissionObjectHqRed]->Durability) > ((ThreeDObjects[MissionObjectHqRed]->maxDurability) * 0.70)) {
                        Condition1 = true;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition1 = true.", LOG_MOST);
                    } else {
                        Condition1 = false;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition1 = false.", LOG_MOST);
                    }
                    if (BattleshipSunkAlertCountRed <= 2) {
                        Condition2 = true;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition2 = true.", LOG_MOST);
                    } else {
                        Condition2 = false;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Condition2 = false.", LOG_MOST);
                    }
                    if (Condition1 && Condition2) {
                        display((char*)"LoadVariablesFromNetworkApiPacket(): Dropping RedHQ durability to 69%.", LOG_MOST);
                        ThreeDObjects[MissionObjectHqRed]->Durability = ((ThreeDObjects[MissionObjectHqRed]->maxDurability) * 0.69);
                        sprintf(SystemMessageBufferA, "RED TEAM BATTLESHIP DESTROYED.");
                        NewSystemMessageNeedsScrolling = true;
                    }
                    BattleshipSunkAlertCountRed++;
                }
                if (InPacket.UdpObjDamageId % 2) {
                    if (ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_AIRFIELD00) {
                        sprintf(SystemMessageBufferA, "A REDTEAM AIRFIELD HAS BEEN DESTROYED.");
                        NewSystemMessageNeedsScrolling = true;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): InPacket says A RedTeam airfield has been destroyed.", LOG_MOST);
                        if (MyNetworkId % 2) {
                            IffOnOff = 0; // Temporarily disable IFF. (Player can over-ride.)
                            RadarOnOff = 0; // Temporarily disable RADAR. (Player can over-ride.)
                        }
                        RedTeamAirfieldDestroyedNotificationCount++;
                        sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): RedTeamAirfieldDestroyedNotificationCount incremented to %d", RedTeamAirfieldDestroyedNotificationCount);
                        display(DebugBuf, LOG_MOST);
                        if (RedTeamAirfieldDestroyedNotificationCount > 12) {
                            RedTeamAirfieldDestroyedNotificationCount = 0;
                        }
                        if (RedTeamAirfieldDestroyedNotificationCount < 8) {

                            ThreeDObjects[InPacket.UdpObjDamageId]->DamageInNetQueue = 300000; // Compel repetition of airfield-destroying damage
                            if (RedTeamAirfieldDestroyedNotificationCount >= 7) {
                                // Reset all memory of this destruction event to prevent its further propogation.
                                ThreeDObjects[InPacket.UdpObjDamageId]->DamageInNetQueue = 0.0;
                                DamageToClaim = 0.0;
                                MissionAircraftDamaged = 0;
                            }
                        }
                    }
                } else {
                    if (ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_AIRFIELD00) {
                        sprintf(SystemMessageBufferA, "A BLUETEAM AIRFIELD HAS BEEN DESTROYED.");
                        NewSystemMessageNeedsScrolling = true;
                        display((char*)"LoadVariablesFromNetworkApiPacket(): InPacket says A BlueTeam airfield has been destroyed.", LOG_MOST);
                        if ((MyNetworkId % 2) == 0) {
                            IffOnOff = 0; // Temporarily disable IFF (Player can over-ride.)
                            RadarOnOff = 0; // Temporarily disable RADAR (Player can over-ride.)
                        }
                        BlueTeamAirfieldDestroyedNotificationCount++;
                        sprintf(DebugBuf, "LoadVariablesFromNetworkApiPacket(): BlueTeamAirfieldDestroyedNotificationCount incremented to %d", BlueTeamAirfieldDestroyedNotificationCount);
                        display(DebugBuf, LOG_MOST);
                        if (BlueTeamAirfieldDestroyedNotificationCount > 12) {
                            BlueTeamAirfieldDestroyedNotificationCount = 0;
                        }
                        if (BlueTeamAirfieldDestroyedNotificationCount < 8) {

                            display((char*)"LoadVariablesFromNetworkApiPacket(): Compelling repetition of BlueTeamHQ destruction claim across network.", LOG_MOST);
                            ThreeDObjects[InPacket.UdpObjDamageId]->DamageInNetQueue = 300000; // Compel repetition of airfield-destroying damage
                            if (BlueTeamAirfieldDestroyedNotificationCount >= 7) {
                                // Reset all memory of this destruction event to prevent its further propogation.
                                ThreeDObjects[InPacket.UdpObjDamageId]->DamageInNetQueue = 0.0;
                                DamageToClaim = 0.0;
                                MissionAircraftDamaged = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    if (InPacket.UdpObjDamageAmount < 0.0) { // Get here if received damage represents a static update

        InPacket.UdpObjDamageAmount *= -1.0;

        if (ThreeDObjects[InPacket.UdpObjDamageId]->Durability > (AIRFIELDMAXDURABILITY * 0.15)) {
            if (
                (!(InPacket.UdpObjDamageId % 2)) &&
                (ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_AIRFIELD00) &&
                (CurrentMissionNumber == MISSION_NETWORKBATTLE01 || CurrentMissionNumber == MISSION_NETWORKBATTLE03)
                ) {
                if (!ThreeDObjects[InPacket.UdpObjDamageId]->active) {
                    ThreeDObjects[InPacket.UdpObjDamageId]->DamageInNetQueue = 299000;
                    display((char*)"LoadVariablesFromNetworkApiPacket() Informing all that BlueTeam battleship has been destroyed. DamageInNetQueue = 299000.", LOG_MOST);
                }
            } else if (
                (InPacket.UdpObjDamageId % 2) &&
                (ThreeDObjects[InPacket.UdpObjDamageId]->id == STATIC_AIRFIELD00) &&
                (CurrentMissionNumber == MISSION_NETWORKBATTLE01 || CurrentMissionNumber == MISSION_NETWORKBATTLE03)
                )

            { // Get here if this static update indicates RedTeam airfield has strength that cannot be maintained without a battleship
                if (!ThreeDObjects[InPacket.UdpObjDamageId]->active) {
                    ThreeDObjects[InPacket.UdpObjDamageId]->DamageInNetQueue = 299000;
                    display((char*)"LoadVariablesFromNetworkApiPacket() Informing all that RedTeam battleship has been destroyed. DamageInNetQueue = 299000.", LOG_MOST);
                }
            }
        }
        if (InPacket.UdpObjDamageAmount < ThreeDObjects[InPacket.UdpObjDamageId]->Durability) {
            ThreeDObjects[InPacket.UdpObjDamageId]->Durability = InPacket.UdpObjDamageAmount; // Update addressed 3d Object with lower static value.
        }
    }
}

void MilestoneCorrectionCheck() {
    MilestoneCorrectionTimer -= (DeltaTime * 1000);
    if (MilestoneCorrectionTimer <= 0) {

        MilestoneCorrectionTimer = 100000000;
        sprintf(
            DebugBuf,
            "MilestoneCorrectionCheck(): Transmitting %d as MissionChronoMilestone.",
            MissionChronoMilestone
        );
        display(DebugBuf, LOG_MOST);
        MissionChronoMilestone++;
        if (MissionChronoMilestone > 10) {
            MissionChronoMilestone = 10;
        }
        switch (MissionChronoMilestone) {
        case 2:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC22", 15);
            break;
        }
        case 3:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC33", 15);
            break;
        }
        case 4:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC44", 15);
            break;
        }
        case 5:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC55", 15);
            break;
        }
        case 6:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC66", 15);
            break;
        }
        case 7:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC77", 15);
            break;
        }
        case 8:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC88", 15);
            break;
        }
        case 9:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC99", 15);
            break;
        }
        case 10:
        {
            strncpy(&MorseCharacterOut[0], "CCCCCCCCCC00", 15);
            break;
        }
        default:
        {
            display((char*)"GetNetworkApiPacket(): Attempt to advertise invalid MissionChronoMilestone failed.", LOG_MOST);
        }
        }
    }
}

void ProcessUdpObjFlightDetails() {
    if (InPacket.UdpObjFlightDetails & 4) {
        ThreeDObjects[InPacket.UdpObjPlayerNumber]->SpeedBrake = 1;
    } else {
        ThreeDObjects[InPacket.UdpObjPlayerNumber]->SpeedBrake = 0;
    }
    if (InPacket.UdpObjFlightDetails & 3) {
        ThreeDObjects[InPacket.UdpObjPlayerNumber]->FlapsLevel = (InPacket.UdpObjFlightDetails & 3);
    } else {
        ThreeDObjects[InPacket.UdpObjPlayerNumber]->FlapsLevel = 0;
    }
    if (InPacket.UdpObjFlightDetails & 8) {
        sprintf(SystemMessageBufferA, "PLAYER %d FIRED A FLARE.", InPacket.UdpObjPlayerNumber);
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
    }
    if (InPacket.UdpObjFlightDetails & 16) {
        sprintf(SystemMessageBufferA, "PLAYER %d FIRED A CHAFF PACKET.", InPacket.UdpObjPlayerNumber);
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
    }
    if (InPacket.UdpObjFlightDetails & 32) {
        float XDistance = fabs(InPacket.UdpObjXPosition - fplayer->tl->x);
        float YDistance = fabs(InPacket.UdpObjYPosition - fplayer->tl->y);
        float ZDistance = fabs(InPacket.UdpObjZPosition - fplayer->tl->z);
        float TotalDistance = XDistance + YDistance + ZDistance;

        int volume;
        if (TotalDistance > 200) {
            volume = 0;
        } else {
            volume = (int)126 - (int)(TotalDistance / 1.8);
        }
        sprintf(SystemMessageBufferA, "PLAYER %d FIRED A ROCKET.", InPacket.UdpObjPlayerNumber);
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
        if (MyNetworkId % 2 != InPacket.UdpObjPlayerNumber % 2) {

            sound->setVolume(SOUND_FIVEBEEPS00, volume);
            sound->play(SOUND_FIVEBEEPS00, false);
        }
    }
}

void RepairDamagedAirfields() {
    static bool FoundHeavilyDamagedBlueAirfield;
    static bool FoundHeavilyDamagedRedAirfield;
    static bool SirenOn = false;
    static bool PriorSirenState = false;
    unsigned char NearestAirfieldNumber = 28;
    unsigned char Object;
    static int SirenVolume = 64;
    static int SirenOnTimer = 0;
    float XDistance[32] = { 10.0 };
    float YDistance[32] = { 10.0 };
    float ZDistance[32] = { 10.0 };
    float XYZDistance[32] = { 10.0 };
    float NearestXYZDistance = 100.0;
    AirfieldRepairsAcceleratedForBlueTeamTimer--;
    if (AirfieldRepairsAcceleratedForBlueTeamTimer < 0) {
        AirfieldRepairRateNormalForBlueTeam = true;
        AirfieldRepairsAcceleratedForBlueTeam = false;
        AirfieldRepairsStoppedForBlueTeam = false;
        AirfieldRepairsAcceleratedForBlueTeamTimer = 0;
    }
    AirfieldRepairsStoppedForBlueTeamTimer--;
    if (AirfieldRepairsStoppedForBlueTeamTimer < 0) {
        AirfieldRepairsStoppedForBlueTeam = false;
        AirfieldRepairsAcceleratedForBlueTeam = false;
        AirfieldRepairRateNormalForBlueTeam = true;
        AirfieldRepairsStoppedForBlueTeamTimer = 0;
    }
    AirfieldRepairsAcceleratedForRedTeamTimer--;
    if (AirfieldRepairsAcceleratedForRedTeamTimer < 0) {
        AirfieldRepairsAcceleratedForRedTeam = false;
        AirfieldRepairsStoppedForRedTeam = false;
        AirfieldRepairRateNormalForRedTeam = true;
        AirfieldRepairsAcceleratedForRedTeamTimer = 0;
    }
    AirfieldRepairsStoppedForRedTeamTimer--;
    if (AirfieldRepairsStoppedForRedTeamTimer < 0) {
        AirfieldRepairsStoppedForRedTeam = false;
        AirfieldRepairRateNormalForRedTeam = true;
        AirfieldRepairsAcceleratedForRedTeam = false;
        AirfieldRepairsStoppedForRedTeamTimer = 0;
    }
    FoundHeavilyDamagedBlueAirfield = true;
    FoundHeavilyDamagedRedAirfield = true;
    for (Object = 1; Object < 30; Object++) {
        if (ThreeDObjects[Object]->id == STATIC_AIRFIELD00 && ThreeDObjects[Object]->active) {

            if ((ThreeDObjects[Object]->Durability) < ((ThreeDObjects[Object]->maxDurability) * 0.01)) {
                ThreeDObjects[Object]->Durability = -10.0;
            }

            if (Object % 2) {
                if (ThreeDObjects[Object]->Durability >= ThreeDObjects[Object]->maxDurability * 0.20) {

                    FoundHeavilyDamagedRedAirfield = false;
                }
            } else {
                if (ThreeDObjects[Object]->Durability >= ThreeDObjects[Object]->maxDurability * 0.20) {

                    FoundHeavilyDamagedBlueAirfield = false;
                }
            }

            XDistance[Object] = fabs(fplayer->tl->x - ThreeDObjects[Object]->tl->x);
            YDistance[Object] = fabs(fplayer->tl->y - ThreeDObjects[Object]->tl->y);
            ZDistance[Object] = fabs(fplayer->tl->z - ThreeDObjects[Object]->tl->z);
            XYZDistance[Object] = XDistance[Object] + YDistance[Object] + ZDistance[Object];
            if (XYZDistance[Object] < NearestXYZDistance) {
                NearestXYZDistance = XYZDistance[Object];
                NearestAirfieldNumber = Object;
            }
            if (ThreeDObjects[Object]->Durability < (AIRFIELDMAXDURABILITY * 0.99)) {

                unsigned char aircraft;
                unsigned char NearestSentient = 0;
                float Xtemp;
                float Ytemp;
                float Ztemp;
                float SentientXYZtemp;
                float PlayerXYZtemp;
                float NearestSentientFoundThusFar = 20000.0;
                for (aircraft = 1; aircraft <= 10; aircraft++) {
                    if ((TestForSentience(aircraft)) && (ThreeDObjects[aircraft]->tl->y > (SeaLevel - 30))) {
                        Xtemp = ((fabs)((ThreeDObjects[Object]->tl->x) - (ThreeDObjects[aircraft]->tl->x)));
                        Ytemp = ((fabs)((ThreeDObjects[Object]->tl->y) - (ThreeDObjects[aircraft]->tl->y)));
                        Ztemp = ((fabs)((ThreeDObjects[Object]->tl->z) - (ThreeDObjects[aircraft]->tl->z)));
                        SentientXYZtemp = Xtemp + Ytemp + Ztemp;
                        if (SentientXYZtemp < NearestSentientFoundThusFar) {
                            NearestSentientFoundThusFar = SentientXYZtemp;
                            NearestSentient = aircraft;
                        }
                    }
                }

                Xtemp = ((fabs)((ThreeDObjects[Object]->tl->x) - (fplayer->tl->x)));
                Ytemp = ((fabs)((ThreeDObjects[Object]->tl->y) - (fplayer->tl->y)));
                Ztemp = ((fabs)((ThreeDObjects[Object]->tl->x) - (fplayer->tl->x)));
                PlayerXYZtemp = Xtemp + Ytemp + Ztemp;
                if (PlayerXYZtemp < NearestSentientFoundThusFar) {
                    NearestSentient = MyNetworkId;
                }
                // OK. At this point, NearestSentient identifies the flying Sentinent aircraft nearest this damaged airfield,
                // whether it is the current player or some other Sentient player. Make repairs to this airfield, but modify
                // the rate of repairs if any Sentient aircraft are nearby: if the nearest Sentient aircraft is an ally and
                // close enough to dominate, repairs are accelerated 5X. If the nearest Sentient aircraft is hostile and
                // close enough to dominate, repairs are stopped.
                //
                // A value of 0.0 is INVALID for SentientXYZtemp. Avoid it explicitly:
                //
                if (SentientXYZtemp == 0.0) {
                    SentientXYZtemp = 5000.0; // Temporarily replace 0.0 with a very high value to prevent its influence.
                }
                if ((PlayerXYZtemp < 400) || (SentientXYZtemp < 400)) {
                    if (NearestSentient % 2 == Object % 2) {
                        //sprintf (DebugBuf, "RepairDamagedAirfields(): Nearest Sentient is %d, is friendly, and is accelerating repairs at field %d.", NearestSentient, Object);
                        //display (DebugBuf, LOG_MOST);
                        ThreeDObjects[Object]->Durability += (AIRFIELDREPAIRVALUE * 5.0);
                        if (Object % 2) {
                            AirfieldRepairsAcceleratedForRedTeam = true;
                            AirfieldRepairsAcceleratedForRedTeamTimer = 10;
                        } else {
                            AirfieldRepairsAcceleratedForBlueTeam = true;
                            AirfieldRepairsAcceleratedForBlueTeamTimer = 10;
                        }
                    } else {
                        sprintf(DebugBuf, "RepairDamagedAirfields(): Nearest Sentient is %d, is hostile, and is halting repairs at field %d.", NearestSentient, Object);
                        display(DebugBuf, LOG_MOST);
                        if (Object % 2) {
                            AirfieldRepairsStoppedForRedTeam = true;
                            AirfieldRepairsStoppedForRedTeamTimer = 10;
                        } else {
                            AirfieldRepairsStoppedForBlueTeam = true;
                            AirfieldRepairsStoppedForBlueTeamTimer = 10;
                        }
                    }
                } else {
                    ThreeDObjects[Object]->Durability += AIRFIELDREPAIRVALUE;
                    if (Object % 2) {
                        AirfieldRepairRateNormalForRedTeam = true;
                    } else {
                        AirfieldRepairRateNormalForBlueTeam = true;
                    }
                }
                if (XYZDistance[Object] < 500) {
                    SirenOn = true;

                    SirenOnTimer += 2000;
                    if (SirenOnTimer > 15000) {
                        SirenOnTimer = 15000;
                    }
                }
            }
        }
    }
    if (PriorSirenState == false) {
        if (SirenOn == true) {
            sound->play(SOUND_AIRRAIDSIREN, true);
            PriorSirenState = true;
        }
    } else {

        SirenOnTimer -= 1000;
        if (SirenOnTimer < 0) {
            SirenOnTimer = 0;
            // Siren has been on long enough with no indication of refreshing it.
            sound->stop(SOUND_AIRRAIDSIREN);
            SirenOn = false;
            PriorSirenState = false;
        }

        if (
            (ThreeDObjects[NearestAirfieldNumber]->Durability > 0.0) &&
            (ThreeDObjects[NearestAirfieldNumber]->Durability < (AIRFIELDMAXDURABILITY * 0.99))
            ) {
            SirenVolume = 16384 / (int)(XYZDistance[NearestAirfieldNumber] * XYZDistance[NearestAirfieldNumber]);
            // Keep acoustic volume low enough to avoid distortion. Absolute limit is 127, but lower is safer.
            if (SirenVolume > 80) {
                SirenVolume = 80;
            }
            SirenVolume -= 3;
            if (SirenVolume < 4) {
                SirenVolume = 0;
            }
            sound->setVolume(SOUND_AIRRAIDSIREN, SirenVolume);
        } else {
            SirenVolume = 0;
        }
    }
    if (FoundHeavilyDamagedBlueAirfield) {
        AllBlueTeamAirfieldsAreHeavilyDamaged = true;
    } else {
        AllBlueTeamAirfieldsAreHeavilyDamaged = false;
    }
    if (FoundHeavilyDamagedRedAirfield) {
        AllRedTeamAirfieldsAreHeavilyDamaged = true;
    } else {
        AllRedTeamAirfieldsAreHeavilyDamaged = false;
    }
}

void Mission::draw() {}

void Mission::init() {}

Mission::Mission() {
    int i;
    timer = 0;
    for (i = 0; i < 3; i++) {
        selfighter[i] = 0;
    }
    selfighter[0] = DefaultAircraft;
    selfighter[1] = FIGHTER_HAWK;
    selfighter[2] = FIGHTER_SPIT9;
    selfighters = 2;
    wantfighter = 0;
    selweapons = 3;
    selweapon[0] = BOMB01;
    selweapon[1] = MISSILE_DF1;
    selweapon[2] = MISSILE_AIR2;
    wantweapon = 0;
    textcolor.setColor(255, 255, 0, 180);
    clouds = 0;
    heading = 180;
    state = 0;
    LandedAtSafeSpeed = false;
}

void Mission::playerInit() {
    int i;
    fplayer = ThreeDObjects[0];
    fplayer->target = NULL;
    fplayer->newinit(selfighter[wantfighter], 1, 0);
    fplayer->ai = false;
    for (i = 0; i < missiletypes; i++) {
        fplayer->missiles[i] = 0;
    }
    for (i = 0; i < missileracks; i++) {
        fplayer->missilerack[i] = -1;
    }
    fplayer->missileCount();
}

int Mission::processtimer(Uint32 dt) {
    display((char*)"Function Entry: Mission::processtimer()", LOG_MOST);
    return 0;
}

void Mission::start() {
    RadarReflectorBlueHasBeenDestroyedAtLeastOnce = false;
    RadarReflectorRedHasBeenDestroyedAtLeastOnce = false;
    AutoPilotActive = false;
}

MissionDemo1::MissionDemo1() {
    id = MISSION_DEMO;
    strncpy(name, "DEMO", 1024);
}

void MissionDemo1::start() {
    day = 1;
    clouds = 0;
    weather = WEATHER_SUNNY;
    sungamma = 0;
    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_SEA, NULL);
    fplayer = ThreeDObjects[0];
    ThreeDObjects[0]->tl->x = 1620;
    ThreeDObjects[0]->tl->z = 300;
    ThreeDObjects[0]->newinit(FIGHTER_GENERIC01, 1, 0);
}

int MissionDemo1::processtimer(Uint32 dt) {
    timer += dt;
    ThreeDObjects[0]->tl->x = 1620;
    ThreeDObjects[0]->tl->z = 300;
    ThreeDObjects[0]->tl->y = 150;
    fplayer->thrust = 0;
    fplayer->realspeed = 0;
    camera = 3;
    return (id);
}

void MissionDemo1::draw() {
    sunlight = 1;
}

MissionTutorial1::MissionTutorial1() {
    id = MISSION_TUTORIAL;
    strncpy(name, "TUTORIAL1: OFFLINE FLIGHT BASICS", 1024);
    strncpy(briefing, "LEARN TO HANDLE YOUR AIRCRAFT AND THE BASIC CONTROLS.\nTHIS VERY PRIMITIVE MISSION WILL HELP GET YOU READY FOR\nREAL FUN ONLINE!", 1024);
    font1->drawTextScaled(0, 0, -4, briefing, 10);
    heading = 210;
    selfighter[0] = DefaultAircraft;
    wantfighter = 0;
    selweapons = 1;
    selweapon[0] = MISSILE_AIR2;
    wantweapon = 0;
    event_CommsMacro10();
}

void MissionTutorial1::start() {
    NoMissionHasYetCommenced = false;
    day = 1;
    clouds = 2;
    weather = WEATHER_SUNNY;
    camera = 0;
    sungamma = 50;
    RadarOnOff = 1;
    RadarZoom = 4;
    if (!HudLadderBarsOnOff) {
        event_HudLadderBarsOnOff();
    }

    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_ALPINE_SEA, NULL);
    SeaLevel = -13.0;
    l->flatten(AirfieldXMin + 28.0, AirfieldYMin + 4, 29.2, 5);
    l->flatten(AirfieldXMin + 46, AirfieldYMin + 5, 7, 6);
    playerInit();
    fplayer->tl->x = 220;
    fplayer->tl->z = -30;
    fplayer->realspeed = (fplayer->DiveSpeedLimit1 * 0.75);
    fplayer->InertiallyDampenedPlayerSpeed = (fplayer->DiveSpeedLimit1 * 0.75);
    int i;
    for (i = 0; i <= 9; i++) {
        fplayer->SpeedHistoryArray[i] = (fplayer->DiveSpeedLimit1 * 0.75);
    }
    IffOnOff = 0;
    event_IffOnOff();
}

int MissionTutorial1::processtimer(Uint32 dt) {
    timer += dt;
    fplayer->recelevatoreffect = 0;

    if (!fplayer->active && fplayer->explode >= 35 * timestep) {
        return 2;
        sound->stop(SOUND_PLANE1);
        sound->stop(SOUND_PLANE2);
        sound->stop(SOUND_WINDNOISE);
        WindNoiseOn = false;
    }
    if (!ThreeDObjects[1]->active && !ThreeDObjects[2]->active && state == 1) {
        return 1;
    }
    return 0;
}

void MissionTutorial1::draw() {
    char buf[250], buf2[10];
    int timeroff = 100 * timestep;
    int timerdelay = 300 * timestep;
    int timerlag = 20 * timestep;
    static bool BeepLatch = false;

    if (timer >= 0 && timer <= 30 * timestep) {
        font1->drawTextCentered(0, 6, -1, name, &textcolor);
    } else if (timer > 50 * timestep && timer <= 180 * timestep) {
        if (controls == CONTROLS_JOYSTICK) {
            if (!BeepLatch) {
                BeepLatch = true;
                sound->play(SOUND_BEEP1, false);
            }
            font1->drawTextCentered(0, 11, -2.25, (char*)"JIGGLE YOUR THROTTLE AT THE START OF", &textcolor);
            font1->drawTextCentered(0, 10, -2.25, (char*)"EVERY MISSION TO START FUEL FLOW.", &textcolor);
        }
    } else if (timer > 190 * timestep && timer <= 400 * timestep) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"LEAVE THE JOYSTICK CENTERED.", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"THE FIGHTER SHOULD FLY STRAIGHT ON.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"IF NOT, RECALIBRATE YOUR JOYSTICK", &textcolor);
        } else if (controls == CONTROLS_MOUSE) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"THE MENU OPTIONS/CONTROLS LETS YOU", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"DETERMINE THE INPUT DEVICE.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"CURRENTLY, THIS IS THE MOUSE", &textcolor);
        } else if (controls == CONTROLS_KEYBOARD) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"THE MENU OPTIONS/CONTROLS LETS YOU", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"DETERMINE THE INPUT DEVICE.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"CURRENTLY, THIS IS THE KEYBOARD", &textcolor);
        }
    } else if (timer > timeroff + timerdelay && timer <= timeroff + 2 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"MOVING THE JOYSTICK LEFT OR RIGHT", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"WILL AFFECT THE AILERON.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"THUS YOU WILL ONLY ROLL", &textcolor);
        } else if (controls == CONTROLS_MOUSE) {
            if (!mouse_reverse && !mouse_relative) {
                font1->drawTextCentered(0, 9, -2.25, (char*)"THE MOUSE INTERFACE IS VERY EASY.", &textcolor);
                font1->drawTextCentered(0, 8, -2.25, (char*)"ALWAYS POINT TO WHERE YOU WANT TO FLY.", &textcolor);
                font1->drawTextCentered(0, 7, -2.25, (char*)"YOU'LL HAVE TO MOVE THE MOUSE PERMANENTLY", &textcolor);
            } else if (mouse_reverse && !mouse_relative) {
                font1->drawTextCentered(0, 9, -2.25, (char*)"THE REVERSE MOUSE IS FOR EXPERIENCED GAMERS.", &textcolor);
                font1->drawTextCentered(0, 8, -2.25, (char*)"THE STANDARD MOUSE INTERFACE MAY BE", &textcolor);
                font1->drawTextCentered(0, 7, -2.25, (char*)"EASIER TO LEARN", &textcolor);
            } else {
                font1->drawTextCentered(0, 9, -2.25, (char*)"MOUSE RELATIVE IS A LOT OF WORK.", &textcolor);
                font1->drawTextCentered(0, 8, -2.25, (char*)"ONLY THE RELATIVE MOUSE COORDINATES (MOVING)", &textcolor);
                font1->drawTextCentered(0, 7, -2.25, (char*)"WILL HAVE AN EFFECT", &textcolor);
            }
        } else if (controls == CONTROLS_KEYBOARD) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"DON'T TRY TO FLY WITH JUST THE KEYBOARD. USING A", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"JOYSTICK IS STRONLY RECOMMENDED, BUT IF NECESSARY", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"YOU CAN GET BY WITH MOUSE AND KEYBOARD.", &textcolor);
        }
    } else if (timer > timeroff + 2 * timerdelay && timer <= timeroff + 3 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"MOVING UP OR DOWN WILL AFFECT", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"THE ELEVATOR.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"YOU'LL START TO FLY A LOOP", &textcolor);
        } else if (controls == CONTROLS_MOUSE || controls == CONTROLS_KEYBOARD) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"MOVING RIGHT OR LEFT WILL AFFECT THE AILERON,", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"MOVING UP OR DOWN WILL AFFECT THE ELEVATOR.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"THUS YOU CAN FLY ROLLS AND LOOPS", &textcolor);
        }
    } else if (timer > timeroff + 3 * timerdelay && timer <= timeroff + 4 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"IF YOUR JOYSTICK HAS A RUDDER, YOU", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"MAY ALTER THE FIGHTER'S RUDDER.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"YOU'LL SLIGHTLY FLY TO THE LEFT OR RIGHT", &textcolor);
        } else if (controls == CONTROLS_MOUSE) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"MOVING THE MOUSE SLIGHTLY LEFT OR RIGHT", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"WILL AFFECT THE RUDDER.", &textcolor);
        } else if (controls == CONTROLS_KEYBOARD) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"TO ALTER THE RUDDER", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"USE THE KEYS PGUP AND PGDN", &textcolor);
        }
    } else if (timer > timeroff + 4 * timerdelay && timer <= timeroff + 5 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"YOUR JOYSTICK HAS ALSO A THROTTLE", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"TO SPEEDUP OR DECELERATE.", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"THERE IS NO WAY TO ENTIRELY STOP", &textcolor);
        } else {
            font1->drawTextCentered(0, 9, -2.25, (char*)"USE THE SQUARE BRACKET KEYS TO ALTER", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"YOUR THROTTLE (SPEED).", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"THERE IS NO WAY TO ENTIRELY STOP", &textcolor);
        }
    } else if (timer > timeroff + 5 * timerdelay && timer <= timeroff + 7 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"THE BUTTONS ON YOUR JOYSTICK CAN CONTROL ALL", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"OF YOUR WEAPONS AND FLIGHT SURFACES. YOU CAN MAKE", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"ANY BUTTON ACTIVATE ANY CONTROL BY EDITING THE", &textcolor);
            font1->drawTextCentered(0, 6, -2.25, (char*)"LACCONTROLS.TXT FILE IN THE .LAC FOLDER WITHIN", &textcolor);
            font1->drawTextCentered(0, 5, -2.25, (char*)"YOUR HOME FOLDER.", &textcolor);
        } else if (controls == CONTROLS_MOUSE) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"LEFT MOUSE BUTTON: FIRE CANNON", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"RIGHT MOUSE BUTTON: FIRE MISSILE", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"BUT YOU SHOULD REALLY PREFER THE KEYBOARD", &textcolor);
        } else if (controls == CONTROLS_KEYBOARD) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"NOW, LETS HAVE A LOOK AT SOME IMPORTANT KEYS", &textcolor);
        }
    } else if (timer > timeroff + 6 * timerdelay && timer <= timeroff + 8 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"A SUMMARY OF COMMANDS CAN BE FOUND IN THE MENU.", &textcolor);
            font1->drawTextCentered(0, 8, -2.25, (char*)"\"ESC\" WILL SHOW THE MENU", &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"AND RETURN BACK TO THE ACTION", &textcolor);
        } else {
            key2string(key_PRIMARY, buf2);
            sprintf(buf, "%s: FIRE CANNON", buf2);
            font1->drawTextCentered(0, 6, -2.25, buf, &textcolor);
            key2string(key_WEAPONSELECT, buf2);
            sprintf(buf, "%s: CHOOSE MISSILE", buf2);
            font1->drawTextCentered(0, 5, -2.25, buf, &textcolor);
            key2string(key_SECONDARY, buf2);
            sprintf(buf, "%s: FIRE MISSILE", buf2);
            font1->drawTextCentered(0, 4, -2.25, buf, &textcolor);
        }
    } else if (timer > timeroff + 7 * timerdelay && timer <= timeroff + 9 * timerdelay - timerlag) {
        RadarOnOff = 1;
        if (!RadarWasOn) {
            sound->setVolume(SOUND_BEEP2, 20);
            sound->play(SOUND_BEEP2, false);
            RadarWasOn = 1;
        }
        font1->drawTextCentered(0, 9, -2.25, (char*)"LOOK AT THE RADAR ON THE BOTTOM OF YOUR SCREEN.", &textcolor);
        font1->drawTextCentered(0, 8, -2.25, (char*)"THERE ARE ENEMIES REPRESENTED BY A WHITE DOT (TARGETED)", &textcolor);
        font1->drawTextCentered(0, 7, -2.25, (char*)"AND A YELLOW POINT (NOT TARGETED). ZOOM RADAR IN", &textcolor);
        font1->drawTextCentered(0, 6, -2.25, (char*)"AND OUT WITH HOME AND END KEYS OR WITH NUM+ AND NUM-.", &textcolor);
    } else if (timer > timeroff + 8 * timerdelay && timer <= timeroff + 10 * timerdelay - timerlag) {
        if (controls == CONTROLS_JOYSTICK) {
            font1->drawTextCentered(0, 9, -2.25, (char*)"TARGET AN ADVERSARY WITH A CONFIGURED JOYSTICK BUTTON,", &textcolor);
            key2string(key_TARGETNEXT, buf2);
            sprintf(buf, "HATSWITCH, OR BY PRESSING '%s' ON THE KEYBOARD.", buf2);
            font1->drawTextCentered(0, 8, -2.25, buf, &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"THEN APPROACH!", &textcolor);
        } else {
            font1->drawTextCentered(0, 9, -2.25, (char*)"YOU MAY TARGET AN ENEMY PRESSING", &textcolor);
            key2string(key_TARGETNEXT, buf2);
            sprintf(buf, "OR PRESSING '%s' ON THE KEYBOARD.", buf2);
            font1->drawTextCentered(0, 8, -2.25, buf, &textcolor);
            font1->drawTextCentered(0, 7, -2.25, (char*)"THEN APPROACH!", &textcolor);
        }
    } else if (timer > timeroff + 9 * timerdelay && timer <= timeroff + 11 * timerdelay - timerlag) {
        font1->drawTextCentered(0, 9, -2.25, (char*)"SHOOT THE TARGETS TO COMPLETE", &textcolor);
        font1->drawTextCentered(0, 8, -2.25, (char*)"THIS TUTORIAL SUCCESSFULLY", &textcolor);
    }
    if (timer >= timeroff + 7 * timerdelay && state == 0) {
        state++;
        ThreeDObjects[1]->activate();
        ThreeDObjects[1]->target = ThreeDObjects[0];
        ThreeDObjects[1]->o = &model_figu;
        ThreeDObjects[1]->newinit(FIGHTER_A6M2, 0, 200);
        ThreeDObjects[1]->tl->x = fplayer->tl->x - 30;
        ThreeDObjects[1]->tl->z = fplayer->tl->z - 30;
        ThreeDObjects[2]->activate();
        ThreeDObjects[2]->target = ThreeDObjects[0];
        ThreeDObjects[2]->o = &model_figu;
        ThreeDObjects[2]->newinit(FIGHTER_A6M2, 0, 200);
        ThreeDObjects[2]->tl->x = fplayer->tl->x + 30;
        ThreeDObjects[2]->tl->z = fplayer->tl->z + 30;
    }

    if (timer > timeroff + 10 * timerdelay) {
        if (!ThreeDObjects[1]->active && !ThreeDObjects[2]->active) {
            font1->drawTextCentered(0, 11, -2.25, (char*)"MISSION COMPLETED.", &textcolor);
            font1->drawTextCentered(0, 9, -2.25, (char*)"PRESS <ESC> TO RETURN TO MAIN MENU.", &textcolor);

        }
    }
}

MissionTutorial2::MissionTutorial2() {
    id = MISSION_TUTORIAL2;
    strncpy(name, "TUTORIAL2: AIR-TO-GROUND", 1024);
    strncpy(briefing, "IN THIS VERY SIMPLE MISSION, YOU WILL PRACTICE USING GUNS OR\nCANNONS VS ARMORED TARGETS.", 1024);
    selfighter[0] = DefaultAircraft;
    wantfighter = 0;
    selweapons = 1;
    selweapon[0] = MISSILE_GROUND1;
    wantweapon = 0;
    event_CommsMacro10();
}

void MissionTutorial2::start() {
    NoMissionHasYetCommenced = false;
    int i;
    day = 1;
    clouds = 2;
    weather = WEATHER_SUNNY;
    camera = 0;
    sungamma = 50;
    RadarOnOff = 0;
    event_RadarOnOff();
    IffOnOff = 0;
    RadarZoom = 3;
    event_IffOnOff();
    if (!HudLadderBarsOnOff) {
        event_HudLadderBarsOnOff();
    }
    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_FLATLAND, NULL);
    SeaLevel = -134.0;
    int px, py;

    l->searchPlain(-1, -1, &px, &py);
    l->flatten(AirfieldXMin + 30, AirfieldYMin + 4, 30, 5);
    playerInit();

    fplayer->tl->x = px;
    fplayer->tl->z = py + 150;
    fplayer->phi = 250;
    ConfigureOrdnanceForOnlineMissions();

    for (i = 1; i <= 2; i++) {
        ThreeDObjects[i]->party = 0;
        ThreeDObjects[i]->target = ThreeDObjects[0];
        ThreeDObjects[i]->o = &model_tank1;
        ThreeDObjects[i]->tl->x = px + 300 - i * 4;
        ThreeDObjects[i]->tl->z = py + 300 - i * 4;
        ThreeDObjects[i]->newinit(TANK_GROUND1, 0, 400);
        ThreeDObjects[i]->maxthrust = 0;
        ThreeDObjects[i]->activate();
    }
    fplayer->realspeed = (fplayer->DiveSpeedLimit1 * 0.75);
    fplayer->InertiallyDampenedPlayerSpeed = (fplayer->DiveSpeedLimit1 * 0.75);
    for (i = 0; i <= 9; i++) {
        fplayer->SpeedHistoryArray[i] = (fplayer->DiveSpeedLimit1 * 0.75);
    }
}

int MissionTutorial2::processtimer(Uint32 dt) {
    int i;
    timer += dt;
    fplayer->recelevatoreffect = 0;

    if (!fplayer->active && fplayer->explode >= 35 * timestep) {
        return 2;
    }
    for (i = 1; i <= 2; i++) {
        if (ThreeDObjects[i]->active) {
            ThreeDObjects[i]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 0.1;
        }
    }
    return 1;
}

void MissionTutorial2::draw() {
    int timeroff = 100 * timestep;

    if (timer >= 0 && timer <= timeroff - 20) {
        font1->drawTextCentered(0, 12, -2, name, &textcolor);
    }
}

MissionTutorial3::MissionTutorial3() {
    id = MISSION_TUTORIAL3;
    strncpy(name, "TUTORIAL3: FIGHTERS", 1024);
    strncpy(briefing, "HIGH SPEED DOGFIGHT PRACTICE. FIGHT BOTS WITH YOUR GUNS.\nNOTE THAT BOTS SOMETIMES MAKE SILLY MOVES AND ARE NOT AS SMART\nAS THE HUMAN PLAYERS YOU WILL FIND IN THE ONLINE MISSIONS.", 1024);
    selfighter[0] = DefaultAircraft;
    wantfighter = 0;
    selweapons = 1;
    selweapon[0] = MISSILE_AIR2;
    wantweapon = 0;
    event_CommsMacro10();
}

void MissionTutorial3::start() {
    int i;
    NoMissionHasYetCommenced = false;
    day = 1;
    clouds = 2;
    weather = WEATHER_SUNNY;
    camera = 0;
    IffOnOff = 0;
    RadarOnOff = 0;
    RadarZoom = 1;
    event_RadarOnOff();
    event_RadarZoomIn();
    event_RadarZoomIn();
    event_RadarZoomIn();
    event_RadarZoomIn();
    if (!HudLadderBarsOnOff) {
        event_HudLadderBarsOnOff();
    }
    event_IffOnOff();
    sungamma = 25;
    heading = 220;
    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_ALPINE, NULL);
    SeaLevel = 15.15;
    l->flatten(AirfieldXMin + 30, AirfieldYMin + 4, 30, 5);
    playerInit();
    fplayer->tl->x = 20;
    fplayer->tl->z = 70;
    fplayer->phi = 60;
    for (i = 1; i <= 12; i++) {
        ThreeDObjects[i]->party = 0;
        ThreeDObjects[i]->target = ThreeDObjects[0];
        ThreeDObjects[i]->o = &model_figAL;
        ThreeDObjects[i]->tl->x = -i * 120;
        ThreeDObjects[i]->tl->z = -i * 12;
        ThreeDObjects[i]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 45;
        ThreeDObjects[i]->newinit(BOMBER_G5M, 0, 400, 100, 800); // id, party, stupidity, precision, passivity
        ThreeDObjects[i]->deactivate();
        ThreeDObjects[i]->MyMissionPlayerNumber = i;
    }

    ThreeDObjects[2]->o = &model_figz;
    ThreeDObjects[2]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 45;
    ThreeDObjects[2]->newinit(FIGHTER_FW190, 0, 400, 100, 800); // id, party, stupidity, precision, passivity
    ThreeDObjects[2]->deactivate();

    ThreeDObjects[6]->o = &model_figv;
    ThreeDObjects[6]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 45;
    ThreeDObjects[6]->newinit(FIGHTER_A6M2, 0, 400, 100, 800); // id, party, stupidity, precision, passivity
    ThreeDObjects[6]->deactivate();

    ThreeDObjects[8]->o = &model_figv;
    ThreeDObjects[8]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 45;
    ThreeDObjects[8]->newinit(FIGHTER_A6M2, 0, 400, 100, 800); // id, party, stupidity, precision, passivity
    ThreeDObjects[8]->deactivate();

    MyNetworkId = 1;
    ThreeDObjects[2]->activate();
    ThreeDObjects[0]->target = 0;
    event_targetPreviousBlue();
    state = 0;
    laststate = 0;
    texttimer = 0;
    fplayer->realspeed = (fplayer->DiveSpeedLimit1 * 0.75);
    fplayer->InertiallyDampenedPlayerSpeed = (fplayer->DiveSpeedLimit1 * 0.75);
    for (i = 0; i <= 9; i++) {
        fplayer->SpeedHistoryArray[i] = (fplayer->DiveSpeedLimit1 * 0.75);
    }
}

int MissionTutorial3::processtimer(Uint32 dt) {
    bool AtLeastOneBlueTeamBotIsStillAlive = false;
    int i;
    fplayer->recelevatoreffect = 0;

    if (texttimer >= 200 * timestep) {
        texttimer = 0;
    }
    if (texttimer > 0) {
        texttimer += dt;
    }
    timer += dt;
    if (!fplayer->active && fplayer->explode >= 35 * timestep) {
        return 2;
    }

    BattleDamageRiskTimer += DeltaTime;
    if ((BattleDamageRiskTimer > 5000) || (BattleDamageRiskTimer > (abs)(myrandom(131072)))) { //  Get here at least every 5 seconds, or possibly sooner by random chance
        BattleDamageRiskTimer = 0;
        CalcDamageRiskFromNearbyOpposition();
        ThreeDObjects[0]->Durability -= CalculatedDamageDueToCurrentRisk; //  Admit damage for risk we took.
        if (CalculatedDamageDueToCurrentRisk > 0) {
            sprintf(DebugBuf, "MissionTutorial3::processtimer fplayer->Durability is now %f.", fplayer->Durability);
            display(DebugBuf, LOG_MOST);
            if (fplayer->Durability < 0) { //  Get here if damage from locally managed airfields or bombers killed us.
                UpdateOnlineScoreLogFileWithCalculatedRisks();
            }
        }
        CalculatedDamageDueToCurrentRisk = 0; //  After admitting that damage amount, clear it.
    }

    for (i = 1; i <= 12; i++) {
        if (ThreeDObjects[i]->active) {
            if (!(i % 2)) {
                AtLeastOneBlueTeamBotIsStillAlive = true;
            }
        }
    }
    if (AtLeastOneBlueTeamBotIsStillAlive) {
        return 0;
    }

    state++;
    if (state >= 3) {
        state = 3;
    } else {
        display((char*)"MissionTutorial3::processtimer(): Advancing state.", LOG_MOST);
    }

    if (state == 1) {
        display((char*)"MissionTutorial3::processtimer(): state advanced from 0 to 1.", LOG_MOST);
        for (i = 2; i <= 6; i = (i + 2)) {
            ThreeDObjects[i]->activate();
            ThreeDObjects[i]->tl->x = fplayer->tl->x + 50 + 10 * i;
            ThreeDObjects[i]->tl->z = fplayer->tl->z + 50 + 10 * i;
            ThreeDObjects[i]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 25;
        }
        return 0;
    } else if (state == 2) {
        display((char*)"MissionTutorial3::processtimer(): state advanced from 1 to 2.", LOG_MOST);
        for (i = 8; i <= 12; i = (i + 2)) {
            ThreeDObjects[i]->activate();
            ThreeDObjects[i]->tl->x = fplayer->tl->x + 50 + 10 * i;
            ThreeDObjects[i]->tl->z = fplayer->tl->z + 50 + 10 * i;
            ThreeDObjects[i]->tl->y = l->getHeight(ThreeDObjects[i]->tl->x, ThreeDObjects[i]->tl->z) + 15;
        }
        return 0;
    } else if (state == 3) {
        display((char*)"MissionTutorial3::processtimer(): state advanced from 2 to 3.", LOG_MOST);
        return 0;
    }
    return 1;
}

void MissionTutorial3::draw() {
    char buf[250], buf2[10];
    int timeroff = 190 * timestep, timerdelay = 400 * timestep, timerlag = 20 * timestep;

    if (laststate != state) {
        texttimer = 1;
        laststate = state;
    }
    if (texttimer > 0) {
        if (state == 1) {
            static bool Latch = 0;
            font1->drawTextCentered(0, 7, -2.5, (char*)"YOU DEFEATED A SINGLE OPPONENT IN AN EARLY-WAR GERMAN FIGHTER PLANE.", &textcolor);
            font1->drawTextCentered(0, 6, -2.5, (char*)"BUT CAN YOU HANDLE 2 OPPONENTS, WHERE ONE HAS A TAIL GUNNER?", &textcolor);
            if ((!(NetworkMode & 16)) && (!Latch)) {
                //popen ("espeak -p 10 -a 66  -s 160 \"YOU DEFEATED A SINGLE OPPONENT IN AN EARLY-WAR GERMAN FIGHTER PLANE. BUT CAN YOU HANDLE TWO OPPONENTS, WHERE ONE HAS A TAIL GUNNER? \"", "r");
                Latch = 1;
            }
            return;
        }
        if (state == 2) {
            static bool Latch = 0;
            font1->drawTextCentered(0, 6, -2.5, (char*)"OK, LET'S TRY THREE OPPONENTS. TWO HAVE TAIL GUNNERS.", &textcolor);
            if ((!(NetworkMode & 16)) && (!Latch)) {
                //popen ("espeak -p 10 -a 66  -s 160 \"OK, LET'S TRY THREE OPPONENTS. TWO HAVE TAIL GUNNERS. \"", "r");
                Latch = 1;
            }
            return;
        }
    }
    if (state == 3) {
        static bool Latch = 0;
        font1->drawTextCentered(0, 12, -2.5, (char*)"MISSION COMPLETE.", &textcolor);
        font1->drawTextCentered(0, 10, -2.5, (char*)"FOR A MORE SOPHISTICATED MISSION, WE RECOMMEND NETWORK BATTLE 03.", &textcolor);
        if ((!(NetworkMode & 16)) && (!Latch)) {
            //popen ("espeak -p 10 -a 66  -s 160 \"MISSION COMPLETE. FOR A MORE SOPHISTICATED MISSION, WE RECOMMEND NETWORK BATTLE 03. \"", "r");
            Latch = 1;
        }
        if (timer > 1000) {
            state = 4;
        }
    }
    if (timer >= 0 && timer <= timeroff - timerlag) {
        font1->drawTextCentered(0, 12, -2, name, &textcolor);
    }
    if (timer >= timeroff + 6 * timerdelay && timer <= timeroff + 8 * timerdelay - timerlag && state > 0) {
        font1->drawTextCentered(0, 15, -2.5, (char*)"SOME TARGETING HINTS FOR RED-TEAM PLAYERS LIKE YOU:", &textcolor);
        key2string(key_TARGETPREVIOUS, buf2);
        sprintf(buf, "'%s' WILL TARGET THE PREVIOUS BLUE RADAR BLIP", buf2);
        font1->drawTextCentered(0, 13, -2.5, buf, &textcolor);
        key2string(key_RadarZoomIn, buf2);
        sprintf(buf, "'%s' WILL ZOOM RADAR RANGE IN,", buf2);
        font1->drawTextCentered(0, 10, -2.5, buf, &textcolor);
        key2string(key_RadarZoomOut, buf2);
        sprintf(buf, "'%s' WILL ZOOM RADAR RANGE OUT,", buf2);
        font1->drawTextCentered(0, 9, -2.5, buf, &textcolor);
        key2string(key_TARGETNEXT, buf2);
        sprintf(buf, "('%s' WOULD TARGET THE NEXT RED RADAR BLIP,)", buf2);
        font1->drawTextCentered(0, 7, -2.5, buf, &textcolor);
    }
}

MissionHeadToHead00::MissionHeadToHead00() {

    id = MISSION_HEADTOHEAD00;
    strncpy(name, "HEAD TO HEAD 00", 1024);
    strncpy(briefing, "SHOOT MINDLESS BOTS OR A SENTIENT NETWORK PEER!\nTHIS MISSION REQUIRES INTERNET ACCESS. EDIT YOUR LACCONFIG.TXT\nFILE TO SPECIFY THE IP ADDRESS OF YOUR SINGLE OPPONENT\nOR LAC SERVER. ONLY 2 PLAYERS IN THIS MISSION.", 1024);
    selfighter[0] = DefaultAircraft;
    selfighter[1] = FIGHTER_A6M2;
    selfighter[2] = FIGHTER_HAWK;
    selfighters = 2;
    selweapons = 1;

    NetworkReceiveTimerInterval = NetworkTransmitTimerInterval / 3;
    LoadServerIpAddress();

    NetworkOpponent = 0;
    if ((NetworkMode & 1) == 0) {
        if (OpenUdpSocketForReceiving() == 0) {
            ConfigureIncomingUdpSocket();
        } else {
        }
        if (OpenUdpSocketForSending() == 0) {
            ConfigureOutgoingUdpSocket();
        } else {
        }
    } else if ((NetworkMode & 1) == 1) {
        if (OpenClientUdpSocket() == 0) {
            ConfigureClientUdpSocket();
        } else {
        }
    } else {
    }
    event_CommsMacro10();
}

void MissionHeadToHead00::start() {
    NoMissionHasYetCommenced = false;

    NetworkPlayerKilled = false;
    state = 0;
    laststate = 0;
    texttimer = 0;
    int i;
    int i2;
    day = 1;
    clouds = 2;
    weather = WEATHER_SUNNY;
    camera = 0;
    sungamma = 50;
    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_ALPINE_SEA, NULL);
    SeaLevel = -12.915000;

    l->flatten(AirfieldXMin + 28.0, AirfieldYMin + 4, 29.2, 5);
    l->flatten(AirfieldXMin + 46, AirfieldYMin + 5, 7, 6);
    playerInit();
    PlayerAircraftType = fplayer->id;
    fplayer->party = 1;

    int r = myrandom(200);
    r -= 100;
    float RandomFloat = (float)r;
    fplayer->tl->x = AirfieldXMin;
    fplayer->tl->x += RandomFloat;
    fplayer->tl->z = AirfieldYMin;
    fplayer->tl->z += RandomFloat;
    MissionRunning = false;
    fplayer->phi = 270;
    fplayer->maxthrust *= 1.10;

    HudOnOff = 1;
    if (!HudLadderBarsOnOff) {
        event_HudLadderBarsOnOff();
    }
    IffOnOff = 0;
    MapViewOnOff = 0;
    RadarOnOff = 0;
    RadarZoom = 1;
    ScreenFOVx = 1.0;
    ScreenFOVy = 1.0;

    event_IffOnOff();
    event_RadarOnOff();
    MaxPlayersInCurrentMission = 2;

    for (i = 1; i <= 9; i++) {
        ThreeDObjects[i]->target = ThreeDObjects[0];
        ThreeDObjects[i]->tl->x = -i * 10;
        ThreeDObjects[i]->tl->z = -i * 10;
        ThreeDObjects[i]->o = &model_figv;
        ThreeDObjects[i]->party = 1;
        ThreeDObjects[i]->newinit(FIGHTER_A6M2, 0, 1200);
        for (i2 = 0; i2 < missiletypes; i2++) {
            ThreeDObjects[i]->missiles[i2] = 0;
        }
        NetworkApiPriorXPosition[i] = -15;
        NetworkApiPriorZPosition[i] = 45;
        NetworkApiPriorYPosition[i] = 5;

        if (i > 1) {
            ThreeDObjects[i]->deactivate();
        }
    }
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    ThreeDObjects[1]->thrustDown();
    NetworkApiPriorTimer[MissionHeadToHead00State] = timer;

    state = 1;
    MissionHeadToHead00State = (unsigned char)state;
    MissionOutPacketCount = 0;
    MissionIdNegotiationCount = 0;
    fplayer->realspeed = (fplayer->DiveSpeedLimit1 * 0.75);
    fplayer->InertiallyDampenedPlayerSpeed = (fplayer->DiveSpeedLimit1 * 0.75);
    for (i = 0; i <= 9; i++) {
        fplayer->SpeedHistoryArray[i] = (fplayer->DiveSpeedLimit1 * 0.75);
    }
    ConfigureOrdnanceForOnlineMissions();
    // Ensure aircraft is ready for combat
    ThrustReadiness = (
        (float)fplayer->DefensiveLethality +
        fplayer->maxthrust +
        fplayer->RollRate +
        fplayer->manoeverability +
        fplayer->maxDurability +
        fplayer->maxgamma +
        (float)fplayer->statLethality +
        fplayer->StaticDrag +
        fplayer->SpeedBrakePower +
        fplayer->MaxFullPowerAltRatio +
        fplayer->inertia +
        fplayer->deadweight +
        fplayer->CompressibilitySpeed +
        fplayer->CompressibilitySpeedWithSpeedBrakes +
        fplayer->StallSpeed +
        fplayer->ServiceCeilingAltitude
        );
    if (fplayer->WepCapable) {
        ThrustReadiness += 200;
    }
    if (ThrustReadiness < 1000) {
        display((char*)"Error. Selected Aircraft ThrustReadiness is insufficient.", LOG_MOST);
        game_quit(); // Airplane performance parameters didn't load properly.
    }
}

int MissionHeadToHead00::processtimer(Uint32 dt) {

    extern int PriorPeerId;
    bool AtLeastOneActiveAiIsStillAlive = false;
    int i;
    int BytesReceived = 0;
    fplayer->recelevatoreffect = 0;

    if (!MissionRunning) {

        DegradeFlightModelDueToOrdnanceLoad();
        fplayer->tl->y = l->getHeight(AirfieldXMin + 1, AirfieldYMin + 2);
        if (fplayer->missiles[0] >= 4) {
            fplayer->tl->y += 160;
            fplayer->tl->x = AirfieldXMin - 120;
        } else {
            fplayer->tl->y += 21;
        }

        fplayer->UndercarriageLevel = 0;
        fplayer->FlapsLevel = 1;
        MissionRunning = true;
    }

    StateTransitionTimer += dt;
    texttimer += dt;
    timer += dt;
    if (StateTransitionTimer < 0) {
        DiscardAnyInPacketsInQueue();
    }

    PriorPeerId = ThreeDObjects[state]->id;

    NetworkReceiveTimer += dt;
    if ((NetworkReceiveTimer > NetworkReceiveTimerInterval) && (StateTransitionTimer >= 0)) {
        NetworkReceiveTimer = 0;
        BytesReceived = GetNetworkApiPacket();
        if (BytesReceived == sizeof(LacUdpApiPacket)) {
            display((char*)"MissionHeadtoHead00 BytesReceived=", LOG_NET);
            sprintf(DebugBuf, "%i", BytesReceived);
            display(DebugBuf, LOG_NET);
            MissedPacketCount = 0;
            MissionHeadToHead00LoadVariablesFromNetworkApiPacket(timer);
            if (PriorPeerId != ThreeDObjects[state]->id) {

                ThreeDObjects[state]->newinit(ThreeDObjects[state]->id, 0, 395);
            }
            if (!PeerPacketReceivedInThisMissionState) {
                PeerPacketReceivedInThisMissionState = true;
                sound->setVolume(SOUND_NEWBANDITONRADARO1, 99);
                sound->play(SOUND_NEWBANDITONRADARO1, false);
            }
        } else {
            MissedPacketCount++;
            if (MissedPacketCount > 75 * (200 / NetworkReceiveTimerInterval)) {
                MissedPacketCount = 0;
                if (PeerPacketReceivedInThisMissionState) {
                    PeerPacketReceivedInThisMissionState = false;
                    sound->setVolume(SOUND_RADARBANDITDISAPPEARED01, 99);
                    sound->play(SOUND_RADARBANDITDISAPPEARED01, false);
                }
            }
        }
    }

    NetworkTransmitTimer += dt;
    if (NetworkTransmitTimer > NetworkTransmitTimerInterval && !NetworkPlayerKilled) {
        NetworkTransmitTimer = 0;
        MissionHeadToHead00RetrieveFirstDamageDescription();
        SendNetworkApiPacket();
    }

    if (!fplayer->active && fplayer->explode >= 2 * timestep) {
        NetworkPlayerKilled = true;
        sound->haltMusic();
        sound->stop(SOUND_PLANE1);
        sound->stop(SOUND_PLANE2);
        sound->stop(SOUND_WINDNOISE);
        WindNoiseOn = false;
    }
    if (!fplayer->active && fplayer->explode >= 100 * timestep) {

        display((char*)"MissionHeadToHead00::processtimer() NetworkPlayerKilled.", LOG_MOST);
        game_quit();
    }

    for (i = 0; i <= 9; i++) {
        if (ThreeDObjects[i]->active)
            if (ThreeDObjects[i]->party == 0) {
                AtLeastOneActiveAiIsStillAlive = true;
            }
    }
    if (AtLeastOneActiveAiIsStillAlive) {
        return 0;
    }

    DiscardAnyInPacketsInQueue();

    NetworkReceiveTimer = -2500; // Wait awhile before getting next InPacket
    StateTransitionTimer = -2000;
    state++;
    NetworkOpponent = false;
    PeerPacketReceivedInThisMissionState = false;
    if (state > 10) {
        state = 10;
    }
    ThreeDObjects[1]->fighterkills = state - 1;
    MissionHeadToHead00State = (unsigned char)state; // Advertise our state globally

    if (state == 2) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 40;
        return 0;
    }
    if (state == 3) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 50;
        return 0;
    }
    if (state == 4) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 60;
        return 0;
    }
    if (state == 5) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 70;
        return 0;
    }
    if (state == 6) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 80;
        return 0;
    }
    if (state == 7) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 90;
        return 0;
    }
    if (state == 8) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 100;
        return 0;
    }
    if (state == 9) {

        ThreeDObjects[state]->activate();
        int phi = 120 * i;
        ThreeDObjects[state]->tl->x = -10;
        ThreeDObjects[state]->tl->z = fplayer->tl->z + 40 * SIN(phi);
        ThreeDObjects[state]->tl->y = l->getHeight(ThreeDObjects[state]->tl->x, ThreeDObjects[state]->tl->z) + 110;
        return 0;
    }
    return 1;
}

void MissionHeadToHead00::draw() {
    int timeroff = 100 * timestep, timerlag = 20 * timestep;

    if (timer >= 0 && timer <= timeroff - timerlag) {
        font1->drawTextCentered(0, 12, -2, name, &textcolor);
    }
}

void MissionHeadToHead00LoadVariablesFromNetworkApiPacket(int timer) {

    unsigned char PlayerNumber;

    extern LacUdpApiPacket InPacket;
    display((char*)"MissionHeadToHead00LoadVariablesFromNetworkApiPacket()", LOG_NET);

    if (InPacket.NetworkApiVersion != NetworkApiVersion) {

        sound->setVolume(SOUND_BEEP1, 80);
        sound->play(SOUND_BEEP1, false);
        display((char*)"MissionHeadToHead00LoadVariablesFromNetworkApiPacket() discarded a UDP packet.", LOG_ERROR);
        display((char*)"Reason: Unexpected NetworkApiVersionNumber:", LOG_ERROR);
        sprintf(DebugBuf, "We are using NetworkApiVersion %d", NetworkApiVersion);
        display(DebugBuf, LOG_ERROR);
        if (NetworkApiVersion < InPacket.NetworkApiVersion) {
            sprintf(DebugBuf, "We received an InPacket using newer NetworkApiVersion %d", InPacket.NetworkApiVersion);
            display(DebugBuf, LOG_ERROR);
            display((char*)"This means that you probably need to download a newer version of LAC for compatibility.", LOG_ERROR);
        } else {
            sprintf(DebugBuf, "We received an InPacket using older NetworkApiVersion %d", LOG_ERROR);
            display(DebugBuf, LOG_ERROR);
            display((char*)"Please inform all players that you have upgraded to a newer version of LAC for compatibility.", LOG_ERROR);
        }
        return;
    }
    NetworkOpponent = 1;

    PlayerNumber = MissionHeadToHead00State;
    display((char*)"MissionHeadToHead00LoadVariablesFromNetworkApiPacket() PlayerNumber=", LOG_NET);
    sprintf(DebugBuf, "%d", PlayerNumber);
    display(DebugBuf, LOG_NET);

    ThreeDObjects[PlayerNumber]->id = (int)InPacket.UdpObjVehicle;

    ThreeDObjects[PlayerNumber]->tl->x = InPacket.UdpObjXPosition;
    ThreeDObjects[PlayerNumber]->tl->y = InPacket.UdpObjYPosition;
    ThreeDObjects[PlayerNumber]->tl->z = InPacket.UdpObjZPosition;

    ThreeDObjects[PlayerNumber]->gamma = InPacket.UdpObjGamma;
    ThreeDObjects[PlayerNumber]->phi = InPacket.UdpObjPhi;
    ThreeDObjects[PlayerNumber]->theta = InPacket.UdpObjTheta;

    ThreeDObjects[PlayerNumber]->realspeed = InPacket.UdpObjSpeed;
    ThreeDObjects[PlayerNumber]->thrust = InPacket.UdpObjThrust;
    ThreeDObjects[PlayerNumber]->elevatoreffect = InPacket.UdpObjElevator;
    ThreeDObjects[PlayerNumber]->ruddereffect = InPacket.UdpObjRudder;
    ThreeDObjects[PlayerNumber]->rolleffect = InPacket.UdpObjAileron;
    NetworkApiPriorXPosition[MissionHeadToHead00State] = InPacket.UdpObjXPosition;
    NetworkApiPriorYPosition[MissionHeadToHead00State] = InPacket.UdpObjYPosition;
    NetworkApiPriorZPosition[MissionHeadToHead00State] = InPacket.UdpObjZPosition;
    NetworkApiPriorTimer[MissionHeadToHead00State] = timer;
    fplayer->Durability -= InPacket.UdpObjDamageAmount; // Accept damage from peer
}

bool MissionHeadToHead00RetrieveFirstDamageDescription() {
    display((char*)"MissionHeadToHead00RetrieveFirstDamageDescription()", LOG_NET);
    MissionAircraftDamaged = 1;
    DamageToClaim = ThreeDObjects[1]->DamageInNetQueue;
    ThreeDObjects[1]->DamageInNetQueue = 0;
    return (false);
}

MissionFreeFlightWW2::MissionFreeFlightWW2() {
    id = MISSION_FREEFLIGHTWW2;
    strncpy(name, "FREE FLIGHT", 1024);
    strncpy(briefing, "FREE FLIGHT OVER THE BLUE OCEAN, WITH NO OPPOSITION", 1024);
    selweapons = 1;
    wantfighter = 0;
    selweapons = 1;
    selweapon[0] = MISSILE_AIR2;
    wantweapon = 0;
    event_CommsMacro10();
}

void MissionFreeFlightWW2::start() {
    int i;
    NoMissionHasYetCommenced = false;
    day = 1;
    clouds = 2;
    weather = WEATHER_SUNNY;
    camera = 0;
    sungamma = 25;
    RadarOnOff = 1;
    RadarZoom = 1;
    IffOnOff = 1;
    event_RadarOnOff();
    event_IffOnOff();
    heading = 220;

    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_ALPINE_SEA, NULL);
    SeaLevel = -12.915;
    l->flatten(AirfieldXMin + 28.0, AirfieldYMin + 4, 29.2, 5);
    l->flatten(AirfieldXMin + 46, AirfieldYMin + 5, 7, 6);
    playerInit();
    fplayer->tl->x = 0;
    fplayer->tl->y = 200;
    fplayer->tl->z = 50;
    state = 0;
    laststate = 0;
    texttimer = 0;
    if (fplayer->id == FIGHTER_HAWK) {
        if (HudLadderBarsOnOff == 0) {
            event_HudLadderBarsOnOff(); // Turn on Hud Ladder Bars if in a jet
        }
        event_IffOnOff();
    }
    if (fplayer->id == FIGHTER_HAWK) {
        fplayer->missiles[0] = 0;
        fplayer->missiles[1] = 4;
        fplayer->missiles[2] = 2;
        fplayer->missiles[3] = 0;
        fplayer->missiles[4] = 0;
        fplayer->chaffs = 10;
        fplayer->flares = 10;
    } else {
        fplayer->missiles[0] = 0;
        fplayer->missiles[1] = 0;
        fplayer->missiles[2] = 0;
        fplayer->missiles[3] = 0;
        fplayer->missiles[4] = 0;
        fplayer->chaffs = 0;
        fplayer->flares = 0;
    }
    fplayer->realspeed = (fplayer->DiveSpeedLimit1 * 0.75);
    fplayer->InertiallyDampenedPlayerSpeed = (fplayer->DiveSpeedLimit1 * 0.75);
    for (i = 0; i <= 9; i++) {
        fplayer->SpeedHistoryArray[i] = (fplayer->DiveSpeedLimit1 * 0.75);
    }
}

int MissionFreeFlightWW2::processtimer(Uint32 dt) {
    fplayer->recelevatoreffect = 0;
    if (texttimer >= 200 * timestep) {
        texttimer = 0;
    }
    if (texttimer > 0) {
        texttimer += dt;
    }
    timer += dt;
    return 0;
}

void MissionFreeFlightWW2::draw() {
    if (timer >= 0 && timer <= 50 * timestep) {
        font1->drawTextCentered(0, 12, -2, name, &textcolor);
    }
}

void TestDamageMissionObjectHqBlue() {
    display((char*)"TestDamageMissionObjectHqBlue():  Function Entry.", LOG_MOST);
    sprintf(DebugBuf, "TestDamageMissionHqBlue():  BlueHq Strength at function entry = %f. fplayer->Durability = %f.", ThreeDObjects[MissionObjectHqBlue]->Durability, fplayer->Durability);
    display(DebugBuf, LOG_MOST);
    if (ThreeDObjects[MissionObjectHqBlue]->Durability > ((ThreeDObjects[MissionObjectHqBlue]->maxDurability) / 5.0)) {
        display((char*)"TestDamageMissionObjectHqBlue():  BlueHq strength is higher than TestDamage threshold.", LOG_MOST);
        display((char*)"TestDamageMissionObjectHqBlue():  Inflicting heavy damage on MissionObjectHqBlue.", LOG_MOST);
        ThreeDObjects[MissionObjectHqBlue]->Durability -= AIRFIELDMAXDURABILITY / 10.0;
        ThreeDObjects[MissionObjectHqBlue]->DamageInNetQueue = AIRFIELDMAXDURABILITY / 10.0;
        sprintf(DebugBuf, "TestDamageMissionHqBlue(): Strength after new damage = %f. MissionEndingTimer = %d. MissionEndingTimer2 = %d.", ThreeDObjects[MissionObjectHqBlue]->Durability, MissionEndingTimer, MissionEndingTimer2);
        display(DebugBuf, LOG_MOST);
    } else {
        display((char*)"TestDamageMissionObjectHqBlue():  BlueHq strength is lower than TestDamage threshold. NOT inflicting more damage.", LOG_MOST);
        sprintf(DebugBuf, "TestDamageMissionHqBlue(): Strength now = %f. MissionEndingTimer = %d. MissionEndingTimer2 = %d.", ThreeDObjects[MissionObjectHqBlue]->Durability, MissionEndingTimer, MissionEndingTimer2);
        display(DebugBuf, LOG_MOST);
    }
    sprintf(DebugBuf, "TestDamageMissionHqBlue(): At function exit, fplayer->Durability = %f.\n", fplayer->Durability);
    display(DebugBuf, LOG_MOST);
}

void TestDamageMissionObjectHqRed() {
    display((char*)"TestDamageMissionObjectHqRed():  Function Entry.", LOG_MOST);
    sprintf(DebugBuf, "TestDamageMissionHqRed():  RedHq Strength at function entry = %f. fplayer->Durability = %f.", ThreeDObjects[MissionObjectHqRed]->Durability, fplayer->Durability);
    display(DebugBuf, LOG_MOST);
    if (ThreeDObjects[MissionObjectHqRed]->Durability > ((ThreeDObjects[MissionObjectHqRed]->maxDurability) / 5.0)) {
        display((char*)"TestDamageMissionObjectHqRed():  RedHq strength is higher than TestDamage threshold.", LOG_MOST);
        display((char*)"TestDamageMissionObjectHqRed():  Inflicting heavy damage on MissionObjectHqRed.", LOG_MOST);
        ThreeDObjects[MissionObjectHqRed]->Durability -= AIRFIELDMAXDURABILITY / 10.0;
        ThreeDObjects[MissionObjectHqRed]->DamageInNetQueue = AIRFIELDMAXDURABILITY / 10.0;
        sprintf(DebugBuf, "TestDamageMissionHqRed(): Strength after new damage = %f. MissionEndingTimer = %d. MissionEndingTimer2 = %d.", ThreeDObjects[MissionObjectHqRed]->Durability, MissionEndingTimer, MissionEndingTimer2);
        display(DebugBuf, LOG_MOST);
    } else {
        display((char*)"TestDamageMissionObjectHqRed():  RedHq strength is lower than TestDamage threshold. NOT inflicting more damage.", LOG_MOST);
        sprintf(DebugBuf, "TestDamageMissionHqRed(): Strength now = %f. MissionEndingTimer = %d. MissionEndingTimer2 = %d.", ThreeDObjects[MissionObjectHqRed]->Durability, MissionEndingTimer, MissionEndingTimer2);
        display(DebugBuf, LOG_MOST);
    }
    sprintf(DebugBuf, "TestDamageMissionHqRed(): At function exit, fplayer->Durability = %f.\n", fplayer->Durability);
    display(DebugBuf, LOG_MOST);
}

void TestDamageMissionObjectAirfieldBlue2() {
    if (ThreeDObjects[MissionObjectAirfieldBlue2]->Durability > ((ThreeDObjects[MissionObjectAirfieldBlue2]->maxDurability) / 7.0)) {
        display((char*)"TestDamageMissionObjectAirfieldBlue2(): Inflicting heavy damage on MissionObjectAirfieldBlue2.", LOG_MOST);
        ThreeDObjects[MissionObjectAirfieldBlue2]->Durability -= AIRFIELDMAXDURABILITY / 10.2;
        ThreeDObjects[MissionObjectAirfieldBlue2]->DamageInNetQueue = AIRFIELDMAXDURABILITY / 10.0;
        sprintf(DebugBuf, "TestDamageMissionObjectAirfieldBlue2(): Strength now = %f", ThreeDObjects[MissionObjectAirfieldBlue2]->Durability);
        display(DebugBuf, LOG_MOST);
    }
}

void TestDamageMissionObjectAirfieldRed2() {
    if (ThreeDObjects[MissionObjectAirfieldRed2]->Durability > ((ThreeDObjects[MissionObjectAirfieldRed2]->maxDurability) / 7.0)) {
        display((char*)"TestDamageMissionObjectAirfieldRed2(): Inflicting heavy damage on MissionObjectAirfieldRed2.", LOG_MOST);
        ThreeDObjects[MissionObjectAirfieldRed2]->Durability -= AIRFIELDMAXDURABILITY / 10.2;
        ThreeDObjects[MissionObjectAirfieldRed2]->DamageInNetQueue = AIRFIELDMAXDURABILITY / 10.0;
        sprintf(DebugBuf, "TestDamageMissionObjectAirfieldRed2(): Strength now = %f", ThreeDObjects[MissionObjectAirfieldRed2]->Durability);
        display(DebugBuf, LOG_MOST);
    }
}

void TestDamageMissionObjectCarrierBlue1() {
    if (ThreeDObjects[MissionObjectCarrierBlue1]->Durability > ((ThreeDObjects[MissionObjectCarrierBlue1]->maxDurability) / 7.0)) {
        display((char*)"TestDamageMissionObjectCarrierBlue1(): Inflicting heavy damage on MissionObjectCarrierBlue1.", LOG_MOST);
        ThreeDObjects[MissionObjectCarrierBlue1]->Durability -= ThreeDObjects[MissionObjectCarrierBlue1]->maxDurability / 10.0;
        ThreeDObjects[MissionObjectCarrierBlue1]->DamageInNetQueue = ThreeDObjects[MissionObjectCarrierBlue1]->maxDurability / 10.0;
        sprintf(DebugBuf, "TestDamageMissionObjectCarrierBlue1(): Strength now = %f", ThreeDObjects[MissionObjectCarrierBlue1]->Durability);
        display(DebugBuf, LOG_MOST);
    }
}

void TestDamageMissionObjectCarrierRed1() {
    if (ThreeDObjects[MissionObjectCarrierRed1]->Durability > ((ThreeDObjects[MissionObjectCarrierRed1]->maxDurability) / 7.0)) {
        display((char*)"TestDamageMissionObjectCarrierRed1(): Inflicting heavy damage on MissionObjectCarrierRed1.", LOG_MOST);
        ThreeDObjects[MissionObjectCarrierRed1]->Durability -= ThreeDObjects[MissionObjectCarrierRed1]->maxDurability / 10.0;
        ThreeDObjects[MissionObjectCarrierRed1]->DamageInNetQueue = ThreeDObjects[MissionObjectCarrierRed1]->maxDurability / 10.0;
        sprintf(DebugBuf, "TestDamageMissionObjectCarrierRed1(): Strength now = %f", ThreeDObjects[MissionObjectCarrierRed1]->Durability);
        display(DebugBuf, LOG_MOST);
    }
}

#include "MissionNetworkBattle01.cpp"

#include "MissionNetworkBattle02.cpp"

#include "MissionNetworkBattle03.cpp"

#include "MissionNetworkBattle04.cpp"

#include "MissionNetworkBattle05.cpp"

#include "MissionNetworkBattle06.cpp"

#include "MissionNetworkBattle07.cpp"

#include "MissionNetworkBattle08.cpp"

#include "MissionNetworkBattle09.cpp"

#include "MissionNetworkBattle10.cpp"

void RearmRefuelRepair() {
    char TerrainTypeHere;

    TerrainTypeHere = l->GLLandscape::getTerrainType(fplayer->tl->x, fplayer->tl->z);

    if (TerrainTypeHere == 0) {
        if (fplayer->tl->y < 13 || fplayer->tl->y > 25) {
            //display ("RearmRefuelRepair() aborting because player has not landed on a runway or an aircraft carrier.", LOG_MOST);
            return;
        }
    }
#ifndef RASPBIAN
    else if (TerrainTypeHere != -1) {
        //display ("RearmRefuelRepair() aborting because player has not landed on a runway.", LOG_MOST);
        return;
    }
#else
    else if (TerrainTypeHere != 255) {
        display((char*)"RearmRefuelRepair() aborting because player has not landed on a runway.", LOG_MOST);
        return;
    }
#endif
    if (FratricideShameFactor > 60000.0) {
        sprintf(SystemMessageBufferA, "YOU ARE ORDERED TO THE BRIG AWATING COURT-MARTIAL FOR TREASON!");
        NewSystemMessageNeedsScrolling = true;
        return;
    }
    if (MyNetworkId % 2) {
        if (fplayer->tl->x < 0.0) {
            sprintf(SystemMessageBufferA, "THIS IS A HOSTILE AIRFIELD!");
            NewSystemMessageNeedsScrolling = true;

            if (fplayer->FuelLevel > 6) {
                fplayer->FuelLevel = 6;
            }
            if (fplayer->ammo > 30) {
                fplayer->ammo = 30;
            }
            return;
        }
    } else {
        if (fplayer->tl->x > 0.0) {
            sprintf(SystemMessageBufferA, "THIS IS A HOSTILE AIRFIELD!");
            NewSystemMessageNeedsScrolling = true;

            if (fplayer->FuelLevel > 6) {
                fplayer->FuelLevel = 6;
            }
            if (fplayer->ammo > 30) {
                fplayer->ammo = 30;
            }
            return;
        }
    }
    FuelLevelAtLastLanding = fplayer->FuelLevel;
    LandingTimer += DeltaTime;
    if (fplayer->id != FIGHTER_ME163) {
        if (fplayer->FuelLevel >= 99 && fplayer->Durability >= fplayer->maxDurability) {
            fplayer->FuelLevel = 100;
            if (RefuelRearmRepairDurationTimer < 76) {
                sprintf(SystemMessageBufferA, "REARMED, REFUELED, REPAIRED.");
                NewSystemMessageNeedsScrolling = true;
                ConfigureOrdnanceForOnlineMissions();
            }
        }
        if (LandingTimer > 1000 && fplayer->realspeed < 0.05) {
            LandingTimer = 0;

            fplayer->InertiallyDampenedPlayerSpeed = 0.0;
            ClearSpeedHistoryArrayFlag = true;
            fplayer->accx = 0.0;
            fplayer->accy = 0.0;
            fplayer->accz = 0.0;
            fplayer->realspeed = 0.0;
            RefuelRearmRepairDurationTimer++;

            fplayer->Durability *= 1.02;
            if (fplayer->Durability > fplayer->maxDurability) {
                fplayer->Durability = fplayer->maxDurability;

                ConfigureOrdnanceForOnlineMissions();
                IffOnOff = true;
            }
            if (CurrentMissionNumber == MISSION_NETWORKBATTLE03) {
                if (fplayer->FuelLevel < 25) {
                    fplayer->FuelLevel += 10;
                } else if (fplayer->FuelLevel < 50) {
                    fplayer->FuelLevel += 20;
                } else if (fplayer->FuelLevel < 75) {
                    fplayer->FuelLevel += 30;
                } else {
                    fplayer->FuelLevel += 40;

                    fplayer->maxthrust = PlayersOriginalMaxThrust;
                    fplayer->RollRate = PlayersOriginalRollRate;
                }
            } else {

                if (RefuelRearmRepairDurationTimer == 1) {
                    if (MyNetworkId & 1) {
                        VocalizeBlueHqStatus();
                    } else {
                        VocalizeRedHqStatus();
                    }

                    HudLadderBarsOnOff = 0;
                    RadarOnOff = 0;
                    HudOnOff = 0;
                    IffOnOff = 0;
                }
                if (RefuelRearmRepairDurationTimer == 1) {
                    sprintf(SystemMessageBufferA, "WELCOME BACK. REQUESTING AIRCRAFT SERVICE...");
                    NewSystemMessageNeedsScrolling = true;
                }
                if (RefuelRearmRepairDurationTimer == 2) {
                    HudOnOff = 1;
                }
                if (RefuelRearmRepairDurationTimer == 3) {
                    HudLadderBarsOnOff = 1;
                }
                if (RefuelRearmRepairDurationTimer == 4) {
                    RadarOnOff = 1;
                }
                if (RefuelRearmRepairDurationTimer == 5) {
                    IffOnOff = 1;
                    event_UnMuteMorseAll();
                }
                if (fplayer->FuelLevel < 25) {
                    fplayer->FuelLevel += 0.5;
                } else if (fplayer->FuelLevel < 50) {
                    fplayer->FuelLevel += 2;
                } else if (fplayer->FuelLevel < 75) {
                    fplayer->FuelLevel += 3;
                } else {
                    fplayer->FuelLevel += 4;

                    fplayer->maxthrust = PlayersOriginalMaxThrust;
                    fplayer->RollRate = PlayersOriginalRollRate;
                }
            }
        }
        lastDurability = PlayersOriginalDurability;
        if (fplayer->ammo < 1600) {
            fplayer->ammo = 1600;
        }
    } else {
        if (fplayer->realspeed < 0.03) {
            Me163LandingTimer -= DeltaTime;
        }
        if (LandingTimer > 1000 && fplayer->realspeed < 0.02) {
            if (Me163LandingTimer < 60000 && Me163LandingTimer >= 25000) {
                fplayer->FuelLevel -= 3;
                if (fplayer->FuelLevel <= 0) {
                    fplayer->FuelLevel = 0;
                }
            }
            if (Me163LandingTimer < 17000 && Me163LandingTimer >= 1100) {
                fplayer->FuelLevel += 6;
                if (fplayer->FuelLevel >= 100) {
                    fplayer->FuelLevel = 100;
                }
            }
            LandingTimer = 0;
        }

        if (Me163LandingTimer < 87000 && Me163LandingTimer >= 40000) {
            if (fplayer->FuelLevel != 100) {
                sprintf(SystemMessageBufferA, "CYCLING ME163 REFUEL CREW....");
                NewSystemMessageNeedsScrolling = true;
            }
        } else if (Me163LandingTimer < 40000 && Me163LandingTimer >= 20000) {
            if (fplayer->FuelLevel != 100) {
                sprintf(SystemMessageBufferA, "MOUNTING TAKEOFF WHEELS....");
                NewSystemMessageNeedsScrolling = true;
            }
        } else if (Me163LandingTimer < 20000 && Me163LandingTimer >= 10000) {
            fplayer->FuelLevel = FuelLevelAtLastLanding;
            if (fplayer->FuelLevel != 100) {
                sprintf(SystemMessageBufferA, "PUMPING FUEL FROM TRUCK #1....");
                NewSystemMessageNeedsScrolling = true;
            }
        } else if (Me163LandingTimer < 10000 && Me163LandingTimer >= 1100) {
            if (fplayer->FuelLevel != 100) {
                sprintf(SystemMessageBufferA, "PUMPING FUEL FROM TRUCK #2....");
                NewSystemMessageNeedsScrolling = true;
            }
        } else if (Me163LandingTimer < 1100) {
            if (fplayer->FuelLevel >= 100) {
                sprintf(SystemMessageBufferA, "REARMED, REFUELED, REPAIRED");
                NewSystemMessageNeedsScrolling = true;
            }
            fplayer->FuelLevel = 100;
            fplayer->maxthrust = PlayersOriginalMaxThrust;
            fplayer->RollRate = PlayersOriginalRollRate;
            lastDurability = PlayersOriginalDurability;
            fplayer->Durability = fplayer->maxDurability;
            fplayer->ammo = 120;
        }
    }

    if (MyNetworkId % 2) {
        if (ThreeDObjects[MissionObjectHqRed]->Durability < ThreeDObjects[MissionObjectHqRed]->maxDurability * 0.4) {
            DetermineCurrentAirfield();
            if (fplayer->HistoricPeriod > 1 && AirfieldChosenForLanding == 1) {
                if (RefuelRearmRepairDurationTimer < 5) {
                    sprintf(SystemMessageBufferA, "LOW AMMO & FUEL FOR LATE-WAR PLANES DUE TO HQ DAMAGE.");
                    NewSystemMessageNeedsScrolling = true;
                }
                fplayer->FuelLevel *= 0.2;

                if (fplayer->FuelLevel < FuelLevelAtLastLanding) {
                    fplayer->FuelLevel = FuelLevelAtLastLanding;
                }
                fplayer->ammo /= 5;

                int i2;
                for (i2 = 0; i2 < missiletypes; i2++) {
                    if (i2 == 0) {
                        fplayer->missiles[i2] /= 3;
                    }
                    if (i2 == 5) {
                        fplayer->missiles[i2] /= 3;
                    }
                }
            } else {

            }
        } else {
        }
    } else {
        if (ThreeDObjects[MissionObjectHqBlue]->Durability < ThreeDObjects[MissionObjectHqBlue]->maxDurability * 0.4) {
            DetermineCurrentAirfield();
            if (fplayer->HistoricPeriod > 1 && AirfieldChosenForLanding == 1) {
                if (RefuelRearmRepairDurationTimer < 5) {
                    sprintf(SystemMessageBufferA, "LOW AMMO & FUEL FOR LATE-WAR PLANES DUE TO HQ DAMAGE.");
                    NewSystemMessageNeedsScrolling = true;
                }
                fplayer->FuelLevel *= 0.2;

                if (fplayer->FuelLevel < FuelLevelAtLastLanding) {
                    fplayer->FuelLevel = FuelLevelAtLastLanding;
                }
                fplayer->ammo /= 5;

                int i2;
                for (i2 = 0; i2 < missiletypes; i2++) {
                    if (i2 == 0) {
                        fplayer->missiles[i2] /= 3;
                        display((char*)"RearmRefuelRepair() diminishing BlueTeam late-war bomb load due to heavy HQ airfield damage", LOG_MOST);
                    }
                    if (i2 == 5) {
                        fplayer->missiles[i2] /= 3;
                        display((char*)"RearmRefuelRepair() diminishing BlueTeam late-war rocket load due to heavy HQ airfield damage", LOG_MOST);
                    }
                }
            } else {

            }
        } else {
        }
    }
}
