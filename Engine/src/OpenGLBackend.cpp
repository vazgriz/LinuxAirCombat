#include "Engine/OpenGLBackend.h"

#include <glad/glad.h>

using namespace LACEngine;

OpenGLBackend::OpenGLBackend() {

}

OpenGLBackend::~OpenGLBackend() {

}

void OpenGLBackend::SetWindowSize(int32_t width, int32_t height) {
    glViewport(0, 0, width, height);
}