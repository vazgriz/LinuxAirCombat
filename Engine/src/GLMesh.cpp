#include "Engine/OpenGL/GLMesh.h"

#include "glad/glad.h"

using namespace LACEngine;

GLMesh::GLMesh() : vertexArrayObject(0) {

}

GLMesh::~GLMesh() {
    glDeleteBuffers(static_cast<uint32_t>(vertexIDs.size()), vertexIDs.data());
    glDeleteVertexArrays(1, &vertexArrayObject);
}

GLMesh::GLMesh(GLMesh&& other) noexcept {
    vertexIDs = std::move(other.vertexIDs);
    vertexArrayObject = other.vertexArrayObject;

    other.vertexArrayObject = 0;
}

void GLMesh::Bind() {
    glBindVertexArray(vertexArrayObject);
}