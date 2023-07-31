
MissionNetworkBattle02::MissionNetworkBattle02() {
    //
    //  Set up menu system to allow the player to read a description
    //  of the mission and select appropriate aircraft and
    //  munitions. Also open the necessary UDP sockets for
    //  outgoing and incoming traffic:
    //
    display((char*)"@MissionNetworkBattle02::MissionNetworkBattle02()", LOG_MOST);
    id = MISSION_NETWORKBATTLE02;

    if ((NetworkMode & 1) == 0) {
        strncpy(name, "WRONG NETWORK MODE!", 1024);
        strncpy(briefing, "LACCONFIG.TXT FILE MUST SET MODE 1, 3, OR 5 AND A SERVER ADDRESS.", 1024);
    } else {
        strncpy(name, "NETWORKBATTLE02", 1024);
        strncpy(briefing, "REQUIRES INTERNET. FINDS AND USES A FREE LAC SERVER. TEN\nNETWORK PLAYERS IN 2 TEAMS. 1ST TEAM TO DESTROY ENEMY BASE WINS.\nDESERT TERRAIN. YOU WILL NEED TO LAND & FUEL UP BEFORE LAUNCHING.\nBOTS REPLACE ANY OF THE 10 ONLINE PLAYERS NOT PRESENT.", 1024);
    }
    selfighter[0] = DefaultAircraft;
    selfighter[1] = FIGHTER_A6M2;
    selfighter[2] = FIGHTER_P51D;
    selweapons = 0;
    if ((NetworkMode & 1) == 0) {
        selfighters = 0;
    } else {
        selfighters = 2;
    }
    //
    //  Calculate a reasonable value for NetworkReceiveTimerInterval,
    //  based on the value of NetworkTransmitTimerInterval as configured
    //  within the "LacConfig.txt" file. We ought to check for InPackets
    //  more frequently than we are sending OutPackets, by the ratio of
    //  possible players in the mission. Thus in this case, where we
    //  could have as many as ten players in the mission, we will check
    //  for InPackets about twelve times as frequently as we send
    //  OutPackets as follows:
    //
    NetworkReceiveTimerInterval = NetworkTransmitTimerInterval / 12;
    //
    LoadServerIpAddress(); //  Get Peer IP address from LacConfig.txt
    //
    //  Turn off the global "NetworkOpponent" flag until a remote peer connects
    //  from the network. This flag will be activated if and when
    //  incoming UDP packets are ever received from a sentient:
    //
    NetworkOpponent = 0; //  Start mission with AI Maneuovering opponent.

    if ((NetworkMode & 1) == 1) { //  ClientServer mode requires only a single UDP port, used both for sending and receiving
        display((char*)"@Attempting MissionNetworkBattle02 in ClientServer Network mode.", LOG_NET);
        if (OpenClientUdpSocket() == 0) { //  Get here if we were able to open the required ClientServer UDP Socket
            display((char*)"@MissionNetworkBattle02 ClientServer mode succesfully opened ClientUDP socket", LOG_NET);
            ConfigureClientUdpSocket();
        } else { //  Get here if we were unable to open the required ClientUDP socket
            display((char*)"@MissionNetworkBattle02 ClientServer mode unable to open ClientUDP socket.", LOG_NET);
        }
    } else {
        display((char*)"Incorrect network mode configured in LacConfig.txt file.", LOG_ERROR);
        sound->setVolume(SOUND_BEEP1, 126);
        sound->play(SOUND_BEEP1, false);
    }
    //
    //  Now switch the user's "Mumble" application to the appropriate channel according to his team affiliation.
    //
    event_CommsMacro17();
} //  end MissionNetworkBattle02::MissionNetworkBattle02 ()


