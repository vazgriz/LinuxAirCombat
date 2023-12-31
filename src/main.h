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

/* This file includes the main program. */

#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "aiobject.h"
#include "model.h"
#include "3ds.h"
#include "effects.h"
#include "audio.h"
#include "pilots.h"

extern char* getKeyString(int key, char* str); // get name of a keyboard's key (ENTER, SPACE)

extern AIObj* ThreeDObjects[maxfighter];
extern AIObj* fplayer; // the active human player
extern AIObj* missile[maxmissile];
extern CBlackSmoke* blacksmoke[maxblacksmoke];
extern CExplosion* explosion[maxexplosion];
extern CLoad3DS g_Load3ds;
extern CModel* getModel(int id); // own export: main.h may be included in the cpp files
extern CModel model_Airfield00;
extern CModel model_chaff1;
extern CModel model_cannon1;
extern CModel model_cannon2;
extern CModel model_cannon1b;
extern CModel model_cannon2b;
extern CModel model_fig; // fighter models
extern CModel model_figa;
extern CModel model_figb;
extern CModel model_figc;
extern CModel model_figi;
extern CModel model_figu;
extern CModel model_figv;
extern CModel model_figw;
extern CModel model_figx;
extern CModel model_figy;
extern CModel model_figz;
extern CModel model_figAA;
extern CModel model_figAB;
extern CModel model_figAC;
extern CModel model_figAD;
extern CModel model_figAE;
extern CModel model_figAF;
extern CModel model_figAG;
extern CModel model_figAH;
extern CModel model_figAI;
extern CModel model_figAJ;
extern CModel model_figAK;
extern CModel model_figAL;
extern CModel model_figAM;
extern CModel model_figAN;
extern CModel model_figAO;
extern CModel model_figAP;
extern CModel model_figAQ;
extern CModel model_figAR;
extern CModel model_figAS;
extern CModel model_figAT;
extern CModel model_figAU;
extern CModel model_figAV;
extern CModel model_figAW;
extern CModel model_figAX;
extern CModel model_figAY;
extern CModel model_figAZ;
extern CModel model_figBA;
extern CModel model_figBB;
extern CModel model_figBC;
extern CModel model_figBD;
extern CModel model_figBE;
extern CModel model_figBF;
extern CModel model_figBG;
extern CModel model_figBH;
extern CModel model_figBI;
extern CModel model_figBJ;
extern CModel model_figBK;
extern CModel model_figBL;
extern CModel model_figBM;
extern CModel model_figBN;
extern CModel model_figBO;
extern CModel model_figBP;
extern CModel model_figBQ;
extern CModel model_figBR;
extern CModel model_figBS;
extern CModel model_figBT;
extern CModel model_flak1;
extern CModel model_flarak1;
extern CModel model_flare1;
extern CModel model_LacText;
extern CModel model_bomb01;
extern CModel model_missile2;
extern CModel model_missile3;
extern CModel model_missile4;
extern CModel model_missile5;
extern CModel model_missile6;
extern CModel model_missile7;
extern CModel model_missile8;
extern CModel model_RadarReflector;
extern CModel model_tank1;
extern CModel model_tank2;
extern CModel model_battery;
extern CModel model_battleship;
extern CModel model_carrier00;
extern CModel model_hall2;
extern CModel model_rubble1;
extern CModel model_depot1;
extern CModel model_tent1;
extern CTexture* texsun, * texflare1, * texflare2, * texflare3, * texflare4, * texcross, * texcross2;
extern CTexture* texradar1, * texradar2;
extern DynamicObj* flare[maxflare];
extern DynamicObj* groundobj[maxgroundobj];
extern DynamicObj* chaff[maxchaff];
extern Flash* flash1; // the thunderstorm flash
extern Font* font1, * font2;
extern PilotList* pilots; // other pilots of the Eagle Squad
extern SoundSystem* sound;
extern Space* space; // the scene (everything) without the landscape
extern Star* star[maxstar]; // the stars at night
