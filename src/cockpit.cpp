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

/* This file includes the cockpit rendering methods. */

#include <stdio.h>
#include "cockpit.h"
#include "gl.h"
#include "glland.h"
#include "main.h"
#include "mathtab.h"
#include "mission.h"
#include "pilots.h"

#define BIG_BLIP 3
#define BIG_DIAMONDBLIP 5
#define BIG_TRIANGLEBLIP 4
#define TRIANGLE_BLIP 1
#define SQUARE_BLIP   2

extern bool AirfieldRepairRateNormalForBlueTeam;
extern bool AirfieldRepairRateNormalForRedTeam;
extern bool AirfieldRepairsAcceleratedForBlueTeam;
extern bool AirfieldRepairsAcceleratedForRedTeam;
extern bool AirfieldRepairsStoppedForBlueTeam;
extern bool AirfieldRepairsStoppedForRedTeam;
extern bool AllBlueTeamAirfieldsAreHeavilyDamaged;
extern bool AllRedTeamAirfieldsAreHeavilyDamaged;
extern bool CapsLockActive;
extern bool ClimbAngleExceedsMaxSustainable;
extern bool GunCameraActive;
extern bool InPacketContainsMumbleBroadcast;
extern bool InPacketContainsMumbleNarrowcast;
extern bool MumbleBroadcastRequested;
extern bool MumbleCurrentMissionBlueSubChannelRequested;
extern bool MumbleCurrentMissionRedSubChannelRequested;
extern bool MumbleIsAccessible;
extern bool MumbleManagement;
extern bool MumbleTransmissionRequested;
extern bool MumbleTunedToCurrentMissionChannel;
extern bool MumbleTunedToMyBlueMissionAndSubchannel;
extern bool MumbleTunedToMyRedMissionAndSubchannel;
extern bool NewSystemMessageNeedsScrolling;
extern bool OnTheGround;
extern bool PeerPacketReceivedInThisMissionState;
extern bool StrategicEnemyBomberBeyondRadarDisplay;
extern bool SystemMessageFlag;
extern bool TargetSelectNotYetInitialized;

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

extern unsigned char MumbleChannelPresumed;
extern unsigned char MyNetworkId;
extern unsigned char NetworkOpponent;
extern unsigned char NewestInPacketId;
extern unsigned char NewestMumblePacketId;
extern unsigned char PreviousMorseSender;
extern unsigned char Realm;
extern unsigned char SelectedMissionTarget;
extern unsigned char ServerMessageRecipient;

extern char CurrentMissionNumber;

extern unsigned int DisplayedAirSpeed;

extern char CommsMacro01String1[64];
extern char CommsMacro02String1[64];
extern char CommsMacro03String1[64];
extern char CommsMacro04String1[64];
extern char CommsMacro05String1[64];
extern char CommsMacro06String1[64];
extern char CommsMacro07String1[64];
extern char CommsMacro08String1[64];
extern char CommsMacro09String1[64];
extern char CommsMacro10String1[64];
extern char CommunityHandle[20];
extern char DebugBuf[];
extern char MorseRadioMessageBuffer[];
extern char NetworkPlayerMumbleChannel[];
extern char ServerMessageBuffer[];
extern char SystemMessageBuffer0[64];
extern char SystemMessageBuffer1[64];
extern char SystemMessageBuffer2[64];
extern char SystemMessageBufferA[64];

extern char PlayerIdStrings[10][9];

extern int16_t PriorServerMessageChecksum;
extern int16_t ServerMessageChecksumBuffer;

extern Uint32 DeltaTime;

extern int HudOnOff;
extern int HudLadderBarsOnOff;
extern int IffOnOff;
extern int NetworkTransmitTimer;
extern int MissionMumbleTimer[32];
extern int MissionPacketTimer[32];
extern int MorsePanelHighlightTimer;
extern int NetworkMode;
extern int PlayerEngineType;
extern int RadarOnOff;
extern int RadarZoom;
extern int ServerMessageTimer;
extern int SkewViewUp;
extern int StrategicWarningTimer;
extern int ThrottleReference;

extern long int MorsePanelActiveTimer;

extern unsigned int SystemMessageRepeatCounter;

extern float DamageRatio;
extern float FratricideShameFactor;
extern float PlayerAltitude;
extern float PlayerDamagePercent;
extern float ScreenFOVx;
extern float SeaLevel;
extern float TargetAltitude;
extern float TrueAirSpeed;

Cockpit::Cockpit() {
    flarewarning = 0;
    chaffwarning = 0;
}

void Cockpit::cockpitvertex(float phi, float gamma) {

    float fpt = -fplayer->theta + 180;
    float sinfpt = SIN(fpt), cosfpt = COS(fpt);
    float x = cosfpt * phi + sinfpt * gamma + 180;
    float y = sinfpt * phi - cosfpt * gamma + 180;
    glVertex3f(10 * SIN(x), 10 * SIN(y), -10 * COS(x) * COS(y));
}

void Cockpit::drawBlip(int shape, float x, float y, float z, unsigned char r, unsigned char g, unsigned char b) {
    float blipsize;
    float bigblipsize;
    float hugeblipsize;
    if (!(NetworkMode & 128)) {
        blipsize = 0.02;
        bigblipsize = 0.04;
        hugeblipsize = 0.10;
    } else {
        blipsize = 0.04;
        bigblipsize = 0.07;
        hugeblipsize = 0.11;
    }
    int alpha = 200;
    CColor color;
    glColor4ub(r, g, b, alpha);
    glBegin(GL_QUADS);
    switch (shape) {
    case BIG_BLIP:
        glVertex3f(x + bigblipsize, y + bigblipsize, z);
        glVertex3f(x + bigblipsize, y - bigblipsize, z);
        glVertex3f(x - bigblipsize, y - bigblipsize, z);
        glVertex3f(x - bigblipsize, y + bigblipsize, z);
        glVertex3f(x + bigblipsize, y + bigblipsize, z);
        break;
    case BIG_DIAMONDBLIP:
        glVertex3f(x, y + hugeblipsize, z);
        glVertex3f(x - hugeblipsize, y, z);
        glVertex3f(x, y - hugeblipsize, z);
        glVertex3f(x + hugeblipsize, y, z);
        glVertex3f(x, y + hugeblipsize, z);
        break;
    case BIG_TRIANGLEBLIP:
        glVertex3f(x, y + bigblipsize, z);
        glVertex3f(x + bigblipsize, y - hugeblipsize, z);
        glVertex3f(x - bigblipsize, y - hugeblipsize, z);
        glVertex3f(x, y + bigblipsize, z);
        break;
    case SQUARE_BLIP:
        glVertex3f(x + blipsize, y + blipsize, z);
        glVertex3f(x + blipsize, y - blipsize, z);
        glVertex3f(x - blipsize, y - blipsize, z);
        glVertex3f(x - blipsize, y + blipsize, z);
        glVertex3f(x + blipsize, y + blipsize, z);
        break;
    case TRIANGLE_BLIP:
        glVertex3f(x, y + blipsize, z);
        glVertex3f(x + blipsize, y - blipsize, z);
        glVertex3f(x - blipsize, y - blipsize, z);
        glVertex3f(x, y + blipsize, z);
    default:
        abort();
    }
    glEnd();
}

