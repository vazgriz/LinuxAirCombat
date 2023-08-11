#include "Engine/OpenGL/OpenGLProgram.h"

#include <glad/glad.h>

using namespace LACEngine;

OpenGLProgram::OpenGLProgram() :m_programID(0) {
    m_programID = glCreateProgram();
}

OpenGLProgram::~OpenGLProgram() {
    glDeleteProgram(m_programID);
    m_programID = 0;
}

OpenGLProgram::OpenGLProgram(OpenGLProgram&& other) noexcept {
    m_programID = other.m_programID;
    other.m_programID = 0;
}

void OpenGLProgram::AttachShader(const OpenGLShader& shader) {
    glAttachShader(m_programID, shader.GetID());
}

void OpenGLProgram::Link() {
    glLinkProgram(m_programID);
}

void OpenGLProgram::Use() {
    glUseProgram(m_programID);
}