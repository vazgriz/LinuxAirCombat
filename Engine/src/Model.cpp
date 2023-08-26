#include "Engine/Model.h"

using namespace LACEngine;

Material& Model::AddMaterial() {
    m_materials.emplace_back(std::make_shared<Material>());
    return *m_materials.back();
}

Mesh& Model::AddMesh() {
    m_meshes.emplace_back(std::make_shared<Material>());
    return *m_meshes.back();
}

size_t Model::GetMaterialCount() const {
    return m_materials.size();
}

std::shared_ptr<Material> Model::GetMaterial(size_t index) {
    return m_materials[index];
}

std::shared_ptr<const Material> Model::GetMaterial(size_t index) const {
    return m_materials[index];
}

size_t Model::GetMeshCount() const {
    return m_meshes.size();
}

std::shared_ptr<Mesh> Model::GetMesh(size_t index) {
    return m_meshes[index];
}

std::shared_ptr<const Mesh> Model::GetMesh(size_t index) const {
    return m_meshes[index];
}

void Model::SetMainScale(float scale) {
    m_mainScale = scale;
}

float Model::GetMainScale() const {
    return m_mainScale;
}