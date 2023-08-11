#pragma once

#include "Engine/OpenGL/OpenGLShader.h"

namespace LACEngine {
class OpenGLProgram {
public:
    OpenGLProgram();
    ~OpenGLProgram();

    OpenGLProgram(OpenGLProgram&& other) noexcept;

    void AttachShader(const OpenGLShader& shader);
    void Link();
    void Use();

private:
    uint32_t m_programID;
};

}