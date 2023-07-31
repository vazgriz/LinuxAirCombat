/*
    LAC (Linux Air combat)
    Copyright 2015 by Robert J. Bosen.

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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
    USA
*/

#include "common.h"
#include "glland.h"
#include "NetworkApi.h"
#include "mission.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

extern bool ChaffPacketFired;
extern bool FlareFired;
extern bool GunCameraActive;
extern bool GunCameraStartSegmentFlag;
extern bool GunCameraStopSegmentFlag;
extern bool InPacketContainsMumbleBroadcast;
extern bool InPacketContainsMumbleNarrowcast;
extern bool LandedAtSafeSpeed;
extern bool MissileFired;
extern bool MumbleBroadcastRequested;
extern bool MumbleChannelExitRequested;
extern bool MumbleCurrentMissionChannelRequested;
extern bool MumbleCurrentMissionBlueSubChannelRequested;
extern bool MumbleCurrentMissionRedSubChannelRequested;
extern bool MumbleChannelMainRequested;
extern bool MumbleIsAccessible;
extern bool MumbleManagement;
extern bool MumbleTransmissionRequested;
extern bool NetworkMissionIsActiveWithDataFlow;
extern bool NewSystemMessageNeedsScrolling;
extern bool Promoted;
extern bool UdpSetupCompleted;

extern bool MorseSquelches[10];

extern char CurrentMissionNumber;

extern char CommunityHandle[20];
extern char DebugBuf[];
extern char MorseCharacterOut[48];
extern char MorseRadioMessageBuffer[];
extern char NetworkPlayerMumbleChannel[];
extern char SystemMessageBufferA[];
extern char NetworkPassword[];
extern char RemoteDnsIpAddress[];
extern char ServerIpAddressAscii[];
extern char ServerMessageBuffer[81];

extern char PlayerIdStrings[10][9];

extern float DamageToClaim;

extern unsigned char MissionObjectHqBlue;
extern unsigned char MissionObjectHqRed;
extern unsigned char MaxPlayersInCurrentMission;
extern unsigned char MissionChronoMilestone;
extern unsigned char MissionCommander;
extern unsigned char MissionHeadToHead00State;
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
extern unsigned char MissionOutPacketCount;
extern unsigned char MorseCharacterIn;
extern unsigned char MumbleChannelPresumed;
extern unsigned char MyNetworkId;
extern unsigned char NetworkApiVersion;
extern unsigned char NewestInPacketId;
extern unsigned char NewestMumblePacketId;
extern unsigned char PreviousMorseInCharacter;
extern unsigned char PreviousMorseSender;
extern unsigned char Realm;
extern unsigned char RepeatedMorseInCharCount;
extern unsigned char ServerIpByte1of4;
extern unsigned char ServerIpByte2of4;
extern unsigned char ServerIpByte3of4;
extern unsigned char ServerIpByte4of4;
extern unsigned char ServerMessageRecipient;

extern int IffOnOff;
extern int MissionAircraftDamaged;
extern int MissionMumbleTimer[32];
extern int MissionPacketTimer[32];
extern int MorsePanelHighlightTimer;
extern int NetworkMode; // Mode 0 = PeerToPeer. Mode 1 = ClientServer.
extern int NetworkReceiveTimer;
extern int NetworkTransmitTimer;
extern int PlayerAircraftType;
extern int ServerMessageTimer;
extern unsigned int MyInPortNumber;
extern unsigned int PeerInPortNumber;

extern Uint16 OutGoingPacketSignature;

extern long MilestoneCorrectionTimer;
extern long int MorsePanelActiveTimer;

extern float FratricideShameFactor;
extern float ThrustReadiness;

extern void SwitchMumbleToSecretChannel(unsigned char);
extern void CleanPlayerIdStrings();
extern void event_CommsMacro10();
extern void event_CommsMacro17();
extern void event_CommsMacro18();
extern void VocalizeMorseCharacter(unsigned char);

/* Function Prototypes: */
void AdjustHeightAboveRunwayIfLanded();
int  AuthenticateInPacket();
void ConvertStringToUpperCase(char* Pointer);
int  DiscardAnyInPacketsInQueue();
bool MissionNetworkBattle01RetrieveFirstDamageDescription();
void SendAdmin012Packet();
void SendAdmin013Packet();
void SignOutPacket();
void ShiftServerIpAddressAsciiLeft(char);
void UpdateOnlineScoreLogFileWithDefeats();
void UpdateOnlineScoreLogFileWithVictories();

char ServerIpAddressDottedDecimal[16];
int ClientSocketHandle;
int InSocketHandle;
int OutSocketHandle;
unsigned long int AdminOutPacketCount = 0;
struct hostent* hostlist;
struct sockaddr_in ClientDestinationAddress;
struct sockaddr_in ClientSourceAddress;
struct sockaddr_in InSocketAddress;
struct sockaddr_in OutSocketAddress;
socklen_t ClientDestinationAddressLength = sizeof(ClientDestinationAddress);
socklen_t ClientSourceAddressLength = sizeof(ClientSourceAddress);
socklen_t InSocketAddressLength = sizeof(InSocketAddress);
socklen_t OutSocketAddressLength = sizeof(OutSocketAddress);
LacUdpApiPacket OutPacket;
LacUdpApiPacket InPacket;
Admin012Packet Admin012OutPacket;
Admin013Packet Admin013InPacket;
Admin014Packet Admin014InPacket;
Admin013Packet Admin013OutPacket;

LacUdpApiPacket PriorInPacket[32];

/* Low-Level Network Functions: */

void AdjustHeightAboveRunwayIfLanded() {
    if (!LandedAtSafeSpeed) {
        return;
    }

    OutPacket.UdpObjYPosition -= (fplayer->zoom * 0.7);
}

int AuthenticateInPacket() {

    unsigned int PayloadSize = sizeof(InPacket);
    unsigned int NetworkPasswordSize = 32;
    unsigned char CrcByte1of2 = 0;
    unsigned char CrcByte2of2 = 0;
    unsigned char InPacketBuffer[PayloadSize];
    unsigned char InPacketPositionPointer = 0;
    unsigned char PasswordPositionPointer = 0;
    Uint16 CalculatedHash = 0;
    memcpy(InPacketBuffer, &InPacket, PayloadSize);
    for (PasswordPositionPointer = 0; PasswordPositionPointer < NetworkPasswordSize; PasswordPositionPointer++) {
        CrcByte1of2 ^= NetworkPassword[PasswordPositionPointer];
    }
    CrcByte2of2 = CrcByte1of2;

    for (InPacketPositionPointer = 0; InPacketPositionPointer < PayloadSize; InPacketPositionPointer++) {
        CrcByte1of2 ^= InPacketBuffer[InPacketPositionPointer];
        CrcByte2of2 = (CrcByte1of2 ^ InPacketPositionPointer);
    }

    CalculatedHash = (Uint16)CrcByte1of2 * 256;
    CalculatedHash += (Uint16)CrcByte2of2;
    if (CalculatedHash == InPacket.UdpObjHash) {
        return(0);
    } else {
        return (-1); // return -1 to signal unauthenticated
    }
}

