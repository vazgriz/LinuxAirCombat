#pragma once
#include <stdint.h>

#include "Engine/Mesh.h"
#include "Engine/Texture.h"

namespace LACEngine {

class RenderBackend {
public:
    RenderBackend();
    virtual ~RenderBackend() = 0;

    virtual void SetWindowSize(int32_t width, int32_t height) = 0;

    virtual void LoadMesh(Mesh& mesh) = 0;
    virtual void UnloadMesh(Mesh& mesh) = 0;

    virtual void LoadTexture(Texture& texture) = 0;
    virtual void UnloadTexture(Texture& texture) = 0;
};

}