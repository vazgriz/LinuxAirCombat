#pragma once
#include <vector>
#include <memory>

#include "Engine/Material.h"

namespace LACEngine {
class RenderBackend;

enum class MeshData {
    Position,
    Normal,
    UV,
    VertexColor
};

enum class VertexFormat {
    Float32_Vec4,
    Float32_Vec3,
    Float32_Vec2,
    Uint8_Vec4
};

class VertexData {
public:
    VertexData(MeshData meshDataType, VertexFormat vertexFormat);

    MeshData GetMeshDataType() const;
    VertexFormat GetVertexFormat() const;

    bool IsLocalDataLoaded();
    void LoadLocalData(size_t size, void* data);

    const void* GetLocalData() const;
    size_t GetLocalDataSize() const;

private:
    MeshData m_meshDataType;
    VertexFormat m_vertexFormat;
    std::vector<char> m_localData;  //stored CPU data
};

class Mesh {
public:
    Mesh();
    ~Mesh();

    void SetRenderBackend(RenderBackend* renderBackend);

    void AddVertexData(const std::shared_ptr<VertexData>& vertexData);

    void* GetRenderData() const;
    void SetRenderData(void* data);

    size_t GetVertexDataCount() const;
    const VertexData& GetVertexData(size_t i) const;

    void SetHasTexture(bool value);
    bool HasTexture() const;

    void SetMaterial(const std::shared_ptr<Material>& material);
    std::shared_ptr<Material> GetMaterial();
    std::shared_ptr<const Material> GetMaterial() const;

private:
    RenderBackend* m_renderBackend;
    void* m_renderData;
    std::vector<std::shared_ptr<VertexData>> m_vertexData;

    bool m_hasTexture;
    std::shared_ptr<Material> m_material;
};

}