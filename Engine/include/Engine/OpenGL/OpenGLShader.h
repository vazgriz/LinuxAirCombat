#pragma once
#include <stdint.h>
#include <string>

namespace LACEngine {
class OpenGLShader {
public:
    OpenGLShader(uint32_t shaderType);
    ~OpenGLShader();

    OpenGLShader(OpenGLShader&& other) noexcept;

    uint32_t GetID() const;

    void LoadSource(int32_t size, const char* data);
    void LoadSource(const std::string& data);

private:
    uint32_t m_shaderID;
};
}