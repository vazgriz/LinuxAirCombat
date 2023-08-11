#include "Engine/Mesh.h"

using namespace LACEngine;

VertexData::VertexData(MeshData meshDataType, VertexFormat vertexFormat) {
    m_meshDataType = meshDataType;
    m_vertexFormat = vertexFormat;
}

bool VertexData::IsLocalDataLoaded() {
    return m_localData.size() > 0;
}

void VertexData::LoadLocalData(size_t size, void* data) {
    m_localData.reserve(size);
    memcpy(m_localData.data(), data, size);
}

void Mesh::AddVertexData(const std::shared_ptr<VertexData>& vertexData) {
    m_vertexData.push_back(vertexData);
}