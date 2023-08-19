#pragma once
#include <stdint.h>
#include <string>

namespace LACEngine {
class GLShader {
public:
    GLShader(uint32_t shaderType);
    ~GLShader();

    GLShader(GLShader&& other) noexcept;

    uint32_t GetID() const;

    void LoadSource(int32_t size, const char* data);
    void LoadSource(const std::string& data);

private:
    uint32_t m_shaderID;
};
}