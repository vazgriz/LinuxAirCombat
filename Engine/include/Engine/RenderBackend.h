#pragma once
#include <stdint.h>

#include "Engine/Mesh.h"

namespace LACEngine {

class RenderBackend {
public:
    RenderBackend();
    virtual ~RenderBackend() = 0;

    virtual void SetWindowSize(int32_t width, int32_t height) = 0;

    virtual void LoadMesh(const Mesh& mesh) = 0;
};

}