void MissionNetworkBattle02::start() {
    NoMissionHasYetCommenced = false;
    //
    //
    //  Initialize the landscape, place the player within it, and
    //  optimize cockpit instruments. Then load armament for both
    //  peers and spawn the AI aircraft for the mission.
    //
    //
    MissionStateNetworkBattle = 0;
    display((char*)"@MissionNetworkBattle02::start()", LOG_MOST);
    NetworkPlayerKilled = false;
    if ((MyNetworkId == 0) || (MyNetworkId > MaxPlayersInCurrentMission)) { //  Get here if "MyNetworkId" has not yet been initialized or if its value is too high
        MyNetworkId = myrandom(MaxPlayersInCurrentMission); //  Randomize MyNetworkId
        MyNetworkId++;
    }
    int i, i2;
    day = 1;
    clouds = 2;
    weather = WEATHER_SUNNY;
    camera = 0;
    sungamma = 25;
    heading = 220;
    if (l != NULL) {
        delete l;
    }
    l = new GLLandscape(space, LANDSCAPE_DESERT, NULL);
    SeaLevel = 39.0; //  Must be adjusted for some terrains.
    //
    //  Now landscape a long, flat runway:
    //
    l->flatten(AirfieldXMin + 28.0, AirfieldYMin + 4, 29.2, 5); //  Flatten runway 29.2 units long, 6 units wide
    l->flatten(AirfieldXMin + 46, AirfieldYMin + 5, 7, 6); //  Flatten adjacent tarmac area 7 units long, 6 units wide
    //
    //  Now insert "Airfield00" structures onto the landscape near the runway, treating those structures as if
    //  they were a single fighter aircraft so they can be damaged and/or destroyed. This will be the HQ
    //  airfield for the BlueTeam.
    //
    int n = MissionObjectRadarRed1; //  Rectangular RADAR Reflector
    ThreeDObjects[n]->tl->x = AirfieldXMin + 41.0;
    ThreeDObjects[n]->tl->z = AirfieldYMin + 6.2;
    ThreeDObjects[n]->o = &model_RadarReflector;
    ThreeDObjects[n]->newinit(STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects[n]->impact = 0.0;
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 0.66;

    n = MissionObjectHqRed;
    ThreeDObjects[n]->tl->x = AirfieldXMin + 46.5;
    ThreeDObjects[n]->tl->z = AirfieldYMin + 8;
    ThreeDObjects[n]->o = &model_Airfield00;
    ThreeDObjects[n]->newinit(STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 6.0;

    n = MissionObjectRadarBlue1; //  Rectangular RADAR Reflector
    ThreeDObjects[n]->tl->x = AirfieldXMin - 470.58; //  -470.5 ends up with the tower just barely within the convex reflector.
    ThreeDObjects[n]->tl->z = AirfieldYMin + 6.25;
    ThreeDObjects[n]->o = &model_RadarReflector;
    ThreeDObjects[n]->newinit(STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects[n]->impact = 0.0;
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 0.66;

    n = MissionObjectHqBlue; //  BlueTeam HQ airfield Facilities
    ThreeDObjects[n]->tl->x = -304;
    ThreeDObjects[n]->tl->z = 11.0;
    ThreeDObjects[n]->o = &model_Airfield00;
    ThreeDObjects[n]->newinit(STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 6.0;

    playerInit();
    PlayerAircraftType = fplayer->id;
    MissionRunning = false; //  Semaphore. Set on first pass through mission processtimer().
    fplayer->phi = 270;
    display((char*)"MissionNetworkBattle02::start setting PlayerAircraftType to: ", LOG_MOST);
    sprintf(DebugBuf, "%d", PlayerAircraftType);
    display(DebugBuf, LOG_MOST);
    //  Initialize all cockpit instruments to a stable starting point
    HudOnOff = 1;               //  Start out with HUD on.
    IffOnOff = 0;                 //  Initialize IFF to off.
    MapViewOnOff = 0;           //  Make sure we have MapView off at start.
    RadarOnOff = 0;               //  Initialize RADAR to off.
    RadarZoom = 1;              //  Set RADAR Range to 50 miles for this mission.
    ScreenFOVx = 1.0;           //  Reset view zoom to normal
    ScreenFOVy = 1.0;           //  Reset view zoom to normal
    //  Now optimize all cockpit instruments for this mission
    event_IffOnOff();           //  Turn on IFF for this mission.
#ifndef STEAMDECK
    event_RadarOnOff();         //  Turn on RADAR for this mission
#endif
    if (!HudLadderBarsOnOff) {
        event_HudLadderBarsOnOff();
    }
    event_ZoomFovOut();         //  Start with wide field of view.
    event_ZoomFovOut();
    MaxPlayersInCurrentMission = 10;
    //
    //   Spawn ten shiny new AI aircraft, Defaulting to A6M2 "Zeroes".
    //   Throughout this mission, arriving UDP InPackets representing
    //   flight by remote, network-accessible peer client copies of LAC
    //   are accepted and examined, and the activities they
    //   describe are applied to the active AI aircraft designated
    //   within each received InPacket.
    //
    for (i = 1; i <= 10; i++) {
        //  Initialize opponents. Last argument to newinit(),
        //   although it is named "intelligence" in the code,
        //   determines their effectivness. Lower means more
        //   effective. 400 is a pretty good value. 1200 makes
        //   them quite dumb.
        ThreeDObjects[i]->newinit(FIGHTER_A6M2, 0, 400);
        // Preserve aircraft type for later comparison to detect changes.
        MissionNetworkBattle02PriorAircraft[i] = FIGHTER_A6M2;
        ThreeDObjects[i]->target = NULL;
        ThreeDObjects[i]->o = &model_figv;
        //  Position fighters in scattered pattern
        ThreeDObjects[i]->tl->x = -200 + (myrandom(400) - 200) + (150 * SIN(i * 360 / 11));
        ThreeDObjects[i]->tl->z = 200 + (myrandom(400) - 200) + (150 * COS(i * 360 / 11));
        ThreeDObjects[i]->ammo = 1600;
        ThreeDObjects[i]->Sentient = 0; //  All fighters are bots until a stream of Inpackets reveals them to be Sentient.
        ThreeDObjects[i]->MyMissionPlayerNumber = i;
        sprintf(DebugBuf, "MissionNetworkBattle02::start() initializing Bot #%d", i);
        display(DebugBuf, LOG_MOST);
        sprintf(
            DebugBuf,
            "MissionNetworkBattle02::start() ThreeDObjects [i]->MyMissionPlayerNumber = %d",
            ThreeDObjects[i]->MyMissionPlayerNumber
        );
        display(DebugBuf, LOG_MOST);
        for (i2 = 0; i2 < missiletypes; i2++) {
            ThreeDObjects[i]->missiles[i2] = 0;
        }
    }
    texttimer = 0;
    MissionOutPacketCount = 0;
    MissionIdNegotiationCount = 0;
    NetworkTransmitTimer = -1000; //  Don't send any OutPackets for the first 1 second of the mission.
    ConfigureOrdnanceForOnlineMissions();
    UpdateOnlineScoreLogFileWithNewSorties();
    ArmPlayerAtRequestedField();
    if (MyNetworkId % 2) { //  Get here if player is a member of RedTeam
        fplayer->target = ThreeDObjects[MissionObjectHqBlue]; //  Target BlueTeam HQ
    } else { //  Get here if player is a member of BlueTeam
        fplayer->target = ThreeDObjects[MissionObjectHqRed]; //  Target RedTeam HQ
    }
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
} //  end MissionNetworkBattle02::start ()

int MissionNetworkBattle02::processtimer(Uint32 dt) {
    //
    //  Get here every few milliseconds during this mission.
    //  Update all timers and initiate timer-dependent
    //  logic as necessary.
    //
    //  Local Variables:
    //
    int i;
    int MissionAircraftNumber;
    int BytesReceived = 0;
    //
    // Recommend an initial elevator effect of "0" do avoid a lot of redouts:
    //
    fplayer->recelevatoreffect = 0;
    MissionNetworkBattle02Timer += DeltaTime; //  Advance by milliseconds
    MissionNetworkBattleRadarTimer += DeltaTime; //  Advance by milliseconds
    MumbleTimeRemainingBeforeChannelReset -= DeltaTime;
    if (MumbleTimeRemainingBeforeChannelReset < 1000) { //  Get here if it's been too long since our last Mumble command
        if (MumbleManagement) {
            event_CommsMacro17(); //  Reset player to proper Mumble TeamCast channel
            //  Now format a message to be displayed on the Cockpit's "SystemMessage Panel":
            sprintf(SystemMessageBufferA, "MUMBLE RESET TO TEAMCAST CHANNEL.");
            //  And inform cockpit.cpp to scroll our new message into view:
            NewSystemMessageNeedsScrolling = true;
            sound->setVolume(SOUND_BEEP1, 60); //@ Medium-volume beep
            sound->play(SOUND_BEEP1, false);
        } else { // Get here if user disabled LAC's management of Mumble channel changes.
            MumbleChannelPresumed = 95; //@ Signal cockpit Mumble Panel
            if (!(NetworkMode & 16)) { // Get here if Mumble vocalization is NOT disabled.
                popen("espeak -p 10 -a 66  -s 160 \"Team is switching back to the TeamCast Channel.\"", "r");
            }
            sprintf(SystemMessageBufferA, "TEAM SWITCHING TO TEAMCAST CHANNEL.");
            //  And inform cockpit.cpp to scroll our new message into view:
            NewSystemMessageNeedsScrolling = true;
        }
        //  Now make sure we will do this again after a LONG time, to force
        //  everybody to monitor the appropriate Mumble channel periodically:
        MumbleTimeRemainingBeforeChannelReset = 10000000; //  10,000 seconds
    }
    if (MissionNetworkBattleRadarTimer > 100) { //  Get here 10 times /second. Rotate the two RADAR antennas.
        MissionNetworkBattleRadarTimer = 0;
        if (ThreeDObjects[MissionObjectRadarBlue1]->Durability > 200) { //  Get here if the BlueTeam HQ airfield is not too damaged for RADAR Antenna Rotation.
            ThreeDObjects[MissionObjectRadarBlue1]->phi += 10; //  Rotate the BlueTeam Radar Reflector antenna
        }
        if (ThreeDObjects[MissionObjectRadarBlue1]->phi >= 360) {
            ThreeDObjects[MissionObjectRadarBlue1]->phi = 0;
        }
        if (ThreeDObjects[MissionObjectRadarRed1]->Durability > 200) { //  Get here if the RedTeam HQ airfield is not too damaged for RADAR Antenna Rotation.
            ThreeDObjects[MissionObjectRadarRed1]->phi += 10; //  Rotate the RedTeam Radar Reflector antenna
        }
        if (ThreeDObjects[MissionObjectRadarRed1]->phi >= 360) {
            ThreeDObjects[MissionObjectRadarRed1]->phi = 0;
        }
        AutoPilot(); //  If player has requested "AutoPilot", hold this altitude.
    }

    MissionNetworkBattle02Timer += DeltaTime; //  Advance by milliseconds
    if (MissionNetworkBattle02Timer > 1000) { //  Get here once every second.
        if (FratricideShameFactor < 60000.0) { //  Get here if repentence is still possible
            FratricideShameFactor *= 0.85; //  Shame doesn't last forever...
            if (FratricideShameFactor < 100) {
                FratricideShameFactor = 0;
            }
        }
        if (FratricideShameFactor > 100) { //  Get here if we should be ashamed of ourselves for fratricide
            IffOnOff = 0; // Punishment for recent, possible innocent, fratricide attempt(s)
            sprintf(SystemMessageBufferA, "IFF DEACTIVATED");
            NewSystemMessageNeedsScrolling = true;
        }
        if (FratricideShameFactor > 40000) { //  Get here if we should be ashamed of ourselves for fratricide
            IffOnOff = 0; // Punishment for recent, very serious fratricide attempt(s)
            RadarOnOff = 0; // More punishment
            HudOnOff = 0; // More punishment
            sprintf(SystemMessageBufferA, "IFF, RADAR, & TACTICAL STATUS DEACTIVATED");
            NewSystemMessageNeedsScrolling = true;
        }
        int AircraftCount;
        for (AircraftCount = 0; AircraftCount <= 10; AircraftCount++) {
            if (ThreeDObjects[AircraftCount]->Sentient > 1) {
                ThreeDObjects[AircraftCount]->Sentient--; //  "Age" the Sentient value so it expires if not refreshed by more InPackets
            }
        }
        if (GoodMenuBehavior > 1) { //  GoodMenuBehavior dosen't last forever.
            GoodMenuBehavior--;
            if (GoodMenuBehavior < 2) {
                ReturnedToCombat = false;
            }
        }
        if (ReturnedToCombat && GoodMenuBehavior < 2) { //  Get here if the player previously pressed <ESC> then returned to flight, but has not yet been fully punished
            sound->play(SOUND_BEEP1, false);
            fplayer->Durability *= 0.05; //  Punish player
            fplayer->Durability--;
            sprintf(SystemMessageBufferA, "ABUSE OF <ESC> DETECTED.");
            NewSystemMessageNeedsScrolling = true;
            if (!(NetworkMode & 16)) { // Get here if the user has not disabled espeak
                popen("espeak -p 130 -a 127 -s 165 \"Escape abuse detected.\"", "r");
            }
        }
        if (MissionIdNegotiationCount > 32) { //  Get here if we've been unable to negotiate unique value for "MyNetworkId" after 32 attempts
            sound->setVolume(SOUND_BEEP1, 20); //  and beep softly
            sound->play(SOUND_BEEP1, false);
            sprintf(SystemMessageBufferA, "THIS MISSION IS FULL. TRY ANOTHER.");
            NewSystemMessageNeedsScrolling = true;
        }
        MissionNetworkBattle02Timer = 0;
        RepairDamagedAirfields();
    } //  end if (MissionNetworkBattle02Timer > 1000)
    BattleDamageRiskTimer += DeltaTime;
    if ((BattleDamageRiskTimer > 5000) || (BattleDamageRiskTimer > (abs)(myrandom(131072)))) { //  Get here at least every 5 seconds, or possibly sooner by random chance
        BattleDamageRiskTimer = 0;
        CalcDamageRiskFromNearbyOpposition();
        ThreeDObjects[0]->Durability -= CalculatedDamageDueToCurrentRisk; //  Admit damage for risk we took.
        if (CalculatedDamageDueToCurrentRisk > 0) {
            sprintf(DebugBuf, "MissionNetworkBattle02::processTimer() fplayer->Durability is now %f.", fplayer->Durability);
            display(DebugBuf, LOG_MOST);
            if (fplayer->Durability < 0) { //  Get here if damage from locally managed airfields or bombers killed us.
                UpdateOnlineScoreLogFileWithCalculatedRisks();
            }
        }
        CalculatedDamageDueToCurrentRisk = 0; //  After admitting that damage amount, clear it.
    }

    StaticObjectUpdateTimer += DeltaTime;
    if (StaticObjectUpdateTimer > 4000) { //  Get here when it's time to update network peers regarding any damaged airfields, etc.
        static bool TeamSwitcher = false;
        float TempFloat1;
        StaticObjectUpdateTimer = 0;
        //
        //  Now check the "Durability" attribute of static 3d objects (like airfield facilities)
        //  to see if one can be found that has sustained battle damage. If so, invert the value
        //  of that Durability attribute (resulting in a negative number) so that other logic will
        //  transmit and interpret it as an absolute value instead of a relative damage value.
        //
        if (TeamSwitcher == false) { //  Get here if it's time to handle Blue Team facilities
            TeamSwitcher = true;
            if ((ThreeDObjects[MissionObjectHqBlue]->Durability > 0) && ((ThreeDObjects[MissionObjectHqBlue]->Durability) < (ThreeDObjects[MissionObjectHqBlue]->maxDurability))) { //  Get here if BlueTeam HQ Airfield facilities have been damaged
                TempFloat1 = ThreeDObjects[MissionObjectHqBlue]->Durability;
                TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
                ThreeDObjects[MissionObjectHqBlue]->DamageInNetQueue = TempFloat1;
            }
        } else { //  Get here if it's time to handle Red Team facilities
            TeamSwitcher = false;
            if ((ThreeDObjects[MissionObjectHqRed]->Durability > 0) && ((ThreeDObjects[MissionObjectHqRed]->Durability) < (ThreeDObjects[MissionObjectHqRed]->maxDurability))) { //  Get here if RedTeam HQ Airfield facilities have been damaged
                TempFloat1 = ThreeDObjects[MissionObjectHqRed]->Durability;
                TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
                ThreeDObjects[MissionObjectHqRed]->DamageInNetQueue = TempFloat1;
            }
        }
    }
    if (!MissionRunning) { //  Get here if this is the FIRST pass through processtimer().
        //  Set up player details that cannot be set up in mission start().
        DegradeFlightModelDueToOrdnanceLoad();
        fplayer->FuelLevel = 6.0;
        if (fplayer->missiles[0] >= 4) { //  Get here if this is a medium or heavy bomber. Cut fuel enough to prevent reaching next airfield.
            fplayer->FuelLevel = 1.0;
        }
        if (fplayer->missiles[0] >= 12) { //  Get here if this is a heavy bomber. Cut fuel enough to prevent reaching next airfield.
            fplayer->FuelLevel = 0.5;
        }
        if (MyNetworkId % 2) { //  Red team. Need to reverse compass direction to fly toward action.
            fplayer->phi -= 180;
        }
        //  Player aircraft altitude at startup should be very low above ground.
        fplayer->tl->y = l->getHeight(AirfieldXMin, AirfieldYMin);
        fplayer->tl->y += 20.0;
        /*
        *
        * The following block of code attempts to cause the player to
        * spawn with zero airspeed. It works, but it isn't sufficient
        * becuase something else causes airspeed to build back to
        * about 160 MPH within about one second after spawning.
        *
        * However, it may be useful in the future, so it ought to
        * be preserved.
        */
        fplayer->realspeed = 0.0;
        fplayer->InertiallyDampenedPlayerSpeed = 0.0;
        ClearSpeedHistoryArrayFlag = true;
        fplayer->accx = 0.0;
        fplayer->accy = 0.0;
        fplayer->accz = 0.0;

        //  Airfield 0 facilities altitude
        ThreeDObjects[MissionObjectHqBlue]->tl->y = l->getHeight(AirfieldXMin + 5, AirfieldYMin + 5);
        ThreeDObjects[MissionObjectHqBlue]->tl->y += 0.9;
        ThreeDObjects[MissionObjectRadarBlue1]->tl->y = ThreeDObjects[MissionObjectHqBlue]->tl->y + 2.0; //  Radar Reflector 2 units higher than airfield

        //  Airfield 1 facilities altitude
        ThreeDObjects[MissionObjectHqRed]->tl->y = l->getHeight(AirfieldXMin + 5, AirfieldYMin + 5);
        ThreeDObjects[MissionObjectHqRed]->tl->y += 0.9;
        ThreeDObjects[MissionObjectRadarRed1]->tl->y = ThreeDObjects[MissionObjectHqRed]->tl->y + 2.0; //  Radar Reflector 2 units higher than airfield

        if (fplayer->missiles[0] >= 6 || fplayer->id == FIGHTER_D3A || fplayer->id == BOMBER_B5N) { //  Heavy bombers need more initial altitude and distance to avoid stalling and crashing...
            fplayer->tl->y += 20;
            sprintf(DebugBuf, "MissionNetworkBattle02::processtimer() Heavy bomber launching. AirfieldRequested = %d", AirfieldRequested);
            display(DebugBuf, LOG_MOST);
            if (AirfieldRequested >= 3) { //  Get here if launching from the most remote airfield (in a heavy bomber).
                display((char*)"MissionNetworkBattle02::processtimer() Increasing heavy bomber spawn altitude from Field 4", LOG_MOST);
                fplayer->tl->y += 320; // This is a heavy bomber airfield. Give them extra altitude at start. 320 yields 9400ft.
                fplayer->FuelLevel = 99; // Full fuel when willing to take off from most remote airfield.
            }
        }
        fplayer->UndercarriageLevel = 0;
        fplayer->FlapsLevel = 0;
        MissionRunning = true;
        for (i = 1; i <= 10; i++) { // Start bots at medium altitude
            ThreeDObjects[i]->tl->y += 150;
        }
    }
    timer += dt; //  Advance mission timer.
    //
    //  The next few blocks of code will play various audio messages
    //  at the beginning of the mission to help the player become
    //  oriented.
    //
    if (timer > 10000 && MissionStateNetworkBattle == 0 && NetworkTransmitTimer >= NetworkTransmitTimerInterval) { //  Mission has just begun and we've just begun transmitting OutPackets with an available setting for MyNetworkId
        if (MyNetworkId % 2) { //  Get here if MyNetworkId is an odd number
            sound->setVolume(SOUND_RED, 126);
            sound->play(SOUND_RED, false);
        } else {
            sound->setVolume(SOUND_BLUE, 126);
            sound->play(SOUND_BLUE, false);
        }
        MissionStateNetworkBattle = 1;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 1 && (timer > PriorStateEndTimer + 600)) {
        if (!RadarOnOff) {
            // If player has not already activated RADAR, to it for him:
            event_RadarOnOff();
        }
        switch (MyNetworkId) {
        case 1:
        {
            sound->setVolume(SOUND_DIGIT001, 126);
            sound->play(SOUND_DIGIT001, false);
            break;
        }
        case 2:
        {
            sound->setVolume(SOUND_DIGIT002, 126);
            sound->play(SOUND_DIGIT002, false);
            break;
        }
        case 3:
        {
            sound->setVolume(SOUND_DIGIT003, 126);
            sound->play(SOUND_DIGIT003, false);
            break;
        }
        case 4:
        {
            sound->setVolume(SOUND_DIGIT004, 126);
            sound->play(SOUND_DIGIT004, false);
            break;
        }
        case 5:
        {
            sound->setVolume(SOUND_DIGIT005, 126);
            sound->play(SOUND_DIGIT005, false);
            break;
        }
        case 6:
        {
            sound->setVolume(SOUND_DIGIT006, 126);
            sound->play(SOUND_DIGIT006, false);
            break;
        }
        case 7:
        {
            sound->setVolume(SOUND_DIGIT007, 126);
            sound->play(SOUND_DIGIT007, false);
            break;
        }
        case 8:
        {
            sound->setVolume(SOUND_DIGIT008, 126);
            sound->play(SOUND_DIGIT008, false);
            break;
        }
        case 9:
        {
            sound->setVolume(SOUND_DIGIT009, 126);
            sound->play(SOUND_DIGIT009, false);
            break;
        }
        case 10:
        {
            sound->setVolume(SOUND_DIGIT010, 126);
            sound->play(SOUND_DIGIT010, false);
            break;
        }
        default:
        {
            break;
        }
        }
        MissionStateNetworkBattle = 2;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 2 && (timer > PriorStateEndTimer + 1100)) {
        //
        //  This is a good place to degrade fuel, ammo, and ordnance according to
        //  the repair state of our HQ airfield, so that new players, just entering
        //  the battle in a late-war aircraft, will suffer degredation, but
        //  if they enter the battle in an early-war aircraft, no such degredation
        //  is asserted:
        //
        if (MyNetworkId % 2) { //  RedTeam
            if (ThreeDObjects[MissionObjectHqRed]->Durability < ThreeDObjects[MissionObjectHqRed]->maxDurability * 0.4) { //  Get here if player's RedTeam HQ is heavily damaged. Diminish fuel/armament for late-war aircraft.
                display((char*)"MissionNetworkBattle02 state 2: Player's RedTeam HQ is heavily damaged.", LOG_MOST);
                if (fplayer->HistoricPeriod > 1) { //  Get here if the player is flying a late-war or postwar aircraft
                    fplayer->FuelLevel *= 0.2;
                    fplayer->ammo /= 5;
                    //
                    //  Now diminish late-war aircraft bomb and rocket ordnance due to heavy HQ airfield damage
                    //
                    int i2;
                    for (i2 = 0; i2 < missiletypes; i2++) {
                        if (i2 == 0) { //  Rack0 = BOMB01
                            fplayer->missiles[i2] /= 3;
                            display((char*)"MissionNetworkBattle02::processtimer() diminishing RedTeam late-war bomb load due to heavy HQ airfield damage", LOG_MOST);
                        }
                        if (i2 == 5) { //  Rack5 = DFM Rockets
                            fplayer->missiles[i2] /= 3;
                            display((char*)"MissionNetworkBattle02::processtimer() diminishing RedTeam late-war rocket load due to heavy HQ airfield damage", LOG_MOST);
                        }
                    }
                } else { //  Get here if flying an early-war aircraft
                    sprintf(SystemMessageBufferA, "WE HAVE FUEL/ORDNANCE FOR THAT AIRCRAFT.");
                    NewSystemMessageNeedsScrolling = true;
                }
            } else { //  Get here if player's RedTeam HQ is NOT heavily damaged.
                display((char*)"MissionNetworkBattle02 state 2: Player's RedTeam HQ is NOT heavily damaged.", LOG_MOST);
                sprintf(SystemMessageBufferA, "OUR HQ FACILITIES PERMIT FULL FUEL/ORDNANCE.");
                NewSystemMessageNeedsScrolling = true;
            }
        } else { //  BlueTeam
            if (ThreeDObjects[MissionObjectHqBlue]->Durability < ThreeDObjects[MissionObjectHqBlue]->maxDurability * 0.4) { //  Get here if player's BlueTeam HQ is heavily damaged. Diminish fuel/armament for late-war aircraft.
                if (fplayer->HistoricPeriod > 1) { //  Get here if the player is flying a late-war or postwar aircraft
                    fplayer->FuelLevel *= 0.2;
                    fplayer->ammo /= 5;
                    //
                    //  Now diminish late-war aircraft bomb and rocket ordnance due to heavy HQ airfield damage
                    //
                    int i2;
                    for (i2 = 0; i2 < missiletypes; i2++) {
                        if (i2 == 0) { //  Rack0 = BOMB01
                            fplayer->missiles[i2] /= 3;
                            display((char*)"MissionNetworkBattle02::processtimer() diminishing BlueTeam late-war bomb load due to heavy HQ airfield damage", LOG_MOST);
                        }
                        if (i2 == 5) { //  Rack5 = DFM Rockets
                            fplayer->missiles[i2] /= 3;
                            display((char*)"MissionNetworkBattle02::processtimer() diminishing BlueTeam late-war rocket load due to heavy HQ airfield damage", LOG_MOST);
                        }
                    }
                } else { //  Get here if flying an early-war aircraft.
                    sprintf(SystemMessageBufferA, "WE HAVE FUEL/ORDNANCE FOR THAT AIRCRAFT.");
                    NewSystemMessageNeedsScrolling = true;
                }
            } else { //  Get here if player's BlueTeam HQ is NOT heavily damaged.
                sprintf(SystemMessageBufferA, "OUR HQ FACILITIES PERMIT FULL FUEL/ORDNANCE.");
                NewSystemMessageNeedsScrolling = true;
            }
        }
        sound->setVolume(SOUND_YOUHAVEAUTHORITYTOPROCEED, 126);
        sound->play(SOUND_YOUHAVEAUTHORITYTOPROCEED, false);
        MissionStateNetworkBattle = 3;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 3 && (timer > PriorStateEndTimer + 2700)) {
        sound->setVolume(SOUND_WEAPONSFREE, 126);
        sound->play(SOUND_WEAPONSFREE, false);
        MissionStateNetworkBattle = 4;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 4 && (timer > PriorStateEndTimer + 3000)) {
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
        sprintf(SystemMessageBufferA, "LAC SERVER IS AT LACSERVER2.LINUXAIRCOMBAT.COM");
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_MISSIONTELEMETRYAVAILABLEFROMLACSERVERAT, 126);
        sound->play(SOUND_MISSIONTELEMETRYAVAILABLEFROMLACSERVERAT, false);
        MissionStateNetworkBattle = 5;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 5 && (timer > PriorStateEndTimer + 3300)) {
        sound->setVolume(SOUND_BOSENETDOTNODASHIPDOTBIZ, 126);
        sound->play(SOUND_BOSENETDOTNODASHIPDOTBIZ, false);
        MissionStateNetworkBattle = 6;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 6 && (timer > PriorStateEndTimer + 3700)) {
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
        sprintf(SystemMessageBufferA, "TUNE MUMBLE RADIO: LACSERVER2.LINUXAIRCOMBAT.COM");
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_GLOBALASSIGNMENTAUDIOATMUMBLE, 126);
        sound->play(SOUND_GLOBALASSIGNMENTAUDIOATMUMBLE, false);
        MissionStateNetworkBattle = 7;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 7 && (timer > PriorStateEndTimer + 2500)) {
        sound->setVolume(SOUND_BOSENETDOTNODASHIPDOTBIZ, 126);
        sound->play(SOUND_BOSENETDOTNODASHIPDOTBIZ, false);
        MissionStateNetworkBattle = 8;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 8 && (timer > PriorStateEndTimer + 3500)) {
        sound->setVolume(SOUND_MISSIONCOMMSONCHANNEL, 126);
        sound->play(SOUND_MISSIONCOMMSONCHANNEL, false);
        MissionStateNetworkBattle = 9;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 9 && (timer > PriorStateEndTimer + 2000)) {
        sound->setVolume(SOUND_LINUXAIRCOMBAT, 126);
        sound->play(SOUND_LINUXAIRCOMBAT, false);
        MissionStateNetworkBattle = 10;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 10 && (timer > PriorStateEndTimer + 1500)) {
        sound->setVolume(SOUND_MISSIONNETWORKBATTLE02, 126);
        sound->play(SOUND_MISSIONNETWORKBATTLE02, false);
        MissionStateNetworkBattle = 11;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 11 && (timer > PriorStateEndTimer + 2500)) {
        sound->setVolume(SOUND_SQUADCOMMSONSUBCHANNEL, 126);
        sound->play(SOUND_SQUADCOMMSONSUBCHANNEL, false);
        MissionStateNetworkBattle = 12;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 12 && (timer > PriorStateEndTimer + 2500)) {
        sound->setVolume(SOUND_RED, 126);
        if (MyNetworkId % 2) {
            sound->setVolume(SOUND_RED, 126);
            sound->play(SOUND_RED, false);
        } else {
            sound->setVolume(SOUND_BLUE, 126);
            sound->play(SOUND_BLUE, false);
        }
        //
        // Disable or remove the following four lines unless you are testing
        // mission-ending conditions and need to assert some automated airfield damage.
        //
        //sprintf (DebugBuf, "MissionNetworkBattle03::processtimer(): BlueHQ Strength = %f. MissionEndingTimer = %d. MissionEndingTimer2 = %d.\n", ThreeDObjects[MissionObjectHqBlue]->Durability, MissionEndingTimer, MissionEndingTimer2);
        //display (DebugBuf, LOG_MOST);
        //display ((char *)"MissionNetworkBattle03::processtimer(): Invoking TestDamageMissionObjectHqBlue().", LOG_MOST);
        //TestDamageMissionObjectHqRed(); // DebugRJB
        //
        // Also modify the following line depending on whether testing automated damage or not:
        //
        MissionStateNetworkBattle = 13; // Normally 13. Change to 11 to repeat TestDamage calls.
        //
        //
        PriorStateEndTimer = timer;
    }
    //
    //  Loop through all Mission aircraft and determine whether we should re-spawn any
    //  that have been destroyed. Also, preserve each aircraft type prior to arrival
    //  of the next InPacket.
    //
    for (MissionAircraftNumber = 1; MissionAircraftNumber <= 10; MissionAircraftNumber++) {
        //  Examine all 10 aircraft and consider replacing any that have exploded.
        if (ThreeDObjects[0]->explode > 500 * timestep) { //  Player's aircraft exploded recently but has not been re-spawned and player hasn't pressed <ESC>.
            game_quit(); // Player plane is dead and player has waited for program to exit automagically.
        }
        if (ThreeDObjects[0]->explode > 450 * timestep) { //  Player's aircraft exploded recently and he is almost out of time to press <ESC> before program exits.
            sound->setVolume(SOUND_BEEP1, 20); //  and beep softly
            sound->play(SOUND_BEEP1, false);
        }
        if (!ThreeDObjects[MissionAircraftNumber]->active && (myrandom(1000) > 995)) { //  Get here 0.5% of the time when any other plane explodes or crashes. Re-spawn destroyed aircraft.
            GetNetworkApiPacket(); //  Throw away any InPacket that has already sneaked in....
            DiscardAnyInPacketsInQueue(); //  Remove any stale inpackets that might otherwise corrupt our respawning parameters
            InPacket.UdpObjXPosition -= 300; //  Make SURE no InPacket places replacement bot nearby.
            InPacket.UdpObjZPosition -= 300; //  Make SURE no InPacket places replacement bot nearby.
            //
            //  At this point we may want to wait for one or two packet
            //  periods since, due to network latency and the normal time
            //  between our OutPackets, the remote peer won't learn of
            //  his death instantly. Although the remote peer will stop
            //  sending packets once he knows he's dead, during the
            //  interim we must expect him to send one or two more
            //  packets as if he's still alive. If we generate and
            //  position our new bot before the remote peer stops
            //  sending packets, then the arrival of just one of those
            //  packets will cause our bot to instantly leap to the
            //  XYZ position last occupied by the remote peer and
            //  continue from there. That's NOT what we want because
            //  it would make it look like our Victim didn't really die!
            //  Accordingly, we want to set the global "NetworkReceiveTimer"
            //  back to -2000 to make it wait awhile as follows:
            //
            if (ThreeDObjects[MissionAircraftNumber]->Sentient > 3) {//  Get here if the destroyed aircraft was piloted by a Sentient
                GetNetworkApiPacket(); //  Throw away any InPacket that has already sneaked in....
                DiscardAnyInPacketsInQueue(); //  Remove any stale inpackets that might otherwise corrupt our respawning parameters
                InPacket.UdpObjXPosition -= 300; //  Make SURE no InPacket places replacement bot nearby.
                InPacket.UdpObjZPosition -= 300; //  Make SURE no InPacket places replacement bot nearby.
                NetworkReceiveTimer = -400; // Wait awhile before getting next InPacket
                // Preserve this aircraft type for later comparison to detect future changes:
                MissionNetworkBattle02PriorAircraft[MissionAircraftNumber] = ThreeDObjects[MissionAircraftNumber]->id;
            }
            ThreeDObjects[MissionAircraftNumber]->newinit(FIGHTER_A6M2, i + 1, 400);
            ThreeDObjects[MissionAircraftNumber]->id = FIGHTER_A6M2;
            ThreeDObjects[MissionAircraftNumber]->Durability = ThreeDObjects[MissionAircraftNumber]->maxDurability; //  Repair the new aircraft
            ThreeDObjects[MissionAircraftNumber]->immunity = 50 * timestep; //  Make this new aircraft invulnerable for the first few seconds
            ThreeDObjects[MissionAircraftNumber]->activate(); //  Activate that new aircraft
            ThreeDObjects[MissionAircraftNumber]->killed = false;
            ThreeDObjects[MissionAircraftNumber]->ammo = 1600;
            ThreeDObjects[MissionAircraftNumber]->MyMissionPlayerNumber = MissionAircraftNumber; //  Make my player number globally visible
            //
            //  Move to a new, random position in the neighborhood.
            //
            ThreeDObjects[MissionAircraftNumber]->tl->x = 200 + (myrandom(20) - 10);
            ThreeDObjects[MissionAircraftNumber]->tl->z = 200 + (myrandom(20) - 10);
            ThreeDObjects[MissionAircraftNumber]->tl->y = l->getHeight(ThreeDObjects[MissionAircraftNumber]->tl->x, ThreeDObjects[MissionAircraftNumber]->tl->z);
            ThreeDObjects[MissionAircraftNumber]->tl->y += 260 + (myrandom(80) - 40);
            ThreeDObjects[MissionAircraftNumber]->Sentient = 0;
            ThreeDObjects[MissionAircraftNumber]->thrustUp();
            ThreeDObjects[MissionAircraftNumber]->thrustUp();
            sprintf(
                DebugBuf,
                "MissionNetworkBattle02::processTimer() spawning new aircraft %d at X=%f Y=%f Z=%f",
                MissionAircraftNumber,
                ThreeDObjects[MissionAircraftNumber]->tl->x,
                ThreeDObjects[MissionAircraftNumber]->tl->y,
                ThreeDObjects[MissionAircraftNumber]->tl->z
            );
            display(DebugBuf, LOG_MOST);
            for (i = 0; i < missiletypes; i++) {
                ThreeDObjects[MissionAircraftNumber]->missiles[i] = 0;
            }
            ThreeDObjects[MissionAircraftNumber]->explode = 0; //  Stop the explosion.
            ThreeDObjects[MissionAircraftNumber]->target = NULL;
        } //  End of logic that replaces destroyed aircraft to keep the mission running for awhile.
    } //  End of loop that examines each mission aircraft to preserve their type and respawn those destroyed.
// Check to see if the player's aircraft has been destroyed:
    if (!ThreeDObjects[0]->active) { //  Get here whenever the player's aircraft has been destroyed.
        static bool PlayerKilledEventSkipFlag = false;
        if (PlayerKilledEventSkipFlag == false) {
            PlayerKilledEventSkipFlag = true;
            NetworkPlayerKilled = true;
        }
        sound->stop(SOUND_PLANE1);
        sound->stop(SOUND_PLANE2);
        sound->stop(SOUND_WINDNOISE);
        WindNoiseOn = false;
    }
    //
    //  Update NetworkReceiveTimer and determine if it's now time
    //  to check for arrival of a new NetworkApi UDP packet:
    //
    NetworkReceiveTimer += dt;
    if (NetworkReceiveTimer > NetworkReceiveTimerInterval) {
        NetworkReceiveTimer = 0;
        BytesReceived = GetNetworkApiPacket();
        if (BytesReceived == sizeof(LacUdpApiPacket)) { //  Get here if a new InPacket has arrived.
            display((char*)"MissionNetworkBattle02 BytesReceived=", LOG_NET);
            sprintf(DebugBuf, "%i", BytesReceived);
            display(DebugBuf, LOG_NET);
            LoadVariablesFromNetworkApiPacket(timer);
            if (MissionNetworkBattle02PriorAircraft[InPacket.UdpObjPlayerNumber] != InPacket.UdpObjVehicle) { //  Get here if this network peer is in a different aircraft
                //
                //  Now we must tell higher-level logic about the new aircraft type:
                //
                ThreeDObjects[InPacket.UdpObjPlayerNumber]->id = (int)InPacket.UdpObjVehicle;
                ThreeDObjects[InPacket.UdpObjPlayerNumber]->newinit(ThreeDObjects[InPacket.UdpObjPlayerNumber]->id, 0, 400);
            }
            //  Now preserve this InPacket's aircraft type for comparison with the next InPacket for this player:
            MissionNetworkBattle02PriorAircraft[InPacket.UdpObjPlayerNumber] = InPacket.UdpObjVehicle;
        } //  end "Get here if a new InPacket has arrived".
    }
    //
    //  Update NetworkTransmitTimer and determine if it's now time
    //  to send a new NetworkApi UDP packet:
    //
    NetworkTransmitTimer += dt;
    if (NetworkTransmitTimer > NetworkTransmitTimerInterval && !NetworkPlayerKilled) { //  Get here if we're alive and it's time to send a new network API packet.
        NetworkTransmitTimer = 0;
        MissionNetworkBattle02RetrieveFirstDamageDescription();
        SendNetworkApiPacket();
    }
    if (MissionEndingTimer) { //  Get here if one of the two teams has won the battle
        if (MissionEndingTimer == 13000 && !MissionEndingTimer2) { // Get here just once, as soon as an airfield is destroyed.
            display((char*)"MissionNetworkBattle02::processtimer(): Playing SOUND_MISSIONENDINGINSTRUMENTAL.", LOG_MOST);
            if ((ThreeDObjects[MissionObjectHqBlue]->Durability) < ((ThreeDObjects[MissionObjectHqBlue]->maxDurability) * 0.33)) { // Get here when BlueHQ is destroyed.
                ThreeDObjects[MissionObjectRadarBlue1]->Durability = 0.0; // Destroy RADAR antenna
                ThreeDObjects[28]->DamageInNetQueue = 500000; // Trigger network transmission of Destruction Claim
                sprintf(SystemMessageBufferA, "THE REDTEAM HAS WON THE BATTLE!");
                NewSystemMessageNeedsScrolling = true;
                if (MyNetworkId & 1) { //@ Get here if player is on RedTeam. Celebrate victory:
                    sound->play(SOUND_MISSIONENDINGINSTRUMENTAL, false); // Joyful trumpet fanfare
                } else { //@ Get here if player is on BlueTeam. No celebration.
                    sound->play(SOUND_DEFEAT00, false); // Sad mood music
                }
            } else if ((ThreeDObjects[MissionObjectHqRed]->Durability) < ((ThreeDObjects[MissionObjectHqBlue]->maxDurability) * 0.33)) { // Get here when RedHQ is destroyed.
                ThreeDObjects[MissionObjectRadarRed1]->Durability = 0.0; // Destroy RADAR antenna
                ThreeDObjects[29]->DamageInNetQueue = 500000; // Trigger network transmission of Destruction Claim
                sprintf(SystemMessageBufferA, "THE BLUETEAM HAS WON THE BATTLE!");
                NewSystemMessageNeedsScrolling = true;
                if (MyNetworkId & 1) { //@ Get here if player is on RedTeam. No celebration.:
                    sound->play(SOUND_DEFEAT00, false); // Sad mood music
                } else { //@ Get here if player is on BlueTeam. Celebrate victory.
                    sound->play(SOUND_MISSIONENDINGINSTRUMENTAL, false); // Joyful trumpet fanfare
                }
            }
            NewSystemMessageNeedsScrolling = true;
        }
        MissionEndingTimer -= dt; //  Diminish by milliseconds
        if (MissionEndingTimer < 5000) {
            display((char*)"MissionNetworkBattle02::processtimer() Playing audio file MissionEndingIn15SecCountdown.wav", LOG_MOST);
            sound->play(SOUND_MISSIONENDINGIN15SECCOUNTDOWN, false);
            MissionEndingTimer = 0;
            MissionEndingTimer2 = 16000;
        }
    }
    if (MissionEndingTimer2) {
        MissionEndingTimer2 -= dt; //  Diminish by milliseconds
        if (MissionEndingTimer2 < 1000) { //  Get here when all conditions to forcibly end mission are satisfied
            display((char*)"MissionNetworkBattle02::processtimer(): Mission ending now.", LOG_MOST);
            fplayer->Durability = -1.0;
            if ((ThreeDObjects[MissionObjectHqBlue]->Durability) < ((ThreeDObjects[MissionObjectHqBlue]->maxDurability) * 0.33)) { // Get here if RedTeam won the battle.
                if (MissionEndingTimer2 > 800) {
                    sound->play(SOUND_REDTEAMHASWONBATTLE, false);
                }
            } else { // Get here if BlueTeam won the battle.
                if (MissionEndingTimer2 > 800) {
                    sound->play(SOUND_BLUETEAMHASWONBATTLE, false);
                }
            }
        }
    }

    return 0;
} //  end MissionNetworkBattle02::processtimer (Uint32 dt)

void MissionNetworkBattle02::draw() {
    if (timer >= 0 && timer <= 50 * timestep) {
        font1->drawTextCentered(0, 12, -2, name, &textcolor);
    }
} //  end MissionNetworkBattle02::draw ()



//
//  MissionNetworkBattle02RetrieveFirstDamageDescription()
//
//  This function will search the "DamageInNetQueue" member among all mission objects.
//  If none of them have sustained any damage, it will set the new global integer
//  "MissionAircraftDamaged" to 0 and it will also set the new global float variable
//  "DamageToClaim" to  0.0 and return false. On the other hand, as soon as it finds
//  any object with damage, it copies the floating-point damage value into "DamageToClaim",
//  clears out the associated "DamageInNetQueue", stores the associated mission aircraft
//  number in "MissionAircraftDamaged", and returns true.
//
bool MissionNetworkBattle02RetrieveFirstDamageDescription() {
    int Mission3dObject;
    display((char*)"MissionNetworkBattle02RetrieveFirstDamageDescription()", LOG_NET);
    for (Mission3dObject = 1; Mission3dObject <= 29; Mission3dObject++) { //  Loop through all mission aircraft EXCEPT ThreeDObjects[0], which represents the human player.
        if (ThreeDObjects[Mission3dObject]->DamageInNetQueue > 0.0) { //  Get here as soon as we find any damage to claim. Clients will subtract the damage amount they receive.
            DamageToClaim = ThreeDObjects[Mission3dObject]->DamageInNetQueue; //  Positive value signals new damage
            ThreeDObjects[Mission3dObject]->DamageInNetQueue = 0.0;
            MissionAircraftDamaged = Mission3dObject;
            return true;
        }
        if (ThreeDObjects[Mission3dObject]->DamageInNetQueue < 0.0) { //  Get here if it's time to transmit a static damage value. Clients will update damage to received value.
            DamageToClaim = ThreeDObjects[Mission3dObject]->DamageInNetQueue; //  Negative value signals static update
            ThreeDObjects[Mission3dObject]->DamageInNetQueue = 0.0;
            MissionAircraftDamaged = Mission3dObject;
            return true;
        }
    }
    //  Get here if we have no damage to claim
    MissionAircraftDamaged = 0;
    DamageToClaim = 0.0;
    return (false);
} //  end MissionNetworkBattle02RetrieveFirstDamageDescription()

