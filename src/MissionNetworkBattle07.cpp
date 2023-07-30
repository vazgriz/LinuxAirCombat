
//
//  This file implements "MissionNetworkBattle07".
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
//
//  Mission-wide variables:
//
//  The following set of floating-point XZ position variables
//  were captured during developmental run-time exercises with
//  code that is NOT used for routine mission play, and the
//  resulting, hard-coded position data is retrieved from these
//  mission-wide locations as needed whenever run-time activities
//  receive notice that the MissionCommander's computer has reached
//  any of the corresponding MissionChronoMilestones:
//
float RedTeamCarrier07XPositionAtMilestone1 =  272.105042;
float RedTeamCarrier07ZPositionAtMilestone1 =  -76.429771;
float RedTeamCarrier07PhiAtMilestone1 = 246.202545;
float RedTeamCarrier07XPositionAtMilestone2 =  260.318420;
float RedTeamCarrier07ZPositionAtMilestone2 =  -136.597427;
float RedTeamCarrier07PhiAtMilestone2 = 315.804138;
float RedTeamCarrier07XPositionAtMilestone3 =  266.714844;
float RedTeamCarrier07ZPositionAtMilestone3 =  -66.925232;
float RedTeamCarrier07PhiAtMilestone3 = 234.528992;
float RedTeamCarrier07XPositionAtMilestone4 =  198.952469;
float RedTeamCarrier07ZPositionAtMilestone4 =  -49.964832;
float RedTeamCarrier07PhiAtMilestone4 = 153.413849;
float RedTeamCarrier07XPositionAtMilestone5 =  171.683975;
float RedTeamCarrier07ZPositionAtMilestone5 =  -114.148750;
float RedTeamCarrier07PhiAtMilestone5 = 72.458717;
float RedTeamCarrier07XPositionAtMilestone6 =  231.078461;
float RedTeamCarrier07ZPositionAtMilestone6 =  -151.122269;
float RedTeamCarrier07PhiAtMilestone6 = 351.185089;
float RedTeamCarrier07XPositionAtMilestone7 =  276.633148;
float RedTeamCarrier07ZPositionAtMilestone7 =  -98.321991;
float RedTeamCarrier07PhiAtMilestone7 = 270.229950;
float RedTeamCarrier07XPositionAtMilestone8 =  230.909607;
float RedTeamCarrier07ZPositionAtMilestone8 =  -44.914185;
float RedTeamCarrier07PhiAtMilestone8 = 188.474792;
float RedTeamCarrier07XPositionAtMilestone9 =  171.672470;
float RedTeamCarrier07ZPositionAtMilestone9 =  -81.931099;
float RedTeamCarrier07PhiAtMilestone9 = 107.359657;
float RedTeamCarrier07XPositionAtMilestone10 = 198.961212;
float RedTeamCarrier07ZPositionAtMilestone10 = -146.105331;
float RedTeamCarrier07PhiAtMilestone10 = 26.405413;

float BlueTeamCarrier07XPositionAtMilestone1 =  -239.394958;
float BlueTeamCarrier07ZPositionAtMilestone1 =  -76.429771;
float BlueTeamCarrier07PhiAtMilestone1 = 246.202545;
float BlueTeamCarrier07XPositionAtMilestone2 =  -251.181580;
float BlueTeamCarrier07ZPositionAtMilestone2 =  -136.597427;
float BlueTeamCarrier07PhiAtMilestone2 = 315.804138;
float BlueTeamCarrier07XPositionAtMilestone3 =  -244.785156;
float BlueTeamCarrier07ZPositionAtMilestone3 =  -66.925232;
float BlueTeamCarrier07PhiAtMilestone3 = 234.528992;
float BlueTeamCarrier07XPositionAtMilestone4 =  -312.547516;
float BlueTeamCarrier07ZPositionAtMilestone4 =  -49.964832;
float BlueTeamCarrier07PhiAtMilestone4 = 153.413849;
float BlueTeamCarrier07XPositionAtMilestone5 =  -339.816040;
float BlueTeamCarrier07ZPositionAtMilestone5 =  -114.148750;
float BlueTeamCarrier07PhiAtMilestone5 = 72.458717;
float BlueTeamCarrier07XPositionAtMilestone6 =  -280.421539;
float BlueTeamCarrier07ZPositionAtMilestone6 =  -151.122269;
float BlueTeamCarrier07PhiAtMilestone6 = 351.185089;
float BlueTeamCarrier07XPositionAtMilestone7 =  -234.866852;
float BlueTeamCarrier07ZPositionAtMilestone7 =  -98.321991;
float BlueTeamCarrier07PhiAtMilestone7 = 270.229950;
float BlueTeamCarrier07XPositionAtMilestone8 =  -280.590393;
float BlueTeamCarrier07ZPositionAtMilestone8 =  -44.914185;
float BlueTeamCarrier07PhiAtMilestone8 = 188.474792;
float BlueTeamCarrier07XPositionAtMilestone9 =  -339.827545;
float BlueTeamCarrier07ZPositionAtMilestone9 =  -81.931099;
float BlueTeamCarrier07PhiAtMilestone9 = 107.359657;
float BlueTeamCarrier07XPositionAtMilestone10 = -312.538788;
float BlueTeamCarrier07ZPositionAtMilestone10 = -146.105331;
float BlueTeamCarrier07PhiAtMilestone10 = 26.405413;

float MissionObjectCarrierBlue1RudderDegreesM07 = 0.16;
float MissionObjectCarrierBlue1ThrustM07 = 0.15;
float MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
float MissionObjectCarrierRed1ThrustM07 = 0.15;

//
// Mission-specific code commences here:
//
MissionNetworkBattle07::MissionNetworkBattle07 ()
    {
    //
    //  Set up menu system to allow the player to read a description
    //  of the mission and select appropriate aircraft and
    //  munitions. Also open the necessary UDP sockets for
    //  outgoing and incoming traffic:
    //
    display ((char *)"MissionNetworkBattle07::MissionNetworkBattle07()", LOG_MOST);
    id = MISSION_NETWORKBATTLE07;
    if ((NetworkMode & 1)== 0)
       {
       strncpy (name, "WRONG NETWORK MODE!", 1024);
       strncpy (briefing, "LACCONFIG.TXT FILE MUST SET MODE 1, 3, OR 5 AND A SERVER ADDRESS.", 1024);
       }
    else
       {
       strncpy (name, "NETWORK MISSION 07 (BETA TEST)", 1024);
       strncpy (briefing, "UNFINISHED MISSION, STILL UNDER DEVELOPMENT.\n10 NETWORK PLAYERS IN 2 TEAMS. 1ST TEAM TO DESTROY 2 ENEMY BASES\nWINS. ISLAND TERRAIN. YOUR FUEL LEVEL IS LOW. LAND AND REFUEL\nIMMEDIATELY. BOTS REPLACE ANY OF THE ONLINE PLAYERS NOT PRESENT.", 1024);
       }
    selfighter [0] = DefaultAircraft;
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
    NetworkReceiveTimerInterval =  NetworkTransmitTimerInterval/ 12;
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
    if ((NetworkMode & 1) == 1)
      { //  ClientServer mode requires only a single UDP port, used both for sending and receiving
      display ((char *)"Attempting MissionNetworkBattle07 in ClientServer Network mode.", LOG_NET);
      if (OpenClientUdpSocket() == 0)
        { //  Get here if we were able to open the required ClientServer UDP Socket
        display ((char *)"MissionNetworkBattle07 ClientServer mode succesfully opened ClientUDP socket", LOG_NET);
        ConfigureClientUdpSocket();
        }
      else
        { //  Get here if we were unable to open the required ClientUDP socket
        display ((char *)"MissionNetworkBattle07 ClientServer mode unable to open ClientUDP socket.", LOG_NET);
        }
      }
    else
      {
      display ((char *)"Incorrect network mode configured in LacConfig.txt file.", LOG_ERROR);
      sound->setVolume (SOUND_BEEP1, 126);
      sound->play (SOUND_BEEP1, false);
      }
    //
    //  Now switch the user's "Mumble" application to the appropriate channel:
    //
    event_CommsMacro17();
    } //  end MissionNetworkBattle07::MissionNetworkBattle07 ()

