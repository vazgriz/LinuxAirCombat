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

#include "Engine/MeshLoader3ds.h"
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

void CLoad3DS::Compile(Model& model) {
    // Merge numerically equal vertices
    // This is necessary to get a smooth shaded object
    int i;
    for (i = 0; i < model.GetMeshCount(); i++) {
        Mesh& co = *model.GetMesh(i);
        for (int i2 = 1; i2 < co.numVertices; i2++) {
            for (int i3 = 0; i3 < i2; i3++) {
                if (co.vertex[i2].vector.isEqual(&co.vertex[i3].vector) &&   // same coordinates
                    co.vertex[i2].tex.isEqual(&co.vertex[i3].tex))           // same texture coordinates
                {
                    for (int i4 = 0; i4 < co.numTriangles; i4++) {
                        if (co.triangle[i4].v[0] == &co.vertex[i2]) {
                            co.triangle[i4].v[0] = &co.vertex[i3];
                        }
                        if (co.triangle[i4].v[1] == &co.vertex[i2]) {
                            co.triangle[i4].v[1] = &co.vertex[i3];
                        }
                        if (co.triangle[i4].v[2] == &co.vertex[i2]) {
                            co.triangle[i4].v[2] = &co.vertex[i3];
                        }
                    }
                }
            }
        }
    }
    // Scale texture coordinated by uscale, vscale
    for (i = 0; i < model.GetMeshCount(); i++) {
        Mesh& co = *model.GetMesh(i);
        float uscale = co.material->uscale;
        float vscale = co.material->vscale;
        float uoffset = co.material->uoffset;
        float voffset = co.material->voffset;

        for (int i2 = 0; i2 < co.numVertices; i2++) {
            float ax = co.vertex[i2].tex.x - 0.5;
            float ay = co.vertex[i2].tex.y - 0.5;
            float phi = -co.material->wrot;
            co.vertex[i2].tex.x = ax * COS(phi) - ay * SIN(phi) + 0.5;
            co.vertex[i2].tex.y = ax * SIN(phi) + ay * COS(phi) + 0.5;
            co.vertex[i2].tex.x -= uoffset;
            co.vertex[i2].tex.y += voffset;
            co.vertex[i2].tex.x = (co.vertex[i2].tex.x - 0.5) * uscale + 0.5;
            co.vertex[i2].tex.y = (co.vertex[i2].tex.y - 0.5) * vscale + 0.5;
        }
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
        for (i2 = 0; i2 < object.numVertices; i2++) {
            if (object.hasTexture) {
                CVertex* v = &object.vertex[i2];
                CTexture* tex = object.material->texture;
                tex->getColor(&c, (int)(v->tex.x * tex->width), (int)(v->tex.y * tex->height));
                int val;
                if (c.c[0] < 200 || c.c[1] < 200) {
                    val = c.c[0];
                    val = val * 2 / 3;
                    c.c[0] = val;
                    val = c.c[1];
                    val = val * 2 / 3;
                    c.c[1] = val;
                    val = c.c[2];
                    val = val * 2 / 3;
                    c.c[2] = val;
                }
                v->color.take(&c);
            } else {
                if (object.material) {
                    object.vertex[i2].color.c[0] = object.material->color.c[0];
                    object.vertex[i2].color.c[1] = object.material->color.c[1];
                    object.vertex[i2].color.c[2] = object.material->color.c[2];
                } else {
                    object.vertex[i2].color.c[0] = 200;
                    object.vertex[i2].color.c[1] = 200;
                    object.vertex[i2].color.c[2] = 200;
                }
            }
        }
    }
}

