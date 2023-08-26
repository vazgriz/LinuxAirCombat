#pragma once
#include <string>

#include "Engine/Color.h"
#include "Engine/Texture.h"

namespace LACEngine {

class Material {
public:
    std::string name; // unique name
    std::string filename; // unique file name
    Color color; // uniform color
    std::shared_ptr<Texture> texture; // reference to a texture (or NULL if there is no texture)
    float utile; // tiling coordinates
    float vtile;
    float uoffset; // texture offsets (the importer must calculate u/v due to offsets)
    float voffset;
    float uscale; // texture scaling (the importer must calculate u/v due to scaling)
    float vscale;
    float wrot; // rotation in degree (the importer must calculate u/v due to wrot)
};

}