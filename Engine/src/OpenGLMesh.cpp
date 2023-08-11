#include "Engine/OpenGL/OpenGLMesh.h"

#include "glad/glad.h"

using namespace LACEngine;

OpenGLMesh::OpenGLMesh() : vertexArrayObject(0) {

}

OpenGLMesh::~OpenGLMesh() {
    glDeleteBuffers(static_cast<uint32_t>(vertexIDs.size()), vertexIDs.data());
    glDeleteVertexArrays(1, &vertexArrayObject);
}

OpenGLMesh::OpenGLMesh(OpenGLMesh&& other) noexcept {
    vertexIDs = std::move(other.vertexIDs);
    vertexArrayObject = other.vertexArrayObject;

    other.vertexArrayObject = 0;
}

void OpenGLMesh::Bind() {
    glBindVertexArray(vertexArrayObject);
}