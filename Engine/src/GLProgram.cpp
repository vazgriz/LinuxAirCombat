#include "Engine/OpenGL/GLProgram.h"

#include <glad/glad.h>

using namespace LACEngine;

GLProgram::GLProgram() :m_programID(0) {
    m_programID = glCreateProgram();
}

GLProgram::~GLProgram() {
    glDeleteProgram(m_programID);
    m_programID = 0;
}

GLProgram::GLProgram(GLProgram&& other) noexcept {
    m_programID = other.m_programID;
    other.m_programID = 0;
}

void GLProgram::AttachShader(const GLShader& shader) {
    glAttachShader(m_programID, shader.GetID());
}

void GLProgram::Link() {
    glLinkProgram(m_programID);
}

void GLProgram::Use() {
    glUseProgram(m_programID);
}