#pragma once
#include <stdint.h>

namespace LACEngine {

class RenderBackend {
public:
    RenderBackend();
    virtual ~RenderBackend() = 0;

    virtual void SetWindowSize(int32_t width, int32_t height) = 0;
};

}