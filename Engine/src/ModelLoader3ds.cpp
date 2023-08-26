/*
    LAC (Linux Air combat)
    Copyright 2015 by Robert J. Bosen. Major portions of
    this code were derived from "gl-117", by Thomas A. Drexl and
    other contributors, who are mentioned in the "Credits" menu.

    This file is part of LAC.

    LAC is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    LAC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LAC; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* This file includes a 3ds loader. Thanks to the great NeHe Tutorials! */

/*
* "3ds" seems to be a reference to the well-known .3ds files made
* immortal by Audodesk's venerable old "3d Studio" graphics tools
* back in the 1990s. This simulator requires a folder named "models"
* containing several .3ds files that describe all of the important
* graphical components. This graphical file format suffers from the
* following well-known limitations, which limit all of the graphics
* used hereafter:
*
*  1- All meshes must be made of triangles.
*  2- All texture filenames are limited to the 8.3 DOS format.
*  3- The number of vertices and polygons per mesh is limited to 65536.
*  4- Accurate vertex normals cannot be stored in the .3ds file.
*     Instead "smoothing groups"[note 1] are used so that the receiving
*     program can recreate a (hopefully good) representation of the
*     vertex normals. This is still a hold-over legacy for many
*     animation programs today which started in the 1980s.
*  5- Object, light and camera names are limited to 10 characters.
*     Material names are limited to 16 characters.
*  6- Directional light sources are not supported.
*
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <stdexcept>

#include <glm/glm.hpp>

#include "Engine/ModelLoader3ds.h"
#include "Engine/Directories.h"

using namespace LACEngine;

extern char DebugBuf[];

FILE* debugstream3ds = stdout;

/****************************************************************************
3DS LOADER
****************************************************************************/

void CLoad3DS::CleanUp() {
    delete file;
}

// Contructor -> initialization
CLoad3DS::CLoad3DS() {
    currentChunk = new Chunk;

    if (currentChunk == NULL) {
        throw std::runtime_error("Out of memory");
    }
    tempChunk = new Chunk;
    if (tempChunk == NULL) {
        throw std::runtime_error("Out of memory");
    }
}

void CLoad3DS::ComputeColors(Model& model) {
    int i, i2;
    Color c;

    if (model.GetMeshCount() == 0) {
        return;
    }

    for (i = 0; i < model.GetMeshCount(); i++) {
        Mesh& object = *model.GetMesh(i);
        if (!object.HasTexture()) {
            size_t count = object.GetVertexData(0).GetVertexCount();
            std::shared_ptr<VertexData> vertexData = std::make_shared<VertexData>(MeshData::VertexColor, VertexFormat::Uint8_Vec4);
            vertexData->ResizeLocalData(count * VertexData::GetVertexSize(VertexFormat::Uint8_Vec4));

            Color* colors = reinterpret_cast<Color*>(vertexData->GetLocalData());
            std::shared_ptr<Material> material = object.GetMaterial();

            for (size_t i = 0; i < count; i++) {
                if (material != nullptr) {
                    colors[i] = material->color;
                } else {
                    colors[i].r = 200;
                    colors[i].g = 200;
                    colors[i].b = 200;
                }
            }
        }
    }
}