void LoadServerIpAddress() {
    if (strcmp(RemoteDnsIpAddress, "void.void.void") == 0) {
        display((char*)"LoadServerIpAddress() did not find a configured DNS name in LacConfig.txt", LOG_NET);
        sprintf(&ServerIpAddressAscii[0], "%03i", ServerIpByte1of4);
        sprintf(&ServerIpAddressAscii[3], ".");
        sprintf(&ServerIpAddressAscii[4], "%03i", ServerIpByte2of4);
        sprintf(&ServerIpAddressAscii[7], ".");
        sprintf(&ServerIpAddressAscii[8], "%03i", ServerIpByte3of4);
        sprintf(&ServerIpAddressAscii[11], ".");
        sprintf(&ServerIpAddressAscii[12], "%03i", ServerIpByte4of4);
        ServerIpAddressAscii[15] = 0;
    } else {
        display((char*)"LoadServerAddress() found text in LacConfig.txt that might be a valid DNS name.", LOG_NET);
        strcpy(ServerIpAddressAscii, RemoteDnsIpAddress);
    }

    unsigned char Index1 = 0;
    if (ServerIpAddressAscii[Index1] == '0') {
        ShiftServerIpAddressAsciiLeft(--Index1);
    }
    for (Index1 = 0; Index1 < 15; Index1++) {
        if (ServerIpAddressAscii[Index1] == '.') {
            if (ServerIpAddressAscii[(Index1 + 1)] == '0') {
                ShiftServerIpAddressAsciiLeft(Index1);
            }
            if (ServerIpAddressAscii[(Index1 + 1)] == '0') {
                ShiftServerIpAddressAsciiLeft(Index1);
            }
        }
    }
    display((char*)"ServerIpAddressAscii=", LOG_MOST);
    display(ServerIpAddressAscii, LOG_MOST);
    display((char*)"Looking up Hostname:", LOG_MOST);
    hostlist = gethostbyname(ServerIpAddressAscii);
    if (hostlist == NULL) {
        if (!(NetworkMode & 16)) {
            popen("espeak -p 70 \"LAC IS UNABLE TO RESOLVE THE HOST NAME. THIS MEANS YOU HAVE NO INTERNET ACCESS OR ELSE YOUR DNS SERVER IS TEMPORARILY DOWN. NONE OF LAC'S ONLINE MISSIONS WILL WORK.\"", "r");
        }
        display((char*)"\n", LOG_MOST);
        display((char*)"LoadServerIpAddress() UNABLE TO RESOLVE HOST NAME.", LOG_MOST);
        display((char*)"THIS MEANS YOU HAVE NO INTERNET ACCESS, OR ELSE YOUR", LOG_MOST);
        display((char*)"DNS SERVER IS TEMPORARILY DOWN. IF YOUR COMPUTER CANNOT", LOG_MOST);
        display((char*)"GET INTERNET ACCESS, NONE OF LAC'S ONLINE MISSIONS", LOG_MOST);
        display((char*)"WILL WORK AND LAC MAY EXIT IF YOU ATTEMPT TO START ANY", LOG_MOST);
        display((char*)"OF THOSE ONLINE MISSIONS.", LOG_MOST);
        if (strcmp(RemoteDnsIpAddress, "void.void.void") != 0) {

            display((char*)"\n", LOG_MOST);
            display((char*)"UNFORTUNATELY, LAC IS CONFIGURED TO USE DNS TO FIND THE", LOG_MOST);
            display((char*)"LAC SERVER, BUT DNS SERVICES CANNOT BE ACCESSED. THIS MAY", LOG_MOST);
            display((char*)"BE ONLY A TEMPORARY SITUATION, BUT FOR NOW THIS IS A FATAL", LOG_MOST);
            display((char*)"ERROR. LAC IS TERMINATING.", LOG_MOST);
            exit(0);
        }
    } else {
        display((char*)"LoadServerIpAddress() resolved to valid hostlist.", LOG_NET);
        if (hostlist->h_addrtype != AF_INET) {
            display((char*)"Server IP Address is not properly formatted for IPV4.", LOG_NET);
        }

        inet_ntop(AF_INET, hostlist->h_addr_list[0], ServerIpAddressDottedDecimal, 15);
        display((char*)"LoadServerIpAddress() Resolved Server IP to:", LOG_NET);
        sprintf(DebugBuf, "%s", ServerIpAddressDottedDecimal);
        display(DebugBuf, LOG_NET);
    }
}

void ShiftServerIpAddressAsciiLeft(char Index1) {
    unsigned char NewIndex = Index1;
    while (NewIndex++ < 15) {
        ServerIpAddressAscii[NewIndex] = ServerIpAddressAscii[NewIndex + 1];
    }
}

short int OpenClientUdpSocket() {
    ClientSocketHandle = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (ClientSocketHandle < 0) {
        display((char*)"OpenClientUdpSocket() unable to open requested Datagram Socket", LOG_NET);
        return (1);
    } else {
        return (0);
    }
}

short int OpenUdpSocketForSending() {
    OutSocketHandle = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (OutSocketHandle < 0) {
        display((char*)"NetworkApi.cpp OpenUdpSocketForSending() unable to open requested Datagram Socket", LOG_NET);
        return (1);
    } else {
        return (0);
    }
}

short int OpenUdpSocketForReceiving() {
    if (UdpSetupCompleted) {
        return 0;
    }
    InSocketHandle = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (InSocketHandle < 0) {
        display((char*)"NetworkApi.cpp OpenUdpSocketForReceiving() unable to open requested Datagram Socket. errno=", LOG_NET);
        sprintf(DebugBuf, "%s", strerror(errno));
        display(DebugBuf, LOG_NET);
        return (1);
    } else {
        display((char*)"OpenUdpSocketForReceiving() returned 0 indicating success.", LOG_NET);
        display((char*)"InSocketHandle=", LOG_NET);
        sprintf(DebugBuf, "%i", InSocketHandle);
        display(DebugBuf, LOG_NET);
        return (0);
    }
}