void Cockpit::drawChassis() {
    extern int SkewViewUp;
    extern float ScreenFOVx;
    float xl;
    float yl;
    float yf;
    float zf;

    yf = -5.0 - (float)SkewViewUp / 2.5;
    zf = -8.0 * ScreenFOVx;
    xl = 6.5;
    yl = 1.75;
    glEnable(GL_ALPHA_TEST);
    // Draw Chassis outline on the HUD
    glColor4ub(40, 40, 40, 128);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 0);

    glVertex3f(-xl - 4, yf - yl, zf);
    glVertex3f(-xl - 3.4, (yf - yl + 1), zf);
    glVertex3f(-xl + 1, yf + yl, zf);
    glVertex3f(xl - 1, yf + yl, zf);
    glVertex3f(xl + 3.4, (yf - yl + 1), zf);
    glVertex3f(xl + 4, yf - yl, zf);
    glVertex3f(-xl - 4, yf - yl, zf);
    glEnd();
    // Draw Morse Code Radio Panel
    if (CapsLockActive) {
        glColor4ub(3, (70 + MorsePanelHighlightTimer / 16), 4, 128);
    } else {
        glColor4ub(43, (43 + MorsePanelHighlightTimer / 16), 43, 128);
    }
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 0);
    glVertex3f((-xl + 12.3) * 0.450, (yf - yl - 21.0) * 0.2, zf);
    glVertex3f((-xl + 12.8) * 0.450, (yf + yl - 21.4) * 0.2, zf);
    glVertex3f((xl + 11.1) * 0.200, (yf + yl - 21.4) * 0.2, zf);
    glVertex3f((xl + 12.3) * 0.200, (yf - yl - 21.0) * 0.2, zf);
    glVertex3f((-xl + 10.3) * 0.450, (yf - yl - 21.0) * 0.2, zf);
    glVertex3f((-xl + 10.3) * 0.450, (yf - yl - 22.0) * 0.2, zf);
    glVertex3f((-xl + 10.3) * 0.450, (yf + yl - 23.0) * 0.2, zf);
    glVertex3f((xl + 11.0) * 0.273, (yf + yl - 23.0) * 0.2, zf);
    glVertex3f((xl + 11.0) * 0.273, (yf - yl - 22.0) * 0.2, zf);
    glVertex3f((-xl + 10.3) * 0.450, (yf - yl - 22.0) * 0.2, zf);
    glEnd();
}