void CLoad3DS::ComputeNormals(Model& model) {
    if (model.GetMeshCount() <= 0) {
        return;
    }

    for (int i = 0; i < model.GetMeshCount(); i++) {
        Mesh& object = *model.GetMesh(i);

        size_t positionIndex = 0;

        for (size_t i = 0; i < object.GetVertexDataCount(); i++) {
            const VertexData& data = object.GetVertexData(i);
            if (data.GetMeshDataType() == MeshData::Position) {
                positionIndex = i;
                break;
            }
        }

        const VertexData& positionData = object.GetVertexData(positionIndex);
        size_t vertexCount = positionData.GetVertexCount();

        std::shared_ptr<VertexData> vertexData = std::make_shared<VertexData>(MeshData::Normal, VertexFormat::Float32_Vec3);
        vertexData->ResizeLocalData(vertexCount * sizeof(glm::vec3));

        const glm::vec3* positions = reinterpret_cast<const glm::vec3*>(positionData.GetLocalData());
        glm::vec3* normals = reinterpret_cast<glm::vec3*>(vertexData->GetLocalData());

        if (object.HasIndexData()) {
            const uint16_t* indexData = object.GetIndexData();
            size_t indexDataCount = object.GetIndexDataCount();

            for (size_t j = 0; j < indexDataCount; j += 3) {
                if (j + 2 >= indexDataCount) break;
                uint16_t i1 = indexData[i];
                uint16_t i2 = indexData[i + 1];
                uint16_t i3 = indexData[i + 3];

                glm::vec3 p1 = positions[i1];
                glm::vec3 p2 = positions[i2];
                glm::vec3 p3 = positions[i3];

                glm::vec3 normal = ComputeNormal(p1, p2, p3);

                normals[i1] = normal;
                normals[i2] = normal;
                normals[i3] = normal;
            }
        } else {
            for (size_t j = 0; j < vertexCount; j += 3) {
                if (j + 2 >= vertexCount) break;
                glm::vec3 p1 = positions[j];
                glm::vec3 p2 = positions[j + 1];
                glm::vec3 p3 = positions[j + 2];

                glm::vec3 normal = ComputeNormal(p1, p2, p3);

                normals[j] = normal;
                normals[j + 1] = normal;
                normals[j + 2] = normal;
            }
        }
    }
}

glm::vec3 CLoad3DS::ComputeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    glm::vec3 a = glm::normalize(p2 - p1);
    glm::vec3 b = glm::normalize(p3 - p1);
    glm::vec3 c = glm::cross(a, b);

    return c;
}

int CLoad3DS::GetString(char* buffer) {
    return file->readString(buffer);
}

int CLoad3DS::GetString(std::string& string) {
    return file->readString(string);
}

bool CLoad3DS::Import3DS(Model& model, const char* filename) {
    char message[255] = { 0 };
    file = new BinaryFile(filename);

    if (file == NULL) {
        throw std::runtime_error("Out of memory");
    }

    ReadChunk(currentChunk);

    if (currentChunk->ID != PRIMARY) {
        throw std::runtime_error("Unable to load PRIMARY chuck from file: " + std::string(filename));
    }

    ProcessNextChunk(model, currentChunk);

    ComputeNormals(model);

    LoadTextures(model);

    ComputeColors(model);
    // Clean up
    CleanUp();
    return true;
}

void CLoad3DS::LoadTextures(Model& model) {
    for (int i = 0; i < model.GetMeshCount(); i++) {
        Mesh& mesh = *model.GetMesh(i);

        if (mesh.HasTexture() && mesh.GetMaterial() != nullptr) {
            Material& material = *mesh.GetMaterial();
            std::string filename = Directories::getTextures(material.filename);

            material.texture = TryLoadFromTGA(filename, TextureAlphaType::None);
            if (material.texture == nullptr) {
                mesh.SetHasTexture(false);
            }
        }
    }
}

void CLoad3DS::ProcessNextChunk(Model& model, Chunk* previousChunk) {
    char version[10];
    currentChunk = new Chunk;
    if (currentChunk == NULL) {
        throw std::runtime_error("Out of memory");
    }
    while (previousChunk->bytesRead < previousChunk->length) {
        ReadChunk(currentChunk);
        if (currentChunk->ID == 0 && currentChunk->length == 0) {
            throw std::runtime_error("Error reading chunk");
        }
        switch (currentChunk->ID) {
        case VERSION:
            currentChunk->bytesRead += file->readString(version, 10, currentChunk->length - currentChunk->bytesRead);
            if (version[0] > 0x03) {
                throw std::runtime_error("This 3DS file version is newer than 3 so it may load incorrectly");
            }
            break;
        case OBJECTINFO:

            break;
        case MATERIAL:
        {
            model.AddMaterial();
            ProcessNextMaterialChunk(model, currentChunk);
            break;
        }
        case OBJECT:
        {
            Mesh& newMesh = model.AddMesh();
            std::string name;
            currentChunk->bytesRead += GetString(name);
            newMesh.SetName(name);
            ProcessNextObjectChunk(model, newMesh, currentChunk);
            break;
        }
        case MAINSCALE:
            float mainscale;
            currentChunk->bytesRead += file->readFloat(&mainscale);
            model.SetMainScale(mainscale);
            currentChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
            break;
        case EDITKEYFRAME:
            currentChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
            break;
        default:
            currentChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
            break;
        }
        previousChunk->bytesRead += currentChunk->bytesRead;
    }
    delete currentChunk;
    currentChunk = previousChunk;
}

