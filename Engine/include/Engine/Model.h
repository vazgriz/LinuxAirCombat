#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Engine/Mesh.h"
#include "Engine/Material.h"

namespace LACEngine {

class Model {
public:
    Material& AddMaterial();
    Mesh& AddMesh();

    size_t GetMaterialCount() const;
    std::shared_ptr<Material> GetMaterial(size_t index);
    std::shared_ptr<const Material> GetMaterial(size_t index) const;

    size_t GetMeshCount() const;
    std::shared_ptr<Mesh> GetMesh(size_t index);
    std::shared_ptr<const Mesh> GetMesh(size_t index) const;

    void SetMainScale(float scale);
    float GetMainScale() const;

private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::vector<std::shared_ptr<Material>> m_materials;

    float m_mainScale;
};

Model Load3DS(const std::string& filename);

}