void Cockpit::drawCounter() {
    CColor blue(0, 100, 255);
    CColor red(255, 0, 0);
    CColor grey(160, 160, 160);
    CColor yellow(255, 255, 0);
    CColor yellow1(200, 200, 0);
    CColor yellow2(170, 170, 0);
    CColor purple(255, 000, 255);
    CColor white(255, 255, 255);
    CColor green(0, 255, 0);
    CColor black(0, 0, 0);
    extern float ScreenFOVx;
    extern float SeaLevel;
    int i;
    char buf[STDSIZE];
    float xf = 2.8F, yf = -1.0F, zf = -4.0F * ScreenFOVx, yf2 = -1.3F;
    bool flarewarn = false, chaffwarn = false;
    static int16_t ServerMessageChecksum = 0;
    ServerMessageTimer += dt;
    char* ServerMessagePointer = &ServerMessageBuffer[0];

    if (ServerMessageTimer < 20000) {
        if (ServerMessageBuffer[0]) {
            if (MyNetworkId % 2) {
                if (ServerMessageRecipient == 13 || ServerMessageRecipient == MyNetworkId || ServerMessageRecipient == 0 || ServerMessageRecipient == 12) {

                    while (*ServerMessagePointer != 0) {
                        ServerMessageChecksum += *ServerMessagePointer;
                        ServerMessagePointer++;
                    }
                    if (PriorServerMessageChecksum != ServerMessageChecksum) {

                        font1->drawTextCentered(xf * 1.0 - 3.0, (yf) * -16, zf * 0.70, ServerMessageBuffer, &black);
                    }
                    ServerMessageChecksumBuffer = ServerMessageChecksum;
                    ServerMessageChecksum = 0;
                }
            } else {
                if (ServerMessageRecipient == 13 || ServerMessageRecipient == MyNetworkId || ServerMessageRecipient == 0 || ServerMessageRecipient == 11) {

                    while (*ServerMessagePointer != 0) {
                        ServerMessageChecksum += *ServerMessagePointer;
                        ServerMessagePointer++;
                    }
                    if (PriorServerMessageChecksum != ServerMessageChecksum) {

                        font1->drawTextCentered(xf * 1.0 - 3.0, (yf) * -16, zf * 0.70, ServerMessageBuffer, &black);
                    }
                    ServerMessageChecksumBuffer = ServerMessageChecksum;
                    ServerMessageChecksum = 0;
                }
            }
        } else {
            //display ((char *)"Cockpit::drawCounter() Nothing in ServerMessageBuffer[0].", LOG_MOST);
        }
    } else {
        ServerMessageBuffer[0] = 0;
        PriorServerMessageChecksum = ServerMessageChecksumBuffer;
    }

    if (MorsePanelActiveTimer > 0) {
        MorsePanelActiveTimer -= DeltaTime;
    }

    MorsePanelHighlightTimer -= DeltaTime / 8;
    if (MorsePanelHighlightTimer < 40) {
        MorsePanelHighlightTimer = 40;
    }
    for (i = 0; i < maxmissile; i++) {
        if (missile[i]->active) {
            if (missile[i]->target == fplayer) {
                if (missile[i]->id <= BOMB01) {
                    flarewarn = true;
                } else {
                    chaffwarn = true;
                }
            }
        }
    }
    if (flarewarn && game == GAME_PLAY) {
        if (flarewarning <= 0) {
            flarewarning = 10 * timestep;
            sound->play(SOUND_BEEP2, false);
        }
        flarewarning -= dt;
    }
    if (chaffwarn && game == GAME_PLAY) {
        if (chaffwarning <= 0) {
            chaffwarning = 10 * timestep;
            sound->play(SOUND_BEEP1, false);
        }
        chaffwarning -= dt;
    }

    if (GunCameraActive) {
        sprintf(buf, "C");
        font1->drawTextCentered(xf * 10, (yf - 1.00) * 10, zf, buf, &yellow);
    } else {
        sprintf(buf, "C");
        font1->drawTextCentered(xf * 10, (yf - 1.00) * 10, zf, buf, &grey);
    }

    sprintf(buf, "CHAFF: %d", fplayer->chaffs);
    font1->drawTextCentered(xf * 10, (yf - 1.95) * 10, zf, buf, &grey);

    if (fplayer->FlapsLevel) {
        sprintf(buf, "FLAPS: -%d", fplayer->FlapsLevel);
    } else {
        sprintf(buf, "FLAPS:  0");
    }
    font1->drawTextCentered(xf * 10.1, (yf - 1.80) * 10, zf, buf, &white);
    sprintf(buf, "SPEED BRAKE: %d", fplayer->SpeedBrake);
    font1->drawTextCentered(xf * 10.83, (yf - 1.5) * 10.6, zf, buf, &white);
    if (MumbleIsAccessible) {
        sprintf(buf, "MUMBLE PANEL");
        font1->drawTextCentered(xf * 5.5, (yf - 1.5) * 9.0, zf, buf, &white);
    } else {
        sprintf(buf, "MUMBLE NOT INSTALLED");
        font1->drawTextCentered(xf * 5.9, (yf - 1.5) * 9.0, zf, buf, &grey);
    }
    switch (MumbleChannelPresumed) {
    case 1:
    {
        strncpy(buf, CommsMacro01String1, 64);
        MumbleTunedToMyBlueMissionAndSubchannel = false;
        MumbleTunedToMyRedMissionAndSubchannel = false;
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE01) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &purple);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        }
        break;
    }
    case 2:
    {
        strncpy(buf, CommsMacro02String1, 64);
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE01 && (MyNetworkId % 2 == 0)) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &blue);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyBlueMissionAndSubchannel = true;
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToMyRedMissionAndSubchannel = false;
        }
        break;
    }
    case 3:
    {
        strncpy(buf, CommsMacro03String1, 64);
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE01 && MyNetworkId % 2) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &red);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyRedMissionAndSubchannel = true;
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToMyRedMissionAndSubchannel = false;
        }
        break;
    }
    case 4:
    {
        strncpy(buf, CommsMacro04String1, 64);
        MumbleTunedToMyBlueMissionAndSubchannel = false;
        MumbleTunedToMyRedMissionAndSubchannel = false;
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE02) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &purple);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        }
        break;
    }
    case 5:
    {
        strncpy(buf, CommsMacro05String1, 64);
        if ((CurrentMissionNumber == MISSION_NETWORKBATTLE02) && (MyNetworkId % 2 == 0)) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &blue);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyBlueMissionAndSubchannel = true;
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToMyRedMissionAndSubchannel = false;
        }
        break;
    }
    case 6:
    {
        strncpy(buf, CommsMacro06String1, 64);
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE02 && MyNetworkId % 2) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &red);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyRedMissionAndSubchannel = true;
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToMyRedMissionAndSubchannel = false;
        }
        break;
    }
    case 7:
    {
        strncpy(buf, CommsMacro07String1, 64);
        MumbleTunedToMyBlueMissionAndSubchannel = false;
        MumbleTunedToMyRedMissionAndSubchannel = false;
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE03) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &purple);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        }
        break;
    }
    case 8:
    {
        strncpy(buf, CommsMacro08String1, 64);
        if ((CurrentMissionNumber == MISSION_NETWORKBATTLE03) && (MyNetworkId % 2 == 0)) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &blue);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyBlueMissionAndSubchannel = true;
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToMyRedMissionAndSubchannel = false;
        }
        break;
    }
    case 9:
    {
        strncpy(buf, CommsMacro09String1, 64);
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE03 && MyNetworkId % 2) {
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &red);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyRedMissionAndSubchannel = true;
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToMyRedMissionAndSubchannel = false;
        }
        break;
    }
    case 10:
    {
        MumbleTunedToMyBlueMissionAndSubchannel = false;
        MumbleTunedToMyRedMissionAndSubchannel = false;
        strncpy(buf, CommsMacro10String1, 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    case 90:
    {
        strncpy(buf, "MUMBLE UNRESPONSIVE", 64);
        font1->drawText(xf * 3.0, (yf - 22.5), zf, buf, &grey);
        // strncpy (buf, "PLEASE INSTALL MUMBLE.", 64 );
        // font1->drawText (xf*3.1, (yf-23.5), zf, buf, &grey);
        break;
    }
    case 91:
    {
        strncpy(buf, "PLEASE INSTALL MUMBLE", 64);
        font1->drawText(xf * 3.0, (yf - 22.5), zf, buf, &grey);
        // strncpy (buf, "PLEASE INSTALL MUMBLE.", 64 );
        // font1->drawText (xf*3.1, (yf-23.5), zf, buf, &grey);
        break;
    }
    case 92:
    {
        strncpy(buf, "MUMBLE INACCESSIBLE.", 64);
        font1->drawText(xf * 3.1, (yf - 22.5), zf, buf, &grey);
        break;
    }
    case 93:
    {
        strncpy(buf, "MUMBLE NOT MANAGED.", 64);
        font1->drawText(xf * 3.1, (yf - 22.5), zf, buf, &grey);
        break;
    }
    case 94:
    {
        strncpy(buf, "MISSIONCAST", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    case 95:
    {
        strncpy(buf, "TEAMCAST", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    case 96:
    {
        strncpy(buf, "EXPERIMENTAL", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &white);
        break;
    }
    case 97:
    {
        strncpy(buf, "SECRET", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    case 98:
    {
        strncpy(buf, "UNCHANGED", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    case 99:
    {
        strncpy(buf, "UKNOWN", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    case 100:
    {
        if (MyNetworkId % 2) {
            if (CurrentMissionNumber >= 23) {
                sprintf(buf, "REALM%.2dM%dRED", Realm, (CurrentMissionNumber - 20));
            } else {
                sprintf(buf, "REALM%.2dM%dRED", Realm, (CurrentMissionNumber - 19));
            }
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &red);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyRedMissionAndSubchannel = true;
            MumbleTunedToMyBlueMissionAndSubchannel = false;
            MumbleTunedToCurrentMissionChannel = false;
        } else {
            if (CurrentMissionNumber >= 23) {
                sprintf(buf, "REALM%.2dM%dBLUE", Realm, (CurrentMissionNumber - 20));
            } else {
                sprintf(buf, "REALM%.2dM%dBLUE", Realm, (CurrentMissionNumber - 19));
            }
            if (MumbleIsAccessible) {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &blue);
            } else {
                font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
            }
            MumbleTunedToMyBlueMissionAndSubchannel = true;
            MumbleTunedToMyRedMissionAndSubchannel = false;
            MumbleTunedToCurrentMissionChannel = false;
        }
        break;
    }
    case 101:
    {
        if (CurrentMissionNumber >= 23) {
            sprintf(buf, "REALM%.2dM%d", Realm, (CurrentMissionNumber - 20));
        } else {
            sprintf(buf, "REALM%.2dM%d", Realm, (CurrentMissionNumber - 19));
        }
        if (MumbleIsAccessible) {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &purple);
        } else {
            font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        }
        MumbleTunedToMyBlueMissionAndSubchannel = false;
        MumbleTunedToMyRedMissionAndSubchannel = false;
        MumbleTunedToCurrentMissionChannel = true;
        break;
    }
    default:
    {
        strncpy(buf, "UNDEFINED COMM ERROR", 64);
        font1->drawText(xf * 3.75, (yf - 1.5) * 9.5, zf, buf, &grey);
        break;
    }
    }
    PlayerDamagePercent = 100 * (1 - (fplayer->Durability / fplayer->maxDurability));
    sprintf(buf, "DAMAGE:   %3.0f", PlayerDamagePercent);
    if (fplayer->Durability == fplayer->maxDurability) {
        font1->drawTextCentered(xf * 10.58, (yf - 1.35) * 10.66, zf, buf, &white);
    } else {
        font1->drawTextCentered(xf * 10.58, (yf - 1.35) * 10.66, zf, buf, &grey);
    }
    if (NewSystemMessageNeedsScrolling) {
        if (strcmp(SystemMessageBufferA, SystemMessageBuffer0)) {
            SystemMessageRepeatCounter = 1;
            strncpy(SystemMessageBuffer2, SystemMessageBuffer1, 64);
            strncpy(SystemMessageBuffer1, SystemMessageBuffer0, 64);
            strncpy(SystemMessageBuffer0, SystemMessageBufferA, 64);
        } else {
            SystemMessageRepeatCounter++;
        }
        NewSystemMessageNeedsScrolling = false;
    }

    sprintf(DebugBuf, "%d", SystemMessageRepeatCounter);
    font1->drawText(-46.0F, (yf - 2.3) * 10, zf, DebugBuf, &yellow);

    font1->drawText(-41.0F, (yf - 2.1) * 10, zf, SystemMessageBuffer2, &yellow2);
    font1->drawText(-41.0F, (yf - 2.2) * 10, zf, SystemMessageBuffer1, &yellow1);
    font1->drawText(-41.0F, (yf - 2.3) * 10, zf, SystemMessageBuffer0, &yellow);

    sprintf(DebugBuf, "%d", PreviousMorseSender);
    if (PreviousMorseSender % 2) {
        font1->drawText(12.2F, (yf - 1.1) * 10, zf * 0.80, DebugBuf, &red);
    } else {
        font1->drawText(12.2F, (yf - 1.1) * 10, zf * 0.80, DebugBuf, &blue);
    }
    font1->drawText(10.0F, (yf - 2.2) * 10, zf * 1.15, MorseRadioMessageBuffer, &yellow);
    sprintf(buf, "FUEL:   %4.0f", fplayer->FuelLevel);
    if (fplayer->FuelLevel > 20) {
        font1->drawTextCentered(xf * 10.32, (yf - 1.2) * 10.7, zf, buf, &white);
    } else {
        font1->drawTextCentered(xf * 10.32, (yf - 1.2) * 10.7, zf, buf, &grey);
    }
    if (CurrentMissionNumber != MISSION_TUTORIAL2) {
        PlayerAltitude = (25.0 * (fplayer->tl->y + SeaLevel)) - 17.0;
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE05) {
            PlayerAltitude -= 3000;
        }
        sprintf(buf, "ALTITUDE: %5.0f", PlayerAltitude);
        font1->drawTextCentered(-29.0, (yf - 1.34) * 10, zf, buf, &white);
    } else {
        sprintf(buf, "ALTITUDE: %5.0f", (25.0 * (fplayer->tl->y - SeaLevel * 1.3)) - 17.0);
        font1->drawTextCentered(-29.0, (yf - 1.34) * 10, zf, buf, &white);
    }
    if (!OnTheGround) {
        DisplayedAirSpeed = (int)(fplayer->InertiallyDampenedPlayerSpeed / timestep * 35000.0F);
        float DegreesToRadiansFactor = 0.01745333;
        float AltitudeRatio = 1.0 + (0.5 * (fplayer->tl->y / MAXALTITUDE));
        int IAS = DisplayedAirSpeed / AltitudeRatio;
        float FloatGS = (float)DisplayedAirSpeed;
        FloatGS *= fabs(cos((fplayer->gamma) * DegreesToRadiansFactor));
        int GS = (int)FloatGS;
        sprintf(buf, "SPEED   TAS: %3d  IAS: %3d  GS: %3d", DisplayedAirSpeed, IAS, GS);
    } else {
        if (TrueAirSpeed < 500) {
            sprintf(buf, "SPEED:       %3.0f", TrueAirSpeed);
        }
    }
    font1->drawTextCentered(-23.20, (yf - 1.22) * 10, zf, buf, &white);
    sprintf(buf, "AMMO %4d", fplayer->ammo);
    if (fplayer->ammo > 200) {
        font1->drawTextCentered(28.8, (yf - 1.2) * 10, zf, buf, &white);
    } else {
        font1->drawTextCentered(28.8, (yf - 1.2) * 10, zf, buf, &grey);
    }

    if (
        (FratricideShameFactor < 40000) &&
        (
            CurrentMissionNumber == MISSION_NETWORKBATTLE01 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE02 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE03 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE04 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE05 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE06 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE07 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE08 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE09 ||
            CurrentMissionNumber == MISSION_NETWORKBATTLE10
            )
        ) {
        if (MyNetworkId % 2) {
            sprintf(buf, "HQ STATUS: %5.0f ", (ThreeDObjects[MissionObjectHqRed]->Durability / ThreeDObjects[MissionObjectHqRed]->maxDurability) * 100.0);
            if (ThreeDObjects[MissionObjectHqRed]->Durability >= ThreeDObjects[MissionObjectHqRed]->maxDurability) {
                font1->drawTextCentered(15.0, (yf - 0.80) * 18, zf * 1.00, buf, &red);
            } else {
                font1->drawTextCentered(15.0, (yf - 0.80) * 18, zf * 1.00, buf, &red);
                if (AirfieldRepairRateNormalForRedTeam) {
                    sprintf(buf, "1X");
                    font1->drawTextCentered(23.5, (yf - 0.80) * 18, zf * 1.00, buf, &red);
                } else if (AirfieldRepairsAcceleratedForRedTeam) {
                    sprintf(buf, "5X");
                    font1->drawTextCentered(23.5, (yf - 0.80) * 18, zf * 1.00, buf, &red);
                } else if (AirfieldRepairsStoppedForRedTeam) {
                    sprintf(buf, "0X");
                    font1->drawTextCentered(23.5, (yf - 0.80) * 18, zf * 1.00, buf, &red);
                }
            }
            if ((SelectedMissionTarget % 2 == MyNetworkId % 2) && (SelectedMissionTarget > 10)) { // Get here if targetting an ally. Report status of selected target
                sprintf(
                    buf,
                    "TARGET %d STATUS: %5.0f ",
                    SelectedMissionTarget,
                    (ThreeDObjects[SelectedMissionTarget]->Durability / ThreeDObjects[SelectedMissionTarget]->maxDurability)
                    * 100.0
                );
                font1->drawTextCentered(15, (yf - 0.80) * 17, zf * 1.00, buf, &red);
            }
        } else {
            sprintf(buf, "HQ STATUS: %5.0f ", (ThreeDObjects[MissionObjectHqBlue]->Durability / ThreeDObjects[MissionObjectHqBlue]->maxDurability) * 100.0);
            if (ThreeDObjects[MissionObjectHqBlue]->Durability >= ThreeDObjects[MissionObjectHqBlue]->maxDurability) {
                font1->drawTextCentered(15.0, (yf - 0.80) * 18, zf * 1.00, buf, &blue);
            } else {
                font1->drawTextCentered(15.0, (yf - 0.80) * 18, zf * 1.00, buf, &blue);
                if (AirfieldRepairRateNormalForBlueTeam) {
                    sprintf(buf, "1X");
                    font1->drawTextCentered(23.5, (yf - 0.80) * 18, zf * 1.00, buf, &blue);
                }
                if (AirfieldRepairsAcceleratedForBlueTeam) {
                    sprintf(buf, "5X");
                    font1->drawTextCentered(23.5, (yf - 0.80) * 18, zf * 1.00, buf, &blue);
                }
                if (AirfieldRepairsStoppedForBlueTeam) {
                    sprintf(buf, "0X");
                    font1->drawTextCentered(23.5, (yf - 0.80) * 18, zf * 1.00, buf, &blue);
                }
            }
            if ((SelectedMissionTarget % 2 == MyNetworkId % 2) && (SelectedMissionTarget > 10)) { // Get here if targetting an ally. Report status of selected target
                sprintf(
                    buf,
                    "TARGET %d STATUS: %5.0f ",
                    SelectedMissionTarget,
                    (ThreeDObjects[SelectedMissionTarget]->Durability / ThreeDObjects[SelectedMissionTarget]->maxDurability)
                    * 100.0
                );
                font1->drawTextCentered(15, (yf - 0.80) * 17, zf * 1.00, buf, &blue);
            }
        }
    }

    MissionPacketTimer[NewestInPacketId] -= DeltaTime;
    if (MissionPacketTimer[NewestInPacketId] < 0) {
        MissionPacketTimer[NewestInPacketId] = 0;
    }
    sprintf(buf, "   ROUTER PANEL");
    font1->drawTextCentered(17.0, (yf - 0.80) * 10, zf * 1.00, buf, &white);
    sprintf(buf, "    1  2 3 4 5  6 7 8 9 10");
    font1->drawTextCentered(17.0, (yf - 0.90) * 10, zf * 1.00, buf, &yellow);
    sprintf(buf, "P");
    font1->drawTextCentered(9, (yf - 1.00) * 10, zf * 1.00, buf, &yellow);
    sprintf(buf, "V");
    font1->drawTextCentered(9, (yf - 1.10) * 10, zf * 1.00, buf, &yellow);

    switch (NewestInPacketId) {
    case 0:
    {
        break;
    }
    case 1:
    {
        if (MissionPacketTimer[1] > 0) {
            sprintf(buf, "01");
            font1->drawTextCentered(11.4, (yf - 1.00) * 10, zf * 1.00, buf, &red);
        }
        if (MissionMumbleTimer[1] > 0) {
            font1->drawTextCentered(11.4, (yf - 1.10) * 10, zf * 1.00, buf, &red);
        }
        break;
    }
    case 2:
    {
        if (MissionPacketTimer[2] > 0) {
            sprintf(buf, "02");
            font1->drawTextCentered(12.8, (yf - 1.00) * 10, zf * 1.00, buf, &blue);
        }
        if (MissionMumbleTimer[2] > 0) {
            font1->drawTextCentered(12.8, (yf - 1.10) * 10, zf * 1.00, buf, &blue);
        }
        break;
    }
    case 3:
    {
        if (MissionPacketTimer[3] > 0) {
            sprintf(buf, "03");
            font1->drawTextCentered(14.2, (yf - 1.00) * 10, zf * 1.00, buf, &red);
        }
        if (MissionMumbleTimer[3] > 0) {
            font1->drawTextCentered(14.2, (yf - 1.10) * 10, zf * 1.00, buf, &red);
        }
        break;
    }
    case 4:
    {
        if (MissionPacketTimer[4] > 0) {
            sprintf(buf, "04");
            font1->drawTextCentered(15.6, (yf - 1.00) * 10, zf * 1.00, buf, &blue);
        }
        if (MissionMumbleTimer[4] > 0) {
            font1->drawTextCentered(15.6, (yf - 1.10) * 10, zf * 1.00, buf, &blue);
        }
        break;
    }
    case 5:
    {
        if (MissionPacketTimer[5] > 0) {
            sprintf(buf, "05");
            font1->drawTextCentered(17.0, (yf - 1.00) * 10, zf * 1.00, buf, &red);
        }
        if (MissionMumbleTimer[5] > 0) {
            font1->drawTextCentered(17.0, (yf - 1.10) * 10, zf * 1.00, buf, &red);
        }
        break;
    }
    case 6:
    {
        if (MissionPacketTimer[6] > 0) {
            sprintf(buf, "06");
            font1->drawTextCentered(18.4, (yf - 1.00) * 10, zf * 1.00, buf, &blue);
        }
        if (MissionMumbleTimer[6] > 0) {
            font1->drawTextCentered(18.4, (yf - 1.10) * 10, zf * 1.00, buf, &blue);
        }
        break;
    }
    case 7:
    {
        if (MissionPacketTimer[7] > 0) {
            sprintf(buf, "07");
            font1->drawTextCentered(19.9, (yf - 1.00) * 10, zf * 1.00, buf, &red);
        }
        if (MissionMumbleTimer[7] > 0) {
            font1->drawTextCentered(19.9, (yf - 1.10) * 10, zf * 1.00, buf, &red);
        }
        break;
    }
    case 8:
    {
        if (MissionPacketTimer[8] > 0) {
            sprintf(buf, "08");
            font1->drawTextCentered(21.3, (yf - 1.00) * 10, zf * 1.00, buf, &blue);
        }
        if (MissionMumbleTimer[8] > 0) {
            font1->drawTextCentered(21.3, (yf - 1.10) * 10, zf * 1.00, buf, &blue);
        }
        break;
    }
    case 9:
    {
        if (MissionPacketTimer[9] > 0) {
            sprintf(buf, "09");
            font1->drawTextCentered(22.7, (yf - 1.00) * 10, zf * 1.00, buf, &red);
        }
        if (MissionMumbleTimer[9] > 0) {
            font1->drawTextCentered(22.7, (yf - 1.10) * 10, zf * 1.00, buf, &red);
        }
        break;
    }
    case 10:
    {
        if (MissionPacketTimer[10] > 0) {
            sprintf(buf, "10");
            font1->drawTextCentered(24.1, (yf - 1.00) * 10, zf * 1.00, buf, &blue);
        }
        if (MissionMumbleTimer[10] > 0) {
            font1->drawTextCentered(24.1, (yf - 1.10) * 10, zf * 1.00, buf, &blue);
        }
        break;
    }
    default:
    {
        // display ((char *)"Cockpit::drawCounter() Telemetry panel received invalid InPacket.UdpObjMissionId.", LOG_MOST);
        break;
    }
    }

    MissionMumbleTimer[NewestMumblePacketId] -= DeltaTime;
    if (MissionMumbleTimer[NewestMumblePacketId] < 0) {
        MissionMumbleTimer[NewestMumblePacketId] = 0;
    }
    if (NewestMumblePacketId == MyNetworkId) {
        if (MumbleIsAccessible && MumbleManagement) {
            sprintf(buf, "TRANSMITTING"); // Default MumblePanel label
        } else {
            sprintf(buf, ""); // Default MumblePanel label
        }
        if (MumbleTransmissionRequested) {
            if (MumbleTunedToMyBlueMissionAndSubchannel) {
                if (MumbleIsAccessible) {
                    sprintf(buf, "TEAMCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &blue);
                } else {
                    sprintf(buf, "CANNOT TEAMCAST");
                    font1->drawText(10.0, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            } else if (MumbleTunedToMyRedMissionAndSubchannel) {
                if (MumbleIsAccessible) {
                    sprintf(buf, "TEAMCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &red);
                } else {
                    sprintf(buf, "CANNOT TEAMCAST");
                    font1->drawText(10.0, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            } else if (MumbleTunedToCurrentMissionChannel) {
                if (MumbleIsAccessible) {
                    sprintf(buf, "NARROWCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &white);
                } else {
                    sprintf(buf, "CANNOT NARROWCAST");
                    font1->drawText(9.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            } else {
                font1->drawText(10.5, (yf - 1.10) * 12.0, zf * 1.00, buf, &grey);
            }
        } else if (MumbleBroadcastRequested && MumbleManagement) {
            if (MumbleTunedToMyBlueMissionAndSubchannel) {
                if (MumbleIsAccessible) {
                    sprintf(buf, "MISSIONCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &purple);
                } else {
                    sprintf(buf, "CANNOT MISSIONCAST");
                    font1->drawText(9.7, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            } else if (MumbleTunedToMyRedMissionAndSubchannel) {
                if (MumbleIsAccessible) {
                    sprintf(buf, "MISSIONCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &purple);
                } else {
                    sprintf(buf, "CANNOT MISSIONCAST");
                    font1->drawText(9.7, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            } else if (
                MumbleTunedToCurrentMissionChannel &&
                (
                    CurrentMissionNumber == MISSION_NETWORKBATTLE01 ||
                    CurrentMissionNumber == MISSION_NETWORKBATTLE02 ||
                    CurrentMissionNumber == MISSION_NETWORKBATTLE03
                    )
                ) {
                if (MumbleIsAccessible) {
                    sprintf(buf, "REALMCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &white);
                } else {
                    sprintf(buf, "CANNOT REALMCAST");
                    font1->drawText(9.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            } else {
                if (MumbleIsAccessible && MumbleManagement) {
                    sprintf(buf, "BROADCASTING");
                    font1->drawText(10.5, (yf - 1.06) * 12.0, zf * 1.00, buf, &white);
                } else {
                    sprintf(buf, "");
                    font1->drawText(9.0, (yf - 1.06) * 12.0, zf * 1.00, buf, &grey);
                }
            }
        }
    } else if (NewestMumblePacketId != 0) {
        if (MumbleIsAccessible) {
            sprintf(buf, "RECEIVING");
        } else {
            sprintf(buf, "MISSED VOICE MSG.");
            sprintf(SystemMessageBufferA, "PLAYER %s IS TRYING TO SPEAK WITH YOU.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
            NewSystemMessageNeedsScrolling = true;
        }
        if (NetworkPlayerMumbleChannel[NewestMumblePacketId] == MUMBLEROOTCHANNEL) {
            if (NewestMumblePacketId & 1) {
                font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &red);
            } else {
                font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &blue);
            }
        } else if (NetworkPlayerMumbleChannel[NewestMumblePacketId] == MUMBLECURRENTMISSIONCHANNEL) {
            font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &green);
        } else if (NetworkPlayerMumbleChannel[NewestMumblePacketId] == MUMBLECURRENTMISSIONBLUESUBCHANNEL) {
            if (MyNetworkId % 2) {
                if (InPacketContainsMumbleBroadcast) {
                    font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &purple);
                }
            } else {
                font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &blue);
            }
        } else if (NetworkPlayerMumbleChannel[NewestMumblePacketId] == MUMBLECURRENTMISSIONREDSUBCHANNEL) {
            if (MyNetworkId % 2) {
                font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &red);
            } else {
                if (InPacketContainsMumbleBroadcast) {
                    font1->drawText(10.5, (yf - 1.05) * 12.0, zf * 1.00, buf, &purple);
                }
            }
        }
    }
    if (RadarOnOff && IffOnOff && RadarZoom != 8) {
        TargetAltitude = 25.0 * (ThreeDObjects[SelectedMissionTarget]->tl->y + SeaLevel);
        if (CurrentMissionNumber == MISSION_NETWORKBATTLE05) {
            TargetAltitude -= 3000;
        }
        if (CurrentMissionNumber == MISSION_TUTORIAL2) {
            TargetAltitude += 7700;
        }
        sprintf(buf, "TAR ALT:  %5.0f", TargetAltitude);
        if (SelectedMissionTarget % 2) {
            font1->drawTextCentered(-29.0, (yf - 1.45) * 10, zf, buf, &red);
        } else {
            font1->drawTextCentered(-29.0, (yf - 1.45) * 10, zf, buf, &blue);
        }
    }
    if (mission->id == MISSION_HEADTOHEAD00) {
        sprintf(buf, "VICTORIES: %d", ThreeDObjects[1]->fighterkills);
        font1->drawText(-33.4F, (yf - 1.6) * 10, zf, buf, &yellow);
        sprintf(buf, "DATA FLOW: %d", PeerPacketReceivedInThisMissionState);
        font1->drawText(-33.4F, (yf - 1.8) * 10, zf, buf, &yellow);
    } else if (1) {
        sprintf(buf, "COMMUNITYHANDLE");
        font1->drawTextCentered(-22.0, (yf - 0.87) * 10, zf, buf, &white);
        sprintf(buf, "%.8s", CommunityHandle);
        if (MyNetworkId % 2) {
            font1->drawTextCentered(-22.0, (yf - 0.98) * 10, zf, buf, &red);
        } else {
            font1->drawTextCentered(-22.0, (yf - 0.98) * 10, zf, buf, &blue);
        }
        sprintf(buf, "VICTORIES: %d", ThreeDObjects[0]->fighterkills);
        font1->drawText(-41.0F, (yf - 1.56) * 10, zf, buf, &yellow);
        if (MyNetworkId % 2) {
            sprintf(buf, "MY NETWORK ID = RED %d", MyNetworkId);
            font1->drawText(-41.0F, (yf - 1.67) * 10, zf, buf, &red);
        } else {
            sprintf(buf, "MY NETWORK ID = BLUE %d", MyNetworkId);
            font1->drawText(-41.0F, (yf - 1.67) * 10, zf, buf, &blue);
        }
        if ((IffOnOff) && (ThreeDObjects[SelectedMissionTarget]->Sentient < 3) && (RadarZoom != 8)) {
            switch (SelectedMissionTarget % 2) {
            case 0:
            {
                if (SelectedMissionTarget == MissionObjectHqBlue) {
                    sprintf(DebugBuf, "TARGET ID= %d (HQ BLUE)", MissionObjectHqBlue);
                } else if (SelectedMissionTarget == MissionObjectAirfieldBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectAirfieldBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectAirfieldBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectAirfieldBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarBlue1) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR BLUE1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarBlue2) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR BLUE2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarBlue3) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR BLUE3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarBlue4) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR BLUE4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarHqBlue) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR HQBLUE)", SelectedMissionTarget);
                } else {
                    sprintf(DebugBuf, "TARGET ID= BLUE %d", SelectedMissionTarget);
                }
                font1->drawText(-41.0F, (yf - 1.78) * 10, zf, DebugBuf, &blue);
                break;
            }
            case 1:
            {
                if (SelectedMissionTarget == MissionObjectHqRed) {
                    sprintf(DebugBuf, "TARGET ID= %d (HQ RED)", MissionObjectHqRed);
                } else if (SelectedMissionTarget == MissionObjectAirfieldRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectAirfieldRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectAirfieldRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectAirfieldRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (AIRFIELD RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBatteryRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTERY RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBattleshipRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (BATTLESHIP RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectDestroyerRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (DESTROYER RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectBunkerRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (BUNKER RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectCarrierRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (CARRIER RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarRed1) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR RED1)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarRed2) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR RED2)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarRed3) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR RED3)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarRed4) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR RED4)", SelectedMissionTarget);
                } else if (SelectedMissionTarget == MissionObjectRadarHqRed) {
                    sprintf(DebugBuf, "TARGET ID= %d (RADAR HQRED)", SelectedMissionTarget);
                } else {
                    sprintf(DebugBuf, "TARGET ID= RED %d", SelectedMissionTarget);
                }
                font1->drawText(-41.0F, (yf - 1.78) * 10, zf, DebugBuf, &red);
                break;
            }
            default:
            {
                break;
            }
            }
        } else {
            if (IffOnOff && (RadarZoom != 8)) {
                switch (SelectedMissionTarget % 2) {
                case 0:
                {
                    sprintf(buf, "TARGET ID= %s", PlayerIdStrings[(SelectedMissionTarget - 1)]);
                    font1->drawText(-41.0F, (yf - 1.78) * 10, zf, buf, &blue);
                    break;
                }
                case 1:
                {
                    sprintf(buf, "TARGET ID= %s", PlayerIdStrings[(SelectedMissionTarget - 1)]);
                    font1->drawText(-41.0F, (yf - 1.78) * 10, zf, buf, &red);
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
        }
    }
    if (fplayer->UndercarriageLevel) {
        if (fplayer->id != FIGHTER_ME163) {
            sprintf(buf, "UNDERCARRIAGE");
        } else {
            sprintf(buf, "LANDING SKID");
        }
        font1->drawTextCentered(xf * -9, (yf - 1.1) * 10, zf, buf, &white);
    }
    sprintf(buf, "FLARE: %d", fplayer->flares);
    font1->drawTextCentered(xf * 10, (yf2 - 1.8) * 10, zf, buf, &grey);

    if (fplayer->id > LASTJETFIGHTER) {
        PlayerEngineType = 0;
    } else {
        PlayerEngineType = 1; // Cue jet engine sounds
    }
    if (fplayer->id == FIGHTER_ME163) {
        PlayerEngineType = 1;
    }
}

void Cockpit::drawCross() {
    glDisable(GL_LIGHTING);
    gl->enableAlphaBlending();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.1);
    if (ClimbAngleExceedsMaxSustainable) {
        setColor(128);
    } else {
        setColor(254);
    }
    gl->enableTextures(texcross->textureID);
    float xf = 0.1, yf = 0.1, zf = 2.0;
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3f(-xf, -yf, -zf);
    glTexCoord2d(0, 1);
    glVertex3f(-xf, yf, -zf);
    glTexCoord2d(1, 1);
    glVertex3f(xf, yf, -zf);
    glTexCoord2d(1, 0);
    glVertex3f(xf, -yf, -zf);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    gl->disableAlphaBlending();

}

//
// Draw a horizontally scrolling digital direction indicator across
// the top of our HUD. Also draw ladder bars.
void Cockpit::drawHeading() {
    extern float ScreenFOVx;
    CColor color;
    int i = 0;
    int alpha = 175;
    setColor(&color, alpha);
    glDisable(GL_LIGHTING);
    glLineWidth(LINEWIDTH(2.0F));
    glDisable(GL_DEPTH_TEST);
    float xf;
    float yf = 17.5;
    float zf = -2.5 * ScreenFOVx;
    float g = 0.5;
    for (i = 0; i < 360; i += 5) {
        float p = (float)i - fplayer->phi;
        p = p - 37;
        if (p < -180) {
            p += 360;
        }
        if (p > 180) {
            p -= 360;
        }
        if (p >= -40 && p <= 40) {
            if ((i - mission->heading) % 90 == 0) {
                g = 0.6;
            } else if (!(i % 10)) {
                g = 0.3;
            } else {
                g = 0.1;
            }
            xf = p / 6.0;
            gl->enableAlphaBlending();
            setColor(alpha);
            glBegin(GL_LINES);
            glVertex3f(xf * 0.1, (yf - g) * 0.1, zf);
            glVertex3f(xf * 0.1, yf * 0.1, zf);
            glEnd();
            if (i == mission->heading) {
                font1->drawText(xf - 0.5, yf - 2.0, zf, (char*)"S", &color);
            } else if (i == mission->heading + 90 || i == mission->heading - 270) {
                font1->drawText(xf - 0.5, yf - 2.0, zf, (char*)"E", &color);
            } else if (i == mission->heading + 180 || i == mission->heading - 180) {
                font1->drawText(xf - 0.5, yf - 2.0, zf, (char*)"N", &color);
            } else if (i == mission->heading + 270 || i == mission->heading - 90) {
                font1->drawText(xf - 0.5, yf - 2.0, zf, (char*)"W", &color);
            }
        }
    }
    if (HudOnOff && HudLadderBarsOnOff) {
        gl->enableAlphaBlending();
        float dgamma = fplayer->gamma - (int)fplayer->gamma;
        float innerx = 5, outerx = 10;
        int step = 15;
        glLineWidth(LINEWIDTH(1.2F));
        glBegin(GL_LINES);
        float tmp = fplayer->gamma - 179.5;
        //
        // Draw center ladder rung:
        //
        cockpitvertex(-innerx, tmp);
        cockpitvertex(-20, tmp);
        cockpitvertex(innerx, tmp);
        cockpitvertex(20, tmp);
        //
        // Draw remaining ladder rungs:
        for (i = -175 + step; i < 200; i += step) {
            float tmp = int(-i + fplayer->gamma + 538) % 360 - 180;
            tmp += dgamma;
            cockpitvertex(-innerx, tmp + 1);
            cockpitvertex(-innerx, tmp);
            cockpitvertex(innerx, tmp + 1);
            cockpitvertex(innerx, tmp);
            cockpitvertex(-outerx, tmp);
            cockpitvertex(-innerx, tmp);
            cockpitvertex(innerx, tmp);
            cockpitvertex(outerx, tmp);
        }
        glEnd();
    }
    gl->disableAlphaBlending();
    glLineWidth(LINEWIDTH(2.0F));
} // end Cockpit::drawHeading ()

void Cockpit::drawRadar() {
    int i;
    float SelectedRadarBlipX = 0.0;
    float SelectedRadarBlipY = 0.0;
    float SelectedRadarBlipZ = 0.0;
    float yf = -4.2 - (float)SkewViewUp / 2.5;
    float zf = -7.0 * ScreenFOVx;
    gl->enableAlphaBlending();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.1);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    setColor(150);
    float xl, yl;

    gl->enableTextures(texradar2->textureID);
    xl = 1.55;
    yl = 1.33;
    glBegin(GL_QUADS);
    if (RadarOnOff) {
        if (StrategicEnemyBomberBeyondRadarDisplay) {
            glColor4ub(250, 250, 00, 140);
        } else {
            glColor4ub(30, 250, 30, 140);
        }
    } else {
        glColor4ub(30, 80, 30, 150);
    }
    glTexCoord2d(0, 0);
    glVertex3f(-xl, yf - yl, zf);
    glTexCoord2d(0, 1);
    glVertex3f(-xl, yf + yl, zf);
    glTexCoord2d(1, 1);
    glVertex3f(xl, yf + yl, zf);
    glTexCoord2d(1, 0);
    glVertex3f(xl, yf - yl, zf);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(LINEWIDTH(1.0F));
    glBegin(GL_LINES);
    glVertex3f(0, yf - yl * 0.9, zf);
    glVertex3f(0, yf + yl * 0.9, zf);
    glVertex3f(-xl * 0.9, yf, zf);
    glVertex3f(xl * 0.9, yf, zf);
    glEnd();
    if (!RadarOnOff) {
        return;
    }

    for (i = 0; i < maxfighter; i++) {
        if (ThreeDObjects[i] != fplayer && ThreeDObjects[i]->active) {

            int aw = fplayer->getAngle(ThreeDObjects[i]);
            if (aw < 0) {
                aw += 360;
            }
            if (aw > 360) {
                aw = aw % 360; // Fix with modulus operator.
            }

            float d = fplayer->distanceXZ(ThreeDObjects[i]) / 2000.0 * (RadarZoom + 1);

            if (MyNetworkId % 2) {
                if (AllRedTeamAirfieldsAreHeavilyDamaged) {
                    d *= 1000;
                    RadarZoom = 8;
                } else {
                    if (RadarZoom == 8) {
                        RadarZoom = 2;
                    }
                }
            } else {
                if (AllBlueTeamAirfieldsAreHeavilyDamaged) {
                    d *= 1000;
                    RadarZoom = 8;
                } else {
                    if (RadarZoom == 8) {
                        RadarZoom = 2;
                    }
                }
            }
            if (RadarZoom == 7) {
                d = d * 2.0;
            }
            if (RadarZoom == 1) {
                d = d * 0.35;
            }
            if (RadarZoom == 0) {
                d = d * 0.2;
            }

            if (isnan(d)) { // Error! Get here if "d" is not a number. Replace it with a harmless floating-point number.
                display((char*)"Cockpit__drawCounter(): Discarding invalid value of d.", LOG_MOST);
                // Extensive experience has revealed that on very rare occasions at this point, the
                // value of "d" is somehow corrupted, or is otherwise "Not A Number".  In c++, this
                // is known as "nan" and it causes a segmentation fault. In this case, we replace "d"
                // with a genuine floating-point number of sufficient magnitude to avoid displaying
                // the corresponding dot on the RADAR screen.
                d = 7.0; // 7.0 is big enough to push this dot beyond RADAR edges.
                // When d is corrupted, we often find "aw" may also be corrupted. Accordingly,
                // we also replace that value with something harmless:
                aw = 25;
                sprintf(DebugBuf, "Cockpit::drawCounter() DebugRJBCC08 Object#%d. d=%f. aw=%d. yf=%f.", i, d, aw, yf);
                display(DebugBuf, LOG_MOST);
            }
            float px = -d * SIN(aw);
            float py = yf + d * COS(aw);
            if (((d < 1.18) || (px >= -0.95 && px <= 0.95 && py >= yf - 0.95 && py <= yf + 0.95)) && ThreeDObjects[i]->tl->y > (SeaLevel - 30)) {
                if (IffOnOff) {

                    if ((NetworkOpponent && PeerPacketReceivedInThisMissionState) || (ThreeDObjects[i]->Sentient > 1)) {
                        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9) {
                            if (ThreeDObjects[i]->maxDurability > 2401) {
                                drawBlip(BIG_DIAMONDBLIP, px, py, zf, 255, 000, 000);
                            } else {
                                drawBlip(BIG_BLIP, px, py, zf, 255, 000, 000);
                            }
                        } else {
                            if (ThreeDObjects[i]->maxDurability > 2401) {
                                drawBlip(BIG_DIAMONDBLIP, px, py, zf, 000, 000, 255);
                            } else {
                                drawBlip(BIG_BLIP, px, py, zf, 000, 000, 255);
                            }
                        }
                    } else {
                        if (1) {
                            if (i % 2) {
                                drawBlip(SQUARE_BLIP, px, py, zf, 255, 000, 000);
                            } else {
                                drawBlip(SQUARE_BLIP, px, py, zf, 000, 000, 255);
                            }
                        } else if (i % 2) {
                            drawBlip(SQUARE_BLIP, px, py, zf, 255, 000, 000);
                        } else {
                            drawBlip(SQUARE_BLIP, px, py, zf, 000, 000, 255);
                        }
                    }
                } else {
                    drawBlip(SQUARE_BLIP, px, py, zf, 160, 160, 160);
                }
                if (i == SelectedMissionTarget) {

                    SelectedRadarBlipX = px;
                    SelectedRadarBlipY = py;
                    SelectedRadarBlipZ = zf;
                }
                if (StrategicWarningTimer == 0) {
                    StrategicEnemyBomberBeyondRadarDisplay = false; // Disable warning about off-screen strategic hostile bomber
                }
            } else {
                if (
                    (ThreeDObjects[i]->tl->y > (SeaLevel + 31)) &&
                    (
                        (ThreeDObjects[i]->id == BOMBER_B29) ||
                        (ThreeDObjects[i]->id == BOMBER_B17) ||
                        (ThreeDObjects[i]->id == BOMBER_B24) ||
                        (ThreeDObjects[i]->id == BOMBER_LANCASTER) ||
                        (ThreeDObjects[i]->id == BOMBER_HE111)
                        )
                    ) {
                    if (i % 2 != MyNetworkId % 2) {
                        StrategicEnemyBomberBeyondRadarDisplay = true;
                        StrategicWarningTimer = 200;
                    }
                }
            }
        }
    }
    for (i = 0; i < maxmissile; i++) {
        if (missile[i]->target == fplayer && missile[i]->active) {
            int aw = fplayer->getAngle(missile[i]);
            if (aw < 0) {
                aw += 360;
            }
            float d = fplayer->distance(missile[i]) / 2000.0 * RadarZoom;
            if (RadarZoom == 7) {
                d = d * 2.0;
            }
            if (RadarZoom == 1) {
                d = d * 0.35;
            }
            if (RadarZoom == 0) {
                d = d * 0.2;
            }
            float px = -d * SIN(aw);
            float py = yf + d * COS(aw);
            if ((d < 1.2) || (px >= -1.2 && px <= 1.2 && py >= yf - 1.1 && py <= yf + 1.1)) {
                drawBlip(TRIANGLE_BLIP, px, py, zf, 000, 000, 000);
            }
        }
    }
    gl->disableAlphaBlending();
    switch (RadarZoom) {
    case 0:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"500KM", 240);
        break;
    case 1:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"200KM", 240);
        break;
    case 2:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"050KM", 240);
        break;
    case 3:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"035KM", 240);
        break;
    case 4:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"025KM", 240);
        break;
    case 5:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"020KM", 240);
        break;
    case 6:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"016KM", 240);
        break;
    case 7:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"007KM", 240);
        break;
    case 8:
        font1->drawTextCentered(0.0, (yf - 1.0) * 7.2, zf * 0.7, (char*)"NO SIGNAL", 240);
        break;
    }
    if (!IffOnOff) {
        font1->drawTextCentered(0.3, (yf - 0.85) * 7.2, zf * 0.7, (char*)"NO IFF ", 240);
    }

    if (IffOnOff && SelectedMissionTarget > 0 && SelectedMissionTarget < 30 && camera == 0) {
        drawBlip(SQUARE_BLIP, SelectedRadarBlipX, SelectedRadarBlipY, SelectedRadarBlipZ, 255, 255, 255);
    }
}

/**********************************
* drawTargeter()
**********************************/
void Cockpit::drawTargeter() {
    if (!HudOnOff) {
        return;
    }
    if (!RadarOnOff) {
        return;
    }
    if (!IffOnOff) {
        return;
    }
    if ((CurrentMissionNumber == MISSION_NETWORKBATTLE02) || (CurrentMissionNumber == MISSION_NETWORKBATTLE06)) {
        if (ThreeDObjects[SelectedMissionTarget]->tl->y < (SeaLevel - 30.0)) {
            return;
        }
    }

    if (SelectedMissionTarget != 0) {
        float myphi = fplayer->phi;
        if (myphi < 0) {
            myphi += 360;
        }
        float ex1 = COS((int)myphi) * ThreeDObjects[SelectedMissionTarget]->zoom, ey1 = -SIN((int)myphi) * ThreeDObjects[SelectedMissionTarget]->zoom;
        float ex2 = -ex1, ey2 = -ey1;
        float ez = ThreeDObjects[SelectedMissionTarget]->zoom;
        gl->enableAlphaBlending();
        bool full = false;

        if (ThreeDObjects[SelectedMissionTarget]->Sentient > 3 && IffOnOff) {
            if (SelectedMissionTarget % 2) {
                glColor4ub(255, 000, 000, 255);
                full = true;
            } else {
                glColor4ub(000, 000, 255, 255);
                full = true;
            }
        }

        if (1) {
            if (ThreeDObjects[SelectedMissionTarget]->Sentient < 3) {
                if (SelectedMissionTarget % 2) {
                    if (NetworkMode & 128) {
                        glColor4ub(255, 000, 000, 180);
                    } else {
                        glColor4ub(255, 000, 000, 90);
                    }
                    full = true;
                } else {
                    if (NetworkMode & 128) {
                        glColor4ub(000, 000, 255, 180);
                    } else {
                        glColor4ub(000, 000, 255, 90);
                    }
                    full = true;
                }
            }
        }

        if (!full) {
            float dx = (ex2 - ex1) / 4;
            float dy = (ey2 - ey1) / 4;
            float dz = ez / 2;
            glBegin(GL_LINE_STRIP);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y + ez - dz, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1 + dx, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1 + dy);
            glEnd();
            glBegin(GL_LINE_STRIP);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2 - dx, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2 - dy);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2, ThreeDObjects[SelectedMissionTarget]->tl->y + ez - dz, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2);
            glEnd();
            glBegin(GL_LINE_STRIP);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2, ThreeDObjects[SelectedMissionTarget]->tl->y - ez + dz, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2, ThreeDObjects[SelectedMissionTarget]->tl->y - ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2 - dx, ThreeDObjects[SelectedMissionTarget]->tl->y - ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2 - dy);
            glEnd();
            glBegin(GL_LINE_STRIP);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1 + dx, ThreeDObjects[SelectedMissionTarget]->tl->y - ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1 + dy);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y - ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y - ez + dz, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glEnd();
        } else {
            // Select narrow or wide line width based on the "128 bit" of NetworkMode:
            if (NetworkMode & 128) { // Enhanced display detail
                glLineWidth(8);
            } else { // Normal display detail
                glLineWidth(2);
            }
            glBegin(GL_LINE_STRIP);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex2, ThreeDObjects[SelectedMissionTarget]->tl->y - ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey2);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y - ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glVertex3f(ThreeDObjects[SelectedMissionTarget]->tl->x + ex1, ThreeDObjects[SelectedMissionTarget]->tl->y + ez, ThreeDObjects[SelectedMissionTarget]->tl->z + ey1);
            glEnd();
        }
        gl->disableAlphaBlending();
    }
}

