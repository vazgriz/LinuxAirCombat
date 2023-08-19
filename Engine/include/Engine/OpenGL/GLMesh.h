#pragma once
#include <stdint.h>
#include <vector>

namespace LACEngine {

class GLMesh {
public:
    GLMesh();
    ~GLMesh();

    GLMesh(GLMesh&& other) noexcept;

    void Bind();

    std::vector<uint32_t> vertexIDs;
    uint32_t vertexArrayObject;
};

}