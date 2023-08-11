#pragma once
#include <stdint.h>
#include <vector>

namespace LACEngine {

class OpenGLMesh {
public:
    OpenGLMesh();
    ~OpenGLMesh();

    OpenGLMesh(OpenGLMesh&& other) noexcept;

    void Bind();

    std::vector<uint32_t> vertexIDs;
    uint32_t vertexArrayObject;
};

}