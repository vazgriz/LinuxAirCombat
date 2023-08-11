#pragma once
#include <stdint.h>
#include <vector>

namespace LACEngine {

struct OpenGLMesh {
    std::vector<uint32_t> vertexIDs;
    uint32_t vertexArrayObject;
};

}