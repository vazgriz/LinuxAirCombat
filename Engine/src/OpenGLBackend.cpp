#include "Engine/OpenGLBackend.h"

#include <glad/glad.h>

#include "Engine/OpenGL/OpenGLMesh.h"

using namespace LACEngine;

OpenGLBackend::OpenGLBackend() {

}

OpenGLBackend::~OpenGLBackend() {

}

void OpenGLBackend::SetWindowSize(int32_t width, int32_t height) {
    glViewport(0, 0, width, height);
}

void SetVertexAttribPointer(VertexFormat format) {
    switch (format) {
    case VertexFormat::Float32_Vec3:
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        break;
    }
}

void OpenGLBackend::LoadMesh(Mesh& mesh) {
    std::unique_ptr<OpenGLMesh> meshData = std::make_unique<OpenGLMesh>();
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

    m_meshes.emplace_back(std::move(meshData));
}