void CLoad3DS::ProcessNextMaterialChunk(Model& model, Chunk* previousChunk) {
    currentChunk = new Chunk;

    if (currentChunk == NULL) {
        throw std::runtime_error("Out of memory");
    }

    Material& material = *model.GetMaterial(model.GetMaterialCount() - 1);

    while (previousChunk->bytesRead < previousChunk->length) {
        ReadChunk(currentChunk);
        switch (currentChunk->ID) {
        case MAT_NAME:
            currentChunk->bytesRead += file->readString(material.name, currentChunk->length - currentChunk->bytesRead);
            break;
        case MAT_DIFFUSE:
            ReadColorChunk(material, currentChunk);
            break;
        case MAT_MAP:
            ProcessNextMaterialChunk(model, currentChunk);
            break;
        case MAT_MAPFILE:
            currentChunk->bytesRead += file->readString(material.filename, currentChunk->length - currentChunk->bytesRead);
            {
                for (size_t i = 0; i < material.filename.size(); i++) {
                    material.filename[i] = tolower(material.filename[i]);
                }
            }
            break;
        case MAT_USCALE:
            ReadUScale(material, currentChunk);
            break;
        case MAT_VSCALE:
            ReadVScale(material, currentChunk);
            break;
        case MAT_UOFFSET:
            ReadUOffset(material, currentChunk);
            break;
        case MAT_VOFFSET:
            ReadVOffset(material, currentChunk);
            break;
        case MAT_ROTATION:
            ReadUVRotation(material, currentChunk);
            break;
        default:
            currentChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
            break;
        }
        previousChunk->bytesRead += currentChunk->bytesRead;
    }
    delete currentChunk;
    currentChunk = previousChunk;
}

void CLoad3DS::ProcessNextObjectChunk(Model& model, Mesh& object, Chunk* previousChunk) {
    currentChunk = new Chunk;
    if (currentChunk == NULL) {
        throw std::runtime_error("Out of memory");
    }
    while (previousChunk->bytesRead < previousChunk->length) {
        ReadChunk(currentChunk);
        switch (currentChunk->ID) {
        case OBJECT_MESH:
            ProcessNextObjectChunk(model, object, currentChunk);
            break;
        case OBJECT_VERTICES:
            ReadVertices(object, currentChunk);
            break;
        case OBJECT_FACES: // triangles
            ReadVertexIndices(object, currentChunk);
            break;
        case OBJECT_MATERIAL:
            ReadObjectMaterial(model, object, currentChunk);
            break;
        case OBJECT_UV:
            ReadUVCoordinates(object, currentChunk);
            break;
        case OBJECT_MESHMATRIX:
            ReadMeshMatrix(object, currentChunk);
            break;
        default:
            currentChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
            break;
        }
        previousChunk->bytesRead += currentChunk->bytesRead;
    }
    delete currentChunk;
    currentChunk = previousChunk;
}

void CLoad3DS::ReadChunk(Chunk* pChunk) {
    pChunk->bytesRead = file->readUInt16(&pChunk->ID);
    pChunk->bytesRead += file->readUInt32(&pChunk->length);
}

void CLoad3DS::ReadColorChunk(Material& material, Chunk* pChunk) {
    ReadChunk(tempChunk);
    int max = tempChunk->length - tempChunk->bytesRead;
    tempChunk->bytesRead += file->readBinary(reinterpret_cast<char*>(material.color.elements.data()), std::min(4, max));
    pChunk->bytesRead += tempChunk->bytesRead;
}