void ConfigureClientUdpSocket() {
    /* Local Variables: */
    short unsigned int EphemeralClientPort;
    int BindStatus = 1; // Initialize to 1 to see if it changes to 0 as expected

    memset(&ClientDestinationAddress, 0, ClientDestinationAddressLength);
    ClientDestinationAddress.sin_family = AF_INET;
    memcpy(&ClientDestinationAddress.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
    ClientDestinationAddress.sin_port = htons(PeerInPortNumber);

    memset(&ClientSourceAddress, 0, ClientSourceAddressLength);
    ClientSourceAddress.sin_family = AF_INET;
    ClientSourceAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    ClientSourceAddress.sin_port = 0;
    BindStatus = bind(
        ClientSocketHandle,
        (struct sockaddr*)&ClientSourceAddress,
        sizeof(ClientSourceAddress)
    );
    if (BindStatus < 0) {
        display((char*)"ConfigureClientUdpSocket() cannot bind to an ephemeral UDP port.", LOG_NET);
        sprintf(DebugBuf, "%s", strerror(errno));
        display(DebugBuf, LOG_NET);
    } else {
        display((char*)"ConfigureClientUdpSocket() ClientServer mode bind() succeeded for ClientSourceAddress. BindStatus=", LOG_NET);
        sprintf(DebugBuf, "%i", BindStatus);
        display(DebugBuf, LOG_NET);

        if ((getsockname(ClientSocketHandle, (struct sockaddr*)&ClientSourceAddress, &ClientSourceAddressLength)) != -1) {
            EphemeralClientPort = ntohs(ClientSourceAddress.sin_port);
            display((char*)"EphemeralClientPort = ", LOG_NET);
            sprintf(DebugBuf, "%d", EphemeralClientPort);
            display(DebugBuf, LOG_NET);
        } else {
            display((char*)"ConfigureClientUdpSocket() ClientServer mode getsockname() failed for ClientSourceAddress.", LOG_NET);
        }
    }
    if ((NetworkMode & 1) == 1) {
        EphemeralClientPort = ntohs(ClientSourceAddress.sin_port);
        display((char*)"EphemeralClientPort = ", LOG_NET);
        sprintf(DebugBuf, "%d", EphemeralClientPort);
        display(DebugBuf, LOG_NET);
    }
}

void ConfigureIncomingUdpSocket() {
    /* Local Variables: */
    short unsigned int EphemeralInPort;
    if (UdpSetupCompleted) {
        return;
    }
    int BindStatus = 1; // Initialize to 1 to see if it changes to 0 as expected
    memset(&InSocketAddress, 0, InSocketAddressLength);
    InSocketAddress.sin_family = AF_INET; // Configure for IPV4
    InSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((NetworkMode & 1) == 0) {
        InSocketAddress.sin_port = htons(MyInPortNumber);
    } else if ((NetworkMode & 1) == 1) {
        display((char*)"ConfigureIncomingUdpSocket() InSocketAddress.sin_port=", LOG_NET);
        sprintf(DebugBuf, "%hu", ntohs(InSocketAddress.sin_port));
        display(DebugBuf, LOG_NET);
    }
    if ((NetworkMode & 1) == 0) {

        BindStatus = bind(
            InSocketHandle,
            (struct sockaddr*)&InSocketAddress,
            sizeof(InSocketAddress)
        );
        if (BindStatus < 0) {
            display((char*)"ConfigureIncomingUdpSocket() cannot bind to requested UDP port. Port=", LOG_NET);
            sprintf(DebugBuf, "%i", PeerInPortNumber);
            display(DebugBuf, LOG_NET);
            sprintf(DebugBuf, "%s", strerror(errno));
            display(DebugBuf, LOG_NET);
        } else {
            display((char*)"ConfigureIncomingUdpSocket() PeerToPeer mode bind() succeeded. BindStatus=", LOG_NET);
            sprintf(DebugBuf, "%i", BindStatus);
            display(DebugBuf, LOG_NET);
            display((char*)"InSocketAddress.sin_port = ", LOG_NET);
            sprintf(DebugBuf, "%i", ntohs(InSocketAddress.sin_port));
            display(DebugBuf, LOG_NET);
        }
    }
    if ((NetworkMode & 1) == 1) {

        InSocketAddress.sin_port = 0;
        BindStatus = bind(
            InSocketHandle,
            (struct sockaddr*)&InSocketAddress,
            sizeof(InSocketAddress)
        );
        if (BindStatus < 0) {
            display((char*)"ConfigureIncomingUdpSocket() cannot bind to requested UDP port. Port=", LOG_NET);
            sprintf(DebugBuf, "%i", PeerInPortNumber);
            display(DebugBuf, LOG_NET);
            sprintf(DebugBuf, "%s", strerror(errno));
            display(DebugBuf, LOG_NET);
        } else {
            display((char*)"ConfigureIncomingUdpSocket() ClientServer mode bind() succeeded. BindStatus=", LOG_NET);
            sprintf(DebugBuf, "%i", BindStatus);
            display(DebugBuf, LOG_NET);

            if ((getsockname(InSocketHandle, (struct sockaddr*)&InSocketAddress, &InSocketAddressLength)) != -1) {
                EphemeralInPort = ntohs(InSocketAddress.sin_port);
                display((char*)"EphemeralInPort = ", LOG_NET);
                sprintf(DebugBuf, "%d", EphemeralInPort);
                display(DebugBuf, LOG_NET);
            } else {
                display((char*)"ConfigureIncomingUdpSocket() ClientServer mode getsockname() failed.", LOG_NET);
            }
        }
    }
}

void ConfigureOutgoingUdpSocket() {
    /* Local Variables: */
    short unsigned int DestinationPort;
    memset(&OutSocketAddress, 0, sizeof(struct sockaddr_in));
    display((char*)"ConfigureOutgoingUdpSocket() Using LacConfig.txt PeerInPortNumber for Destination port.", LOG_NET);
    OutSocketAddress.sin_port = htons(PeerInPortNumber);
    DestinationPort = ntohs(OutSocketAddress.sin_port);
    display((char*)"DestinationPort = ", LOG_NET);
    sprintf(DebugBuf, "%d", DestinationPort);
    display(DebugBuf, LOG_NET);
    OutSocketAddress.sin_family = AF_INET;
    memcpy(&OutSocketAddress.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
}

void ConvertStringToUpperCase(char* Pointer) {
    while (*Pointer != '\0') {
        *Pointer = toupper((unsigned char)*Pointer);
        ++Pointer;
    }
}

int DiscardAnyInPacketsInQueue() {
    char ReceiveBuffer[sizeof(InPacket)];
    int RecFromStatus = 0;
    bool PacketIsAvailable = true; // Assume at least one packet is available
    while (PacketIsAvailable) {
        if ((NetworkMode & 1) == 0) {
            RecFromStatus = recvfrom(
                InSocketHandle,
                ReceiveBuffer,
                sizeof(InPacket),
                MSG_DONTWAIT,
                (struct sockaddr*)&InSocketAddress,
                &InSocketAddressLength
            );
        } else if ((NetworkMode & 1) == 1) {
            RecFromStatus = recvfrom(
                InSocketHandle,
                ReceiveBuffer,
                sizeof(InPacket),
                MSG_DONTWAIT,
                (struct sockaddr*)&ClientSourceAddress,
                &ClientSourceAddressLength
            );
        }
        if (RecFromStatus == -1) {
            PacketIsAvailable = false;
            display((char*)"No packet received because:", LOG_NET);
            sprintf(DebugBuf, "%s", strerror(errno));
            display(DebugBuf, LOG_NET);
            return -1;
        } else {
            PacketIsAvailable = true;
            return 0;
        }
    }
    return -1;
}

int GetNetworkApiPacket() {
    /* Local Variables: */
    short unsigned int EphemeralPort;
    char ReceiveBuffer[1024];
    int RecFromStatus = 0;
    if ((NetworkMode & 1) == 0) {
        RecFromStatus = recvfrom(
            InSocketHandle,
            ReceiveBuffer,
            sizeof(InPacket),
            MSG_DONTWAIT,
            (struct sockaddr*)&InSocketAddress,
            &InSocketAddressLength
        );
    } else if ((NetworkMode & 1) == 1) {
        RecFromStatus = recvfrom(
            ClientSocketHandle,
            ReceiveBuffer,
            sizeof(ReceiveBuffer),
            MSG_DONTWAIT,
            (struct sockaddr*)&ClientSourceAddress,
            &ClientSourceAddressLength
        );
    }
    if (RecFromStatus == -1) {
        display((char*)"No packet received because:", LOG_NET);
        sprintf(DebugBuf, "%s", strerror(errno));
        display(DebugBuf, LOG_NET);
        if ((NetworkMode & 1) == 0) {
            if ((getsockname(InSocketHandle, (struct sockaddr*)&InSocketAddress, &InSocketAddressLength)) != -1) {
                EphemeralPort = ntohs(InSocketAddress.sin_port);
                display((char*)"InSocket EphemeralPort = ", LOG_NET);
                sprintf(DebugBuf, "%d", EphemeralPort);
                display(DebugBuf, LOG_NET);
            } else {
                display((char*)"GetNetworkApiPacket() getsockname() failed.", LOG_NET);
            }
        } else if ((NetworkMode & 1) == 1) {
            if ((getsockname(ClientSocketHandle, (struct sockaddr*)&ClientSourceAddress, &ClientSourceAddressLength)) != -1) {
                EphemeralPort = ntohs(ClientSourceAddress.sin_port);
                display((char*)"ClientSocket EphemeralPort = ", LOG_NET);
                sprintf(DebugBuf, "%d", EphemeralPort);
                display(DebugBuf, LOG_NET);
            } else {
                display((char*)"GetNetworkApiPacket() getsockname() failed.", LOG_NET);
            }
        }
        return -1;
    }
    sprintf(DebugBuf, "GetNetworkApiPacket() received %d bytes.\n", RecFromStatus);
    display(DebugBuf, LOG_NET);
    if (RecFromStatus <= (int)sizeof(InPacket)) {
        memcpy(&InPacket, ReceiveBuffer, sizeof(InPacket));
    } else {
        memcpy(&Admin013InPacket, ReceiveBuffer, sizeof(Admin013InPacket));
        memcpy(&InPacket, ReceiveBuffer, sizeof(InPacket));
        display((char*)"GetNetworkApiPacket(): Packet too big for InPacket buffer.", LOG_MOST);
    }
    if (InPacket.UdpObjCommand == 0) {

        if (AuthenticateInPacket() == 0) {
            if (InPacket.UdpObjPlayerNumber == MyNetworkId) {
                display((char*)"GetNetworkApiPacket() detected a conflict with the value of MyNetworkId.", LOG_MOST);
                if (MissionOutPacketCount < 252) {
                    display((char*)"GetNetworkApiPacket() I think I am the newcomer in this situation.", LOG_MOST);
                    MissionIdNegotiationCount++;
                    NetworkTransmitTimer -= 1000;
                    display((char*)"GetNetworkApiPacket() NetworkTransmitTimer waiting an additional 1000 ms.", LOG_MOST);
                    if (MissionIdNegotiationCount > 32) {
                        MissionIdNegotiationCount = 33;
                        display((char*)"GetNetworkApiPacket() failed to find an unused value for MyNetworkID for your team.", LOG_MOST);
                        display((char*)"This probably means that the mission is full. Try another mission or edit your", LOG_MOST);
                        display((char*)"LacConfig.txt file to change your MyNetworkId value to the other team.", LOG_MOST);
                        sound->setVolume(SOUND_BEEP1, 126); // Alert user of error condition
                        sound->play(SOUND_BEEP1, false);
                    } else {
                        switch (MyNetworkId) {
                        case 1:
                        {
                            MyNetworkId = 3;
                            break;
                        }
                        case 2:
                        {
                            MyNetworkId = 4;
                            break;
                        }
                        case 3:
                        {
                            MyNetworkId = 5;
                            break;
                        }
                        case 4:
                        {
                            MyNetworkId = 6;
                            break;
                        }
                        case 5:
                        {
                            MyNetworkId = 7;
                            break;
                        }
                        case 6:
                        {
                            MyNetworkId = 8;
                            break;
                        }
                        case 7:
                        {
                            MyNetworkId = 9;
                            break;
                        }
                        case 8:
                        {
                            MyNetworkId = 10;
                            break;
                        }
                        case 9:
                        {
                            MyNetworkId = 1;
                            break;
                        }
                        case 10:
                        {
                            MyNetworkId = 2;
                            break;
                        }
                        default:
                        {
                            MyNetworkId = 1;
                        }
                        }
                        if (MyNetworkId > MaxPlayersInCurrentMission) {
                            MyNetworkId = 1;
                        }
                        MissionOutPacketCount = 0;
                        display((char*)"GetNetworkApiPacket() Reset MissionOutPacketCount.", LOG_MOST);
                        display((char*)"GetNetworkApiPacket() is trying to find an available value for MyNetworkID. Now trying", LOG_MOST);
                        sprintf(DebugBuf, "%d", MyNetworkId);
                        display(DebugBuf, LOG_MOST);
                    }
                }
                if (MissionOutPacketCount >= 252) {
                    sprintf(
                        DebugBuf,
                        "GetNetworkApiPacket() MyNetworkId collision vs my established number. MyNetworkId=%d, InPacket.UdpObjPlayerNumber=%d. MissionOutPacketCount=%d",
                        MyNetworkId,
                        InPacket.UdpObjPlayerNumber,
                        MissionOutPacketCount
                    );
                    display(DebugBuf, LOG_MOST);
                    sound->setVolume(SOUND_BEEP1, 126); // Alert user of error condition
                    sound->play(SOUND_BEEP1, false);
                    sprintf(SystemMessageBufferA, "NEW PLAYER ID COLLISION VS MYNETWORKID.");
                    NewSystemMessageNeedsScrolling = true;
                    return 0; // Discard this InPacket.
                }
            }

            NetworkMissionIsActiveWithDataFlow = true;

            if (InPacket.UdpObjTerrainOrMorse > LANDSCAPE_ALPINE_SEA) {
                static bool ExpectingChronoMilestone = false;
                static bool ExpectingTeamPlayerNumber = false;
                sprintf(DebugBuf, "GetNetworkApiPacket(): Received Morse character: %c", InPacket.UdpObjTerrainOrMorse);
                display(DebugBuf, LOG_MOST);
                if (!MorseSquelches[InPacket.UdpObjPlayerNumber - 1]) {
                    MorseCharacterIn = InPacket.UdpObjTerrainOrMorse;
                    VocalizeMorseCharacter(MorseCharacterIn);
                    sprintf(DebugBuf, "GetNetworkApiPacket(): MorseCharacterIn = %c", MorseCharacterIn);
                    display(DebugBuf, LOG_MOST);

                    if (strncmp(CommunityHandle, "NEW", 3) == 0) {

                        display((char*)"GetNetworkApiPacket(): New Player received incoming Morse Character.", LOG_MOST);
                        if (MorsePanelActiveTimer <= 0) {
                            sprintf(SystemMessageBufferA, "USE CAPS LOCK TO TRANSMIT MORSE RADIO TEXT.");
                            NewSystemMessageNeedsScrolling = true;
                        }
                    }
                    MorsePanelHighlightTimer = 472;
                    unsigned char ScrollPointer = 0;
                    if (strlen(MorseRadioMessageBuffer) >= 19) {

                        for (ScrollPointer = 0; ScrollPointer < 19; ScrollPointer++) {

                            MorseRadioMessageBuffer[ScrollPointer] = MorseRadioMessageBuffer[ScrollPointer + 1];
                        }
                    }
                    sprintf(DebugBuf, "%c", MorseCharacterIn);
                    strncat(MorseRadioMessageBuffer, DebugBuf, 1);
                    if (ExpectingChronoMilestone) {
                        ExpectingChronoMilestone = false;
                        int InputNumber = MorseCharacterIn - '0';
                        sprintf(DebugBuf, "GetNetworkApiPacket(): While ExpectingChronoMilestone, InputNumber representing MorseCharacterIn digit = %d", InputNumber);
                        display(DebugBuf, LOG_MOST);
                        if (InputNumber > 9) {
                            display((char*)"GetNetworkApiPacket() received invalid value for MissionChronoMilestone.", LOG_MOST);
                        } else {
                            RepeatedMorseInCharCount = 0; // We need not expect more Morse input for this command.
                            display((char*)"GetNetworkApi(): Received valid MissionChronoMilestone command from somebody.", LOG_MOST);
                            if (InputNumber == 1) {

                                MilestoneCorrectionTimer = (MyNetworkId * 60000);
                                sprintf(
                                    DebugBuf,
                                    "GetNetworkApiPacket(): ChronoMilestone command 1 discarded. MilestoneCorrectionTimer set to %ld.",
                                    MilestoneCorrectionTimer
                                );
                                display(DebugBuf, LOG_MOST);
                            } else {
                                if ((InputNumber == 0) || (InputNumber > MissionChronoMilestone)) {
                                    MissionChronoMilestone = InputNumber;
                                    if (InputNumber == 0) {
                                        MissionChronoMilestone = 10;
                                    }

                                    MilestoneCorrectionTimer = 100000000;
                                    sprintf(
                                        DebugBuf,
                                        "GetNetworkApiPacket() Accepted MissionChronoMilestone %d. MilestoneCorrectionTimer set to 10000000.",
                                        MissionChronoMilestone
                                    );
                                    display(DebugBuf, LOG_MOST);
                                } else {
                                    if (InPacket.UdpObjPlayerNumber == MissionCommander) {
                                        MissionChronoMilestone = InputNumber;

                                        MilestoneCorrectionTimer = 100000000;
                                        sprintf(
                                            DebugBuf,
                                            "GetNetworkApiPacket() accepted non-advancing ChronoMilestone %d. MilestoneCorrectionTimer set to 10000000.",
                                            MissionChronoMilestone
                                        );
                                        display(DebugBuf, LOG_MOST);
                                    } else {

                                        MilestoneCorrectionTimer = 100000000;
                                        sprintf(
                                            DebugBuf,
                                            "GetNetworkApiPacket() Discarded non-advancing ChronoMilestone %d from NON-MissionCommander. MilestoneCorrectionTimer set to 10000000.",
                                            MissionChronoMilestone
                                        );
                                        display(DebugBuf, LOG_MOST);
                                    }
                                }
                            }
                        }
                    }

                    if (ExpectingTeamPlayerNumber) {
                        ExpectingTeamPlayerNumber = false;
                        int InputNumber = MorseCharacterIn - '0';
                        sprintf(
                            DebugBuf,
                            "GetNetworkApiPacket(): While ExpectingTeamPlayerNumber, Got InputNumber = %d",
                            InputNumber
                        );
                        display(DebugBuf, LOG_MOST);
                        if (((unsigned char)InputNumber == MyNetworkId)) {
                            display((char*)"GetNetworkApiPacket(): Incoming Morse Message just promoted us!", LOG_MOST);
                            Promoted = true;
                            sprintf(SystemMessageBufferA, "YOU HAVE BEEN PROMOTED.");
                            NewSystemMessageNeedsScrolling = true;
                            RepeatedMorseInCharCount = 0; // We've completed enough of this command to reset RepeatedMorseInCharCount.
                        }
                        if (((unsigned char)InputNumber == 0)) {
                            if (MyNetworkId == 10) {
                                display((char*)"GetNetworkApiPacket(): Incoming Morse Message just promoted us!", LOG_MOST);
                                Promoted = true;
                                sprintf(SystemMessageBufferA, "YOU HAVE BEEN PROMOTED.");
                                NewSystemMessageNeedsScrolling = true;
                                RepeatedMorseInCharCount = 0; // We've completed enough of this command to reset RepeatedMorseInCharCount.
                            }
                        }
                    }
                    if ((MorseCharacterIn == PreviousMorseInCharacter) && (PreviousMorseSender == InPacket.UdpObjPlayerNumber)) {
                        RepeatedMorseInCharCount++;
                        sprintf(DebugBuf, "GetNetworkApiPacket() got a duplicated Morse InCharacter. RepeatedMorseInCharCount = %d.", RepeatedMorseInCharCount);
                        display(DebugBuf, LOG_MOST);
                    } else {
                        RepeatedMorseInCharCount = 0;
                    }
                    PreviousMorseSender = InPacket.UdpObjPlayerNumber;
                    PreviousMorseInCharacter = MorseCharacterIn;
                    if ((RepeatedMorseInCharCount > 7) && ((InPacket.UdpObjPlayerNumber & 1) == (MyNetworkId & 1))) {
                        display((char*)"GetNetworkApiPacket(): Parsing an incoming Morse command sequence from a team-mate.", LOG_MOST);
                        if (MorseCharacterIn == 'M') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command M.", LOG_MOST);
                            event_CommsMacro18();
                            RepeatedMorseInCharCount = 0;
                            if ((NetworkMode & 4)) {
                                MumbleChannelPresumed = 94;
                                sprintf(SystemMessageBufferA, "TEAM SWITCHING TO MISSIONCAST CHANNEL.");
                                NewSystemMessageNeedsScrolling = true;
                                sound->setVolume(SOUND_BEEP1, 60);
                                sound->play(SOUND_BEEP1, false);
                                if (!(NetworkMode & 16)) {
                                    popen("espeak -p 10 -a 33  -s 160 \"Team is switching to the MissionCast Channel.\"", "r");
                                }
                            }
                        } else if (MorseCharacterIn == 'P') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command P.", LOG_MOST);
                            ExpectingTeamPlayerNumber = true;
                            // Don't reset RepeatedMorseInCharCount yet because this command is not yet done....
                        } else if (MorseCharacterIn == 'R') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command R.", LOG_MOST);
                            event_CommsMacro10();
                            RepeatedMorseInCharCount = 0;
                            if ((NetworkMode & 4)) {
                                MumbleChannelPresumed = 10;
                                sprintf(SystemMessageBufferA, "TEAM SWITCHING TO ROOT CHANNEL.");
                                NewSystemMessageNeedsScrolling = true;
                                sound->setVolume(SOUND_BEEP1, 60);
                                sound->play(SOUND_BEEP1, false);
                                if (!(NetworkMode & 16)) {
                                    popen("espeak -p 10 -a 33  -s 160 \"Team is switching to the Root Channel.\"", "r");
                                }
                            }
                        } else if (MorseCharacterIn == 'S') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command S.", LOG_MOST);
                            SwitchMumbleToSecretChannel(InPacket.UdpObjPlayerNumber);
                            RepeatedMorseInCharCount = 0;
                        } else if (MorseCharacterIn == 'T') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command T.", LOG_MOST);
                            event_CommsMacro17();
                            RepeatedMorseInCharCount = 0;
                            if ((NetworkMode & 4)) {
                                MumbleChannelPresumed = 95;
                                sprintf(SystemMessageBufferA, "TEAM SWITCHING TO TEAMCAST CHANNEL.");
                                NewSystemMessageNeedsScrolling = true;
                                sound->setVolume(SOUND_BEEP1, 60);
                                sound->play(SOUND_BEEP1, false);
                                if (!(NetworkMode & 16)) {
                                    popen("espeak -p 10 -a 33  -s 160 \"Team is switching to the TeamCast Channel.\"", "r");
                                }
                            }
                        }
                    }
                    if (RepeatedMorseInCharCount > 7) {
                        display((char*)"GetNetworkApiPacket(): Parsing an incoming Morse command sequence from anybody.", LOG_MOST);
                        if (MorseCharacterIn == 'C') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command C.", LOG_MOST);
                            ExpectingChronoMilestone = true;
                            // Don't reset RepeatedMorseInCharCount yet because this command is not yet done....
                        } else if (MorseCharacterIn == 'D') {
                            display((char*)"GetNetworkApiPacket() detected Morse In Command D.", LOG_MOST);
                            // Don't reset RepeatedMorseInCharCount yet because this command is not yet done....
                        }
                    }
                }
            }

            if (InPacket.UdpObjPlayerNumber & 224) {
                unsigned char MumbleCommand = 0;
                MumbleCommand = InPacket.UdpObjPlayerNumber & 224;
                MumbleCommand /= 32;

                InPacket.UdpObjPlayerNumber &= 31;
                NewestMumblePacketId = InPacket.UdpObjPlayerNumber;
                switch (MumbleCommand) {
                case 1:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    sprintf(SystemMessageBufferA, "%s SWITCHED TO ROOT CHANNEL.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                    NewSystemMessageNeedsScrolling = true;
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    NetworkPlayerMumbleChannel[NewestMumblePacketId] = MUMBLEROOTCHANNEL;
                    break;
                }
                case 2:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    if (MumbleIsAccessible) {
                        sprintf(SystemMessageBufferA, "MUMBLE BROADCAST COMMS FROM %s.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                        NewSystemMessageNeedsScrolling = true;
                    } else {
                        MumbleChannelPresumed = 93; // Signal Mumble panel that a voice broadcast has been missed.
                    }
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    InPacketContainsMumbleNarrowcast = false;
                    InPacketContainsMumbleBroadcast = true;
                    break;
                }
                case 3:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    sprintf(SystemMessageBufferA, "%s SWITCHED TO OUR MISSION CHANNEL.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                    NewSystemMessageNeedsScrolling = true;
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    NetworkPlayerMumbleChannel[NewestMumblePacketId] = MUMBLECURRENTMISSIONCHANNEL;
                    break;
                }
                case 4:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    if (MumbleIsAccessible) {
                        sprintf(SystemMessageBufferA, "MUMBLE NARROWCAST COMMS FROM %s.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                        NewSystemMessageNeedsScrolling = true;
                    } else {

                        MumbleChannelPresumed = 92; // Signal Mumble panel that a voice narrowcast has been missed.
                    }
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    InPacketContainsMumbleNarrowcast = true;
                    InPacketContainsMumbleBroadcast = false;
                    break;
                }
                case 5:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    sprintf(SystemMessageBufferA, "%s SWITCHED TO BLUE TEAM SUBCHANNEL.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                    NewSystemMessageNeedsScrolling = true;
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    NetworkPlayerMumbleChannel[NewestMumblePacketId] = MUMBLECURRENTMISSIONBLUESUBCHANNEL;
                    break;
                }
                case 6:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    sprintf(SystemMessageBufferA, "%s SWITCHED TO RED TEAM SUBCHANNEL.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                    NewSystemMessageNeedsScrolling = true;
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    NetworkPlayerMumbleChannel[NewestMumblePacketId] = MUMBLECURRENTMISSIONREDSUBCHANNEL;
                    break;
                }
                case 7:
                {
                    if (MissionMumbleTimer[NewestMumblePacketId] < 10) {
                        sound->setVolume(SOUND_BEEP1, 20);
                        sound->play(SOUND_BEEP1, false);
                    }
                    sprintf(SystemMessageBufferA, "%s SWITCHED OUT OF OUR MISSION CHANNELS.", PlayerIdStrings[(NewestMumblePacketId - 1)]);
                    NewSystemMessageNeedsScrolling = true;
                    MissionMumbleTimer[NewestMumblePacketId] = 1000;
                    NetworkPlayerMumbleChannel[NewestMumblePacketId] = MUMBLENONMISSIONCHANNEL;
                    break;
                }
                default:
                {
                    break;
                }
                }
            }

            memcpy(&PriorInPacket[InPacket.UdpObjPlayerNumber], ReceiveBuffer, sizeof(InPacket));
            MissionPacketTimer[InPacket.UdpObjPlayerNumber] = 80;

            if (InPacket.UdpObjSpeed < 0.0) {

                InPacket.UdpObjSpeed *= -1.0;

                InPacket.UdpObjFlightDetails &= 127;
            }

            if (InPacket.UdpObjDamageAmount > fplayer->Durability && InPacket.UdpObjDamageId == MyNetworkId) {
                UpdateOnlineScoreLogFileWithDefeats();
            }
            DiscardAnyInPacketsInQueue();

            return RecFromStatus; // Return number of authenticated bytes received.
        } else {
            display((char*)"GetNetworkApiPacket() Packet NOT authenticated. Check NetworkPassword at both ends.", LOG_MOST);
            return (-1); // Indicate that NO valid InPacket has been received.
        }
    } else {
        sprintf(DebugBuf, "Administrative InPacket Command %d received.\n", InPacket.UdpObjCommand);
        display(DebugBuf, LOG_NET);
        display(DebugBuf, LOG_MOST);
        if (InPacket.UdpObjCommand == 12) {
            display((char*)"GetNetworkApiPacket() Processing request for administrative details.", LOG_NET);
            display((char*)"GetNetworkApiPacket() Processing request for administrative details.", LOG_MOST);
            Admin012OutPacket.NetworkApiVersion = NetworkApiVersion;
            Admin012OutPacket.UdpObjCommand = 12;
            Admin012OutPacket.UdpObjMissionOutPacketCount = MissionOutPacketCount;
            Admin012OutPacket.UdpObjMyNetworkId = MyNetworkId;
            Admin012OutPacket.UdpObjRealm = Realm;
            Admin012OutPacket.UdpObjCurrentMissionNumber = CurrentMissionNumber;
            sprintf(Admin012OutPacket.UdpObjLacVersion, VERSIONSTRING);
            //
            // Make doubly sure the following block of code cannot overflow the length of the UdpObjCommunityHandle field.
            // The length of the formatted CommunityHandle string will be tested and replaced if too long:
            //
            sprintf(DebugBuf, "%s", CommunityHandle);
            if (strlen(DebugBuf) < 16) {
                // Due to this length check, we can ignore compiler warnings about possibly writing more than 16 chars here.
                sprintf(Admin012OutPacket.UdpObjCommunityHandle, "%s", CommunityHandle);
            } else {
                sprintf(Admin012OutPacket.UdpObjCommunityHandle, "NAMETOOLONG");
            }
            SendAdmin012Packet();

            GetNetworkApiPacket();
            DiscardAnyInPacketsInQueue();
        }
        if (InPacket.UdpObjCommand == 13) {

            display((char*)"GetNetworkApiPacket() Processing Admin013InPacket.", LOG_NET);
            display((char*)"GetNetworkApiPacket() Processing Admin013InPacket.", LOG_MOST);

            // (Although we TRANSMIT as many as 16 characters in that field to the LAC Server,
            // the LAC Server should someday be enhanced so as to never send us more than the first
            // 8 characters. However, even if a LAC Server DOES send more than 8 characters,
            // each of these ten blocks deliberately truncates them at 8 characters.
            // In all ten of the little code blocks below, we can safely ignore compiler warnings
            // about possibly truncated output, since we are DELIBERATELY limiting copy lengths
            // to avoid ever receiving more than the first 8 characters of CommunityHandles.)
            //
            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle01 = %s", Admin013InPacket.UdpObjCommunityHandle01);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[0], Admin013InPacket.UdpObjCommunityHandle01, (sizeof(PlayerIdStrings[0]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[0]);
            sprintf(DebugBuf, "PlayerIdStrings[0] = %s\n", PlayerIdStrings[0]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle02 = %s", Admin013InPacket.UdpObjCommunityHandle02);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[1], Admin013InPacket.UdpObjCommunityHandle02, (sizeof(PlayerIdStrings[1]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[1]);
            sprintf(DebugBuf, "PlayerIdStrings[1] = %s\n", PlayerIdStrings[1]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle03 = %s", Admin013InPacket.UdpObjCommunityHandle03);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[2], Admin013InPacket.UdpObjCommunityHandle03, (sizeof(PlayerIdStrings[2]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[2]);
            sprintf(DebugBuf, "PlayerIdStrings[2] = %s\n", PlayerIdStrings[2]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle04 = %s", Admin013InPacket.UdpObjCommunityHandle04);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[3], Admin013InPacket.UdpObjCommunityHandle04, (sizeof(PlayerIdStrings[3]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[3]);
            sprintf(DebugBuf, "PlayerIdStrings[3] = %s\n", PlayerIdStrings[3]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle05 = %s", Admin013InPacket.UdpObjCommunityHandle05);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[4], Admin013InPacket.UdpObjCommunityHandle05, (sizeof(PlayerIdStrings[4]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[4]);
            sprintf(DebugBuf, "PlayerIdStrings[4] = %s\n", PlayerIdStrings[4]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle06 = %s", Admin013InPacket.UdpObjCommunityHandle06);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[5], Admin013InPacket.UdpObjCommunityHandle06, (sizeof(PlayerIdStrings[5]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[5]);
            sprintf(DebugBuf, "PlayerIdStrings[5] = %s\n", PlayerIdStrings[5]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle07 = %s", Admin013InPacket.UdpObjCommunityHandle07);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[6], Admin013InPacket.UdpObjCommunityHandle07, (sizeof(PlayerIdStrings[6]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[6]);
            sprintf(DebugBuf, "PlayerIdStrings[6] = %s\n", PlayerIdStrings[6]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle08 = %s", Admin013InPacket.UdpObjCommunityHandle08);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[7], Admin013InPacket.UdpObjCommunityHandle08, (sizeof(PlayerIdStrings[7]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[7]);
            sprintf(DebugBuf, "PlayerIdStrings[7] = %s\n", PlayerIdStrings[7]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle09 = %s", Admin013InPacket.UdpObjCommunityHandle09);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[8], Admin013InPacket.UdpObjCommunityHandle09, (sizeof(PlayerIdStrings[8]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[8]);
            sprintf(DebugBuf, "PlayerIdStrings[8] = %s\n", PlayerIdStrings[8]);
            display(DebugBuf, LOG_NET);

            sprintf(DebugBuf, "Admin013InPacket.UdpObjCommunityHandle10 = %s", Admin013InPacket.UdpObjCommunityHandle10);
            display(DebugBuf, LOG_NET);
            strncpy(PlayerIdStrings[9], Admin013InPacket.UdpObjCommunityHandle10, (sizeof(PlayerIdStrings[9]) - 1));
            ConvertStringToUpperCase(PlayerIdStrings[9]);
            sprintf(DebugBuf, "PlayerIdStrings[9] = %s\n", PlayerIdStrings[9]);
            display(DebugBuf, LOG_NET);
            DiscardAnyInPacketsInQueue();
            CleanPlayerIdStrings();
        }
        if (InPacket.UdpObjCommand == 14) {
            static unsigned int Admin14InPacketCount = 0;
            Admin14InPacketCount++;

            memcpy(&Admin014InPacket, ReceiveBuffer, sizeof(Admin014InPacket));

            if (Admin014InPacket.UdpObjRealm == 0 && Admin014InPacket.UdpObjMissionId == 0 && Admin014InPacket.DestinationPlayerNumber == 0) {
                return (0);
            }

            if ((Admin014InPacket.UdpObjRealm != Realm) && (Admin014InPacket.DestinationPlayerNumber != 13)) {
                return (0);
            }

            ServerMessageTimer = 0;
            strncpy(ServerMessageBuffer, Admin014InPacket.MessageText, sizeof(ServerMessageBuffer));
            ServerMessageRecipient = Admin014InPacket.DestinationPlayerNumber;
        }
    }
    return (0);
}

void SendAdmin012Packet() {
    display((char*)"SendAdmin012Packet()", LOG_NET);
    int Admin012BytesSent = 0;
    Admin012Packet* Admin012OutPacketPointer = &Admin012OutPacket;
    unsigned int Admin012OutPacketSize = sizeof(Admin012OutPacket);
    unsigned int SockAddrInSize = sizeof(struct sockaddr_in);
    Admin012BytesSent = sendto(
        ClientSocketHandle,
        Admin012OutPacketPointer,
        Admin012OutPacketSize,
        0,
        (struct sockaddr*)&ClientDestinationAddress,
        SockAddrInSize
    );
    if (Admin012BytesSent > 0) {
        AdminOutPacketCount++;
        sprintf(DebugBuf, "SendAdmin012Packet() AdminOutPacketCount = %d, Admin012BytesSent = %d", (int)AdminOutPacketCount, Admin012BytesSent);
        display(DebugBuf, LOG_NET);
    } else {
        display((char*)"SendAdmin012Packet() Couldn't send anything to server.", LOG_MOST);
    }
}

void SendAdmin013Packet() {
    display((char*)"SendAdmin013Packet()", LOG_NET);
    display((char*)"SendAdmin013Packet()", LOG_MOST);
    int Admin013BytesSent = 0;
    Admin013Packet* Admin013OutPacketPointer = &Admin013OutPacket;
    unsigned int Admin013OutPacketSize = sizeof(Admin013OutPacket);
    unsigned int SockAddrInSize = sizeof(struct sockaddr_in);
    Admin013BytesSent = sendto(
        ClientSocketHandle,
        Admin013OutPacketPointer,
        Admin013OutPacketSize,
        0,
        (struct sockaddr*)&ClientDestinationAddress,
        SockAddrInSize
    );
    if (Admin013BytesSent > 0) {
        AdminOutPacketCount++;
        sprintf(DebugBuf, "SendAdmin013Packet() AdminOutPacketCount = %d, Admin013BytesSent = %d", (int)AdminOutPacketCount, Admin013BytesSent);
        display(DebugBuf, LOG_NET);
    } else {
        display((char*)"SendAdmin013Packet() Couldn't send anything to server.", LOG_MOST);
    }
}

void SendNetworkApiPacket() {

    int BytesSent = 0;
    LacUdpApiPacket* OutPacketPointer = &OutPacket;
    unsigned int OutPacketSize = sizeof(OutPacket);
    unsigned int SockAddrInSize = sizeof(struct sockaddr_in);

    OutPacket.NetworkApiVersion = NetworkApiVersion;
    OutPacket.UdpObjMissionId = CurrentMissionNumber;
    OutPacket.UdpObjCommand = 0;
    OutPacket.UdpObjRealm = Realm;

    if (MorseCharacterOut[0]) {
        OutPacket.UdpObjTerrainOrMorse = MorseCharacterOut[0];
        VocalizeMorseCharacter(MorseCharacterOut[0]);
        MorsePanelHighlightTimer = 472;
        unsigned char ScrollPointer = 0;

        if (strlen(MorseRadioMessageBuffer) >= 19) {

            for (ScrollPointer = 0; ScrollPointer < 19; ScrollPointer++) {

                MorseRadioMessageBuffer[ScrollPointer] = MorseRadioMessageBuffer[ScrollPointer + 1];
            }
        }
        sprintf(DebugBuf, "%c", MorseCharacterOut[0]);
        strncat(MorseRadioMessageBuffer, DebugBuf, 1);
        MorseCharacterOut[0] = 0;
        PreviousMorseSender = MyNetworkId;
        unsigned char ArrayIndex;
        for (ArrayIndex = 0; ArrayIndex < 47; ArrayIndex++) {

            MorseCharacterOut[ArrayIndex] = MorseCharacterOut[(ArrayIndex + 1)];
        }
        MorseCharacterOut[47] = 0;
    } else {
        OutPacket.UdpObjTerrainOrMorse = LANDSCAPE_ALPINE_SEA;
    }
    OutPacket.UdpObjPlayerNumber = MyNetworkId;
    OutPacket.UdpObjDamageId = 0;
    OutPacket.UdpObjFlightDetails = 0;

    if (GunCameraActive) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 128;
    } else {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails & 127;
    }

    if (fplayer->FlapsLevel == 3 || fplayer->FlapsLevel == 4) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 3;
    } else if (fplayer->FlapsLevel == 2) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 2;
    } else if (fplayer->FlapsLevel == 1) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 1;
    }

    if (fplayer->SpeedBrake) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 4;
    }

    if (FlareFired) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 8;
        FlareFired = false;
    }

    if (ChaffPacketFired) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 16;
        ChaffPacketFired = false;
    }

    if (MissileFired) {
        OutPacket.UdpObjFlightDetails = OutPacket.UdpObjFlightDetails | 32;
        MissileFired = false;
    }
    sprintf(DebugBuf, "SendNetworkApiPacket() OutPacket.UdpObjFlightDetails = %d", OutPacket.UdpObjFlightDetails);
    display(DebugBuf, LOG_NET);
    OutPacket.UdpObjVehicle = (Uint16)PlayerAircraftType;
    OutPacket.UdpObjXPosition = fplayer->tl->x;
    OutPacket.UdpObjYPosition = fplayer->tl->y;
    OutPacket.UdpObjZPosition = fplayer->tl->z;
    AdjustHeightAboveRunwayIfLanded();
    OutPacket.UdpObjGamma = fplayer->gamma;
    OutPacket.UdpObjPhi = fplayer->phi;
    OutPacket.UdpObjTheta = fplayer->theta;
    OutPacket.UdpObjSpeed = fplayer->realspeed;
    OutPacket.UdpObjThrust = fplayer->thrust;
    OutPacket.UdpObjElevator = fplayer->elevatoreffect;
    OutPacket.UdpObjAileron = fplayer->rolleffect;
    OutPacket.UdpObjRudder = fplayer->ruddereffect;
    OutPacket.UdpObjDamageId = MissionAircraftDamaged;
    OutPacket.UdpObjDamageAmount = DamageToClaim;
    ThreeDObjects[MissionAircraftDamaged]->DamageInNetQueue = 0;
    if (DamageToClaim > 0.0) {
        sprintf(DebugBuf, "SendNetworkApiPacket() claiming damage of %f on object %d.", OutPacket.UdpObjDamageAmount, OutPacket.UdpObjDamageId);
        display(DebugBuf, LOG_MOST);
    }
    if (DamageToClaim >= 100000) {
        OutPacket.UdpObjThrust = ThrustReadiness;
    }

    if (OutPacket.UdpObjDamageAmount > 1000.0) {
        UpdateOnlineScoreLogFileWithVictories();
    }
    if (OutPacket.UdpObjDamageId == MissionObjectHqBlue) {
        if (OutPacket.UdpObjDamageAmount > 0.0) {
            sprintf(DebugBuf, "SendNetworkApiPacket(): You damaged the BlueTeam HQ Airfield by %f kilojoules.", OutPacket.UdpObjDamageAmount);
            display(DebugBuf, LOG_MOST);
        }
    }
    if (OutPacket.UdpObjDamageId == MissionObjectHqRed) {
        if (OutPacket.UdpObjDamageAmount > 0.0) {
            sprintf(DebugBuf, "SendNetworkApiPacket(): You damaged the RedTeam HQ Airfield by %f kilojoules.", OutPacket.UdpObjDamageAmount);
            display(DebugBuf, LOG_MOST);
        }
    }

    if (MumbleChannelMainRequested) {
        OutPacket.UdpObjPlayerNumber += 1 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleChannelMainRequested = 0;
    }

    if (MumbleBroadcastRequested) {
        OutPacket.UdpObjPlayerNumber += 2 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleBroadcastRequested = 0;
    }

    if (MumbleCurrentMissionChannelRequested) {
        OutPacket.UdpObjPlayerNumber += 3 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleCurrentMissionChannelRequested = 0;
    }

    if (MumbleTransmissionRequested) {
        OutPacket.UdpObjPlayerNumber += 4 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleTransmissionRequested = 0;
    }

    if (MumbleCurrentMissionBlueSubChannelRequested) {
        OutPacket.UdpObjPlayerNumber += 5 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleCurrentMissionBlueSubChannelRequested = 0;
    }

    if (MumbleCurrentMissionRedSubChannelRequested) {
        OutPacket.UdpObjPlayerNumber += 6 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleCurrentMissionRedSubChannelRequested = 0;
    }

    if (MumbleChannelExitRequested) {
        OutPacket.UdpObjPlayerNumber += 7 * 32;
        NewestMumblePacketId = MyNetworkId;
        MissionMumbleTimer[MyNetworkId] = 400;
        MumbleChannelExitRequested = 0;
    }

    if (GunCameraStartSegmentFlag) {
        display((char*)"SendNetworkApiPacket() marking a GunCameraStartSegment.", LOG_MOST);
        sprintf(DebugBuf, "   Changing OutPacket.UdpObjSpeed from %f", OutPacket.UdpObjSpeed);
        display(DebugBuf, LOG_MOST);
        OutPacket.UdpObjSpeed *= -1.0;
        sprintf(DebugBuf, "   to %f", OutPacket.UdpObjSpeed);
        display(DebugBuf, LOG_MOST);
        GunCameraStartSegmentFlag = false;
        OutPacket.UdpObjFlightDetails = 128;
    }

    if (GunCameraStopSegmentFlag) {

        display((char*)"SendNetworkApiPacket() marking a GunCameraStopSegment.", LOG_MOST);
        sprintf(DebugBuf, "   Changing OutPacket.UdpObjSpeed from %f", OutPacket.UdpObjSpeed);
        display(DebugBuf, LOG_MOST);
        OutPacket.UdpObjSpeed *= -1;
        sprintf(DebugBuf, "   to %f", OutPacket.UdpObjSpeed);
        display(DebugBuf, LOG_MOST);
        GunCameraStopSegmentFlag = false;
        OutPacket.UdpObjFlightDetails = 0;
    }

    SignOutPacket();
    OutPacket.UdpObjHash = OutGoingPacketSignature;

    if ((NetworkMode & 1) == 0) {
        BytesSent = sendto(
            OutSocketHandle,
            OutPacketPointer,
            OutPacketSize,
            0,
            (struct sockaddr*)&OutSocketAddress,
            SockAddrInSize
        );
    } else if ((NetworkMode & 1) == 1) {
        BytesSent = sendto(
            ClientSocketHandle,
            OutPacketPointer,
            OutPacketSize,
            0,
            (struct sockaddr*)&ClientDestinationAddress,
            SockAddrInSize
        );
    }

    if (BytesSent > 0) {
        UdpSetupCompleted = true;
        display((char*)"Data transmitted. BytesSent=", LOG_NET);
        sprintf(DebugBuf, "%i", BytesSent);
        display(DebugBuf, LOG_NET);
        MissionOutPacketCount++;
        if (MissionOutPacketCount > 254) {
            MissionOutPacketCount = 254;
        }
        if (OutPacket.UdpObjDamageAmount > 0.0 && OutPacket.UdpObjDamageAmount < 200000) {
            if (OutPacket.UdpObjDamageId < 11) {
                sprintf(SystemMessageBufferA, "YOU DAMAGED AIRCRAFT %d.", OutPacket.UdpObjDamageId);
            } else {
                sprintf(SystemMessageBufferA, "YOU DAMAGED FACILITY %d.", OutPacket.UdpObjDamageId);
            }
            if (MissionAircraftDamaged % 2 == MyNetworkId % 2) {
                if (CurrentMissionNumber != MISSION_HEADTOHEAD00) {
                    FratricideShameFactor += DamageToClaim;
                    sprintf(SystemMessageBufferA, "YOU INFLICTED FRIENDLY FIRE!");
                    sound->play(SOUND_BEEP2, false);
                }
            }
            NewSystemMessageNeedsScrolling = true;
        }
        NewestInPacketId = MyNetworkId;
        MissionPacketTimer[MyNetworkId] = 80;
    } else {
        display((char*)"Data NOT transmitted.", LOG_NET);
        display((char*)"Return Code=", LOG_NET);
        sprintf(DebugBuf, "%i", BytesSent);
        display(DebugBuf, LOG_NET);
        sprintf(DebugBuf, "%s", strerror(errno));
        display(DebugBuf, LOG_NET);
    }
}

void SignOutPacket() {

    unsigned int PayloadSize = sizeof(OutPacket);
    unsigned int NetworkPasswordSize = 32;
    unsigned char CrcByte1of2 = 0;
    unsigned char CrcByte2of2 = 0;
    unsigned char OutPacketBuffer[PayloadSize];
    unsigned char OutPacketPositionPointer = 0;
    unsigned char PasswordPositionPointer = 0;
    memcpy(OutPacketBuffer, &OutPacket, PayloadSize);
    for (PasswordPositionPointer = 0; PasswordPositionPointer < NetworkPasswordSize; PasswordPositionPointer++) {
        CrcByte1of2 ^= NetworkPassword[PasswordPositionPointer];
    }
    CrcByte2of2 = CrcByte1of2;

    for (OutPacketPositionPointer = 0; OutPacketPositionPointer < PayloadSize; OutPacketPositionPointer++) {
        CrcByte1of2 ^= OutPacketBuffer[OutPacketPositionPointer];
        CrcByte2of2 = (CrcByte1of2 ^ OutPacketPositionPointer);
    }

    OutGoingPacketSignature = (Uint16)CrcByte1of2 * 256;
    OutGoingPacketSignature += (Uint16)CrcByte2of2;
}

