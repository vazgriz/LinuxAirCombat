//
//  This file implements "MissionNetworkBattle05".
//
//  The original version of this file implements the mission as a functional duplicate
//  of our well-known, long-stable "MissionNetworkBattle01", but by altering the
//  code within this file, profound changes can be made. It is easy to change the
//  terrain style and to experiment with various weather effects, or to restrict
//  the choice of aircraft. It is also easy to add additional mission objects, like
//  one or more additional battleships. These can be "animated" so that they move
//  around according to the advance of time.
//
//  Developers familiar with the free, well-known "Blender" graphic rendering
//  application could create 3d models of aircraft carriers, other ships, or
//  anti-aircraft guns which could then be used in new versions of this mission.
//
//  More advanced ideas might include adding additional "HQ" airfields which must be
//  destroyed before either team can claim victory. Or victory could be based on
//  some completely different concept, like some specific number of air-to-air
//  victories for one side or for an individual player, or destruction of three
//  battleships, etc.
//
//  Developers are essentially unrestricted in the design of missions deriving
//  from this framework.
//
//  Throughout this code, it will be helpful to know that syntax like "tl->x",
//  or "tl->y", or "tl->z" refers to the physical location of an object in
//  xyz coordinates, where the "y" coordinate represents altitude. Think of
//  "tl" as "translate" in this context. You will use this syntax to place
//  objects or aircraft within the terrain.
//
//  Many elements of this mission code interact with pre-written, fully debugged
//  functions outside the scope of this file. Sometimes these functions are
//  invoked directly in code that can be seen here, but sometimes these
//  external funcions are invoked indirectly, by setting or adjusting the
//  value of some global variable that acts to "trigger" them. By following
//  the logic patterns visible in this file, mission designers can use those
//  external tools in similar ways.
//
//  Mission designers wishing to modify this mission should NOT change any
//  other source code files unless they coordinate with the primary LAC
//  designer, since any such changes will affect other behavior.
//
//
// Mission-specific code commences here:
//
MissionNetworkBattle05::MissionNetworkBattle05() {
    //
    //  This code is executed as soon as the player selects this mission
    //  from the main menu. It is responsible for display of the associated,
    //  mission-specific menu text. It also sets up the required network
    //  configuration, and associated timers for network events.
    //
    //  Set up menu system to allow the player to read a description
    //  of the mission and select appropriate aircraft and
    //  munitions. Also open the necessary UDP sockets for
    //  outgoing and incoming traffic:
    //
    display((char*)"MissionNetworkBattle05::MissionNetworkBattle05()", LOG_MOST);
    id = MISSION_NETWORKBATTLE05;
    if ((NetworkMode & 1) == 0) {
        strncpy(name, "WRONG NETWORK MODE!", 1024);
        strncpy(briefing, "FOR CLIENT/SERVER MODE, LACCONFIG.TXT FILE MUST SET MODE\nTO AN ODD NUMBER.", 1024);
    } else {
        strncpy(name, "BLAKE'S MISSION: AIR SUPERIORITY", 1024);
        strncpy(briefing, "2 TO 10 NETWORK PLAYERS IN 2 TEAMS. ONLY FIGHTER AIRCRAFT ARE\nPERMITTED. THIS SIMPLE MISSION IS ONLY FOR FIGHTER VERSUS FIGHTER\nDOGFIGHTS. THERE ARE NO GROUND GUNS. LAND ON ANY FLAT GROUND\nTO REFUEL, REARM, & REPAIR. NO JETS, ROCKETS, OR TAIL GUNS.", 1024);
    }
    selfighter[0] = DefaultAircraft;
    selweapons = 0;
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

    //
    //  Configure the network in preparation for online work.
    //
    //  (You don't want to make any changes in this area unless you
    //  know what you are doing and are already comfortable with the
    //  UDP protocol and the DNS system.)
    //
    if ((NetworkMode & 1) == 1) { //  ClientServer mode requires only a single UDP port, used both for sending and receiving
        display((char*)"Attempting MissionNetworkBattle05 in ClientServer Network mode.", LOG_NET);
        if (OpenClientUdpSocket() == 0) { //  Get here if we were able to open the required ClientServer UDP Socket
            display((char*)"MissionNetworkBattle05 ClientServer mode succesfully opened ClientUDP socket", LOG_NET);
            ConfigureClientUdpSocket();
        } else { //  Get here if we were unable to open the required ClientUDP socket
            display((char*)"MissionNetworkBattle05 ClientServer mode unable to open ClientUDP socket.", LOG_NET);
        }
    } else {
        display((char*)"Incorrect network mode configured in LacConfig.txt file.", LOG_ERROR);
        sound->setVolume(SOUND_BEEP1, 126);
        sound->play(SOUND_BEEP1, false);
    }
    //
    //  Now switch the user's "Mumble" application to the appropriate channel:
    //
    event_CommsMacro17();
} //  end MissionNetworkBattle05::MissionNetworkBattle05 ()

