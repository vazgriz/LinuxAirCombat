#include "Engine/Mesh.h"

#include <stdexcept>

using namespace LACEngine;

VertexData::VertexData(MeshData meshDataType, VertexFormat vertexFormat) {
    m_meshDataType = meshDataType;
    m_vertexFormat = vertexFormat;
}

MeshData VertexData::GetMeshDataType() const {
    return m_meshDataType;
}

VertexFormat VertexData::GetVertexFormat() const {
    return m_vertexFormat;
}

bool VertexData::IsLocalDataLoaded() {
    return m_localData.size() > 0;
}

void VertexData::LoadLocalData(size_t size, void* data) {
    m_localData.resize(size);
    memcpy(m_localData.data(), data, size);
}

const void* VertexData::GetLocalData() const {
    return m_localData.data();
}

size_t VertexData::GetLocalDataSize() const {
    return m_localData.size();
}

Mesh::Mesh() : m_renderData(nullptr) {

}

void* Mesh::GetRenderData() const {
    return m_renderData;
}

void Mesh::SetRenderData(void* data) {
    m_renderData = data;
}

void Mesh::AddVertexData(const std::shared_ptr<VertexData>& vertexData) {
    if (vertexData == nullptr) {
        throw std::runtime_error("vertexData was null");
    }

    m_vertexData.push_back(vertexData);
}

size_t Mesh::GetVertexDataCount() const {
    return m_vertexData.size();
}

const VertexData& Mesh::GetVertexData(size_t i) const {
    if (i >= m_vertexData.size()) {
        throw std::runtime_error("invalid vertexData index");
    }

    return *m_vertexData[i];
}
