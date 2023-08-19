#include "Engine/OpenGL/GLShader.h"

#include <iostream>
#include <glad/glad.h>

using namespace LACEngine;

GLShader::GLShader(uint32_t shaderType) : m_shaderID(0) {
    m_shaderID = glCreateShader(shaderType);
}

GLShader::~GLShader() {
    glDeleteShader(m_shaderID);
    m_shaderID = 0;
}

GLShader::GLShader(GLShader&& other) noexcept{
    m_shaderID = other.m_shaderID;
    other.m_shaderID = 0;
}

uint32_t GLShader::GetID() const {
    return m_shaderID;
}

void GLShader::LoadSource(int32_t size, const char* data) {
    glShaderSource(m_shaderID, 1, &data, &size);
    glCompileShader(m_shaderID);

    int  success;
    char infoLog[512];
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
void GLShader::LoadSource(const std::string& data) {
    LoadSource(data.size(), data.data());
}