void Cockpit::drawThrustBar() {
    extern float ScreenFOVx;
    char str[STDSIZE];
    CColor color;
    int alpha = 175;
    float yfv;
    unsigned int red = 128;
    unsigned int green = 128;
    unsigned int blue = 128;
    unsigned int transparency = 255;
    DamageRatio = fplayer->Durability / fplayer->maxDurability;
    if (DamageRatio < 0.6) {
        red = 255;
        green = 0;
        blue = 0;
    }
    glDisable(GL_LIGHTING);
    glLineWidth(LINEWIDTH(1.0F));
    glDisable(GL_DEPTH_TEST);
    gl->enableAlphaBlending();
    glColor4ub(red, green, blue, transparency);
    if (fplayer->WEPLevel) {
        setColor(255);
    }
    float xf = -0.93F, xfl = 0.06F, yf = -2.2F, yfl = 0.7F, zf = -4.0F * ScreenFOVx;
    if (difficulty > 3) {

        if (1) // Production version
        {
            yfv = ((float)ThrottleReference / -65535.0 * 2.8F - 2.1F) / 2.4;
        } else // Development and debugging
        {
            yfv = (fplayer->thrust / fplayer->maxthrust * 2.8F - 2.1F) / 5.0;
            if (yfv > 0.350) {
                yfv = 0.350;
            }

        }
    } else {
        yfv = (fplayer->thrust / fplayer->maxthrust * 2.8F - 2.1F) / 5.0;
    }
    if (yfv > 0.7F) {
        yfv = 0.7F;
    }
    if (yfv < -0.5F) {
        yfv = -0.5F;
    }
    if (fplayer->FuelLevel <= 0) {
        yfv = -0.7;
    }
    glBegin(GL_QUADS);
    glVertex3f(xf - xfl, yf - yfl, zf);
    glVertex3f(xf + xfl, yf - yfl, zf);
    glVertex3f(xf + xfl, yf + yfv, zf);
    glVertex3f(xf - xfl, yf + yfv, zf);
    glEnd();
    setColor(alpha);
    sprintf(str, "THROTTLE");
    font1->drawTextCentered(xf * 10.0F, (yf + 0.36F) * 10.0F, zf, str, &color);
    glEnd();
    gl->disableAlphaBlending();
}

