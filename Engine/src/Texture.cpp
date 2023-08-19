#include "Engine/Texture.h"

using namespace LACEngine;

Texture::Texture(TextureFormat format, int32_t width, int32_t height, TextureAlphaType alphaType)
    : m_renderData(nullptr), m_renderBackend(nullptr) {
    m_format = format;
    m_width = width;
    m_height = height;
    m_alphaType = alphaType;

    m_renderData = nullptr;
    m_renderBackend = nullptr;
}

Texture::Texture(Texture&& other) noexcept
    : m_renderData(nullptr), m_renderBackend(nullptr) {

    m_localData = std::move(other.m_localData);

    if (other.m_renderData != nullptr) {
        m_renderData = other.m_renderData;
        m_renderData = nullptr;
    }

    m_width = other.m_width;
    m_height = other.m_height;
    m_format = other.m_format;
    m_alphaType = other.m_alphaType;
    m_renderBackend = other.m_renderBackend;
}

int32_t Texture::GetWidth() const {
    return m_width;
}

int32_t Texture::GetHeight() const {
    return m_height;
}

TextureFormat Texture::GetFormat() const {
    return m_format;
}

TextureAlphaType Texture::GetAlphaType() const {
    return m_alphaType;
}

void Texture::SetRenderBackend(RenderBackend* renderBackend) {
    m_renderBackend = renderBackend;
}

bool Texture::HasLocalData() const {
    return m_localData.size() > 0;
}

bool Texture::HasRenderData() const {
    return m_renderData != nullptr;
}

char* Texture::GetLocalData() {
    return m_localData.data();
}

size_t Texture::GetLocalDataSize() const {
    size_t bytesPerPixel = 0;

    switch (m_format) {
    case TextureFormat::R:
        bytesPerPixel = 1;
        break;
    case TextureFormat::RG:
        bytesPerPixel = 2;
        break;
    case TextureFormat::RGB:
        bytesPerPixel = 3;
        break;
    case TextureFormat::RGBA:
        bytesPerPixel = 4;
        break;
    }

    return m_width * m_height * bytesPerPixel;
}

char* Texture::CreateLocalData() {
    size_t size = GetLocalDataSize();
    m_localData.resize(size);

    return m_localData.data();
}

void* Texture::GetRenderData() const {
    return m_renderBackend;
}

void Texture::SetRenderData(void* data) {
    m_renderBackend = data;
}