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

/* This file handles all input/output directories. */

#include "dirs.h"
#include "common.h"

#include <PlatformFolders.h>

Dirs::Dirs() {
    saves = sago::getSaveGamesFolder1() + "/Linux Air Combat/Saves";
    textures = "data/textures";
    sound = "data/sounds";
    music = "data/music";
    models = "data/models";
}

std::string Dirs::getSaves(const std::string& name) const {
    return saves + "/" + name;
}

std::string Dirs::getTextures(const std::string& name) const {
    return textures + "/" + name;
}

std::string Dirs::getSounds(const std::string& name) const {
    return sound + "/" + name;
}

std::string Dirs::getMusic(const std::string& name) const {
    return music + "/" + name;
}

std::string Dirs::getModels(const std::string& name) const {
    return models + "/" + name;
}

std::string Dirs::getMaps(const std::string& name) const {
    return maps + "/" + name;
}