void CLoad3DS::ReadMeshMatrix(Mesh& object, Chunk* previousChunk) {
    float matrix[12];
    previousChunk->bytesRead += file->readFloat((float*)matrix, (previousChunk->length - previousChunk->bytesRead) / 4);
    // Where to put theses coords???
}

void CLoad3DS::ReadObjectMaterial(Model& model, Mesh& mesh, Chunk* previousChunk) {
    std::string materialName;
    previousChunk->bytesRead += GetString(materialName);
    for (int i = 0; i < model.GetMaterialCount(); i++) {
        std::shared_ptr<Material> material = model.GetMaterial(i);
        if (materialName == material->name) {
            mesh.SetMaterial(material);

            if (material->filename.size() > 0) {
                mesh.SetHasTexture(true);
            }
            break;
        }
    }
    currentChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
}

void CLoad3DS::ReadUOffset(Material& material, Chunk* previousChunk) {
    previousChunk->bytesRead += file->readFloat(&material.uoffset, 1);
    previousChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
}

void CLoad3DS::ReadUScale(Material& material, Chunk* previousChunk) {
    previousChunk->bytesRead += file->readFloat(&material.uscale, 1);
    previousChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
}

void CLoad3DS::ReadUVRotation(Material& material, Chunk* previousChunk) {
    previousChunk->bytesRead += file->readFloat(&material.wrot, 1);
    previousChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
}

void CLoad3DS::ReadVOffset(Material& material, Chunk* previousChunk) {
    previousChunk->bytesRead += file->readFloat(&material.voffset, 1);
    previousChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
}

void CLoad3DS::ReadVScale(Material& material, Chunk* previousChunk) {
    previousChunk->bytesRead += file->readFloat(&material.vscale, 1);
    previousChunk->bytesRead += file->skip(currentChunk->length - currentChunk->bytesRead);
}

void CLoad3DS::ReadUVCoordinates(Mesh& object, Chunk* previousChunk) {
    uint16_t vertexCount;
    previousChunk->bytesRead += file->readUInt16(&vertexCount);

    int size = vertexCount * sizeof(glm::vec2);
    std::shared_ptr<VertexData> vertexData = std::make_shared<VertexData>(MeshData::UV, VertexFormat::Float32_Vec2);
    vertexData->ResizeLocalData(size);

    previousChunk->bytesRead += file->readBinary(static_cast<char*>(vertexData->GetLocalData()), size);

    object.AddVertexData(vertexData);
}

void CLoad3DS::ReadVertexIndices(Mesh& object, Chunk* previousChunk) {
    uint16_t triangleCount;
    previousChunk->bytesRead += file->readUInt16(&triangleCount);

    //triangle count is the number of triangles in the mesh
    //allocate 3 uint16 for each triangle
    //need to read 4 uint16 values, only save the first 3

    object.ResizeIndexData(triangleCount * 3);

    for (uint16_t i = 0; i < triangleCount; i++) {
        uint16_t buffer[4];
        previousChunk->bytesRead += file->readBinary(reinterpret_cast<char*>(buffer), 4 * sizeof(uint16_t));
        int index = i * 3;
        object.GetIndexData()[index] = buffer[0];
        object.GetIndexData()[index + 1] = buffer[1];
        object.GetIndexData()[index + 2] = buffer[2];
    }

    object.SetHasIndexData(true);
}

void CLoad3DS::ReadVertices(Mesh& object, Chunk* previousChunk) {
    uint16_t vertexCount;
    previousChunk->bytesRead += file->readUInt16(&vertexCount);

    int size = vertexCount * sizeof(glm::vec3);
    std::shared_ptr<VertexData> vertexData = std::make_shared<VertexData>(MeshData::Position, VertexFormat::Float32_Vec3);
    vertexData->ResizeLocalData(size);

    previousChunk->bytesRead += file->readBinary(static_cast<char*>(vertexData->GetLocalData()), size);

    for (uint16_t i = 0; i < vertexCount; i++) {
        glm::vec3& vertex = *reinterpret_cast<glm::vec3*>(vertexData->GetLocalData());
        float tempY = vertex.y;
        vertex.y = vertex.z;
        vertex.z = -tempY;
    }

    object.AddVertexData(vertexData);
}