void Cockpit::drawWeapon() {
    extern float ScreenFOVx;
    char str[20];
    CColor color;
    CVector3 tl, n;
    CRotation r;
    if (!HudOnOff) {
        return;
    }
    if (fplayer->missiles[fplayer->missiletype] <= 0) {

        return;
    }

    color.setColor(240, 240, 240);
    color.c[3] = 255;
    tl.x = 0.35;
    tl.y = -0.3;
    tl.z = -0.5;
    gl->disableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    CModel* missile = NULL;
    if (fplayer->missiletype == 0) {
        missile = &model_bomb01;
    } else if (fplayer->missiletype == 1) {
        missile = &model_missile2;
    } else if (fplayer->missiletype == 2) {
        missile = &model_missile3;
    } else if (fplayer->missiletype == 3) {
        missile = &model_missile4;
    } else if (fplayer->missiletype == 4) {
        missile = &model_missile5;
    } else if (fplayer->missiletype == 5) {
        missile = &model_missile6;
    } else if (fplayer->missiletype == 6) {
        missile = &model_missile7;
    } else if (fplayer->missiletype == 7) {
        missile = &model_missile8;
    }
    float zf = -4.0F * ScreenFOVx;
    font1->drawText(25.2, -32.5, zf, missile->name, &color);
    sprintf(str, "N %d", fplayer->missiles[fplayer->missiletype]);
    font1->drawText(35.2, -32.5, zf, str);
}

void Cockpit::setColor(int alpha) {
    if (fplayer->o == &model_fig) {
        glColor4ub(240, 240, 240, alpha);
    } else {
        glColor4ub(240, 240, 240, alpha);
    }
}

void Cockpit::setColor(CColor* color, int alpha) {
    if (fplayer->o == &model_fig) {
        color->setColor(240, 240, 240, alpha);
    } else {
        color->setColor(240, 240, 240, alpha);
    }
}

