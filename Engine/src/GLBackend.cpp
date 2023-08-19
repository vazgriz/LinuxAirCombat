#include "Engine/GLBackend.h"

#include <glad/glad.h>

#include "Engine/OpenGL/GLMesh.h"
#include "Engine/OpenGL/GLTexture.h"

using namespace LACEngine;

GLBackend::GLBackend() {

}

GLBackend::~GLBackend() {

}

void GLBackend::SetWindowSize(int32_t width, int32_t height) {
    glViewport(0, 0, width, height);
}

void SetVertexAttribPointer(VertexFormat format) {
    switch (format) {
    case VertexFormat::Float32_Vec3:
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        break;
    }
}

void GLBackend::LoadMesh(Mesh& mesh) {
    std::unique_ptr<GLMesh> meshData = std::make_unique<GLMesh>();
    meshData->vertexIDs.resize(mesh.GetVertexDataCount());

    uint32_t& vao = meshData->vertexArrayObject;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    for (size_t i = 0; i < mesh.GetVertexDataCount(); i++) {
        const VertexData& vertexData = mesh.GetVertexData(i);
        uint32_t& vbo = meshData->vertexIDs[i];

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexData.GetLocalDataSize(), vertexData.GetLocalData(), GL_STATIC_DRAW);
        SetVertexAttribPointer(vertexData.GetVertexFormat());
        glEnableVertexAttribArray(i);
    }

    mesh.SetRenderData(meshData.get());
    mesh.SetRenderBackend(this);

    m_meshes.emplace(meshData.get(), std::move(meshData));
}

void GLBackend::UnloadMesh(Mesh& mesh) {
    GLMesh& meshData = *static_cast<GLMesh*>(mesh.GetRenderData());

    glDeleteBuffers(static_cast<int32_t>(meshData.vertexIDs.size()), meshData.vertexIDs.data());
    glDeleteVertexArrays(1, &meshData.vertexArrayObject);

    m_meshes.erase(&meshData);
}

void GLBackend::LoadTexture(Texture& texture) {
    std::unique_ptr<GLTexture> textureData = std::make_unique<GLTexture>();

    glGenTextures(1, &textureData->id);
    glBindTexture(GL_TEXTURE_2D, textureData->id);

    int32_t format = 0;

    switch (texture.GetFormat()) {
    case TextureFormat::R:
        format = GL_R;
        break;
    case TextureFormat::RG:
        format = GL_RG;
        break;
    case TextureFormat::RGB:
        format = GL_RGB;
        break;
    case TextureFormat::RGBA:
        format = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.GetWidth(), texture.GetHeight(), 0, format, GL_UNSIGNED_BYTE, texture.GetLocalData());
    glGenerateMipmap(GL_TEXTURE_2D);

    texture.SetRenderData(textureData.get());
    texture.SetRenderBackend(this);

    m_textures.emplace(textureData.get(), std::move(textureData));
}

void GLBackend::UnloadTexture(Texture& texture) {
    GLTexture& textureData = *static_cast<GLTexture*>(texture.GetRenderData());
    glDeleteTextures(1, &textureData.id);

    m_textures.erase(&textureData);
}