void CLoad3DS::ComputeNormals(Model& model) {
    int i, i2, i3;

    if (model.GetMeshCount() <= 0) {
        return;
    }
    glm::vec3 n;
    for (i = 0; i < model.GetMeshCount(); i++) {
        Mesh& object = *model.GetMesh(i);
        for (i2 = 0; i2 < object.numTriangles; i2++) {
            object.triangle[i2].getNormal(&n);
            for (i3 = 0; i3 < 3; i3++) {
                object.triangle[i2].v[i3]->addNormal(&n);
            }
        }
        for (i2 = 0; i2 < object.numTriangles; i2++) {
            for (i3 = 0; i3 < 3; i3++) {
                object.triangle[i2].v[i3]->normal.norm();
            }
        }
    }
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

    Compile(model);

    ComputeNormals(model);

    LoadTextures(model);

    ComputeColors(model);
    // Set vertices to [(-1,-1,-1);(1,1,1)]
    Normalize(model);
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

void CLoad3DS::Normalize(Model& model) {
    int i, i2;
    float minx = 1E10, miny = 1E10, minz = 1E10;
    float maxx = -1E10, maxy = -1E10, maxz = -1E10;

    for (i = 0; i < model->numObjects; i++) {
        CObject& object = *model->object[i];
        for (i2 = 0; i2 < object.numVertices; i2++) {
            CVertex* v = &object.vertex[i2];
            if (v->vector.x > maxx) {
                maxx = v->vector.x;
            }
            if (v->vector.y > maxy) {
                maxy = v->vector.y;
            }
            if (v->vector.z > maxz) {
                maxz = v->vector.z;
            }
            if (v->vector.x < minx) {
                minx = v->vector.x;
            }
            if (v->vector.y < miny) {
                miny = v->vector.y;
            }
            if (v->vector.z < minz) {
                minz = v->vector.z;
            }
        }
    }
    float tlx = (maxx + minx) / 2.0;
    float tly = (maxy + miny) / 2.0;
    float tlz = (maxz + minz) / 2.0;
    model->scalex = (maxx - minx) * 0.5;
    model->scaley = (maxy - miny) * 0.5;
    model->scalez = (maxz - minz) * 0.5;
    float sc = model->scalex > model->scaley ? model->scalex : model->scaley;
    sc = model->scalez > sc ? model->scalez : sc;
    for (i = 0; i < model->numObjects; i++) {
        CObject& object = *model->object[i];
        for (i2 = 0; i2 < object.numVertices; i2++) {
            CVertex* v = &object.vertex[i2];
            v->vector.x -= tlx;
            v->vector.x /= sc;
            v->vector.y -= tly;
            v->vector.y /= sc;
            v->vector.z -= tlz;
            v->vector.z /= sc;
        }
    }
}

void CLoad3DS::ProcessNextChunk(Model& model, Chunk* previousChunk) {
    char version[10];
    char buf[STDSIZE];
    CObject newObject;
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
            model->AddMaterial();
            ProcessNextMaterialChunk(model, currentChunk);
            break;
        case OBJECT:
            model->addObject(&newObject);
            memset(&newObject, 0, sizeof(CObject));
            currentChunk->bytesRead += GetString(model->object[model->numObjects - 1]->name);
            ProcessNextObjectChunk(model, model->object[model->numObjects - 1].get(), currentChunk);
            break;
        case MAINSCALE:
            float mainscale;
            currentChunk->bytesRead += file->readFloat(&mainscale);
            model->scale = mainscale;
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

void CLoad3DS::ProcessNextMaterialChunk(Model* model, Chunk* previousChunk) {
    currentChunk = new Chunk;

    if (currentChunk == NULL) {
        throw std::runtime_error("Out of memory");
    }

    Material& material = *model->GetMaterial(model->GetMaterialCount() - 1);

    while (previousChunk->bytesRead < previousChunk->length) {
        ReadChunk(currentChunk);
        switch (currentChunk->ID) {
        case MAT_NAME:
            currentChunk->bytesRead += file->readString(material.name);
            break;
        case MAT_DIFFUSE:
            ReadColorChunk(material, currentChunk);
            break;
        case MAT_MAP:
            ProcessNextMaterialChunk(model, currentChunk);
            break;
        case MAT_MAPFILE:
            currentChunk->bytesRead += file->readString(material.filename);
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
    tempChunk->bytesRead += file->readBinary(reinterpret_cast<char*>(material.color.elements.data()), 4);
    pChunk->bytesRead += tempChunk->bytesRead;
}

void CLoad3DS::ReadMeshMatrix(CObject* object, Chunk* previousChunk) {
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

void CLoad3DS::ReadUVCoordinates(CObject* object, Chunk* previousChunk) {
    previousChunk->bytesRead += file->readUInt16((uint16_t*)&object->numTexVertex);
    CVector2* p = new CVector2[object->numTexVertex];
    if (p == NULL) {
        throw std::runtime_error("Out of memory");
    }
    previousChunk->bytesRead += file->readFloat((float*)p, (previousChunk->length - previousChunk->bytesRead) / 4);
    for (int i = 0; i < object->numTexVertex; i++) {
        object->vertex[i].tex.take(&p[i]);
    }
    delete p;
}

void CLoad3DS::ReadVertexIndices(CObject* object, Chunk* previousChunk) {
    uint16_t index = 0;
    previousChunk->bytesRead += file->readUInt16((uint16_t*)&object->numTriangles);
    object->triangle = new CTriangle[object->numTriangles];
    if (object->triangle == NULL) {
        throw std::runtime_error("Out of memory");
    }
    memset(object->triangle, 0, sizeof(CTriangle) * object->numTriangles);
    for (int i = 0; i < object->numTriangles; i++) {
        for (int j = 0; j < 4; j++) {
            previousChunk->bytesRead += file->readUInt16(&index);

            if (j < 3) {
                object->triangle[i].v[j] = &object->vertex[index];
            }
        }
    }
}

void CLoad3DS::ReadVertices(CObject* object, Chunk* previousChunk) {
    int i;
    previousChunk->bytesRead += file->readUInt16((uint16_t*)&object->numVertices);
    object->vertex = new CVertex[object->numVertices];
    if (object->vertex == NULL) {
        throw std::runtime_error("Out of memory");
    }
    memset(object->vertex, 0, sizeof(CVertex) * object->numVertices);
    CVector3* p = new CVector3[object->numVertices];
    if (p == NULL) {
        throw std::runtime_error("Out of memory");
    }
    previousChunk->bytesRead += file->readFloat((float*)p, (previousChunk->length - previousChunk->bytesRead) / 4);
    for (i = 0; i < object->numVertices; i++) {
        object->vertex[i].vector.take(&p[i]);
    }
    // Flip the y values with the z values (as 3DMAX changed them) and negate z
    for (i = 0; i < object->numVertices; i++) {
        float fTempY = object->vertex[i].vector.y;
        object->vertex[i].vector.y = object->vertex[i].vector.z;
        object->vertex[i].vector.z = -fTempY;
    }
    delete p;
}

