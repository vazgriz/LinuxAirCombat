#pragma once

#include "Engine/OpenGL/GLShader.h"

namespace LACEngine {
class GLProgram {
public:
    GLProgram();
    ~GLProgram();

    GLProgram(GLProgram&& other) noexcept;

    void AttachShader(const GLShader& shader);
    void Link();
    void Use();

private:
    uint32_t m_programID;
};

}