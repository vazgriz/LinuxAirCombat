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

#pragma once
#include <string>
#include <memory>

namespace LACEngine {

class Directories {
    static std::string data;
    static std::string saves;
    static std::string textures;
    static std::string music;
    static std::string sound;
    static std::string models;
    static std::string maps;

public:
    static std::string getData(const std::string& name);
    static std::string getSaves(const std::string& name); // get dir name containing the saves, ...
    static std::string getTextures(const std::string& name);
    static std::string getSounds(const std::string& name);
    static std::string getMusic(const std::string& name);
    static std::string getModels(const std::string& name);
    static std::string getMaps(const std::string& name);
};

}
