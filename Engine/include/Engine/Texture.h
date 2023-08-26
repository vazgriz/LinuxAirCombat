#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

namespace LACEngine {
class RenderBackend;

enum struct TextureFormat {
    None,
    R,
    RG,
    RGB,
    RGBA,
    B,
    BG,
    BGR,
    BGRA
};

enum struct TextureAlphaType {
    None = -1,
    BrightnessMask = 0,
    MaxColor,
    Red,
    Midcolor,
    Red_White,
    Red2_Black,
    Red_Black
};

class Texture {
public:
    Texture(TextureFormat format, int32_t width, int32_t height, TextureAlphaType alphaType);
    Texture(const Texture& other) = delete;
    Texture(Texture&& other) noexcept;

    int32_t GetWidth() const;
    int32_t GetHeight() const;
    TextureFormat GetFormat() const;
    TextureAlphaType GetAlphaType() const;

    void SetRenderBackend(RenderBackend* renderBackend);

    bool HasLocalData() const;
    bool HasRenderData() const;

    char* GetLocalData();
    size_t GetLocalDataSize() const;
    char* CreateLocalData();
    void ReleaseLocalData();

    void* GetRenderData() const;
    void SetRenderData(void* data);

private:
    int32_t m_width;
    int32_t m_height;
    TextureFormat m_format;
    TextureAlphaType m_alphaType;

    void* m_renderBackend;
    std::vector<char> m_localData;
    void* m_renderData;
};

std::shared_ptr<Texture> TryLoadFromTGA(const std::string& filename, TextureAlphaType alphaType);

}