void MissionNetworkBattle05::start() {
    NoMissionHasYetCommenced = false;
    //
    //  This code gets executed only once per mission, as it starts up.
    //
    //  Initialize the landscape, place the player within it, and
    //  optimize cockpit instruments. Then load armament for all
    //  peers and spawn the AI aircraft for the mission.
    //
    //
    if (!(NetworkMode & 16)) { // Get here if LAC is NOT configured to ignore espeak
        //popen("espeak -p 10 -a 66  -s 160 \"Welcome to Blake's Mission! This is a very simple, fighter versus fighter mission. You can land on any flat ground for refuel, re-arm, and repair services.\"", "r");
    }
    // Initialize the "mission state", which is tracked in the global variable "MissionStateNetworkBattle".
    // That value will increase at carefully selected time intervals, and is used to trigger time-dependent
    // mission events, like snippets of audio narration that can help the player get oriented to
    // the mission's design:
    MissionStateNetworkBattle = 0;
    display((char*)"MissionNetworkBattle05::start()", LOG_MOST);
    //
    // Now initialize a few other mission-specific variables:
    //
    NetworkPlayerKilled = false;
    int i, i2;
    camera = 0; //  Place player in cockpit, looking forward
    heading = 220; //  Initial direction of travel
    //
    //  Make sure the value of "MyNetworkId" is appropriate, and change
    //  it to a value between 1 and 10 if necessary:
    //
    if ((MyNetworkId == 0) || (MyNetworkId > MaxPlayersInCurrentMission)) { //  Get here if "MyNetworkId" has not yet been initialized or if its value is too high
        MyNetworkId = myrandom(MaxPlayersInCurrentMission); //  Randomize MyNetworkId
        MyNetworkId++;
    }

    //
    //  Now configure the weather conditions for the mission:
    //
    day = 1;
    clouds = 2; //  1, 2, or 3.
    weather = WEATHER_SUNNY; //  Other weather available. Backspace past the underscore, then replace underscore for prompts.
    sungamma = 25; //  Adjust brightness of sun and subtle shading, especially water textures. 25 is nice.

    //
    //  Now generate the landscape, hereafter named simply "l":
    //
    if (l != NULL) { //  If we already have landscape "l", delete it
        delete l;
    }

    //
    //  The next line of code can urge formation of any of various styles of landscape.
    //  The original template for this mission used "LANDSCAPE_ALPINE_SEA" for this, but
    //  we subsequently changed it to "LANDSCAPE_ALPINE_EROSION" instead.
    //
    //  If you edit that keyword inside Codeblocks, it will suggest alternatives that
    //  will cause generation of desert, forest, arctic, or other landscapes.
    //
    l = new GLLandscape(space, LANDSCAPE_ALPINE_EROSION, NULL);

    //
    // Now calibrate the altimeter so it goes to "0" at sea level. If you change the
    // landscape style you will probably need to experiment with it to determine the
    // right value of "SeaLevel" according to appearances as you fly:
    SeaLevel = 100.0; //  Calibrates RADAR and altimeter to about "0" at sea level. Adjust as needed for different terrains. 400 yields about 19000ft. 200 yields about 10000ft.

    //
    //  Now use the landscape's "flatten()" function to landscape a long, flat runway, at landscape XY
    //  coordinates designated by the global floating-point variables "AirfieldXMin", "AirfieldYMin":
    //
    //  (Note that you will need to change the XY values of "AirfieldXMin" and "AirfieldYMin" in main.cpp
    //  if your landscape terrain forces relocation of your airfields.)
    //
    l->flatten(AirfieldXMin + 28.0, AirfieldYMin + 4, 29.2, 5); //  Flatten runway 29.2 units long, 5 units wide
    l->flatten(AirfieldXMin + 46, AirfieldYMin + 5, 7, 6); //  Flatten adjacent tarmac area 7 units long, 6 units wide
    //
    // Over-ride some defaults in the Mission Object Map, since this
    // mission will use a different combination of mission objects:
    //
    MissionObjectBunkerBlue1 = 0;
    MissionObjectBunkerRed1 = 0;
    MissionObjectRadarHqRed = 0;
    MissionObjectRadarHqBlue = 0;
    MissionObjectHqBlue = 0;
    MissionObjectHqRed = 0;
    //
    //  Now insert RedTeam "Airfield00" structures onto the landscape near its runway, treating those structures as if
    //  they were any other mission object so they can be damaged and/or destroyed. This will be the HQ
    //  airfield for the RedTeam, followed by other RedTeam objects:
    //
    //  Note: Later on in this source code file, you will see that we spawn all of the online players
    //  far, Far, FAR away from airfields. Players experience this mission as if there were no defended
    //  airfields and no anti-aircraft batteries at all. Obviously this is not true: the following code
    //  creates defended airfields in the same locations that are used in other missions. Spawning online
    //  players far far away was just an easy way to keep this mission very simple as experienced by
    //  the players, while retaining the overall uniformity of mission design.
    //
    MissionObjectHqRed = 29; // Update Mission Object Map
    int n = MissionObjectHqRed; //  RedTeam HQ airfield facilities
    //  Note that the Airfield is special in that logic in other source code files makes provisions to
    //  periodically transmit its status to the server.
    ThreeDObjects[n]->tl->x = AirfieldXMin + 46.5;
    ThreeDObjects[n]->tl->z = AirfieldYMin + 8;
    //  Airfield X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects[n]->target = ThreeDObjects[0]; //  Airfields don't need a "target".
    ThreeDObjects[n]->o = &model_Airfield00; //  Load the 3d model for generation of its appearance
    ThreeDObjects[n]->newinit(STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability; //  Set initial airfield Durability
    ThreeDObjects[n]->zoom = 6.0; //  Scale airfield to a nice, prominent size.

    MissionObjectRadarHqRed = 27; // Update Mission Object Map
    n = MissionObjectRadarHqRed; //  RedTeam Rectangular RADAR Reflector
    ThreeDObjects[n]->tl->x = AirfieldXMin + 41.0;
    ThreeDObjects[n]->tl->z = AirfieldYMin + 6.2;
    ThreeDObjects[n]->target = ThreeDObjects[0];
    ThreeDObjects[n]->o = &model_RadarReflector;
    ThreeDObjects[n]->newinit(STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects[n]->impact = 0.0;
    ThreeDObjects[n]->party = 1;
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 0.66;

    //
    //  Now insert BlueTeam "Airfield00" structures onto the landscape near its runway, treating those structures as if
    //  they were any other mission object so they can be damaged and/or destroyed. This will be the HQ
    //  airfield for the BlueTeam, followed by other BlueTeam objects:
    //
    MissionObjectHqBlue = 28;  // Update Mission Object Map
    n = MissionObjectHqBlue; //  BlueTeam HQ airfield Facilities
    //  Note that the Airfield is special in that logic in other source code files makes provisions to
    //  periodically transmit its status to the server.
    ThreeDObjects[n]->tl->x = -304;
    ThreeDObjects[n]->tl->z = 11.0;
    //  Airfield X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects[n]->target = ThreeDObjects[0]; //  Airfields don't need a "target".
    ThreeDObjects[n]->o = &model_Airfield00;
    ThreeDObjects[n]->newinit(STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 6.0;

    MissionObjectRadarHqBlue = 26; // Update Mission Object Map
    n = MissionObjectRadarHqBlue; //  BlueTeam Rectangular RADAR Reflector. Carefully place its xz directly atop the airfield tower.
    ThreeDObjects[n]->tl->x = AirfieldXMin - 470.58; //  -470.5 ends up with the tower just barely within the convex reflector.
    ThreeDObjects[n]->tl->z = AirfieldYMin + 6.25;
    ThreeDObjects[n]->target = ThreeDObjects[0];
    ThreeDObjects[n]->o = &model_RadarReflector;
    ThreeDObjects[n]->newinit(STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects[n]->impact = 0.0;
    ThreeDObjects[n]->Durability = ThreeDObjects[n]->maxDurability;
    ThreeDObjects[n]->zoom = 0.66;

    //
    //  Just a few "housekeeping details now, in preparation for running the mission:
    //
    playerInit();
    PlayerAircraftType = fplayer->id;
    MissionRunning = false; //  Semaphore. Set on first pass through mission processtimer().
    fplayer->phi = 270; //  Player's initial direction of travel. (270 = straight West.)

    //
    //  This could be a handy place to update our log file and generate a run-time status update:
    //
    display((char*)"MissionNetworkBattle05::start setting PlayerAircraftType to: ", LOG_MOST);
    sprintf(DebugBuf, "%d", PlayerAircraftType);
    display(DebugBuf, LOG_MOST);

    //  Initialize all cockpit instruments to a stable starting point
    HudOnOff = 1;               //  Start out with HUD on.
    IffOnOff = 0;                 //  Initialize IFF to off.
    MapViewOnOff = 0;           //  Make sure we have MapView off at start.
    RadarOnOff = 0;               //  Initialize RADAR to off.
    RadarZoom = 1;              //  Set RADAR Range to 50 km for this mission.
    ScreenFOVx = 1.0;           //  Reset view zoom to normal
    ScreenFOVy = 1.0;           //  Reset view zoom to normal
    //  Now optimize all cockpit instruments for this mission
    event_IffOnOff();           //  Turn on IFF for this mission.
    if (!HudLadderBarsOnOff) { //  Turn on HUD Ladder bars for this mission
        event_HudLadderBarsOnOff();
    }
    event_ZoomFovOut();         //  Start with wide field of view.
    event_ZoomFovOut();
    MaxPlayersInCurrentMission = 10;
    //
    //   Spawn ten shiny new AI aircraft, Defaulting to F4F "Wildcats".
    //   Throughout this mission, arriving UDP InPackets representing
    //   flight by remote, network-accessible peer client copies of LAC
    //   are accepted and examined, and the activities they
    //   describe are applied to the active AI aircraft designated
    //   within each received InPacket.
    //
    for (i = 1; i <= 10; i++) {
        //   Initialize opponents. Last argument to newinit(),
        //   although it is named "intelligence" in the code,
        //   determines their stupidity. Lower means more
        //   effective. 400 is a pretty good value. 1200 makes
        //   them quite dumb.
        //
        ThreeDObjects[i]->newinit(FIGHTER_F4F, 0, 400);
        // Preserve aircraft type for later comparison to detect changes.
        MissionNetworkBattle05PriorAircraft[i] = FIGHTER_F4F;
        //
        //  The "ThreeDObjects[]" array manages all of the active
        //  mission objects, and it contains an entry for each of
        //  the ten mission aircraft, plus airfields, radar towers,
        //  ships, artillery batteries, etc.. Each of the first ten
        //  entries is used for the mission aircraft and consequently
        //  associated with a multitude of flight "attributes", each
        //  of which is accessed through a syntax like this: "->".
        //
        //  For example, the "Sentient" attribute counts upward
        //  when an aircraft has received a lot of network packets
        //  influencing its position and indicating that it is
        //  being flown by a living human connected via the
        //  Internet. On the other hand, the "Sentient" attribute
        //  counts downward with the routine passage of time.
        //  Accordingly, a "Sentient" value of "0" indicates that
        //  the corresponding aircraft is a "bot" that is not
        //  influenced by a network-connected human.
        //
        //  Choose appropriate starting values for the most important
        //  attributes of all 10 mission aircraft:
        //
        ThreeDObjects[i]->target = NULL; //  Best if bots don't have a target...
        ThreeDObjects[i]->o = &model_figAO; //  Load the appropriate 3d model for appearance of bot.
        //  Position fighters in scattered xz locations:
        ThreeDObjects[i]->tl->x = -200 + (myrandom(400) - 200) + (150 * SIN(i * 360 / 11));
        ThreeDObjects[i]->tl->z = 200 + (myrandom(400) - 200) + (150 * COS(i * 360 / 11));
        ThreeDObjects[i]->ammo = 1600; //  Bots start out with 1600 machine gun bullets
        ThreeDObjects[i]->Sentient = 0; //  All fighters are bots until a stream of InPackets reveals them to be Sentient.
        ThreeDObjects[i]->MyMissionPlayerNumber = i; //  Assign all 10 players their "MyMissionPlayerNumber" (used elsewhere)
        //
        //  This is another good place to update our diagnostic reporting and log with details about our bots:
        //
        sprintf(DebugBuf, "MissionNetworkBattle05::start() initializing Bot #%d", i);
        display(DebugBuf, LOG_MOST);
        sprintf(
            DebugBuf,
            "MissionNetworkBattle05::start() ThreeDObjects [i]->MyMissionPlayerNumber = %d",
            ThreeDObjects[i]->MyMissionPlayerNumber
        );
        display(DebugBuf, LOG_MOST);
        //
        //  Now make sure none of the mission aircraft is lugging missiles or bombs:
        //
        for (i2 = 0; i2 < missiletypes; i2++) { //  examine every "hardpoint" on each aircraft
            ThreeDObjects[i]->missiles[i2] = 0; //  Start out lugging no ordnance anywhere.
        }
    } //  End of loop that spawns and configures all 10 mission bots.
//
//  Just a few more "housekeeping" items to make sure this mission always starts out
//  in the same way with stable counters, timers, ordnance, etc.:
//
    texttimer = 0;
    MissionOutPacketCount = 0;
    MissionIdNegotiationCount = 0;
    NetworkTransmitTimer = -1000; //  Don't send any OutPackets for the first 1 second of the mission.
    ConfigureOrdnanceForOnlineMissions();
    UpdateOnlineScoreLogFileWithNewSorties();
    ArmPlayerAtRequestedField();
    //
    //  Now give the player a starting xz position based on his team affiliation:
    //  Note that the logic can always refer to the player as "fplayer" and associated
    //  attributes can be accessed through syntax like "fplayer->" etc.
    //
    //  By enforcing a huge "Z" position like "15000", we spawn all of these aircraft
    //  very very far away from airfields and from any Sentient players that may ever
    //  enter the mission.
    //
    if (MyNetworkId % 2) { //@ Get here if player is on RedTeam
        display((char*)"MissionNetworkBattle05: Spawning player at 500, 15000", LOG_MOST);
        fplayer->tl->x = 500; //@ was -340
        fplayer->tl->z = 15000.00;
    } else { //@ Get here if player is on BlueTeam
        display((char*)"MissionNetworkBattle05: Spawning player at -500, 15000", LOG_MOST);
        fplayer->tl->x = -500; //@ was -340
        fplayer->tl->z = 15000.00;
    }

    // Ensure aircraft is ready for combat
    //
    //  Do not try to understand or change this "ThrustReadiness" logic. It is
    //  purposely undocumented and is used by the server for some secret, anti-
    //  cheating logic:
    //
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
} //  end MissionNetworkBattle05::start ()

int MissionNetworkBattle05::processtimer(Uint32 dt) {
    //  Get here every few milliseconds during this mission.
    //
    //  This function is the heart and soul of the mission.
    //
    //  This function must be coded for speed and efficiency, since
    //  it is called constantly, as frequently as possible, for as
    //  long as the player remains in flight in this mission.
    //
    //  This big function controls all of the action and dynamic
    //  elements of the mission. Everything that is animated or
    //  dynamic is controlled here, as the logic processes this
    //  function over and over again, as fast as it can go.
    //
    //  Local Variables used throughout this function:
    //
    int i;
    int MissionAircraftNumber;
    int BytesReceived = 0;
    //
    // Recommend an initial elevator effect of "0" do avoid a lot of redouts:
    //
    fplayer->recelevatoreffect = 0;
    //
    //  To begin, we update all timers and initiate timer-dependent
    //  logic as necessary.
    //
    //  The amount of time in milliseconds since the last
    //  commencement of this function is specified by the Unsigned
    //  integer input parameter named "dt", so we will always
    //  increase or decrease our timers by the amount specified in "dt".
    //  The value of "dt" is also available as "DeltaTime".
    //
    //
    //  Now advance a few of the timers that will be used throughout
    //  this mission:
    //
    MissionNetworkBattle05Timer += DeltaTime; //  Advance by milliseconds
    MissionNetworkBattleRadarTimer += DeltaTime; //  Advance by milliseconds
    MumbleTimeRemainingBeforeChannelReset -= DeltaTime; //  This one counts down.
    if (!MissionRunning) { //  Get here if this is the FIRST pass through processtimer().
        //
        //  This block of code is executed only ONCE, at the beginning of the mission.
        //
        //  Set up player details that cannot be set up in mission start().
        DegradeFlightModelDueToOrdnanceLoad(); //  If lugging heavy weapons, diminish climb rate
        fplayer->FuelLevel = 96.0; //  Start the player out with 96% fuel as this mission commences.
        //
        // This mission prohibits use of heavy bombers, medium bombers, or any other aircraft with a
        // tail gunner. The main menu system allows the player to SELECT those aircraft, but
        // we will deny them fuel here:
        //
        if (fplayer->missiles[0] >= 4) { //  Get here if this is a medium or heavy bomber. Cut fuel enough to prevent reaching next airfield.
            fplayer->FuelLevel = 1.0;
        }
        if (fplayer->missiles[0] >= 12) { //  Get here if this is a heavy bomber. Cut fuel enough to prevent reaching next airfield.
            fplayer->FuelLevel = 0.5;
        }
        //
        // Now determine whether the player enters the mission flying straight East or straight
        // West, depending on his team affiliation. Previous logic assumed the player joined the
        // BlueTeam. If he'as actually on the RedTeam, we need to reverse his compass heading,
        // accessed as "fplayer->phi":
        //
        if (fplayer->party == 1) { //  Red team. Need to reverse compass direction to fly toward action.
            fplayer->phi -= 180;
        }
        /*
        *
        * The following block of code attempts to cause the player to
        * spawn with zero airspeed. It works, but it isn't sufficient
        * because something else causes airspeed to build back to
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

        //
        //  Due to the quirky way objects are positioned as a mission commences, this
        //  is the first reasonable opportunity to adjust the altitude of mission
        //  objects populating our landscape. Adjust them all according to the
        //  terrain upon which they are located. This logic is assisted by two
        //  handy terrain functions, named "getHeight()" and "getExactHeight()".
        //  Each expects two input parameters designating a specific terrain
        //  location in XZ coordinates, and each returns the altitude of the
        //  terrain at that point, which equates to the associated Y coordinate.
        //
        //  If you make significant changes to terrain altitudes, you may need
        //  to adjust the following code according to your own observations
        //  in flight to prevent mission objects from floating above the
        //  landscape or sinking out of sight below ground.
        //

        //  Player aircraft altitude at startup should be very low above ground.
        fplayer->tl->y = l->getHeight(AirfieldXMin, AirfieldYMin);
        fplayer->tl->y += 25.0; //  Raise player aircraft 25 units in "y"

        //  Airfield BlueHQ facilities altitude
        ThreeDObjects[MissionObjectRadarHqBlue]->tl->y = l->getExactHeight(AirfieldXMin - 470.58, AirfieldYMin + 6.25); //  BlueTeam Radar Reflector
        ThreeDObjects[MissionObjectRadarHqBlue]->tl->y += 3.0; // Raise  RADAR antenna a little above the ground.
        ThreeDObjects[MissionObjectHqBlue]->tl->y = l->getHeight(-304, 11);
        ThreeDObjects[MissionObjectHqBlue]->tl->y += 0.90; //  BlueTeam airfield facilities get raised 0.90 units

        //  Airfield RedHQ facilities altitude
        ThreeDObjects[MissionObjectRadarHqRed]->tl->y = l->getExactHeight(AirfieldXMin + 41.0, AirfieldXMin + 6.2); //  RedTeam Radar Reflector
        ThreeDObjects[MissionObjectRadarHqRed]->tl->y += 5.6; // Raise RADAR antenna a little above the ground.
        ThreeDObjects[MissionObjectHqRed]->tl->y = l->getHeight(AirfieldXMin + 46.5, AirfieldYMin + 8);
        ThreeDObjects[MissionObjectHqRed]->tl->y += 0.90; //  RedTeam airfield facilities get raised 0.90 units.

        //  Make sure player starts out with landing gear and flaps retracted in any aircraft that permits retraction
        fplayer->UndercarriageLevel = 0;
        fplayer->FlapsLevel = 0;
        //fplayer->FlapsLevel = 1;
        for (i = 1; i <= 10; i++) { // Start all ten bots at medium altitude
            ThreeDObjects[i]->tl->y += 150;
        }
        //
        // Prevent effective use of any bomber aircraft in this mission:
        //
        if (
            (fplayer->id == BOMBER_B17) ||
            (fplayer->id == BOMBER_B24) ||
            (fplayer->id == BOMBER_JU87) ||
            (fplayer->id == BOMBER_G5M) ||
            (fplayer->id == BOMBER_B25) ||
            (fplayer->id == BOMBER_B26) ||
            (fplayer->id == BOMBER_LANCASTER) ||
            (fplayer->id == BOMBER_B29) ||
            (fplayer->id == BOMBER_B5N) ||
            (fplayer->id == BOMBER_DAUNTLESS) ||
            (fplayer->id == BOMBER_DORNIER) ||
            (fplayer->id == BOMBER_HE111) ||
            (fplayer->id == BOMBER_JU88) ||
            (fplayer->id == BOMBER_SB2C) ||
            (fplayer->id == BOMBER_TBF) ||
            (fplayer->id == FIGHTER_D3A) ||
            (fplayer->id == FIGHTER_ME110) ||
            (fplayer->id == FIGHTER_IL2) ||
            (fplayer->id == FIGHTER_ME163) ||
            (fplayer->id == FIGHTER_HAWK)
            ) { // Get here if player is attempting to fly a bomber, jet, or rocket.
            sprintf(SystemMessageBufferA, "THIS MISSION FORBIDS THIS AIRCRAFT. OUT OF FUEL!");
            NewSystemMessageNeedsScrolling = true;
            sound->setVolume(SOUND_BEEP1, 60); //@ Medium-volume beep
            sound->play(SOUND_BEEP1, false);
            fplayer->Durability = fplayer->Durability * 0.1; // Inflict heavy damage on player if he's in a forbidden bomber
            fplayer->FuelLevel = 0;
        }
        //
        //  Now make sure player aircraft is NOT lugging missiles or bombs:
        //
        for (i = 0; i < missiletypes; i++) { //  examine every "hardpoint" on each aircraft
            ThreeDObjects[0]->missiles[i] = 0; //  Start out lugging no ordnance anywhere.
        }
        MissionRunning = true; //  For next pass, Signal that this startup loop has already been done.
    } //  End block of code used only ONCE, at very beginning of the mission.
 //
 //
 //  Continue main line of processtimer() code. This gets executed  many times per second while Mission runs.
 //
    timer += dt; //  Advance mission timer.
    //
    //  The next few blocks of code will play various audio messages
    //  at the beginning of the mission to help the player become
    //  oriented. Individual events are repeated during each of several
    //  values of "MissionStateNetworkBattle". Those "states", in turn,
    //  are advanced step-by-step as "timer" advances beyond various
    //  boundary values.
    //
    //  Mission designers should avoid creating any additional audio
    //  sound files because they use up a lot of RAM and their
    //  creation is beyond the scope of simple mission design,
    //  requiring a lot of complicated steps.
    //
    //  However, Mission designers can easily skip some of the
    //  following audio messages, change them to other pre-existing
    //  soudn clips, or change the timing alloted for each.
    //
    //  Players can also easily invoke text-to-speech audio
    //  through the "espeak" application, since most LAC players
    //  have been installing espeak according to our recommendations.
    //
    //  All of this logic is dominated by the value of "timer",
    //  which triggers transitions among important values of
    //  "MissionStateNetworkBattle", which was just advanced
    //  by the prior line of code. It accumulates the time
    //  duration of the mission in milliseconds.
    //
    if (timer > 10000 && MissionStateNetworkBattle == 0 && NetworkTransmitTimer >= NetworkTransmitTimerInterval) { //  Only get here once, 10 seconds into the mission, as we've just begun transmitting OutPackets
        //  with an available setting for MyNetworkId. Vocalize "Red" or "Blue" according to player's
        //  team affiliation:
        if (MyNetworkId % 2) { //  Get here if MyNetworkId is an odd number
            //  Vocalize "RED"
            sound->setVolume(SOUND_RED, 126);
            sound->play(SOUND_RED, false);
        } else {
            //  Vocalize "BLUE"
            sound->setVolume(SOUND_BLUE, 126);
            sound->play(SOUND_BLUE, false);
        }
        MissionStateNetworkBattle = 1; //  This MissionState is done. Advance to next.
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 1 && (timer > PriorStateEndTimer + 600)) { //  Only get here once, 600 ms after MissionStateNetworkBattle
        //  advances to "1":
        //
        if (!RadarOnOff) {
            // If player has not already activated RADAR, to it for him:
            event_RadarOnOff();
        }
        //  Now vocalize the player's "MyNetworkId" value, a single
        //  digit between "1" and "10". This is part of the mission's
        //  audio greeting for the player during the first few seconds:
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
        MissionStateNetworkBattle = 2; //  This MissionState is done. Advance to next.
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 2 && (timer > PriorStateEndTimer + 1100)) { //  Only get here once, 1100 ms after MissionStateNetworkBattle
        //  advances to "2":
        //
        //  This is a good place to degrade fuel, ammo, and ordnance according to
        //  the repair state of our HQ airfield, so that new players, just entering
        //  the battle in a late-war aircraft, will suffer degredation, but
        //  if they enter the battle in an early-war aircraft, no such degredation
        //  is asserted: Update cockpit "SystemMessagePanel" accordingly:
        //

        sound->setVolume(SOUND_YOUHAVEAUTHORITYTOPROCEED, 126);
        sound->play(SOUND_YOUHAVEAUTHORITYTOPROCEED, false);
        MissionStateNetworkBattle = 3;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 3 && (timer > PriorStateEndTimer + 2700)) { //  Only get here once, 2700 ms after MissionStateNetworkBattle
        //  advances to "3":
        //  Vocalize "Weapons Free"
        sound->setVolume(SOUND_WEAPONSFREE, 126);
        sound->play(SOUND_WEAPONSFREE, false);
        MissionStateNetworkBattle = 4;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 4 && (timer > PriorStateEndTimer + 3000)) { //  Only get here once, 3000 ms after MissionStateNetworkBattle
        //  advances to "4":
        //
        //  Vocalize "Mission telemetry available from LAC server at"
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
        sprintf(SystemMessageBufferA, "LAC SERVER IS AT LACSERVER2.LINUXAIRCOMBAT.COM");
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_MISSIONTELEMETRYAVAILABLEFROMLACSERVERAT, 126);
        sound->play(SOUND_MISSIONTELEMETRYAVAILABLEFROMLACSERVERAT, false);
        MissionStateNetworkBattle = 5;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 5 && (timer > PriorStateEndTimer + 3300)) { //  Only get here once, 3300 ms after MissionStateNetworkBattle
        //  advances to "5":
        //  Vocalize "Linux Air Combat dot com"
        sound->setVolume(SOUND_BOSENETDOTNODASHIPDOTBIZ, 126);
        sound->play(SOUND_BOSENETDOTNODASHIPDOTBIZ, false);
        MissionStateNetworkBattle = 6;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 6 && (timer > PriorStateEndTimer + 3700)) { //  Only get here once, 3700 ms after MissionStateNetworkBattle
        //  advances to "6":
        //
        //  Vocalize "Global assignment audio at"
        sound->setVolume(SOUND_BEEP1, 20);
        sound->play(SOUND_BEEP1, false);
        sprintf(SystemMessageBufferA, "TUNE MUMBLE RADIO: LACSERVER2.LINUXAIRCOMBAT.COM");
        NewSystemMessageNeedsScrolling = true;
        sound->setVolume(SOUND_GLOBALASSIGNMENTAUDIOATMUMBLE, 126);
        sound->play(SOUND_GLOBALASSIGNMENTAUDIOATMUMBLE, false);
        MissionStateNetworkBattle = 7;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 7 && (timer > PriorStateEndTimer + 2500)) { //  Only get here once, 2500 ms after MissionStateNetworkBattle
        //  advances to "7":
        //
        //  Vocalize "Linux Air Combat.com"
        sound->setVolume(SOUND_BOSENETDOTNODASHIPDOTBIZ, 126);
        sound->play(SOUND_BOSENETDOTNODASHIPDOTBIZ, false);
        MissionStateNetworkBattle = 8;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 8 && (timer > PriorStateEndTimer + 3500)) { //  Only get here once, 3500 ms after MissionStateNetworkBattle
        //  advances to "8":
        //
        //  Vocalize "Mission comms on channel"
        sound->setVolume(SOUND_MISSIONCOMMSONCHANNEL, 126);
        sound->play(SOUND_MISSIONCOMMSONCHANNEL, false);
        MissionStateNetworkBattle = 9;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 9 && (timer > PriorStateEndTimer + 2000)) { //  Only get here once, 2000 ms after MissionStateNetworkBattle
        //  advances to "9":
        //
        //  Vocalize "Linux Air Combat"
        sound->setVolume(SOUND_LINUXAIRCOMBAT, 126);
        sound->play(SOUND_LINUXAIRCOMBAT, false);
        MissionStateNetworkBattle = 10;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 10 && (timer > PriorStateEndTimer + 1500)) { //  Only get here once, 1500 ms after MissionStateNetworkBattle
        //  advances to "10":
        //
        //  Vocalize "MissionNetworkBattle01"
        sound->setVolume(SOUND_MISSIONNETWORKBATTLE01, 126);
        sound->play(SOUND_MISSIONNETWORKBATTLE01, false);
        MissionStateNetworkBattle = 11;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 11 && (timer > PriorStateEndTimer + 2500)) { //  Only get here once, 2500 ms after MissionStateNetworkBattle
        //  advances to "11":
        //
        //  Vocalize "Squad comms on subchannel"
        sound->setVolume(SOUND_SQUADCOMMSONSUBCHANNEL, 126);
        sound->play(SOUND_SQUADCOMMSONSUBCHANNEL, false);
        MissionStateNetworkBattle = 12;
        PriorStateEndTimer = timer;
    }
    if (MissionStateNetworkBattle == 12 && (timer > PriorStateEndTimer + 2500)) { //  Only get here once, 2500 ms after MissionStateNetworkBattle
        //  advances to "12":
        //
        //  Vocalize "Red" or "Blue" according to player's team affiliation:
        sound->setVolume(SOUND_RED, 126);
        if (MyNetworkId % 2) {
            sound->setVolume(SOUND_RED, 126);
            sound->play(SOUND_RED, false);
        } else {
            sound->setVolume(SOUND_BLUE, 126);
            sound->play(SOUND_BLUE, false);
        }
        MissionStateNetworkBattle = 13;
        PriorStateEndTimer = timer;
    }

    //
    //  Mission Designers: If you want to insert additional, timed, one-time steps
    //  into your mission, you can continue the pattern of the 12 prior
    //  "MissionStateNetworkBattle" blocks with additional, similar blocks here.
    //
    //  You could create as many new state blocks, each activated according to
    //  the pattern of the above 12 blocks as time and "MissionStateNetworkBattle"
    //  advance, as you want. Within each block you have a lot of freedom
    //  to handle any one-time event you can imagine.
    //
    //  You could easily put new messages into the SystemMessagePanel and/or
    //  play or replay additional sound files or beeps, text-to-voice messages,
    //  or you could change the direction of travel of ships, destroy or repair
    //  objects, change Mumble channels, etc.
    //
    //  Now, after checking to see if we need to process any one-time "MissionState"
    //  events, we need to loop through all Mission aircraft and determine whether
    //  we should re-spawn any that have been destroyed. Also, preserve each aircraft
    //  type prior to arrival of the next InPacket.
    //
    for (MissionAircraftNumber = 1; MissionAircraftNumber <= 10; MissionAircraftNumber++) {
        //  Examine all 10 aircraft and consider replacing any that have exploded.
        if (ThreeDObjects[0]->explode > 500 * timestep) {
            //  Player's aircraft exploded more than 500 ms ago but has not been re-spawned and
            //  player hasn't pressed <ESC>.
            display((char*)"MissionNetworkBattle05::processtimer(): Player plane is dead and player has waited for program to exit. Invoking game_quit().", LOG_MOST);
            game_quit(); // Player plane is dead and player has waited for program to exit.
        }
        if (ThreeDObjects[0]->explode > 450 * timestep) { //  Player's aircraft exploded recently and he is almost out of time to press <ESC> before program exits.
            sound->setVolume(SOUND_BEEP1, 20); //  beep softly
            sound->play(SOUND_BEEP1, false);
        }
        if (!ThreeDObjects[MissionAircraftNumber]->active && (myrandom(10000) > 9990)) { //  Get here 0.5% of the time after any other plane explodes or crashes. Re-spawn destroyed aircraft.
            //
            //  This is a handy place to log some run-time diagnostics:
            //
            sprintf(DebugBuf, "MissionNetworkBattle05::ProcessTimer() re-spawning aircraft #%d.", MissionAircraftNumber);
            display(DebugBuf, LOG_MOST);
            //
            //  We may need some extra steps if this aircraft was flown
            //  by a "Sentient" player.
            //
            //  At this point we may want to wait for one or two packet
            //  periods since, due to network latency and the normal time
            //  between our OutPackets, the remote peer won't learn of
            //  his death instantly. Although the remote peer will stop
            //  sending packets once he knows he's dead, during the
            //  interim we must expect him to send one or two more
            //  packets as if he's still alive. If we generate and
            //  position our replacement bot before the remote peer stops
            //  sending packets, then the arrival of just one of those
            //  packets will cause our new bot to instantly leap to the
            //  XYZ position last occupied by the remote peer and
            //  continue from there. That's NOT what we want because
            //  it would make it look like our Victim didn't really die!
            //  Accordingly, we want to set the global "NetworkReceiveTimer"
            //  back to -400 ms to make it wait awhile, and we want to force
            //  the location of the re-spawned aircraft away from the
            //  prior position as follows:
            //
            if (ThreeDObjects[MissionAircraftNumber]->Sentient > 3) {//  Get here if the destroyed aircraft was piloted by a Sentient. Some extra steps are needed.
                GetNetworkApiPacket(); //  Throw away any InPacket that has already sneaked in....
                DiscardAnyInPacketsInQueue(); //  Remove any stale inpackets that might otherwise corrupt our respawning parameters
                InPacket.UdpObjXPosition -= 300; //  Make SURE no InPacket places replacement bot nearby.
                InPacket.UdpObjZPosition -= 300; //  Make SURE no InPacket places replacement bot nearby.
                NetworkReceiveTimer = -400; // Wait 400 ms before getting next InPacket
                // Preserve this aircraft type for later comparison to detect future changes:
                MissionNetworkBattle05PriorAircraft[MissionAircraftNumber] = ThreeDObjects[MissionAircraftNumber]->id;
            } //  End of special, additional timing and position logic for respawning a formerly "Sentient" player
         //
         //  Now take all steps necessary to re-spawn a new aircraft to replace
         //  the one that was destroyed:
         //
            ThreeDObjects[MissionAircraftNumber]->newinit(FIGHTER_A6M2, i + 1, 400); //  For this mission, bots are always in A6M2 "Zeroes".
            ThreeDObjects[MissionAircraftNumber]->id = FIGHTER_A6M2;
            ThreeDObjects[MissionAircraftNumber]->Durability = ThreeDObjects[MissionAircraftNumber]->maxDurability; //  Repair the new aircraft
            ThreeDObjects[MissionAircraftNumber]->immunity = 50 * timestep; //  Make this new aircraft invulnerable for the first few seconds
            ThreeDObjects[MissionAircraftNumber]->activate(); //  Activate that new aircraft
            ThreeDObjects[MissionAircraftNumber]->killed = false; //  Advertise that he is alive.
            ThreeDObjects[MissionAircraftNumber]->ammo = 1600; //  Bots get 1600 bullets each.
            ThreeDObjects[MissionAircraftNumber]->MyMissionPlayerNumber = MissionAircraftNumber; //  Make my player number globally visible
            //
            //  Move this new aircraft to a new, random position in the neighborhood, at least 200 units removed from prior position:
            //
            ThreeDObjects[MissionAircraftNumber]->tl->x = 200 + (myrandom(20) - 10);
            ThreeDObjects[MissionAircraftNumber]->tl->z = 200 + (myrandom(20) - 10);
            ThreeDObjects[MissionAircraftNumber]->tl->y = l->getHeight(ThreeDObjects[MissionAircraftNumber]->tl->x, ThreeDObjects[MissionAircraftNumber]->tl->z);
            ThreeDObjects[MissionAircraftNumber]->tl->y += 260 + (myrandom(80) - 40);
            ThreeDObjects[MissionAircraftNumber]->Sentient = 0; //  Reset the "Sentient" attribute of this new aircraft (all start out as bots)
            ThreeDObjects[MissionAircraftNumber]->thrustUp(); //  Give this bot some thrust
            ThreeDObjects[MissionAircraftNumber]->thrustUp(); //  And even a bit MORE thrust....
            //
            //  This is a good point to generate some run-time diagnostic reporting and update our logfile about this new aircraft:
            //
            sprintf(
                DebugBuf,
                "MissionNetworkBattle05::processTimer() spawning new aircraft %d at X=%f Y=%f Z=%f",
                MissionAircraftNumber,
                ThreeDObjects[MissionAircraftNumber]->tl->x,
                ThreeDObjects[MissionAircraftNumber]->tl->y,
                ThreeDObjects[MissionAircraftNumber]->tl->z
            );
            display(DebugBuf, LOG_MOST);

            //  Now make sure our new aircraft is NOT lugging any missiles or bombs:
            for (i = 0; i < missiletypes; i++) {
                ThreeDObjects[MissionAircraftNumber]->missiles[i] = 0;
            }
            //  This aircraft may still be in the process of exploding. We should stop that:
            ThreeDObjects[MissionAircraftNumber]->explode = 0; //  Stop the explosion.
            //  Bots behave best if they do NOT have a target:
            ThreeDObjects[MissionAircraftNumber]->target = NULL;
        } //  End of logic that replaces destroyed aircraft to keep the mission running for awhile.
    } //  End of loop that examines each mission aircraft to preserve their type and respawn those destroyed.
// Check to see if the player's aircraft has been destroyed:
    if (!ThreeDObjects[0]->active) { //  Get here whenever the player's aircraft has been destroyed.
        NetworkPlayerKilled = true;
        //  Stop this aircraft from generating any sounds:
        sound->stop(SOUND_PLANE1);
        sound->stop(SOUND_PLANE2);
        sound->stop(SOUND_WINDNOISE);
        WindNoiseOn = false;
    }
    if (MumbleTimeRemainingBeforeChannelReset < 1000) { //  Get here if it's been too long since our last Mumble command
        if (MumbleManagement) {
            event_CommsMacro17(); //  Reset player to proper Mumble TeamCast channel
            //  Now format a message to be displayed on the Cockpit's "SystemMessage Panel":
            sprintf(SystemMessageBufferA, "MUMBLE RESET TO TEAMCAST CHANNEL.");
            //  And inform cockpit.cpp to scroll our new message into view:
            NewSystemMessageNeedsScrolling = true;
            sound->setVolume(SOUND_BEEP1, 60); //@ Medium-volume beep
            sound->play(SOUND_BEEP1, false);
        } else {
            // Get here if user disabled LAC's management of Mumble channel changes.
            //
            // We cannot command Mumble to change channels, but we know that
            // all of the other team members have probably changed channels, and
            // it's a good idea to inform the player about that:
            //
            MumbleChannelPresumed = 95; //@ Signal cockpit Mumble Panel
            if (!(NetworkMode & 16)) { // Get here if Mumble vocalization is NOT disabled.
                //popen("espeak -p 10 -a 66  -s 160 \"Team is switching back to the TeamCast Channel.\"", "r");
            }
            sprintf(SystemMessageBufferA, "TEAM SWITCHING TO TEAMCAST CHANNEL.");
            //  And inform cockpit.cpp to scroll our new message into view:
            NewSystemMessageNeedsScrolling = true;
        }
        //  Now make sure we will do this again after a LONG time, to force
        //  everybody to monitor the appropriate Mumble channel periodically:
        MumbleTimeRemainingBeforeChannelReset = 10000000; //  10,000 seconds
    }
    if (MissionNetworkBattleRadarTimer > 100) { //  Get here 10 times /second.
        MissionNetworkBattleRadarTimer = 0; //  Reset this timer in preparation for next time...
        //
        //  This loop is a handy place for any special code that needs to
        //  be activated periodically for smooth motion, like moving
        //  carriers or testing to see if the operator has activated
        //  "Autopilot", etc:
        //
        AutoPilot(); //  If player has requested "AutoPilot", hold this altitude.
    } //  End loop that gets executed 10 times per second.
    if (MissionNetworkBattle05Timer > 1000) { //  Get here once every second.
        MissionNetworkBattle05Timer = 0;
        //
        //  This loop is a handy place to process events that don't need
        //  attention very often, like checking for "Fratricide" and gradually
        //  "aging" slow processes like "GoodMenuBehavior" and "Sentient"
        //  level.
        //
        if (OnTheGround) { //@ If landed ANYWHERE safely, attempt some minor repairs for the distressed pilot
            if (fplayer->realspeed < ((fplayer->StallSpeed) * 0.2)) { //@ Get here if ground speed is very low. Commence repairs, refuel, etc.
                if (fplayer->FuelLevel < 95) {
                    fplayer->FuelLevel = (0.25 + (fplayer->FuelLevel * 1.01));
                }
                if (fplayer->ammo < 1600) {
                    fplayer->ammo = (1.0 + (fplayer->ammo * 1.05));
                }
                if (fplayer->Durability < fplayer->maxDurability) {
                    fplayer->Durability *= 1.01;
                }
                if (fplayer->Durability > fplayer->maxDurability) {
                    fplayer->Durability = fplayer->maxDurability;
                }
            } else { //@ Get here if ground speed is still too high for ground services
                if (!fplayer->UndercarriageLevel) { //@ Get here if landing gear is not extended. Accumulate damage
                    fplayer->Durability *= 0.7;
                    fplayer->Durability -= ((fplayer->maxDurability) / 3.0); // Make sure it can go negative.
                }
            }
        }
        MilestoneCorrectionCheck();
        //
        // Check for recent Fratricide infractions:
        //
        if (FratricideShameFactor < 60000.0) { //  Get here if repentence is still possible
            FratricideShameFactor *= 0.80; //  Shame doesn't last forever...
            if (FratricideShameFactor <= 50) { //  Get here if it's been a long time since shameful activity
                FratricideShameFactor = 0; //  Erase any remaining shame....
            }
        }
        if (FratricideShameFactor > 50) { //  Get here if we should be ashamed of ourselves for fratricide
            IffOnOff = 0; // Punishment for recent, possibly innocent, fratricide attempt(s)
            //  Format a message for display on cockpit SystemMessagePanel:
            sprintf(SystemMessageBufferA, "IFF DEACTIVATED");
            //  Now set a flag to inform cockpit.cpp to scroll that message into view:
            NewSystemMessageNeedsScrolling = true;
        }
        if (FratricideShameFactor > 40000) { //  Get here if we should be ashamed of ourselves for fratricide
            IffOnOff = 0; // Punishment for recent, very serious fratricide attempt(s)
            RadarOnOff = 0; // More punishment
            HudOnOff = 0; // More punishment
            //  Format a message for display on cockpit SystemMessagePanel:
            sprintf(SystemMessageBufferA, "IFF, RADAR, & TACTICAL STATUS DEACTIVATED");
            //  Now set a flag to inform cockpit.cpp to scroll that message into view:
            NewSystemMessageNeedsScrolling = true;
        }
        //
        //  LAC's online missions use the value of "Sentient" to determine whether
        //  a mission aircraft is being flown by a human or if it is a bot. Higher
        //  numbers of "Sentient" mean, with increasing probability, that the
        //  corresponding aircraft has recently been flown by a human. Lower
        //  values of "Sentient" mean that it has been a long time since a human
        //  controlled the corresponding aircraft, so its recent movements have
        //  been driven by local "bot" logic". This is a handy place to diminish
        //  the value of "Sentient" for all aircraft so that it will eventually
        //  "expire" down toward zero. (Note that every aircraft in the mission is
        //  assigned a "Sentient" attribute, and that the value of "Sentient" is
        //  incremented by mission.cpp's "LoadVariablesFromNetworkApiPacket()"
        //  function every time a network InPacket is received for each aircraft.
        //  Those InPackets arrive 5 times per second from every nearby aircraft
        //  flown by a real, live human opponent, so this value of "Sentient" will
        //  generally be quite high. It only gets down below zero after the logic
        //  in this "once-per-second" loop slowly counts it down or "expires" it:
        //
        int AircraftCount;
        for (AircraftCount = 0; AircraftCount <= 10; AircraftCount++) { //  Examine every aircraft in the mission
            if (ThreeDObjects[AircraftCount]->Sentient > 1) { //  If this aircraft was flown by a Sentient recently
                ThreeDObjects[AircraftCount]->Sentient--; //  "Age" the Sentient value so it expires if not refreshed by more InPackets
            }
        }
        if (GoodMenuBehavior > 1) { //  GoodMenuBehavior dosen't last forever.
            GoodMenuBehavior--;
            if (GoodMenuBehavior < 2) {
                ReturnedToCombat = false; //  "ReturnedToCombat" signals other logic, possibly to guard against cheating.
            }
        }
        if (ReturnedToCombat && GoodMenuBehavior < 2) { //  Get here if the player previously pressed <ESC> then returned to flight, but has not yet been fully punished
            sound->play(SOUND_BEEP1, false);
            fplayer->Durability *= 0.05; //  Punish player with a lot of new damage
            fplayer->Durability--;
            sprintf(SystemMessageBufferA, "ABUSE OF <ESC> DETECTED.");
            NewSystemMessageNeedsScrolling = true;
            if (!(NetworkMode & 16)) { // Get here if the user has not disabled espeak
                //popen("espeak -p 130 -a 127 -s 165 \"Escape abuse detected.\"", "r");
            }
        }
        if (MissionIdNegotiationCount > 32) { //  Get here if we've been unable to negotiate unique value for "MyNetworkId" after 32 attempts
            sound->setVolume(SOUND_BEEP1, 20); //  and beep softly
            sound->play(SOUND_BEEP1, false);
            sprintf(SystemMessageBufferA, "THIS MISSION IS FULL. TRY ANOTHER.");
            NewSystemMessageNeedsScrolling = true;
        }
        RepairDamagedAirfields(); //  Good to do this once each second.
    } //  end of (MissionNetworkBattle05Timer > 1000)
    BattleDamageRiskTimer += DeltaTime;
    if ((BattleDamageRiskTimer > 5000) || (BattleDamageRiskTimer > (abs)(myrandom(131072)))) { //  Get here at least every 5 seconds, or possibly sooner by random chance
        BattleDamageRiskTimer = 0;
        CalcDamageRiskFromNearbyOpposition(); //  Determine if we suffer damage from enemy bombers or airfield
        ThreeDObjects[0]->Durability -= CalculatedDamageDueToCurrentRisk; //  Admit damage for risk we took.
        if (CalculatedDamageDueToCurrentRisk > 0) { //  Get here once every time we suffer new damage. Log it...
            sprintf(DebugBuf, "MissionNetworkBattle05::processTimer() fplayer->Durability is now %f.", fplayer->Durability);
            display(DebugBuf, LOG_MOST);
            if (fplayer->Durability < 0) { //  Get here if damage from locally managed airfields or bombers killed us.
                UpdateOnlineScoreLogFileWithCalculatedRisks(); //  Log it...
            }
        }
        CalculatedDamageDueToCurrentRisk = 0; //  After admitting that damage amount, clear it.
    }
    MissionTenSecondTimer += DeltaTime;
    if (MissionTenSecondTimer > 10000) { // Get here once every 10 seconds
        MissionTenSecondTimer = 0; // Will expire again in 10 more seconds
        //
        // Insert any mission-specific code here that might be appropriate for
        // attention just once every ten seconds:
        //
    }
    StaticObjectUpdateTimer += DeltaTime;
    if (StaticObjectUpdateTimer > 2000) { //  Get here when it's time to update network peers regarding any damaged airfields, etc.
        float TempFloat1;
        StaticObjectUpdateTimer = 0; //  Reset this timer for overflow in 2 more seconds.
        //
        //  Get here about once every 2 seconds.
        //
        //  Now check the "Durability" attribute of static 3d objects (like airfield facilities)
        //  to see if one can be found that has sustained battle damage. If so, invert the value
        //  of that Durability attribute (resulting in a negative number) so that other logic will
        //  transmit and interpret it as an absolute value instead of a relative damage value.
        //
        //  This is because LAC's "classic" missions use negative "Durability" numbers as a special
        //  signal to one another. A negative "Durability" indicates broadcast or reception of
        //  the true, current maintenance state of one of the mission resource facilities. Positive
        //  values, on the other hand, indicate a CHANGE in durability instead of the actual,
        //  correct, current value. From time to time, each LAC client transmits these negative
        //  numbers as "static updates" so that others can know if a mission object is more damaged
        //  than they thought. This block of logic, invoked about once in four seconds, checks all
        //  important mission resources to see if one is damaged. If so, once in 4 seconds, its value
        //  is converted into a negative number and transmitted to the server, which relays it out to
        //  all other nearby players. Other logic receives these negative numbers and, if a mission
        //  resource (like an airfield, battleship, artillery battery, aircraft carrier, or naval
        //  destroyer) was more damaged than previously known, the new value over-writes the old
        //  value. This is one of TWO means by which damage is propogated. The other means comes
        //  about more frequently: At least 5 times per second, every player sends an "OutPacket"
        //  to the server advertising his position, orientation, speed, and other details. Those
        //  packets can also "claim" to have damaged other players or mission objects. That's how
        //  you take and receive most battle damage.
        //
        //  Airfield damage is complicated, because you can "claim" to have damaged an airfield,
        //  but you are also making repairs to your own airfield at various rates. Accordingly,
        //  the exchange of network packets implements kind of an online "debate" about the
        //  true airfield strength. The ultimate strength results from a kind of a compromise
        //  among all of these claims and static updates. During all of these updates and
        //  exchanges, the recipient of any new airfield status information is always required
        //  to accept the WORST status, so if anybody knows of any NEW damage, not previously
        //  known to others, it prevails over any stale information.
        //
        StaticUpdateSwitcher++;
        if (StaticUpdateSwitcher == 1) { //  Get here if it's time to handle MissionObjectHqBlue
            if (ThreeDObjects[MissionObjectHqBlue]->active) { // Get here if this object has NOT been destroyed. Issue Static update of its status.
                TempFloat1 = ThreeDObjects[MissionObjectHqBlue]->Durability;
                TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
                ThreeDObjects[MissionObjectHqBlue]->DamageInNetQueue = TempFloat1;
            } else { //@ Get here if this MissionObject has been destroyed.
                // Inform all other players to drain its repair state down to 0.01:
                ThreeDObjects[MissionObjectHqBlue]->DamageInNetQueue = -0.01;
            }
        } else if (StaticUpdateSwitcher == 2) { //  Get here if it's time to handle MissionObjectHqRed
            if (ThreeDObjects[MissionObjectHqRed]->active) { // Get here if this object has NOT been destroyed. Issue Static update of its status.
                TempFloat1 = ThreeDObjects[MissionObjectHqRed]->Durability;
                TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
                ThreeDObjects[MissionObjectHqRed]->DamageInNetQueue = TempFloat1;
            } else { //@ Get here if this MissionObject has been destroyed.
                // Inform all other players to drain its repair state down to 0.01:
                ThreeDObjects[MissionObjectHqRed]->DamageInNetQueue = -0.01;
            }
        }
        if (StaticUpdateSwitcher > 6) { // Get here if we've exausted all of this mission's use instances of "StaticUpdateSwitcher". Reset it:
            StaticUpdateSwitcher = 0;
        }
    }

    //
    //  Update NetworkReceiveTimer and determine if it's now time
    //  to check for arrival of a new NetworkApi UDP packet:
    //
    NetworkReceiveTimer += dt;
    if (NetworkReceiveTimer > NetworkReceiveTimerInterval) { //  Get here every time NetworkReceiveTimer expires. Check for new InPacket:
        NetworkReceiveTimer = 0; //  Reset timer in preparation for next expiration.
        BytesReceived = GetNetworkApiPacket();
        if (BytesReceived == sizeof(LacUdpApiPacket)) { //  Get here if a new InPacket has arrived.
            //  Report this for run-time debugging and log it in log file:
            display((char*)"MissionNetworkBattle05 BytesReceived=", LOG_NET);
            sprintf(DebugBuf, "%i", BytesReceived);
            display(DebugBuf, LOG_NET);
            //  Now process that InPacket, extracting everything of value from it:
            LoadVariablesFromNetworkApiPacket(timer);
            if (MissionNetworkBattle05PriorAircraft[InPacket.UdpObjPlayerNumber] != InPacket.UdpObjVehicle) { //  Get here if this network peer is in a different type of aircraft
                //
                //  Now we must tell higher-level logic about the new aircraft type. This is
                //  associated as the "id" attribute of each mission object, and is
                //  tracked within the "ThreeDObjects[]" array as follows:
                //
                ThreeDObjects[InPacket.UdpObjPlayerNumber]->id = (int)InPacket.UdpObjVehicle;
                //
                //  And since this remote player is now in a different type of aircraft, we
                //  now need to reinitialize him as follows:
                //
                ThreeDObjects[InPacket.UdpObjPlayerNumber]->newinit(ThreeDObjects[InPacket.UdpObjPlayerNumber]->id, 0, 400);
            }
            //  Now preserve this InPacket's aircraft type for comparison with the next InPacket for this player:
            MissionNetworkBattle05PriorAircraft[InPacket.UdpObjPlayerNumber] = InPacket.UdpObjVehicle;
        } //  end "Get here if a new InPacket has arrived".
    } //  End of logic that handles expiration of NetworkReceiveTimer.
 //
 //  Update NetworkTransmitTimer and determine if it's now time
 //  to send a new NetworkApi UDP packet:
 //
    NetworkTransmitTimer += dt;
    if (NetworkTransmitTimer > NetworkTransmitTimerInterval && !NetworkPlayerKilled) { //  Get here if we're alive and it's time to send a new network API packet.
        NetworkTransmitTimer = 0;
        //  Find out if we've damaged anything since our last OutPacket:
        MissionNetworkBattle05RetrieveFirstDamageDescription();
        //  OK, now our OutPacket is ready. Transmit it:
        SendNetworkApiPacket();
    }
    //
    //  Check for mission-ending conditions. This mission ends when either RedTeam or BlueTeam
    //  destroys the opposing HQ airfield and the opposing Airfield #1:
    //
    static bool BlueHqAlive = true;
    static bool RedHqAlive = true;
    static bool BlueAirfield2Alive = true;
    static bool RedAirfield2Alive = true;
    static bool BlueTeamHasWonTheBattle = false;
    static bool RedTeamHasWonTheBattle = false;

    if (ThreeDObjects[MissionObjectHqBlue]->active) {
        BlueHqAlive = true;
    } else {
        BlueHqAlive = false;
    }

    if (ThreeDObjects[MissionObjectHqRed]->active) {
        RedHqAlive = true;
    } else {
        RedHqAlive = false;
    }

    if ((BlueHqAlive == false) && (BlueAirfield2Alive == false)) {
        BlueTeamHasWonTheBattle = true;
    }

    if ((RedHqAlive == false) && (RedAirfield2Alive == false)) {
        RedTeamHasWonTheBattle = true;
    }

    if (BlueTeamHasWonTheBattle || RedTeamHasWonTheBattle) { //  Get here if one of the two teams has won the battle
        static bool CountdownLatch1 = false;
        static bool CountdownLatch2 = false;
        MissionEndingTimer -= dt; //  Diminish by milliseconds
        if (MissionEndingTimer < -200 && CountdownLatch1 == false) { //  Get here 5 seconds after either team wins the battle.
            display((char*)"MissionNetworkBattle05::processtimer() Playing audio file MissionEndingInstrumental.wav", LOG_MOST);
            sound->play(SOUND_MISSIONENDINGINSTRUMENTAL, false);
            CountdownLatch1 = true; //  Prevent immediate restart of that audio file.
        }
        if (MissionEndingTimer < -1000 && CountdownLatch2 == false) { //  Get here 10 seconds after either team wins the battle.
            display((char*)"MissionNetworkBattle05::processtimer() Playing audio file MissionEndingIn15SecCountdown.wav", LOG_MOST);
            sound->play(SOUND_MISSIONENDINGIN15SECCOUNTDOWN, false);
            if (!(NetworkMode & 16)) {
                //popen("espeak -p 10 -a 66 -s 140 \"Mission ending in 15 seconds.\"", "r");
            }
            CountdownLatch2 = true; //  Prevent immediate restart of that audio file.
            MissionEndingTimer2 = 17000; //  Allow 17 seconds for next phase.
        }
    }
    if (MissionEndingTimer2) { //  Get here many times, but only after the "countdown warning audio" has begun playing.
        MissionEndingTimer2 -= dt; //  Diminish by milliseconds
        if (MissionEndingTimer2 < 1000) { //  Get here 16 seconds after "Countdown warning audio" started.
            //  All conditions to forcibly end mission are satisfied
            display((char*)"MissionNetworkBattle05::processtimer(): Mission ending now.", LOG_MOST);
            fplayer->Durability = -1.0; //  Signal Destruction of player and end the mission.
        }
    }
    return 0;
} //  end MissionNetworkBattle05::processtimer (Uint32 dt)




//
//  This function is no longer important. Earlier versions of LAC used this
//  function to insert prompting text at timed intervals, but more recent
//  missions haven't been using this file. Developers need not add anything
//  here.
//
void MissionNetworkBattle05::draw() {
    if (timer >= 0 && timer <= 50 * timestep) {
        font1->drawTextCentered(0, 12, -2, name, &textcolor);
    }
} //  end MissionNetworkBattle05::draw ()


//
//  MissionNetworkBattle05RetrieveFirstDamageDescription()
//
//  This function will search the "DamageInNetQueue" member among all mission objects.
//  If none of them have sustained any damage, it will set the new global integer
//  "MissionAircraftDamaged" to 0 and it will also set the new global float variable
//  "DamageToClaim" to  0.0 and return false. On the other hand, as soon as it finds
//  any object with damage, it copies the floating-point damage value into "DamageToClaim",
//  clears out the associated "DamageInNetQueue", stores the associated mission aircraft
//  number in "MissionAircraftDamaged", and returns true.
//
//  Mission designers: You probably don't want to change any of this logic!
//
bool MissionNetworkBattle05RetrieveFirstDamageDescription() {
    int Mission3dObject;
    display((char*)"MissionNetworkBattle05RetrieveFirstDamageDescription()", LOG_NET);

    for (Mission3dObject = 1; Mission3dObject <= 10; Mission3dObject++) { //  Loop through all mission aircraft EXCEPT ThreeDObjects[0], which represents the human player.
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
} //  end MissionNetworkBattle05RetrieveFirstDamageDescription()
