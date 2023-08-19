#pragma once
#include <stdint.h>

#include "Engine/RenderBackend.h"
#include "Engine/OpenGL/OpenGLMesh.h"

namespace LACEngine {

class OpenGLBackend : public RenderBackend {
public:
    OpenGLBackend();
    ~OpenGLBackend();

    void SetWindowSize(int32_t width, int32_t height) override;
    void LoadMesh(Mesh& mesh) override;
    void UnloadMesh(Mesh& mesh) override;

private:
    std::vector<std::unique_ptr<OpenGLMesh>> m_meshes;
};

}