#pragma once
#include <stdint.h>
#include <unordered_map>

#include "Engine/RenderBackend.h"
#include "Engine/OpenGL/GLMesh.h"
#include "Engine/OpenGL/GLTexture.h"

namespace LACEngine {

class GLBackend : public RenderBackend {
public:
    GLBackend();
    ~GLBackend();

    void SetWindowSize(int32_t width, int32_t height) override;
    void LoadMesh(Mesh& mesh) override;
    void UnloadMesh(Mesh& mesh) override;
    void LoadTexture(Texture& texture) override;
    void UnloadTexture(Texture& texture) override;

private:
    std::unordered_map<GLMesh*, std::unique_ptr<GLMesh>> m_meshes;
    std::unordered_map<GLTexture*, std::unique_ptr<GLTexture>> m_textures;
};

}