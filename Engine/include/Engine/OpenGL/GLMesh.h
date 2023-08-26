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

    uint32_t vertexArrayObject;
    uint32_t indexBufferID;
    bool hasIndexBuffer;
    std::vector<uint32_t> vertexIDs;
};

}