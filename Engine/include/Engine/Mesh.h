#pragma once
#include <vector>

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
private:
    MeshData m_meshDataType;
    VertexFormat m_vertexFormat;
    void* m_LocalData;
};

class Mesh {
private:
    std::vector<VertexData> m_vertexData;
};

}