void MissionNetworkBattle07::start ()
    {
    NoMissionHasYetCommenced = false;
    //
    //  This code gets executed only once per mission, as it starts up.
    //
    //  Initialize the landscape, place the player within it, and
    //  optimize cockpit instruments. Then load armament for all
    //  peers and spawn the AI aircraft for the mission.
    //
    //
    if (! (NetworkMode & 16))
       {
       popen ("espeak -p 10 -a 66  -s 160 \"Welcome to Net Mission 07! This is an experimental, new mission, still under development. At present it is bigger and more sophisticated than any of our three classic multi-player missions. Victory requires destruction of two opposing airfields.\"", "r");
       }
    MissionStateNetworkBattle = 0;
    display ((char *)"MissionNetworkBattle07::start()", LOG_MOST);
    NetworkPlayerKilled = false;
    //
    //  Make sure the value of "MyNetworkId" is appropriate, and change
    //  it to a value between 1 and 10 if necessary:
    //
    if ((MyNetworkId == 0) || (MyNetworkId > MaxPlayersInCurrentMission))
       { //  Get here if "MyNetworkId" has not yet been initialized or if its value is too high
       MyNetworkId = myrandom(MaxPlayersInCurrentMission); //  Randomize MyNetworkId
       MyNetworkId ++;
       }

    //
    //  Now configure the weather conditions for the mission:
    //
    int i, i2;
    day = 1;
    clouds = 2; //  1, 2, or 3.
    weather = WEATHER_SUNNY; //  Other weather available. Backspace past the underscore, then replace underscore for prompts.
    camera = 0; //  Place player in cockpit, looking forward
    sungamma = 25; //  Adjust brightness of sun and subtle shading, especially water textures. 25 is nice.
    heading = 220; //  Initial direction of travel

    //
    //  Now generate the landscape, hereafter named simply "l":
    //
    if (l != NULL)
        { //  If we already have landscape "l", delete it
        delete l;
        }
    //
    //  The next line of code can urge formation of any of various styles of landscape.
    //  The original template for this mission uses "LANDSCAPE_ALPINE_SEA" for this, but
    //  if you edit that keyword inside Codeblocks, it will suggest alternatives that
    //  will cause generation of desert, forest, arctic, or other landscapes.
    //
    l = new GLLandscape (space, LANDSCAPE_ALPINE_SEA, NULL);
    SeaLevel = -12.915; //  Calibrates altimeter to about "0" at sea level. Adjust as needed for different terrains.

    //
    //  Now use the landscape's "flatten()" function to landscape a long, flat runway, at landscape XY
    //  coordinates designated by the global floating-point variables "AirfieldXMin", "AirfieldYMin":
    //
    //  (Note that you will need to change the XY values of "AirfieldXMin" and "AirfieldYMin" in main.cpp
    //  if your landscape terrain forces relocation of your airfields.)
    //
    l->flatten (AirfieldXMin+28.0, AirfieldYMin+4, 29.2, 5); //  Flatten runway 29.2 units long, 5 units wide
    l->flatten (AirfieldXMin+46, AirfieldYMin+5, 7, 6); //  Flatten adjacent tarmac area 7 units long, 6 units wide
    //
    // Over-ride some defaults in the Mission Object Map, since this
    // mission will use more objects than any prior mission and therefore
    // will re-purpose some of the "Legacy" mission map objects:
    //
    MissionObjectBunkerBlue1 = 0;
    MissionObjectBunkerRed1 = 0;
    MissionObjectRadarHqRed = 0;
    MissionObjectRadarHqBlue = 0;
    MissionObjectHqBlue = 0;
    MissionObjectHqRed = 0;
    MissionObjectAirfieldBlue2 = 0;
    MissionObjectAirfieldRed2 = 0;
    MissionObjectCarrierBlue1 = 0;
    MissionObjectCarrierRed1 = 0;
    MissionObjectRadarBlue2 = 18;
    MissionObjectRadarRed2 = 19;
    //
    //  Now insert RedTeam "Airfield00" structures onto the landscape near the runway, treating those structures as if
    //  they were any other mission object so they can be damaged and/or destroyed. This will be the HQ
    //  airfield for the RedTeam, followed by other RedTeam objects:
    //
    MissionObjectHqRed = 29; // Update Mission Object Map
    int n = MissionObjectHqRed; //  RedTeam HQ airfield facilities
    //  Note that the Airfield is special in that logic in other source code files makes provisions to
    //  periodically transmit its status to the server.
    ThreeDObjects [n]->tl->x = AirfieldXMin + 46.5;
    ThreeDObjects [n]->tl->z = AirfieldYMin + 8;
    //  Airfield X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects [n]->target = ThreeDObjects [0]; //  Airfields don't need a "target".
    ThreeDObjects [n]->o = &model_Airfield00; //  Load the 3d model for generation of its appearance
    ThreeDObjects [n]->newinit (STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability; //  Set initial airfield Durability
    ThreeDObjects [n]->zoom = 6.0; //  Scale airfield to a nice, prominent size.

    MissionObjectRadarHqRed = 27; // Update Mission Object Map
    n = MissionObjectRadarHqRed; //  RedTeam Rectangular RADAR Reflector
    ThreeDObjects [n]->tl->x = AirfieldXMin + 41.0;
    ThreeDObjects [n]->tl->z = AirfieldYMin + 6.2;
    ThreeDObjects [n]->target = ThreeDObjects [0];
    ThreeDObjects [n]->o = &model_RadarReflector;
    ThreeDObjects [n]->newinit (STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects [n]->impact = 0.0;
    ThreeDObjects [n]->party = 1;
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability;
    ThreeDObjects [n]->zoom = 0.66;

    MissionObjectAirfieldRed2 = 23; // Update Mission Object Map
    n = MissionObjectAirfieldRed2; //  RedTeam airfield #2 facilities
    ThreeDObjects [n]->tl->x = 720;
    ThreeDObjects [n]->tl->z = AirfieldYMin + 8;
    //  Airfield X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects [n]->target = ThreeDObjects [0]; //  Airfields don't need a "target".
    ThreeDObjects [n]->o = &model_Airfield00; //  Load the 3d model for generation of its appearance
    ThreeDObjects [n]->newinit (STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability; //  Set initial airfield Durability
    ThreeDObjects [n]->zoom = 6.0; //  Scale airfield to a nice, prominent size.

    MissionObjectCarrierRed1 = 21; // Update Mission Object Map
    n = MissionObjectCarrierRed1; //  Carrier Red1
    ThreeDObjects [n]->tl->x = 185.0;
    ThreeDObjects [n]->tl->z = -60;
    //  Carrier X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects [n]->target = ThreeDObjects [0]; //  Carriers don't need a target.
    ThreeDObjects [n]->phi = 135;
    ThreeDObjects [n]->o = &model_carrier00;
    ThreeDObjects [n]->newinit (STATIC_CARRIER00, 0, 400);
    ThreeDObjects [n]->impact = 10.0; //  Determines damage carriers inflict when they collide with something.
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability; //  Makes the carriers hard to damage.
    ThreeDObjects [n]->zoom = 6.0; //  Scale carrier to a nice, prominent size.
    ThreeDObjects [n]->accx = 1.0;
    ThreeDObjects [n]->accz = 1.0;
    ThreeDObjects [n]->thrust = 1.0;
    ThreeDObjects [n]->realspeed = 1.0;

    MissionObjectRadarRed2 = 19; // Update Mission Object Map
    n = MissionObjectRadarRed2; //  RedTeam Rectangular RADAR Reflector
    ThreeDObjects [n]->tl->x = AirfieldXMin + 552.5;
    ThreeDObjects [n]->tl->z = AirfieldYMin + 6.2;
    ThreeDObjects [n]->target = ThreeDObjects [0];
    ThreeDObjects [n]->o = &model_RadarReflector;
    ThreeDObjects [n]->newinit (STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects [n]->impact = 0.0;
    ThreeDObjects [n]->party = 1;
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability;
    ThreeDObjects [n]->zoom = 0.66;




    //
    //  Now insert BlueTeam "Airfield00" structures onto the landscape near the runway, treating those structures as if
    //  they were a single fighter aircraft so they can be damaged and/or destroyed. This will be the HQ
    //  airfield for the BlueTeam, followed by other BlueTeam objects:
    //
    MissionObjectHqBlue = 28;  // Update Mission Object Map
    n = MissionObjectHqBlue; //  BlueTeam HQ airfield Facilities
    //  Note that the Airfield is special in that logic in other source code files makes provisions to
    //  periodically transmit its status to the server.
    ThreeDObjects [n]->tl->x = -304;
    ThreeDObjects [n]->tl->z = 11.0;
    //  Airfield X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects [n]->target = ThreeDObjects [0]; //  Airfields don't need a "target".
    ThreeDObjects [n]->o = &model_Airfield00;
    ThreeDObjects [n]->newinit (STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability;
    ThreeDObjects [n]->zoom = 6.0;

    MissionObjectRadarHqBlue = 26; // Update Mission Object Map
    n = MissionObjectRadarHqBlue; //  BlueTeam Rectangular RADAR Reflector. Carefully place its xz directly atop the airfield tower.
    ThreeDObjects [n]->tl->x = AirfieldXMin -470.58; //  -470.5 ends up with the tower just barely within the convex reflector.
    ThreeDObjects [n]->tl->z = AirfieldYMin + 6.25;
    ThreeDObjects [n]->target = ThreeDObjects [0];
    ThreeDObjects [n]->o = &model_RadarReflector;
    ThreeDObjects [n]->newinit (STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects [n]->impact = 0.0;
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability;
    ThreeDObjects [n]->zoom = 0.66;

    MissionObjectAirfieldBlue2 = 22;  // Update Mission Object Map
    n = MissionObjectAirfieldBlue2; //  BlueTeam airfield #2 Facilities
    ThreeDObjects [n]->tl->x = -815.5;
    ThreeDObjects [n]->tl->z = 11.0;
    //  Airfield X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects [n]->target = ThreeDObjects [0]; //  Airfields don't need a "target".
    ThreeDObjects [n]->o = &model_Airfield00;
    ThreeDObjects [n]->newinit (STATIC_AIRFIELD00, 0, 400);
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability;
    ThreeDObjects [n]->zoom = 6.0;

    MissionObjectCarrierBlue1 = 20; // Update Mission Object Map
    n = MissionObjectCarrierBlue1; //  Carrier Blue1
    ThreeDObjects [n]->tl->x = -326.0;
    ThreeDObjects [n]->tl->z = -60;
    //  Carrier X and Z positions have been set, but we must wait until later before we can set Y (altitude)...
    ThreeDObjects [n]->target = ThreeDObjects [0]; //  Carriers don't need a target.
    ThreeDObjects [n]->phi = 135;
    ThreeDObjects [n]->o = &model_carrier00;
    ThreeDObjects [n]->newinit (STATIC_CARRIER00, 0, 400);
    ThreeDObjects [n]->impact = 10.0; //  Determines damage carriers inflict when they collide with something.
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability; //  Makes the carriers hard to damage.
    ThreeDObjects [n]->zoom = 6.0; //  Scale carrier to a nice, prominent size.
    ThreeDObjects [n]->accx = 1.0;
    ThreeDObjects [n]->accz = 1.0;
    ThreeDObjects [n]->thrust = 1.0;
    ThreeDObjects [n]->realspeed = 1.0;

    MissionObjectRadarBlue2 = 18; // Update Mission Object Map
    n = MissionObjectRadarBlue2; //  BlueTeam Rectangular RADAR Reflector. Carefully place its xz directly atop the airfield tower.
    ThreeDObjects [n]->tl->x = AirfieldXMin -982.08; //  -470.5 ends up with the tower just barely within the convex reflector.
    ThreeDObjects [n]->tl->z = AirfieldYMin + 6.25;
    ThreeDObjects [n]->target = ThreeDObjects [0];
    ThreeDObjects [n]->o = &model_RadarReflector;
    ThreeDObjects [n]->newinit (STATIC_RADARREFLECTOR, 0, 400);
    ThreeDObjects [n]->impact = 0.0;
    ThreeDObjects [n]->Durability = ThreeDObjects [n]->maxDurability;
    ThreeDObjects [n]->zoom = 0.66;


    //
    //  Just a few "housekeeping details now, in preparation for running the mission:
    //
    playerInit ();
    PlayerAircraftType = fplayer->id;
    MissionRunning = false; //  Semaphore. Set on first pass through mission processtimer().
    fplayer->phi = 270; //  Player's initial direction of travel. (270 = straight West.)

    //
    //  This is a handy place to update our log file and generate a run-time status update:
    //
    display ((char *)"MissionNetworkBattle07::start setting PlayerAircraftType to: ", LOG_MOST);
    sprintf (DebugBuf, "%d", PlayerAircraftType);
    display (DebugBuf, LOG_MOST);

    //  Initialize all cockpit instruments to a stable starting point
    HudOnOff = 1;               //  Start out with HUD on.
    IffOnOff=0;                 //  Initialize IFF to off.
    MapViewOnOff = 0;           //  Make sure we have MapView off at start.
    RadarOnOff=0;               //  Initialize RADAR to off.
    RadarZoom = 1;              //  Set RADAR Range to 50 miles for this mission.
    ScreenFOVx = 1.0;           //  Reset view zoom to normal
    ScreenFOVy = 1.0;           //  Reset view zoom to normal
    //  Now optimize all cockpit instruments for this mission
    event_IffOnOff();           //  Turn on IFF for this mission.
    //@event_RadarOnOff();         //  Turn on RADAR for this mission
    if (!HudLadderBarsOnOff)
        { //  Turn on HUD Ladder bars for this mission
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
    for (i = 1; i <= 10; i ++)
        {
        //  Initialize opponents. Last argument to newinit(),
        //   although it is named "intelligence" in the code,
        //   determines their effectivness. Lower means more
        //   effective. 400 is a pretty good value. 1200 makes
        //   them quite dumb.
        //
        ThreeDObjects [i]->newinit (FIGHTER_F4F, 0, 400);
        // Preserve aircraft type for later comparison to detect changes.
        MissionNetworkBattle07PriorAircraft[i] = FIGHTER_F4F;
        //
        //  The "ThreeDObjects[]" array manages all of the active
        //  mission objects, and it contains an entry for each of
        //  the ten mission aircraft. Each of the ten entries is
        //  associated with a multitude of "attributes", each of
        //  which is accessed through a syntax like this: "->".
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
        ThreeDObjects [i]->target = NULL; //  Best if bots don't have a target...
        ThreeDObjects [i]->o = &model_figAO; //  Load the appropriate 3d model for appearance of bot
        //  Position fighters in scattered xz locations:
        ThreeDObjects [i]->tl->x = -200 + (myrandom(400) - 200) + (150 * SIN(i * 360 / 11));
        ThreeDObjects [i]->tl->z =  200 + (myrandom(400) - 200) + (150 * COS(i * 360 / 11));
        ThreeDObjects [i]->ammo = 1600; //  Bots start out with 1600 machine gun bullets
        ThreeDObjects [i]->Sentient = 0; //  All fighters are bots until a stream of InPackets reveals them to be Sentient.
        ThreeDObjects [i]->MyMissionPlayerNumber = i; //  Assign all 10 players their "MyMissionPlayerNumber" (used elsewhere)
        //
        //  This is another good place to update our diagnostic reporting and log with details about our bots:
        //
        sprintf (DebugBuf, "MissionNetworkBattle07::start() initializing Bot #%d", i);
        display (DebugBuf, LOG_MOST);
        sprintf (
                DebugBuf,
                "MissionNetworkBattle07::start() ThreeDObjects [i]->MyMissionPlayerNumber = %d",
                ThreeDObjects [i]->MyMissionPlayerNumber
                );
        display (DebugBuf, LOG_MOST);
        //
        //  Now make sure none of the mission aircraft is lugging missiles or bombs:
        //
        for (i2 = 0; i2 < missiletypes; i2 ++)
            { //  examine every "hardpoint" on each aircraft
            ThreeDObjects [i]->missiles [i2] = 0; //  Start out lugging no ordnance anywhere.
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
    //  Now give the player a "target" based on his team affiliation: Note that
    //  the logic can always refer to the player as "fplayer" and associated
    //  attributes can be accessed through syntax like "fplayer->" etc.
    //
    if (MyNetworkId%2)
       { //  Get here if player is a member of RedTeam
       fplayer->target = ThreeDObjects[MissionObjectHqBlue]; //  Target BlueTeam HQ
       }
    else
       { //  Get here if player is a member of BlueTeam
       fplayer->target = ThreeDObjects[MissionObjectHqRed]; //  Target RedTeam HQ
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
    if (fplayer->WepCapable)
       {
       ThrustReadiness += 200;
       }
    if (ThrustReadiness < 1000)
       {
       display ((char *)"Error. Selected Aircraft ThrustReadiness is insufficient.", LOG_MOST);
       game_quit(); // Airplane performance parameters didn't load properly.
       }
    } //  end MissionNetworkBattle07::start ()

int MissionNetworkBattle07::processtimer (Uint32 dt)
    {
    //  Get here every few milliseconds during this mission.
    //  Update all timers and initiate timer-dependent
    //  logic as necessary. This big function controls all of the
    //  action and dynamic elements of the mission. Everything
    //  that is animated or dynamic is controlled here, as the
    //  logic processes this function over and over again, as
    //  fast as it can go.
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
    //
    //  Now advance a few of the timers that will be used throughout
    //  this mission:
    //
    MissionNetworkBattle07Timer += DeltaTime; //  Advance by milliseconds
    MissionNetworkBattleRadarTimer += DeltaTime; //  Advance by milliseconds
    MumbleTimeRemainingBeforeChannelReset -= DeltaTime; //  This one counts down.
    if (!MissionRunning)
       { //  Get here if this is the FIRST pass through processtimer().
       //
       //  This block of code is executed only ONCE, at the beginning of the mission.
       //
       //  Set up player details that cannot be set up in mission start().
       DegradeFlightModelDueToOrdnanceLoad(); //  If lugging heavy weapons, diminish climb rate
       fplayer->FuelLevel = 6.0; //  Start the player out with just 6% fuel as this mission commences.
       if (fplayer->missiles [0] >= 4)
          { //  Get here if this is a medium or heavy bomber. Cut fuel enough to prevent reaching next airfield.
          fplayer->FuelLevel = 1.0;
          }
       if (fplayer->missiles [0] >= 12)
          { //  Get here if this is a heavy bomber. Cut fuel enough to prevent reaching next airfield.
          fplayer->FuelLevel = 0.5;
          }
       if (fplayer->party == 1)
          { //  Red team. Need to reverse compass direction to fly toward action.
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

       //  Player aircraft altitude at startup should be very low above ground.
       fplayer->tl->y = l->getHeight(AirfieldXMin, AirfieldYMin);
       fplayer->tl->y += 60.0; //  Raise player aircraft 60 units in "y"

       //  Airfield BlueHQ facilities altitude
       ThreeDObjects[MissionObjectRadarHqBlue]->tl->y = l->getExactHeight(AirfieldXMin -470.58, AirfieldYMin + 6.25); //  BlueTeam Radar Reflector
       ThreeDObjects[MissionObjectRadarHqBlue]->tl->y += 3.0;
       ThreeDObjects[MissionObjectHqBlue]->tl->y = l->getHeight(-304, 11);
       ThreeDObjects[MissionObjectHqBlue]->tl->y += 0.90; //  BlueTeam airfield facilities get raised 0.90 units

       ThreeDObjects[MissionObjectRadarBlue2]->tl->y = l->getExactHeight(AirfieldXMin -982.08, AirfieldYMin + 6.25); //  BlueTeam Radar Reflector
       ThreeDObjects[MissionObjectRadarBlue2]->tl->y += 3.0;
       ThreeDObjects[MissionObjectAirfieldBlue2]->tl->y = l->getExactHeight(-815.5, 11.0);
       ThreeDObjects[MissionObjectAirfieldBlue2]->tl->y += 0.90;

       //  Airfield RedHQ facilities altitude
       ThreeDObjects[MissionObjectRadarHqRed]->tl->y = l->getExactHeight(AirfieldXMin + 41.0, AirfieldXMin + 6.2); //  RedTeam Radar Reflector
       ThreeDObjects[MissionObjectRadarHqRed]->tl->y += 5.6;
       ThreeDObjects[MissionObjectHqRed]->tl->y = l->getHeight(AirfieldXMin + 46.5, AirfieldYMin+8);
       ThreeDObjects[MissionObjectHqRed]->tl->y +=0.90; //  RedTeam airfield facilities get raised 0.90 units.

       ThreeDObjects[MissionObjectRadarRed2]->tl->y = l->getExactHeight(AirfieldXMin + 552.5, AirfieldXMin + 6.2); //  RedTeam Radar Reflector
       ThreeDObjects[MissionObjectRadarRed2]->tl->y += 5.6;
       ThreeDObjects[MissionObjectAirfieldRed2]->tl->y = l->getHeight(720, AirfieldYMin + 8);
       ThreeDObjects[MissionObjectAirfieldRed2]->tl->y +=0.90; //  BlueTeam airfield facilities get raised 0.90 units

       //  BlueTeam Carrier altitude
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->y = l->getExactHeight(185, -60); // was -70
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->y += 1.2; //  Raise Carrier 1.2 units in "y"

       //  RedTeam Carrier altitude
       ThreeDObjects[MissionObjectCarrierRed1]->tl->y = l->getExactHeight(185, -60); // was -70
       ThreeDObjects[MissionObjectCarrierRed1]->tl->y += 1.2; //  Raise Carrier 1.2 units in "y"

       if (fplayer->missiles [0] >= 4 || fplayer->id == FIGHTER_D3A || fplayer->id == BOMBER_B5N)
          { //  Heavy bombers need more initial altitude and distance to avoid stalling and crashing...
          fplayer->tl->y += 60;
          sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() Heavy bomber launching. AirfieldRequested = %d", AirfieldRequested);
          display (DebugBuf, LOG_MOST);
          if (AirfieldRequested >= 3)
             { //  Get here if launching from the most remote airfield (in a heavy bomber).
             display ((char *)"MissionNetworkBattle07::processtimer() Increasing heavy bomber spawn altitude from Field 4", LOG_MOST);
             fplayer->tl->y += 320; // This is a bomber airfield. Give them extra altitude at start. 160 yields 9400 ft.
             fplayer->FuelLevel = 99; // Full fuel when willing to take off from most remote airfield.
             }
          }
       //  Make sure player starts out with landing gear and flaps retracted in any aircraft that permits retraction
       fplayer->UndercarriageLevel = 0;
       fplayer->FlapsLevel = 0;
       //fplayer->FlapsLevel = 1;
       for (i=1; i<=10; i++)
          { // Start bots at medium altitude
          ThreeDObjects[i]->tl->y += 150;
          }
       MissionRunning = true; //  For next pass, Signal that this startup loop has already been done.
       } //  End block of code used only ONCE, at very beginning of mission    //
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
    //  following audio messages or change the timing alloted
    //  for each.
    //
    //  All of this logic is dominated by the value of "timer",
    //  which triggers transitions among important values of
    //  "MissionStateNetworkBattle", which was just advanced
    //  by the prior line of code. It accumulates the time
    //  duration of the mission in milliseconds.
    //
    if (timer > 10000 && MissionStateNetworkBattle == 0 && NetworkTransmitTimer >= NetworkTransmitTimerInterval)
       { //  Only get here once, 10 seconds into the mission, as we've just begun transmitting OutPackets
       //  with an available setting for MyNetworkId. Vocalize "Red" or "Blue" according to player's
       //  team affiliation:
       if (MyNetworkId % 2)
          { //  Get here if MyNetworkId is an odd number
          //  Vocalize "RED"
          sound->setVolume (SOUND_RED, 126);
          sound->play (SOUND_RED, false);
          }
       else
          {
          //  Vocalize "BLUE"
          sound->setVolume (SOUND_BLUE, 126);
          sound->play (SOUND_BLUE, false);
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 1; //  This MissionState is done. Advance to next.
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 1 && (timer > PriorStateEndTimer +600))
       { //  Only get here once, 600 ms after MissionStateNetworkBattle
       //  advances to "1":
       //
       if (!RadarOnOff)
          {
          // If player has not already activated RADAR, to it for him:
          event_RadarOnOff();
          }
       //  Now vocalize the player's "MyNetworkId" value, a single
       //  digit between "1" and "10". This is part of the mission's
       //  audio greeting for the player during the first few seconds:
       switch (MyNetworkId)
          {
          case 1:
              {
              sound->setVolume (SOUND_DIGIT001, 126);
              sound->play (SOUND_DIGIT001, false);
              break;
              }
          case 2:
              {
              sound->setVolume (SOUND_DIGIT002, 126);
              sound->play (SOUND_DIGIT002, false);
              break;
              }
          case 3:
              {
              sound->setVolume (SOUND_DIGIT003, 126);
              sound->play (SOUND_DIGIT003, false);
              break;
              }
          case 4:
              {
              sound->setVolume (SOUND_DIGIT004, 126);
              sound->play (SOUND_DIGIT004, false);
              break;
              }
          case 5:
              {
              sound->setVolume (SOUND_DIGIT005, 126);
              sound->play (SOUND_DIGIT005, false);
              break;
              }
          case 6:
              {
              sound->setVolume (SOUND_DIGIT006, 126);
              sound->play (SOUND_DIGIT006, false);
              break;
              }
          case 7:
              {
              sound->setVolume (SOUND_DIGIT007, 126);
              sound->play (SOUND_DIGIT007, false);
              break;
              }
          case 8:
              {
              sound->setVolume (SOUND_DIGIT008, 126);
              sound->play (SOUND_DIGIT008, false);
              break;
              }
          case 9:
              {
              sound->setVolume (SOUND_DIGIT009, 126);
              sound->play (SOUND_DIGIT009, false);
              break;
              }
          case 10:
              {
              sound->setVolume (SOUND_DIGIT010, 126);
              sound->play (SOUND_DIGIT010, false);
              break;
              }
          default:
              {
              break;
              }
          }
        // Now, if we want to change heading or thrust of our ships as a consequence of
        // the mission advancing through this MissionState, we adjust "RudderDegrees"
        // and "Thrust" variables here:
        MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
        MissionObjectCarrierRed1ThrustM07 = 0.150;
        MissionStateNetworkBattle = 2; //  This MissionState is done. Advance to next.
        PriorStateEndTimer = timer;
        }
    if (MissionStateNetworkBattle == 2 && (timer > PriorStateEndTimer +1100))
       { //  Only get here once, 1100 sec after MissionStateNetworkBattle
       //  advances to "2":
       //
       //  This is a good place to degrade fuel, ammo, and ordnance according to
       //  the repair state of our HQ airfield, so that new players, just entering
       //  the battle in a late-war aircraft, will suffer degredation, but
       //  if they enter the battle in an early-war aircraft, no such degredation
       //  is asserted: Update cockpit "SystemMessagePanel" accordingly:
       //
       if (MyNetworkId%2)
          { //  RedTeam MissionNetworkBattle07
          if (ThreeDObjects[MissionObjectHqRed]->Durability < ThreeDObjects[MissionObjectHqRed]->maxDurability * 0.4)
             { //  Get here if player's RedTeam HQ is heavily damaged. Diminish fuel/armament for late-war aircraft.
             display ((char *)"MissionNetworkBattle07 state 2: Player's RedTeam HQ is heavily damaged.", LOG_MOST);
             if (fplayer->HistoricPeriod > 1)
                { //  Get here if the player is flying a late-war or postwar aircraft in this MissionNetworkBattle07
                fplayer->FuelLevel *= 0.2;
                fplayer->ammo /= 5;
                //
                //  Now diminish late-war aircraft bomb and rocket ordnance due to heavy HQ airfield damage:
                //
                int i2;
                for (i2 = 0; i2 < missiletypes; i2 ++)
                    {
                    if (i2 == 0)
                       { //  Rack0 = BOMB01
                       fplayer->missiles [i2] /= 3;
                       display ((char *)"MissionNetworkBattle07::processtimer() diminishing RedTeam late-war bomb load due to heavy HQ airfield damage", LOG_MOST);
                       }
                    if (i2 == 5)
                       { //  Rack5 = DFM Rockets
                       fplayer->missiles [i2] /=3;
                       display ((char *)"MissionNetworkBattle07::processtimer() diminishing RedTeam late-war rocket load due to heavy HQ airfield damage", LOG_MOST);
                       }
                    }
                }
             else
                { //  Get here if flying an early-war aircraft
                sprintf (SystemMessageBufferA, "WE HAVE FUEL/ORDNANCE FOR THAT AIRCRAFT.");
                NewSystemMessageNeedsScrolling = true;
                }
             }
          else
             { //  Get here if player's RedTeam HQ is NOT heavily damaged.
             display ((char *)"MissionNetworkBattle07 state 1: Player's RedTeam HQ is NOT heavily damaged.", LOG_MOST);
             sprintf (SystemMessageBufferA, "OUR HQ FACILITIES PERMIT FULL FUEL/ORDNANCE.");
             NewSystemMessageNeedsScrolling = true;
             }
          }
       else
          { //  BlueTeam MissionNetworkBattle07
          if (ThreeDObjects[MissionObjectHqBlue]->Durability < ThreeDObjects[MissionObjectHqBlue]->maxDurability * 0.4)
             { //  Get here if player's BlueTeam HQ is heavily damaged. Diminish fuel/armament for late-war aircraft.
             if (fplayer->HistoricPeriod > 1)
                { //  Get here if the player is flying a late-war or postwar aircraft in this MissionNetworkBattle07
                fplayer->FuelLevel *= 0.2;
                fplayer->ammo /= 5;
                //
                //  Now diminish late-war aircraft bomb and rocket ordnance due to heavy HQ airfield damage
                //
                int i2;
                for (i2 = 0; i2 < missiletypes; i2 ++)
                    {
                    if (i2 == 0)
                       { //  Rack0 = BOMB01
                       fplayer->missiles [i2] /= 3;
                       display ((char *)"MissionNetworkBattle07::processtimer() diminishing BlueTeam late-war bomb load due to heavy HQ airfield damage", LOG_MOST);
                       }
                    if (i2 == 5)
                       { //  Rack5 = DFM Rockets
                       fplayer->missiles [i2] /=3;
                       display ((char *)"MissionNetworkBattle07::processtimer() diminishing BlueTeam late-war rocket load due to heavy HQ airfield damage", LOG_MOST);
                       }
                    }
                }
             else
                { //  Get here if flying an early-war aircraft.
                sprintf (SystemMessageBufferA, "WE HAVE FUEL/ORDNANCE FOR THAT AIRCRAFT.");
                NewSystemMessageNeedsScrolling = true;
                }
             }
          else
             { //  Get here if player's BlueTeam HQ is NOT heavily damaged.
             sprintf (SystemMessageBufferA, "OUR HQ FACILITIES PERMIT FULL FUEL/ORDNANCE.");
             NewSystemMessageNeedsScrolling = true;
             }
          }
       sound->setVolume (SOUND_YOUHAVEAUTHORITYTOPROCEED, 126);
       sound->play (SOUND_YOUHAVEAUTHORITYTOPROCEED, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 3;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 3 && (timer > PriorStateEndTimer +2700))
       { //  Only get here once, 2700 ms after MissionStateNetworkBattle
       //  advances to "3":
       //  Vocalize "Weapons Free"
       sound->setVolume (SOUND_WEAPONSFREE, 126);
       sound->play (SOUND_WEAPONSFREE, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 4;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 4 && (timer > PriorStateEndTimer +3000))
       { //  Only get here once, 3000 ms after MissionStateNetworkBattle
       //  advances to "4":
       //
       //  Vocalize "Mission telemetry available from LAC server at"
       sound->setVolume (SOUND_BEEP1, 20);
       sound->play (SOUND_BEEP1, false);
       sprintf (SystemMessageBufferA, "LAC SERVER IS AT LACSERVER2.LINUXAIRCOMBAT.COM");
       NewSystemMessageNeedsScrolling = true;
       sound->setVolume (SOUND_MISSIONTELEMETRYAVAILABLEFROMLACSERVERAT, 126);
       sound->play (SOUND_MISSIONTELEMETRYAVAILABLEFROMLACSERVERAT, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 5;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 5 && (timer > PriorStateEndTimer +3300))
       { //  Only get here once, 3300 sec after MissionStateNetworkBattle
       //  advances to "5":
       //  Vocalize "Linux Air Combat dot com"
       sound->setVolume (SOUND_BOSENETDOTNODASHIPDOTBIZ, 126);
       sound->play (SOUND_BOSENETDOTNODASHIPDOTBIZ, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 6;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 6 && (timer > PriorStateEndTimer +3700))
       { //  Only get here once, 3700 ms after MissionStateNetworkBattle
       //  advances to "6":
       //
       //  Vocalize "Global assignment audio at"
       sound->setVolume (SOUND_BEEP1, 20);
       sound->play (SOUND_BEEP1, false);
       sprintf (SystemMessageBufferA, "TUNE MUMBLE RADIO: LACSERVER2.LINUXAIRCOMBAT.COM");
       NewSystemMessageNeedsScrolling = true;
       sound->setVolume (SOUND_GLOBALASSIGNMENTAUDIOATMUMBLE, 126);
       sound->play (SOUND_GLOBALASSIGNMENTAUDIOATMUMBLE, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 7;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 7 && (timer > PriorStateEndTimer +2500))
       { //  Only get here once, 2500 ms after MissionStateNetworkBattle
       //  advances to "7":
       //
       //  Vocalize "Linux Air Combat.com"
       sound->setVolume (SOUND_BOSENETDOTNODASHIPDOTBIZ, 126);
       sound->play (SOUND_BOSENETDOTNODASHIPDOTBIZ, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 8;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 8 && (timer > PriorStateEndTimer +3500))
       { //  Only get here once, 3500 ms after MissionStateNetworkBattle
       //  advances to "8":
       //
       //  Vocalize "Mission comms on channel"
       sound->setVolume (SOUND_MISSIONCOMMSONCHANNEL, 126);
       sound->play (SOUND_MISSIONCOMMSONCHANNEL, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 9;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 9 && (timer > PriorStateEndTimer +2000))
       { //  Only get here once, 2000 ms after MissionStateNetworkBattle
       //  advances to "9":
       //
       //  Vocalize "Linux Air Combat"
       sound->setVolume (SOUND_LINUXAIRCOMBAT, 126);
       sound->play (SOUND_LINUXAIRCOMBAT, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 10;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 10 && (timer > PriorStateEndTimer +1500))
       { //  Only get here once, 1500 ms after MissionStateNetworkBattle
       //  advances to "10":
       //
       //  Vocalize "MissionNetworkBattle01"
       sound->setVolume (SOUND_MISSIONNETWORKBATTLE01, 126);
       sound->play (SOUND_MISSIONNETWORKBATTLE01, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 11;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 11 && (timer > PriorStateEndTimer +2500))
       { //  Only get here once, 2500 ms after MissionStateNetworkBattle
       //  advances to "11":
       //
       //  Vocalize "Squad comms on subchannel"
       sound->setVolume (SOUND_SQUADCOMMSONSUBCHANNEL, 126);
       sound->play (SOUND_SQUADCOMMSONSUBCHANNEL, false);
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 12;
       PriorStateEndTimer = timer;
       }
    if (MissionStateNetworkBattle == 12 && (timer > PriorStateEndTimer +2500))
       { //  Only get here once, 2500 ms after MissionStateNetworkBattle
       //  advances to "12":
       //
       //  Vocalize "Red" or "Blue" according to player's team affiliation:
       sound->setVolume (SOUND_RED, 126);
       if(MyNetworkId % 2)
          {
          sound->setVolume (SOUND_RED, 126);
          sound->play (SOUND_RED, false);
          }
       else
          {
          sound->setVolume (SOUND_BLUE, 126);
          sound->play (SOUND_BLUE, false);
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 13;
       PriorStateEndTimer = timer;
       }

    //
    //  Mission Designers: If you want to insert additional, timed, one-time steps
    //  into your mission, you can continue the pattern of the 12 prior
    //  "MissionStateNetworkBattle" blocks with additional, similar blocks here.
    //
    //  You could create as many new code blocks, each activated according to
    //  the pattern of the above 12 blocks as time and "MissionStateNetworkBattle"
    //  advance, as you want. Within each block you have a lot of freedom
    //  to handle any one-time event you can imagine.
    //
    //  You could easily put new messages into the SystemMessagePanel and/or
    //  play or replay additional sound files or beeps, or you could change
    //  the direction of travel of ships, destroy or repair objects, change
    //  Mumble channels, etc.
    //
    if (MissionStateNetworkBattle == 13 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "13":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66  -s 140 \"Mission State = 14.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 14;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 14 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "14":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66  -s 140 \"Mission State = 15.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 15;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 15 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "15":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone1;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone1;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone1;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone1;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone1;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone1;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 16;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "15" as our mission
          // state, implying "ChronoMilestone 1".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC11", 16);
          MissionChronoMilestone = 1;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 16 and I am the MissionCommander. Transmitting Milestone 1.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 16 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 1. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #1 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #1.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone1 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone1 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone1 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone1 = %f", RedTeamCarrier07XPositionAtMilestone1);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone1 = %f", RedTeamCarrier07ZPositionAtMilestone1);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone1 = %f", RedTeamCarrier07PhiAtMilestone1);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       } // End MissionState 15 logic

    if (MissionStateNetworkBattle == 16 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "16":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66  -s 140 \"Mission State = 17.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 17;
       PriorStateEndTimer = timer;
       } // End MissionState 16 logic

    if (MissionStateNetworkBattle == 17 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "17":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66  -s 140 \"Mission State = 18.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 18;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 18 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "18":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66  -s 140 \"Mission State = 19.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 19;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 19 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "19":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66  -s 140 \"Mission State = 20.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 20;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 20 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "20":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone2;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone2;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone2;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone2;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone2;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone2;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 21;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "20" as our mission
          // state, implying "ChronoMilestone 2".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC22", 16);
          MissionChronoMilestone = 2;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 21 and I am the MissionCommander. Transmitting Milestone 2.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 21 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 2. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #2 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #2.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone2 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone2 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone2 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone2 = %f", RedTeamCarrier07XPositionAtMilestone2);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone2 = %f", RedTeamCarrier07ZPositionAtMilestone2);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone2 = %f", RedTeamCarrier07PhiAtMilestone2);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 21 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "21":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 22.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 22;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 22 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "22":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 23.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 23;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 23 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "23":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 24.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 24;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 24 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "24":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 25.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 25;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 25 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "25":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 26.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 26;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 26 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "26":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 27.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 27;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 27 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "27":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 28.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle =28;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 28 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "28":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 29.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 29;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 29 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "29":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 30.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 30;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 30 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "30":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 31.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 31;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 31 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "31":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 32.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 32;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 32 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "32":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 33.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 33;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 33 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "33":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 34.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 34;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 34 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "34":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 35.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 35;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 35 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "35":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 36.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 36;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 36 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "36":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 37.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 37;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 37 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "37":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 38.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 38;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 38 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "38":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 39.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 39;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 39 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "39":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 40.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 40;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       }

    if (MissionStateNetworkBattle == 40 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "40":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone3;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone3;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone3;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone3;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone3;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone3;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 41;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "40" as our mission
          // state, implying "ChronoMilestone 3".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC33", 16);
          MissionChronoMilestone = 3;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 41 and I am the MissionCommander. Transmitting Milestone 3.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 41 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 3. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #3 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #3.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone3 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone3 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone3 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone3 = %f", RedTeamCarrier07XPositionAtMilestone3);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone3 = %f", RedTeamCarrier07ZPositionAtMilestone3);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone3 = %f", RedTeamCarrier07PhiAtMilestone3);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 41 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "41":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 42.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 42;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 42 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "42":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 43.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 43;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 43 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "43":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 44.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 44;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 44 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "44":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 45.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 45;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 45 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "45":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 46.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 46;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 46 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "46":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 47.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 47;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 47 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "47":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 48.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 48;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 48 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "48":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 49.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 49;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 49 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "49":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 50.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 50;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 50 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "50":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 51.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 51;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 51 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "51":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 52.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 52;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 52 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "52":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 53.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 53;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 53 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "53":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 54.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 54;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 54 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "54":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 55.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 55;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 55 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "55":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 56.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 56;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 56 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "56":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 57.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 57;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 57 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "57":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 58.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 58;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 58 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "58":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 59.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 59;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 59 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "59":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 60.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 60;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 60 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "60":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone4;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone4;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone4;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone4;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone4;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone4;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 61;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "60" as our mission
          // state, implying "ChronoMilestone 4".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC44", 16);
          MissionChronoMilestone = 4;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 61 and I am the MissionCommander. Transmitting Milestone 4.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 61 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 4. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #4 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #4.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone4 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone4 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone4 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone4 = %f", RedTeamCarrier07XPositionAtMilestone4);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone4 = %f", RedTeamCarrier07ZPositionAtMilestone4);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone4 = %f", RedTeamCarrier07PhiAtMilestone4);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 61 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "61":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 62.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 62;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 62 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "62":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 63.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 63;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 63 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "63":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 64.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 64;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 64 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "64":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 65.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 65;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 65 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "65":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 66.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 66;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 66 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "66":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 67.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 67;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 67 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "67":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 68.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 68;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 68 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "68":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 69.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 69;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 69 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "69":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 70.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 70;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 70 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "70":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State =71.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 71;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 71 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "71":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 72.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 72;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 72 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "72":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 73.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 73;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 73 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "73":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 74.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 74;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 74 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "74":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 75.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 75;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 75 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "75":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 76.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 76;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 76 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "76":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 77.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 77;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 77 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "77":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 78.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 78;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 78 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "78":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 79.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 79;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 79 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "79":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 80.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 80;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 80 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "80":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone5;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone5;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone5;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone5;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone5;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone5;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 81;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "80" as our mission
          // state, implying "ChronoMilestone 5".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC55", 16);
          MissionChronoMilestone = 5;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 81 and I am the MissionCommander. Transmitting Milestone 5.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 81 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 5. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #5 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #5.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone5 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone5 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone5 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone5 = %f", RedTeamCarrier07XPositionAtMilestone5);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone5 = %f", RedTeamCarrier07ZPositionAtMilestone5);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone5 = %f", RedTeamCarrier07PhiAtMilestone5);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 81 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "81":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 82.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 82;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 82 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "82":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 83.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 83;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 83 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "83":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 84.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 84;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 84 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "84":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 85.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 85;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 85 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "85":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 86.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 86;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 86 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "86":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 87.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 87;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 87 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "87":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 88.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 88;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 88 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "88":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 89.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 89;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 89 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "89":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 90.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 90;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 90 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "90":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 91.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 91;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 91 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "91":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 92.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 92;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 92 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "92":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 93.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 93;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 93 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "93":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 94.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 94;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 94 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "94":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 95.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 95;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 95 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "95":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 96.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 96;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 96 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "96":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 97.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 97;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 97 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "97":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 98.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 98;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 98 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "98":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 99.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 99;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 99 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "99":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 100.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 100;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 100 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "100":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone6;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone6;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone6;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone6;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone6;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone6;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 101;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "100" as our mission
          // state, implying "ChronoMilestone 6".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC66", 16);
          MissionChronoMilestone = 6;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 101 and I am the MissionCommander. Transmitting Milestone 6.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 101 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 6. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #6 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #6.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone6 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone6 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone6 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone6 = %f", RedTeamCarrier07XPositionAtMilestone6);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone6 = %f", RedTeamCarrier07ZPositionAtMilestone6);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone6 = %f", RedTeamCarrier07PhiAtMilestone6);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 101 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "101":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 102.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 102;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 102 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "102":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 103.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 103;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 103 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "103":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 104.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 104;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 104 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "104":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 105.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 105;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 105 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "105":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 106.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 106;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 106 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "106":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 107.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 107;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 107 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "107":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 108.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 108;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 108 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "108":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 109.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 109;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 109 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "109":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 110.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 110;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 110 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "110":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 111.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 111;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 111 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "111":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 112.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 112;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 112 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "112":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 113.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 113;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 113 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "113":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 114.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 114;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 114 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "114":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 115.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 115;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 115 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "115":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 116.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 116;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 116 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "116":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 117.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 117;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 117 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "117":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 118.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 118;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 118 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "118":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 119.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 119;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 119 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "119":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 120.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 120;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 120 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "120":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone7;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone7;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone7;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone7;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone7;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone7;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 121;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "120" as our mission
          // state, implying "ChronoMilestone 7".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC77", 16);
          MissionChronoMilestone = 7;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 121 and I am the MissionCommander. Transmitting Milestone 7.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 121 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 7. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #7 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #7.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone7 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone7 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone7 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone7 = %f", RedTeamCarrier07XPositionAtMilestone7);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone7 = %f", RedTeamCarrier07ZPositionAtMilestone7);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone7 = %f", RedTeamCarrier07PhiAtMilestone7);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 121 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "121":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 122.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 122;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 122 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "122":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 123.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 123;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 123 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "123":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 124.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 124;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 124 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "124":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 125.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 125;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 125 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "125":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 126.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 126;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 126 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "126":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 127.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 127;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 127 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "127":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 128.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 128;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 128 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "128":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 129.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 129;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 129 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "129":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 130.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 130;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 130 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "130":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 131.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 131;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 131 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "131":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 132.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 132;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 132 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "132":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 133.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 133;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 133 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "133":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 134.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 134;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 134 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "134":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 135.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 135;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 135 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "135":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 136.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 136;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 136 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "136":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 137.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 137;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 137 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "137":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 138.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 138;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 138 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "138":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 139.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 139;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 139 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "139":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 140.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 140;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 140 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "140":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone8;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone8;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone8;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone8;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone8;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone8;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 141;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "140" as our mission
          // state, implying "ChronoMilestone 8".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC88", 16);
          MissionChronoMilestone = 8;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 141 and I am the MissionCommander. Transmitting Milestone 8.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 141 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 8. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #8 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #8.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone8 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone8 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone8 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone8 = %f", RedTeamCarrier07XPositionAtMilestone8);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone8 = %f", RedTeamCarrier07ZPositionAtMilestone8);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone8 = %f", RedTeamCarrier07PhiAtMilestone8);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 141 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "141":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 142.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 142;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 142 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "142":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 143.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 143;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 143 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "143":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 144.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 144;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 144 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "144":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 145.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 145;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 145 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "145":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 146.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 146;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 146 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "146":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 147.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 147;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 147 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "147":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 148.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 148;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 148 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "148":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 149.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 149;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 149 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "149":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 150.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 150;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 150 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "150":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 151.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 151;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectAirfieldRed2();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 151 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "151":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 152.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 152;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 152 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "152":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 153.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 153;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 153 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "153":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 154.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 154;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 154 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "154":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 155.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 155;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 155 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "155":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 156.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 156;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 156 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "156":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 157.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 157;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 157 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "157":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 158.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 158;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 158 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "158":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 159.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 159;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 159 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "159":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 160.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 160;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 160 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "160":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone9;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone9;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone9;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone9;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone9;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone9;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 161;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "160" as our mission
          // state, implying "ChronoMilestone 9".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC99", 16);
          MissionChronoMilestone = 9;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 161 and I am the MissionCommander. Transmitting Milestone 9.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 161 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 9. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #9 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #9.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone9 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone9 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone9 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone9 = %f", RedTeamCarrier07XPositionAtMilestone9);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone9 = %f", RedTeamCarrier07ZPositionAtMilestone9);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone9 = %f", RedTeamCarrier07PhiAtMilestone9);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 161 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "161":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 162.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 162;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 162 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "162":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 163.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 163;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 163 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "163":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 164.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 164;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 164 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "164":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 165.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 165;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 165 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "165":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 166.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 166;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 166 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "166":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 167.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 167;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 167 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "167":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 168.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 168;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 168 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "168":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 169.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 169;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 169 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "169":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 170.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 170;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 170 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "170":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 171.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 171;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectCarrierRed1();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 171 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "171":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 172.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 172;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 172 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "172":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 173.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 173;
       PriorStateEndTimer = timer;
       // TestDamageMissionObjectHqRed();
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer(): MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       }

    if (MissionStateNetworkBattle == 173 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "173":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 174.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 174;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 174 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "174":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 175.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 175;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 175 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "175":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 176.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 176;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 176 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "176":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 177.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 177;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 177 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "177":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 178.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 178;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 178 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "178":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 179.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 179;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 179 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "179":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 180.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 180;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 180 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "180":
       //
       //
       // We choose this MissionState as a MissionChronoMilestone.
       //
       // Update position and orientation of all mobile, strategic mission objects
       // according to our hard-coded mission logistics:
       //
       ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone10;
       ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone10;
       ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone10;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone10;
       ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone10;
       ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone10;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()a: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       MissionStateNetworkBattle = 181;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()aa: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf, LOG_MOST);
       if (MissionCommander == MyNetworkId)
          { // Get here if the current player is the MissionCommander
          //
          // Now, since we are the MissionCommander, we transmit
          // the current position and status of mobile or changing
          // objects to other players.
          //
          // This is done by sending the following Morse Radio
          // command string referencing "180" as our mission
          // state, implying "ChronoMilestone 10".
          //
          strncpy (&MorseCharacterOut[0], "CCCCCCCCCC00", 16);
          MissionChronoMilestone = 10;
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 181 and I am the MissionCommander. Transmitting Milestone 10.\"", "r");
             }
          }
        else
          {
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 181 and I am Not the MissionCommander.\"", "r");
             }
          }
       //
       // FOR EARLY DEVELOPMENT WORK, It is necessary to capture the exact position of moving
       // aircraft carriers (and any other moving objects) as soon as the mission advances to
       // MissionChronoMilestone 10. We do that during development here, and later on we will
       // use the resulting XZ positions as hard-coded data upon receipt of MissionChronoMilestone
       // #10 messages from a MissionCommander.
       //

       /*
       * The following eleven lines of code may or may not be commented out because they were only used during
       * development use, to capture the referenced values at the moment of MissionChronoMilestone #10.
       * We are retaining the commented-out code block for future reference, but NOT for ordinary
       * use:
       RedTeamCarrier07XPositionAtMilestone10 = ThreeDObjects[MissionObjectCarrierRed1]->tl->x;
       RedTeamCarrier07ZPositionAtMilestone10 = ThreeDObjects[MissionObjectCarrierRed1]->tl->z;
       RedTeamCarrier07PhiAtMilestone10 = ThreeDObjects[MissionObjectCarrierRed1]->phi;
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07XPositionAtMilestone10 = %f", RedTeamCarrier07XPositionAtMilestone10);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07ZPositionAtMilestone10 = %f", RedTeamCarrier07ZPositionAtMilestone10);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer() RedTeamCarrier07PhiAtMilestone10 = %f", RedTeamCarrier07PhiAtMilestone10);
       display (DebugBuf, LOG_MOST);
       sprintf (DebugBuf, "MissionNetworkBattle07::processtimer()b: MissionStateNetworkBattle = %d", MissionStateNetworkBattle);
       display (DebugBuf,LOG_MOST); */
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 181 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "181":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 182.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 182;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 182 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "182":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 183.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 183;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 183 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "183":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 184.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 184;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 184 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "184":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 185.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 185;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 185 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "185":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 186.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 186;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 186 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "186":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 187.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 187;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 187 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "187":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 188.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 188;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 188 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "188":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 189.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 189;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 189 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "189":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 190.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 190;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 190 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "190":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 191.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 191;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 191 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "191":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 192.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 192;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 192 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "192":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 193.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 193;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 193 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "193":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 194.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 194;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 194 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "194":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 195.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 195;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 195 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "195":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 196.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 196;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 196 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "196":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 197.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 197;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 197 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "197":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 198.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 198;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 198 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "198":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 199.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 199;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 199 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "199":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 200.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 200;
       PriorStateEndTimer = timer;
       }

    if (MissionStateNetworkBattle == 200 && (timer > PriorStateEndTimer +10000))
       { //  Only get here once, 10000 ms after MissionStateNetworkBattle
       //  advances to "200":
       //
       if (! (NetworkMode & 16))
          {
          popen ("espeak -p 10 -a 66 -s 140 \"Mission State = 201.\"", "r");
          }
       // Now, if we want to change heading or thrust of our ships as a consequence of
       // the mission advancing through this MissionState, we adjust "RudderDegrees"
       // and "Thrust" variables here:
       MissionObjectCarrierRed1RudderDegreesM07 =  0.16;
       MissionObjectCarrierRed1ThrustM07 = 0.150;
       MissionStateNetworkBattle = 59; // Loop back to a prior state with similar positioning
       MissionChronoMilestone = 4; // Synchronize at prior MissionChronoMilestone with similar positioning
       PriorStateEndTimer = timer;
       }


    //
    //  Now, after checking to see if we need to process any one-time "MissionState"
    //  events, we need to loop through all Mission aircraft and determine whether
    //  we should re-spawn any that have been destroyed. Also, preserve each aircraft
    //  type prior to arrival of the next InPacket.
    //
    for (MissionAircraftNumber=1; MissionAircraftNumber <= 10; MissionAircraftNumber ++)
        {
        //  Examine all 10 aircraft and consider replacing any that have exploded.
        if (ThreeDObjects [0]->explode > 500 * timestep)
           {
           //  Player's aircraft exploded more than 500 ms ago but has not been re-spawned and
           //  player hasn't pressed <ESC>.
           display ((char *)"MissionNetworkBattle07::processtimer(): Player plane is dead and player has waited for program to exit. Invoking game_quit().", LOG_MOST);
           game_quit (); // Player plane is dead and player has waited for program to exit.
           }
        if (ThreeDObjects [0]->explode > 450 * timestep)
           { //  Player's aircraft exploded recently and he is almost out of time to press <ESC> before program exits.
           sound->setVolume (SOUND_BEEP1, 20); //  beep softly
           sound->play (SOUND_BEEP1, false);
           }
        if (!ThreeDObjects[MissionAircraftNumber]->active && (myrandom(10000)>9990))
            { //  Get here 0.5% of the time after any other plane explodes or crashes. Re-spawn destroyed aircraft.
            //
            //  This is a handy place to log some run-time diagnostics:
            //
            sprintf (DebugBuf, "MissionNetworkBattle07::ProcessTimer() re-spawning aircraft #%d.", MissionAircraftNumber);
            display (DebugBuf, LOG_MOST);
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
            //  position our new bot before the remote peer stops
            //  sending packets, then the arrival of just one of those
            //  packets will cause our bot to instantly leap to the
            //  XYZ position last occupied by the remote peer and
            //  continue from there. That's NOT what we want because
            //  it would make it look like our Victim didn't really die!
            //  Accordingly, we want to set the global "NetworkReceiveTimer"
            //  back to -400 to make it wait awhile, and we want to force
            //  the location of the re-spawned aircraft away from the
            //  prior position as follows:
            //
            if (ThreeDObjects[MissionAircraftNumber]->Sentient > 3)
               {//  Get here if the destroyed aircraft was piloted by a Sentient. Some extra steps are needed.
               GetNetworkApiPacket(); //  Throw away any InPacket that has already sneaked in....
               DiscardAnyInPacketsInQueue(); //  Remove any stale inpackets that might otherwise corrupt our respawning parameters
               InPacket.UdpObjXPosition -=300; //  Make SURE no InPacket places replacement bot nearby.
               InPacket.UdpObjZPosition -=300; //  Make SURE no InPacket places replacement bot nearby.
               NetworkReceiveTimer= -400; // Wait awhile before getting next InPacket
               // Preserve this aircraft type for later comparison to detect future changes:
               MissionNetworkBattle07PriorAircraft[MissionAircraftNumber] = ThreeDObjects[MissionAircraftNumber]->id;
               } //  End of special, additional timing and position logic for respawning a formerly "Sentient" player
            //
            //  Now take all steps necessary to re-spawn a new aircraft to replace
            //  the one that was destroyed:
            //
            ThreeDObjects [MissionAircraftNumber]->newinit (FIGHTER_A6M2, i + 1, 400); //  For this mission, bots are always in A6M2 "Zeroes".
            ThreeDObjects [MissionAircraftNumber]->id = FIGHTER_A6M2;
            ThreeDObjects [MissionAircraftNumber]->Durability = ThreeDObjects [MissionAircraftNumber]->maxDurability; //  Repair the new aircraft
            ThreeDObjects [MissionAircraftNumber]->immunity = 50 * timestep; //  Make this new aircraft invulnerable for the first few seconds
            ThreeDObjects [MissionAircraftNumber]->activate (); //  Activate that new aircraft
            ThreeDObjects [MissionAircraftNumber]->killed = false; //  Advertise that he is alive.
            ThreeDObjects [MissionAircraftNumber]->ammo = 1600; //  Bots get 1600 bullets each.
            ThreeDObjects [MissionAircraftNumber]->MyMissionPlayerNumber = MissionAircraftNumber; //  Make my player number globally visible
            //
            //  Move this new aircraft to a new, random position in the neighborhood.
            //
            ThreeDObjects [MissionAircraftNumber]->tl->x = 200 + (myrandom(20) - 10);
            ThreeDObjects [MissionAircraftNumber]->tl->z = 200 + (myrandom(20) - 10);
            ThreeDObjects[MissionAircraftNumber]->tl->y = l->getHeight(ThreeDObjects[MissionAircraftNumber]->tl->x, ThreeDObjects[MissionAircraftNumber]->tl->z);
            ThreeDObjects[MissionAircraftNumber]->tl->y += 260 + (myrandom(80) - 40);
            ThreeDObjects [MissionAircraftNumber]->Sentient = 0; //  Reset the "Sentient" attribute of this new aircraft (all start out as bots)
            ThreeDObjects [MissionAircraftNumber]->thrustUp(); //  Give this bot some thrust
            ThreeDObjects [MissionAircraftNumber]->thrustUp(); //  And even a bit MORE thrust....
            //
            //  This is a good point to generate some run-time diagnostic reporting and update our logfile about this new aircraft:
            //
            sprintf (
                    DebugBuf,
                    "MissionNetworkBattle07::processTimer() spawning new aircraft %d at X=%f Y=%f Z=%f",
                    MissionAircraftNumber,
                    ThreeDObjects[MissionAircraftNumber]->tl->x,
                    ThreeDObjects[MissionAircraftNumber]->tl->y,
                    ThreeDObjects[MissionAircraftNumber]->tl->z
                    );
            display (DebugBuf, LOG_MOST);

            //  Now make sure our new aircraft is NOT lugging any missiles or bombs:
            for (i = 0; i < missiletypes; i ++)
                {
                ThreeDObjects [MissionAircraftNumber]->missiles [i] = 0;
                }
            //  This aircraft may still be in the process of exploding. We should stop that:
            ThreeDObjects [MissionAircraftNumber]->explode = 0; //  Stop the explosion.
            //  Bots behave best if they do NOT have a target:
            ThreeDObjects [MissionAircraftNumber]->target = NULL;
            } //  End of logic that replaces destroyed aircraft to keep the mission running for awhile.
        } //  End of loop that examines each mission aircraft to preserve their type and respawn those destroyed.
    // Check to see if the player's aircraft has been destroyed:
    if (!ThreeDObjects[0]->active)
       { //  Get here whenever the player's aircraft has been destroyed.
       NetworkPlayerKilled = true;
       //  Stop this aircraft from generating any sounds:
       sound->stop (SOUND_PLANE1);
       sound->stop (SOUND_PLANE2);
       sound->stop (SOUND_WINDNOISE);
       WindNoiseOn = false;
       }
    if (MumbleTimeRemainingBeforeChannelReset < 1000)
       { //  Get here if it's been too long since our last Mumble command
       if (MumbleManagement)
          {
          event_CommsMacro17(); //  Reset player to proper Mumble TeamCast channel
          //  Now format a message to be displayed on the Cockpit's "SystemMessage Panel":
          sprintf (SystemMessageBufferA, "MUMBLE RESET TO TEAMCAST CHANNEL.");
          //  And inform cockpit.cpp to scroll our new message into view:
          NewSystemMessageNeedsScrolling = true;
          sound->setVolume (SOUND_BEEP1, 60); //@ Medium-volume beep
          sound->play (SOUND_BEEP1, false);
          }
       else
          { // Get here if user disabled LAC's management of Mumble channel changes.
          MumbleChannelPresumed = 95; //@ Signal cockpit Mumble Panel
          if (! (NetworkMode & 16))
             { // Get here if Mumble vocalization is NOT disabled.
             popen ("espeak -p 10 -a 66  -s 160 \"Team is switching back to the TeamCast Channel.\"", "r");
             }
          sprintf (SystemMessageBufferA, "TEAM SWITCHING TO TEAMCAST CHANNEL.");
          //  And inform cockpit.cpp to scroll our new message into view:
          NewSystemMessageNeedsScrolling = true;
          }
       //  Now make sure we will do this again after a LONG time, to force
       //  everybody to monitor the appropriate Mumble channel periodically:
       MumbleTimeRemainingBeforeChannelReset = 10000000; //  10,000 seconds
       }
    if (MissionNetworkBattleRadarTimer > 100)
       { //  Get here 10 times /second.
       MissionNetworkBattleRadarTimer = 0; //  Reset this timer in preparation for next time...
       //
       //  This loop is a handy place for any special code that needs to
       //  be activated periodically for smooth motion, like moving
       //  carriers or testing to see if the operator has activated
       //  "Autopilot", etc:
       //
       // Rotate the four RADAR antennas:
       //
       if (ThreeDObjects[MissionObjectRadarHqBlue]->Durability > 200)
          { //  Get here if the BlueTeam HQ airfield is not too damaged for RADAR Antenna Rotation.
          ThreeDObjects[MissionObjectRadarHqBlue]->phi += 10; //  Rotate the BlueTeam Radar Reflector antenna 10 degrees.
          }
       if (ThreeDObjects[MissionObjectRadarHqBlue]->phi >= 360)
          { //  If it's rotated beyond 360 degrees, reset it.
          ThreeDObjects[MissionObjectRadarHqBlue]->phi = 0;
          }
       if (ThreeDObjects[MissionObjectRadarHqRed]->Durability > 200)
          { //  Get here if the RedTeam HQ airfield is not too damaged for RADAR Antenna Rotation.
          ThreeDObjects[MissionObjectRadarHqRed]->phi += 10; //  Rotate the RedTeam Radar Reflector antenna 10 degrees.
          }
       if (ThreeDObjects[MissionObjectRadarHqRed]->phi >= 360)
          { //  If it's rotated beyond 360 degrees, reset it.
          ThreeDObjects[MissionObjectRadarHqRed]->phi = 0;
          }
       if (ThreeDObjects[MissionObjectRadarBlue2]->Durability > 200)
          { //  Get here if the BlueTeam HQ airfield is not too damaged for RADAR Antenna Rotation.
          ThreeDObjects[MissionObjectRadarBlue2]->phi += 10; //  Rotate the BlueTeam Radar Reflector antenna 10 degrees.
          }
       if (ThreeDObjects[MissionObjectRadarBlue2]->phi >= 360)
          { //  If it's rotated beyond 360 degrees, reset it.
          ThreeDObjects[MissionObjectRadarBlue2]->phi = 0;
          }
       if (ThreeDObjects[MissionObjectRadarRed2]->Durability > 200)
          { //  Get here if the BlueTeam HQ airfield is not too damaged for RADAR Antenna Rotation.
          ThreeDObjects[MissionObjectRadarRed2]->phi += 10; //  Rotate the BlueTeam Radar Reflector antenna 10 degrees.
          }
       if (ThreeDObjects[MissionObjectRadarRed2]->phi >= 360)
          { //  If it's rotated beyond 360 degrees, reset it.
          ThreeDObjects[MissionObjectRadarRed2]->phi = 0;
          }
       AutoPilot(); //  If player has requested "AutoPilot", hold this altitude.
       //
       // Move naval ships. Each moves to a new position as a consequence of its
       // RudderOffset and Thrust during the prior 100 milliseconds.
       //
       // Adjust phi if our Rudder is not set at 0:
       //
       if (ThreeDObjects[MissionObjectCarrierRed1]->active)
          { //@ Get here if this aircraft carrier has not been destroyed. It can still move.
          ThreeDObjects[MissionObjectCarrierRed1]->phi += MissionObjectCarrierRed1RudderDegreesM07;
          if (ThreeDObjects[MissionObjectCarrierRed1]->phi > 360.0)
             {
             ThreeDObjects[MissionObjectCarrierRed1]->phi -= 360.0;
             }
          if (ThreeDObjects[MissionObjectCarrierRed1]->phi < 0.0)
             {
             ThreeDObjects[MissionObjectCarrierRed1]->phi += 360.0;
             }
          }
       else
          {
          static bool FirstVerbalization = true;
          if (!(NetworkMode & 16))
             { // Get here if the user has not blocked use of espeak
             if (FirstVerbalization)
                { // Get here if we have not yet verbalized "Dead in the water".
                popen ("espeak -p 10 -a 66 \"Now hear this! Now hear this! RedTeam aircraft carrier has been destroyed!\"", "r");
                FirstVerbalization = false; // Prevent re-verbalizing
                }
             }
          }

       if (ThreeDObjects[MissionObjectCarrierRed1]->active)
          { //@ Get here if this aircraft carrier has not been destroyed. It can still move.
          ThreeDObjects[MissionObjectCarrierBlue1]->phi += MissionObjectCarrierBlue1RudderDegreesM07;
          if (ThreeDObjects[MissionObjectCarrierBlue1]->phi > 360.0)
             {
             ThreeDObjects[MissionObjectCarrierBlue1]->phi -= 360.0;
             }
          if (ThreeDObjects[MissionObjectCarrierBlue1]->phi < 0.0)
             {
             ThreeDObjects[MissionObjectCarrierBlue1]->phi += 360.0;
             }
          }
       else
          {
          static bool FirstVerbalization = true;
          if (!(NetworkMode & 16))
             { // Get here if the user has not blocked use of espeak
             if (FirstVerbalization)
                { // Get here if we have not yet verbalized "Dead in the water".
                popen ("espeak -p 10 -a 66 \"Now hear this! Now hear this! BlueTeam aircraft carrier has been destroyed!\"", "r");
                FirstVerbalization = false; // Prevent re-verbalizing
                }
             }
          }
       //
       // Adjust MissionObjectCarrierRed1 XZ position if our Thrust is not set at 0:
       //
       if (ThreeDObjects[MissionObjectCarrierRed1]->active)
          { //@ Get here if this aircraft carrier has not been destroyed. It can still move.
          ThreeDObjects[MissionObjectCarrierRed1]->tl->x -=
             (
             MissionObjectCarrierRed1ThrustM07 * cos (((ThreeDObjects[MissionObjectCarrierRed1]->phi) + 0) * DegreesToRadiansFactor)
             );
          ThreeDObjects[MissionObjectCarrierRed1]->tl->z -=
             (
             MissionObjectCarrierRed1ThrustM07 * sin (((ThreeDObjects[MissionObjectCarrierRed1]->phi) + 0)* DegreesToRadiansFactor)
             );
          }
       //
       // Adjust MissionObjectCarrierBlue1 XZ position if our Thrust is not set at 0:
       //
       if (ThreeDObjects[MissionObjectCarrierBlue1]->active)
          { //@ Get here if this aircraft carrier has not been destroyed. It can still move.
          ThreeDObjects[MissionObjectCarrierBlue1]->tl->x -=
             (
             MissionObjectCarrierBlue1ThrustM07 * cos (((ThreeDObjects[MissionObjectCarrierBlue1]->phi) + 0) * DegreesToRadiansFactor)
             );
          ThreeDObjects[MissionObjectCarrierBlue1]->tl->z -=
             (
             MissionObjectCarrierBlue1ThrustM07 * sin (((ThreeDObjects[MissionObjectCarrierBlue1]->phi) + 0)* DegreesToRadiansFactor)
             );
          }
       //
       // Now we will check to determine whether the value of "MissionChronoMilestone" has advanced
       // since the last time we checked 100 milliseconds ago. To do this, we will compare
       // "MissionChronoMilestone" with "PriorChronoMilestone" as follows:
       //
       if (MissionChronoMilestone != PriorChronoMilestone)
          { // Get here within 100 milliseconds of receipt of a new Chrono Milestone message
          sprintf (DebugBuf, "MissionNetworkBattle07(): Detected change in MissionChronoMilestone. Now %d.", MissionChronoMilestone);
          display (DebugBuf, LOG_MOST);
          sprintf (SystemMessageBufferA, "NEW MISSIONCHRONOMILESTONE = %d", MissionChronoMilestone);
          NewSystemMessageNeedsScrolling = true;
          PriorChronoMilestone = MissionChronoMilestone; // Prevent repeating this change detection.
          //
          // At this point, a more sophisticated mission would move, orient, and configure
          // as many as 10 mobile mission objects according to hard-coded data associated
          // with the received ChronoMilestone value in order to keep them synchronized
          // with the corresponding objects of the MissionCommander. It's as if the
          // MissionCommander's message means: "Everybody listen up! I am the MissionCommander.
          // I am about to send a reference to a hard-coded table of the positions of every
          // object that I have been moving according to my timers, because on my system
          // all of those objects have reached the referenced positions and orientations
          // according to plan. You are ordered to immediately move the corresponding objects
          // on your local maps accordingly, so everybody sees them in matching locations,
          // orientations, etc."
          //
          switch (MissionChronoMilestone)
             {
             case 1:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 1.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 1 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone1;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone1;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone1;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone1;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone1;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone1;
                MissionStateNetworkBattle = 16;
                break;
                }
             case 2:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 2.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 2 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone2;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone2;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone2;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone2;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone2;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone2;
                MissionStateNetworkBattle = 21;
                break;
                }
             case 3:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 3.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 3 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone3;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone3;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone3;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone3;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone3;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone3;
                MissionStateNetworkBattle = 41;
                break;
                }
             case 4:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 4.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 4 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone4;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone4;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone4;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone4;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone4;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone4;
                MissionStateNetworkBattle = 61;
                break;
                }
             case 5:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 5.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 5 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone5;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone5;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone5;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone5;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone5;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone5;
                MissionStateNetworkBattle = 81;
                break;
                }
             case 6:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 6.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 6 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone6;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone6;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone6;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone6;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone6;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone6;
                MissionStateNetworkBattle = 101;
                break;
                }
             case 7:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 7.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 7 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone7;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone7;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone7;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone7;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone7;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone7;
                MissionStateNetworkBattle = 121;
                break;
                }
             case 8:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 8.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 8 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone8;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone8;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone8;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone8;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone8;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone8;
                MissionStateNetworkBattle = 141;
                break;
                }
             case 9:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 9.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 9 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone9;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone9;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone9;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone9;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone9;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone9;
                MissionStateNetworkBattle = 161;
                break;
                }
             case 10:
                {
                //
                // Get here within 100 ms of receipt of a Morse Code message alerting us
                // of the need to immediately update the position, orientation, velocity,
                // durability, or any other attributes of any and all mission objects that
                // change as a result of the mission's design upon reaching
                // MissionChronoMilestone 10.
                //
                if (!(NetworkMode & 16))
                   { // Get here if the user has not blocked use of espeak
                   popen ("espeak -p 10 -a 66 \"Received Mission Chrono Milestone 10 sync command.\"", "r");
                   }
                ThreeDObjects[MissionObjectCarrierRed1]->tl->x = RedTeamCarrier07XPositionAtMilestone10;
                ThreeDObjects[MissionObjectCarrierRed1]->tl->z = RedTeamCarrier07ZPositionAtMilestone10;
                ThreeDObjects[MissionObjectCarrierRed1]->phi = RedTeamCarrier07PhiAtMilestone10;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->x = BlueTeamCarrier07XPositionAtMilestone10;
                ThreeDObjects[MissionObjectCarrierBlue1]->tl->z = BlueTeamCarrier07ZPositionAtMilestone10;
                ThreeDObjects[MissionObjectCarrierBlue1]->phi = BlueTeamCarrier07PhiAtMilestone10;
                MissionStateNetworkBattle = 181;
                break;
                }
             default:
                { // Only get here if the received value of MissionChronoMilestone is > 9.
                display ((char *)"Received invalid value for MissionChronoMilestone.", LOG_MOST);
                }
             }
          }
       } //  End loop that gets executed 10 times per second.
    if (MissionNetworkBattle07Timer > 1000)
       { //  Get here once every second.
       MissionNetworkBattle07Timer = 0;
       //
       //  This loop is a handy place to process events that don't need
       //  attention very often, like checking for "Fratricide" and gradually
       //  "aging" slow processes like "GoodMenuBehavior" and "Sentient"
       //  level.
       //
       // Correct any recent incoming errors in MissionChronoMilestone:
       //
       MilestoneCorrectionCheck();
       //
       // Check for recent Fratricide infractions:
       //
       if (FratricideShameFactor < 60000.0)
          { //  Get here if repentence is still possible
          FratricideShameFactor *= 0.80; //  Shame doesn't last forever...
          if (FratricideShameFactor <= 50)
             { //  Get here if it's been a long time since shameful activity
             FratricideShameFactor = 0; //  Erase any remaining shame....
             }
          }
       if (FratricideShameFactor > 50)
          { //  Get here if we should be ashamed of ourselves for fratricide
          IffOnOff = 0; // Punishment for recent, possibly innocent, fratricide attempt(s)
          //  Format a message for display on cockpit SystemMessagePanel:
          sprintf (SystemMessageBufferA, "IFF DEACTIVATED");
          //  Now set a flag to inform cockpit.cpp to scroll that message into view:
          NewSystemMessageNeedsScrolling = true;
          }
       if (FratricideShameFactor > 40000)
          { //  Get here if we should be ashamed of ourselves for fratricide
          IffOnOff = 0; // Punishment for recent, very serious fratricide attempt(s)
          RadarOnOff = 0; // More punishment
          HudOnOff = 0; // More punishment
          //  Format a message for display on cockpit SystemMessagePanel:
          sprintf (SystemMessageBufferA, "IFF, RADAR, & TACTICAL STATUS DEACTIVATED");
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
       for (AircraftCount =0; AircraftCount<=10; AircraftCount++)
          { //  Examine every aircraft in the mission
          if (ThreeDObjects[AircraftCount]->Sentient >1)
             { //  If this aircraft was flown by a Sentient recently
             ThreeDObjects [AircraftCount]->Sentient --; //  "Age" the Sentient value so it expires if not refreshed by more InPackets
             }
          }
       if (GoodMenuBehavior > 1)
         { //  GoodMenuBehavior dosen't last forever.
         GoodMenuBehavior--;
         if (GoodMenuBehavior <2)
            {
            ReturnedToCombat = false; //  "ReturnedToCombat" signals other logic, possibly to guard against cheating.
            }
         }
       if (ReturnedToCombat && GoodMenuBehavior < 2)
          { //  Get here if the player previously pressed <ESC> then returned to flight, but has not yet been fully punished
          sound->play (SOUND_BEEP1, false);
          fplayer->Durability *= 0.05; //  Punish player with a lot of new damage
          fplayer->Durability--;
          sprintf (SystemMessageBufferA, "ABUSE OF <ESC> DETECTED.");
          NewSystemMessageNeedsScrolling = true;
          if (! (NetworkMode & 16))
             { // Get here if the user has not disabled espeak
             popen ("espeak -p 130 -a 127 -s 165 \"Escape abuse detected.\"", "r");
             }
          }
       if (MissionIdNegotiationCount > 32)
          { //  Get here if we've been unable to negotiate unique value for "MyNetworkId" after 32 attempts
          sound->setVolume (SOUND_BEEP1, 20); //  and beep softly
          sound->play (SOUND_BEEP1, false);
          sprintf (SystemMessageBufferA, "THIS MISSION IS FULL. TRY ANOTHER.");
          NewSystemMessageNeedsScrolling = true;
          }
       RepairDamagedAirfields(); //  Good to do this once each second.
       sprintf (SystemMessageBufferA, "MISSIONCHRONOMILESTONE = %d", MissionChronoMilestone);
       NewSystemMessageNeedsScrolling = true;
       } //  end of (MissionNetworkBattle07Timer > 1000)
    BattleDamageRiskTimer += DeltaTime;
    if ((BattleDamageRiskTimer > 5000) || (BattleDamageRiskTimer > (abs)(myrandom(131072))))
       { //  Get here at least every 5 seconds, or possibly sooner by random chance
       BattleDamageRiskTimer = 0;
       CalcDamageRiskFromNearbyOpposition(); //  Determine if we suffer damage from enemy bombers or airfield
       ThreeDObjects[0]->Durability -= CalculatedDamageDueToCurrentRisk; //  Admit damage for risk we took.
       if (CalculatedDamageDueToCurrentRisk > 0)
          { //  Get here once every time we suffer new damage. Log it...
          sprintf (DebugBuf, "MissionNetworkBattle07::processTimer() fplayer->Durability is now %f.", fplayer->Durability);
          display (DebugBuf, LOG_MOST);
          if (fplayer->Durability < 0)
             { //  Get here if damage from locally managed airfields or bombers killed us.
             UpdateOnlineScoreLogFileWithCalculatedRisks(); //  Log it...
             }
          }
       CalculatedDamageDueToCurrentRisk = 0; //  After admitting that damage amount, clear it.
       }
    MissionTenSecondTimer += DeltaTime;
    if (MissionTenSecondTimer > 10000)
       { // Get here once every 10 seconds
       MissionTenSecondTimer = 0; // Will expire again in 10 more seconds
       HighestRecentMyNetworkId = 0; // Reset records of recent player numbers
       if (MissionCommanderCandidate > MyNetworkId)
          { // If any Inpacket of prior 10 seconds came from a player with higher ID than me
          MissionCommander = MissionCommanderCandidate; // Then THAT player is MissionCommander
          }
       else
          { // Otherwise, I am the MissionCommander
          MissionCommander = MyNetworkId;
          }
       sprintf (SystemMessageBufferA, "MISSIONCOMMANDER = %d", MissionCommander);
       NewSystemMessageNeedsScrolling = true;
       MissionCommanderCandidate = 0; // Erase stale values from prior 10 seconds
       }
    StaticObjectUpdateTimer += DeltaTime;
    if (StaticObjectUpdateTimer > 2000)
       { //  Get here when it's time to update network peers regarding any damaged airfields, etc.
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
       StaticUpdateSwitcher ++;
       if (StaticUpdateSwitcher == 1)
          { //  Get here if it's time to handle MissionObjectHqBlue
          if (ThreeDObjects[MissionObjectHqBlue]->active)
             { // Get here if this object has NOT been destroyed. Issue Static update of its status.
             TempFloat1 = ThreeDObjects[MissionObjectHqBlue]->Durability;
             TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
             ThreeDObjects[MissionObjectHqBlue]->DamageInNetQueue = TempFloat1;
             }
          else
             { //@ Get here if this MissionObject has been destroyed.
             // Inform all other players to drain its repair state down to 0.01:
             ThreeDObjects[MissionObjectHqBlue]->DamageInNetQueue = -0.01;
             }
          }
       else if (StaticUpdateSwitcher == 2)
          { //  Get here if it's time to handle MissionObjectHqRed
          if (ThreeDObjects[MissionObjectHqRed]->active)
             { // Get here if this object has NOT been destroyed. Issue Static update of its status.
             TempFloat1 = ThreeDObjects[MissionObjectHqRed]->Durability;
             TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
             ThreeDObjects[MissionObjectHqRed]->DamageInNetQueue = TempFloat1;
             }
          else
             { //@ Get here if this MissionObject has been destroyed.
             // Inform all other players to drain its repair state down to 0.01:
             ThreeDObjects[MissionObjectHqRed]->DamageInNetQueue = -0.01;
             }
          }
       else if (StaticUpdateSwitcher == 3)
          { //  Get here if it's time to handle MissionObjectAirfieldBlue2
          if (ThreeDObjects[MissionObjectAirfieldBlue2]->active)
             { // Get here if this object has NOT been destroyed. Issue Static update of its status.
             TempFloat1 = ThreeDObjects[MissionObjectAirfieldBlue2]->Durability;
             TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
             ThreeDObjects[MissionObjectAirfieldBlue2]->DamageInNetQueue = TempFloat1;
             }
          else
             { //@ Get here if this MissionObject has been destroyed.
             // Inform all other players to drain its repair state down to 0.01:
             ThreeDObjects[MissionObjectAirfieldBlue2]->DamageInNetQueue = -0.01;
             display ((char *)"MissionNetworkBattle07::processTimer(): MissionObjectAirfieldBlue2 destroyed. Setting DamageInNetQueue = -0.01.",LOG_MOST);
             }
          }
       else if (StaticUpdateSwitcher == 4)
          { //  Get here if it's time to handle MissionObjectAirfieldRed2
          if (ThreeDObjects[MissionObjectAirfieldRed2]->active)
             { // Get here if this object has NOT been destroyed. Issue Static update of its status.
             TempFloat1 = ThreeDObjects[MissionObjectAirfieldRed2]->Durability;
             TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
             ThreeDObjects[MissionObjectAirfieldRed2]->DamageInNetQueue = TempFloat1;
             }
          else
             { //@ Get here if this MissionObject has been destroyed.
             // Inform all other players to drain its repair state down to 0.01:
             ThreeDObjects[MissionObjectAirfieldRed2]->DamageInNetQueue = -0.01;
             display ((char *)"MissionNetworkBattle07::processTimer(): MissionObjectAirfieldRed2 destroyed. Setting DamageInNetQueue = -0.01.",LOG_MOST);
             }
          }
       else if (StaticUpdateSwitcher == 5)
          { //  Get here if it's time to handle MissionObjectCarrierBlue1
          if (ThreeDObjects[MissionObjectCarrierBlue1]->active)
             { // Get here if this object has NOT been destroyed. Issue Static update of its status.
             TempFloat1 = ThreeDObjects[MissionObjectCarrierBlue1]->Durability;
             TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
             ThreeDObjects[MissionObjectCarrierBlue1]->DamageInNetQueue = TempFloat1;
             }
          else
             { //@ Get here if this MissionObject has been destroyed.
             // Inform all other players to drain its repair state down to 0.01:
             ThreeDObjects[MissionObjectCarrierBlue1]->DamageInNetQueue = -0.01;
             display ((char *)"MissionNetworkBattle07::processTimer(): MissionObjectCarrierBlue1 destroyed. Setting DamageInNetQueue = -0.01.",LOG_MOST);
             }
          }
       else if (StaticUpdateSwitcher == 6)
          { //  Get here if it's time to handle MissionObjectCarrierRed1
          if (ThreeDObjects[MissionObjectCarrierRed1]->active)
             { // Get here if this object has NOT been destroyed. Issue Static update of its status.
             TempFloat1 = ThreeDObjects[MissionObjectCarrierRed1]->Durability;
             TempFloat1 *= -1.0; //  Make it a negative number to trigger static transmission logic
             ThreeDObjects[MissionObjectCarrierRed1]->DamageInNetQueue = TempFloat1;
             }
          else
             { //@ Get here if this MissionObject has been destroyed.
             // Inform all other players to drain its repair state down to 0.01:
             ThreeDObjects[MissionObjectCarrierRed1]->DamageInNetQueue = -0.01;
             display ((char *)"MissionNetworkBattle07::processTimer(): MissionObjectCarrierRed1 destroyed. Setting DamageInNetQueue = -0.01.",LOG_MOST);
             }
          }
       if (StaticUpdateSwitcher > 6)
          { // Get here if we've exausted all of this mission's use instances of "StaticUpdateSwitcher". Reset it:
          StaticUpdateSwitcher = 0;
          }
       }

    //
    //  Update NetworkReceiveTimer and determine if it's now time
    //  to check for arrival of a new NetworkApi UDP packet:
    //
    NetworkReceiveTimer += dt;
    if (NetworkReceiveTimer > NetworkReceiveTimerInterval )
       { //  Get here every time NetworkReceiveTimer expires. Check for new InPacket:
       NetworkReceiveTimer = 0; //  Reset timer in preparation for next expiration.
       BytesReceived = GetNetworkApiPacket();
       if (BytesReceived == sizeof (LacUdpApiPacket))
          { //  Get here if a new InPacket has arrived.
          //  Report this for run-time debugging and log it in log file:
          display ((char *)"MissionNetworkBattle07 BytesReceived=", LOG_NET);
          sprintf (DebugBuf, "%i", BytesReceived);
          display (DebugBuf, LOG_NET);
          //  Now process that InPacket, extracting everything of value from it:
          LoadVariablesFromNetworkApiPacket(timer);
          if (MissionNetworkBattle07PriorAircraft[InPacket.UdpObjPlayerNumber] != InPacket.UdpObjVehicle)
             { //  Get here if this network peer is in a different type of aircraft
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
              ThreeDObjects[InPacket.UdpObjPlayerNumber]->newinit (ThreeDObjects[InPacket.UdpObjPlayerNumber]->id, 0, 400);
             }
          //  Now preserve this InPacket's aircraft type for comparison with the next InPacket for this player:
          MissionNetworkBattle07PriorAircraft[InPacket.UdpObjPlayerNumber] = InPacket.UdpObjVehicle;
          } //  end "Get here if a new InPacket has arrived".
       } //  End of logic that handles expiration of NetworkReceiveTimer.
    //
    //  Update NetworkTransmitTimer and determine if it's now time
    //  to send a new NetworkApi UDP packet:
    //
    NetworkTransmitTimer += dt;
    if (NetworkTransmitTimer > NetworkTransmitTimerInterval && !NetworkPlayerKilled)
       { //  Get here if we're alive and it's time to send a new network API packet.
       NetworkTransmitTimer=0;
       //  Find out if we've damaged anything since our last OutPacket:
       MissionNetworkBattle07RetrieveFirstDamageDescription();
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
    static bool MissionObjectCarrierBlue1Alive = true;
    static bool MissionObjectCarrierRed1Alive = true;
    static bool BlueTeamHasWonTheBattle = false;
    static bool RedTeamHasWonTheBattle = false;

    if (ThreeDObjects[MissionObjectHqBlue]->active)
       {
       BlueHqAlive = true;
       }
    else
       {
       BlueHqAlive = false;
       }

    if (ThreeDObjects[MissionObjectHqRed]->active)
       {
       RedHqAlive = true;
       }
    else
       {
       RedHqAlive = false;
       }

    if (ThreeDObjects[MissionObjectAirfieldBlue2]->active)
       {
       BlueAirfield2Alive = true;
       }
    else
       {
       BlueAirfield2Alive = false;
       }

    if (ThreeDObjects[MissionObjectAirfieldRed2]->active)
       {
       RedAirfield2Alive = true;
       }
    else
       {
       RedAirfield2Alive = false;
       }

    if (ThreeDObjects[MissionObjectCarrierBlue1]->active)
       {
       MissionObjectCarrierBlue1Alive = true;
       }
    else
       {
       MissionObjectCarrierBlue1Alive = false;
       }

    if (ThreeDObjects[MissionObjectCarrierRed1]->active)
       {
       MissionObjectCarrierRed1Alive = true;
       }
    else
       {
       MissionObjectCarrierRed1Alive = false;
       }

    if ((BlueHqAlive == false) && (BlueAirfield2Alive ==  false) && (MissionObjectCarrierBlue1Alive == false))
       {
       BlueTeamHasWonTheBattle = true;
       }

    if ((RedHqAlive == false) && (RedAirfield2Alive == false)  && (MissionObjectCarrierRed1Alive == false))
       {
       RedTeamHasWonTheBattle = true;
       }

    if (BlueTeamHasWonTheBattle || RedTeamHasWonTheBattle)
       { //  Get here if one of the two teams has destroyed BOTH of its opposing airfields and carrier.
       static bool CountdownLatch1 = false;
       static bool CountdownLatch2 = false;
       MissionEndingTimer -= dt; //  Diminish by milliseconds
       if (MissionEndingTimer < -200 && CountdownLatch1 == false)
          { //  Get here 5 seconds after either team wins the battle.
          display ((char *)"MissionNetworkBattle07::processtimer() Playing audio file MissionEndingInstrumental.wav", LOG_MOST);
          sound->play (SOUND_MISSIONENDINGINSTRUMENTAL, false);
          CountdownLatch1 = true; //  Prevent immediate restart of that audio file.
          }
       if (MissionEndingTimer < -1000 && CountdownLatch2 == false)
          { //  Get here 10 seconds after either team wins the battle.
          display ((char *)"MissionNetworkBattle07::processtimer() Playing audio file MissionEndingIn15SecCountdown.wav", LOG_MOST);
          sound->play (SOUND_MISSIONENDINGIN15SECCOUNTDOWN, false);
          if (! (NetworkMode & 16))
             {
             popen ("espeak -p 10 -a 66 -s 140 \"Mission ending in 15 seconds.\"", "r");
             }
          CountdownLatch2 = true; //  Prevent immediate restart of that audio file.
          MissionEndingTimer2 = 17000; //  Allow 17 seconds for next phase.
          }
       }
    if (MissionEndingTimer2)
       { //  Get here many times, but only after the "countdown warning audio" has begun playing.
       MissionEndingTimer2 -= dt; //  Diminish by milliseconds
       if (MissionEndingTimer2 < 1000)
          { //  Get here 16 seconds after "Countdown warning audio" started.
          //  All conditions to forcibly end mission are satisfied
          display ((char *)"MissionNetworkBattle07::processtimer(): Mission ending now.", LOG_MOST);
          fplayer->Durability = -1.0; //  Signal Destruction of player and end the mission.
          }
       }
    return 0;
    } //  end MissionNetworkBattle07::processtimer (Uint32 dt)




//
//  This function is no longer important. Earlier versions of LAC used this
//  function to insert prompting text at timed intervals, but more recent
//  missions haven't been using this file. Developers need not add anything
//  here.
//
void MissionNetworkBattle07::draw ()
    {
    if (timer >= 0 && timer <= 50 * timestep)
        {
        font1->drawTextCentered (0, 12, -2, name, &textcolor);
        }
    } //  end MissionNetworkBattle07::draw ()


//
//  MissionNetworkBattle07RetrieveFirstDamageDescription()
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
bool MissionNetworkBattle07RetrieveFirstDamageDescription()
{
int Mission3dObject;
display ((char *)"MissionNetworkBattle07RetrieveFirstDamageDescription()", LOG_NET);

for (Mission3dObject=1; Mission3dObject<=29; Mission3dObject++)
   { //  Loop through all mission aircraft EXCEPT ThreeDObjects[0], which represents the human player.
   if (ThreeDObjects[Mission3dObject]->DamageInNetQueue > 0.0)
      { //  Get here as soon as we find any damage to claim. Clients will subtract the damage amount they receive.
      DamageToClaim =  ThreeDObjects[Mission3dObject]->DamageInNetQueue; //  Positive value signals new damage
      ThreeDObjects[Mission3dObject]->DamageInNetQueue = 0.0;
      MissionAircraftDamaged = Mission3dObject;
      return true;
      }
   if (ThreeDObjects[Mission3dObject]->DamageInNetQueue < 0.0)
      { //  Get here if it's time to transmit a static damage value. Clients will update damage to received value.
      DamageToClaim =  ThreeDObjects[Mission3dObject]->DamageInNetQueue; //  Negative value signals static update
      ThreeDObjects[Mission3dObject]->DamageInNetQueue = 0.0;
      MissionAircraftDamaged = Mission3dObject;
      return true;
      }
   }
//  Get here if we have no damage to claim
MissionAircraftDamaged = 0;
DamageToClaim = 0.0;
return (false);
} //  end MissionNetworkBattle07RetrieveFirstDamageDescription()
