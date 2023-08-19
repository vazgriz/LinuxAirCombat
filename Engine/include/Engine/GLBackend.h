#pragma once
#include <stdint.h>

#include "Engine/RenderBackend.h"
#include "Engine/OpenGL/GLMesh.h"

namespace LACEngine {

class GLBackend : public RenderBackend {
public:
    GLBackend();
    ~GLBackend();

    void SetWindowSize(int32_t width, int32_t height) override;
    void LoadMesh(Mesh& mesh) override;
    void UnloadMesh(Mesh& mesh) override;

private:
    std::vector<std::unique_ptr<GLMesh>> m_meshes;
};

}