#pragma once
#include <vector>
#include <memory>

#include "Engine/Mesh.h"
#include "Engine/Material.h"

namespace LACEngine {

class Model {
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::vector<std::shared_ptr<Mesh>> m_materials;
};

}