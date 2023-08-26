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

#include "Engine/Directories.h"

#include <PlatformFolders.h>

using namespace LACEngine;

std::string Directories::saves = sago::getSaveGamesFolder1() + "/Linux Air Combat/Saves";
std::string Directories::data = "data";
std::string Directories::textures = "data/textures";
std::string Directories::sound = "data/sounds";
std::string Directories::music = "data/music";
std::string Directories::models = "data/models";

std::string Directories::getData(const std::string& name) {
    return data + "/" + name;
}

std::string Directories::getSaves(const std::string& name) {
    return saves + "/" + name;
}

std::string Directories::getTextures(const std::string& name) {
    return textures + "/" + name;
}

std::string Directories::getSounds(const std::string& name) {
    return sound + "/" + name;
}

std::string Directories::getMusic(const std::string& name) {
    return music + "/" + name;
}

std::string Directories::getModels(const std::string& name) {
    return models + "/" + name;
}

std::string Directories::getMaps(const std::string& name) {
    return maps + "/" + name;
}
