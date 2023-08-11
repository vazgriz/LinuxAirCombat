#pragma once
#include <vector>
#include <memory>

namespace LACEngine {
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

    void AddVertexData(const std::shared_ptr<VertexData>& vertexData);

    void* GetRenderData() const;
    void SetRenderData(void* data);

    size_t GetVertexDataCount() const;
    const VertexData& GetVertexData(size_t i) const;

private:
    void* m_renderData;
    std::vector<std::shared_ptr<VertexData>> m_vertexData;
};

}