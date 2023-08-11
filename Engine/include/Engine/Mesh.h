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

    bool IsLocalDataLoaded();
    void LoadLocalData(size_t size, void* data);
private:
    MeshData m_meshDataType;
    VertexFormat m_vertexFormat;
    std::vector<char> m_localData;  //stored CPU data
};

class Mesh {
public:
    void AddVertexData(const std::shared_ptr<VertexData>& vertexData);

private:
    std::vector< std::shared_ptr<VertexData>> m_vertexData;
};

}