#include "Engine/Mesh.h"

#include <stdexcept>

#include "Engine/RenderBackend.h"

using namespace LACEngine;

VertexData::VertexData(MeshData meshDataType, VertexFormat vertexFormat) {
    m_meshDataType = meshDataType;
    m_vertexFormat = vertexFormat;
}

size_t VertexData::GetVertexSize(VertexFormat vertexFormat) {
    switch (vertexFormat) {
    case VertexFormat::Float32_Vec4:
        return 4 * sizeof(float);
    case VertexFormat::Float32_Vec3:
        return 3 * sizeof(float);
    case VertexFormat::Float32_Vec2:
        return 2 * sizeof(float);
    case VertexFormat::Uint8_Vec4:
        return 4 * sizeof(uint8_t);
    }
}

size_t VertexData::GetVertexCount() const {
    return m_count;
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
    ResizeLocalData(size);
    size_t vertexSize = GetVertexSize(m_vertexFormat);
    memcpy(m_localData.data(), data, m_count * size);
}

void VertexData::ResizeLocalData(size_t size) {
    size_t vertexSize = GetVertexSize(m_vertexFormat);
    m_count = size / vertexSize;
    m_localData.resize(m_count * vertexSize);
}

void* VertexData::GetLocalData() {
    return m_localData.data();
}

const void* VertexData::GetLocalData() const {
    return m_localData.data();
}

size_t VertexData::GetLocalDataSize() const {
    return m_localData.size();
}

Mesh::Mesh() : m_renderBackend(nullptr), m_renderData(nullptr), m_hasTexture(false) {

}

Mesh::~Mesh() {
    if (m_renderBackend != nullptr && m_renderData != nullptr) {
        m_renderBackend->UnloadMesh(*this);
    }
}

void Mesh::SetRenderBackend(RenderBackend* renderBackend) {
    m_renderBackend = renderBackend;
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

bool Mesh::HasIndexData() const {
    return m_hasIndexData;
}

size_t Mesh::GetIndexDataCount() const {
    return m_indexData.size();
}

const uint16_t* Mesh::GetIndexData() const {
    return m_indexData.data();
}

bool Mesh::SetHasIndexData(bool value) {
    m_hasIndexData = value;
}

void Mesh::SetIndexData(size_t count, uint16_t* data) {
    m_indexData.resize(count);
    memcpy(m_indexData.data(), data, count * sizeof(uint16_t));
}

void Mesh::ResizeIndexData(size_t count) {
    m_indexData.resize(count);
}

uint16_t* Mesh::GetIndexData() {
    return m_indexData.data();
}

void Mesh::SetHasTexture(bool value) {
    m_hasTexture = value;
}

bool Mesh::HasTexture() const {
    return m_hasTexture;
}

void Mesh::SetMaterial(const std::shared_ptr<Material>& material) {
    m_material = material;
}

std::shared_ptr<Material> Mesh::GetMaterial() {
    return m_material;
}

std::shared_ptr<const Material> Mesh::GetMaterial() const {
    return m_material;
}

void Mesh::SetName(std::string&& name) {
    m_name = std::move(name);
}

void Mesh::SetName(const std::string& name) {
    m_name = name;
}

const std::string& Mesh::GetName() const {
    return m_name;
}