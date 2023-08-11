#pragma once
#include <stdint.h>

#include "Engine/RenderBackend.h"

namespace LACEngine {

class OpenGLBackend {
public:
    OpenGLBackend();
    ~OpenGLBackend();

    void SetWindowSize(int32_t width, int32_t height);
};

}