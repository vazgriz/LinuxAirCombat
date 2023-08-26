#pragma once
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

#include <vector>
#include "Model.h"

#include "Engine/BinaryFile.h"

namespace LACEngine {


    // Primary Chunk (19789)
#define PRIMARY       0x4D4D

// Main Chunks (15677, 2, 45056)
#define VERSION       0x0002
#define MAINSCALE     0x0100
#define OBJECTINFO    0x3D3D
#define EDITKEYFRAME  0xB000

// Sub defines of OBJECTINFO (45055, 16384)
#define MATERIAL	  0xAFFF
#define OBJECT		  0x4000

// Sub defines of MATERIAL
#define MAT_NAME       0xA000
#define MAT_DIFFUSE    0xA020
#define MAT_MAP        0xA200
#define MAT_MAPFILE    0xA300
#define MAT_USCALE     0xA354
#define MAT_VSCALE     0xA356
#define MAT_UOFFSET    0xA358
#define MAT_VOFFSET    0xA35A
#define MAT_ROTATION   0xA35C

// Read new object
#define OBJECT_MESH   0x4100

// Sub defines of OBJECT_MESH
#define OBJECT_VERTICES     0x4110
#define OBJECT_FACES		0x4120
#define OBJECT_MATERIAL		0x4130
#define OBJECT_UV			0x4140
#define OBJECT_MESHMATRIX			0x4160

// Structure for the 3DS indicies
    struct Indices {
        uint16_t a, b, c, bVisible;
    };

    // Chunk info
    struct Chunk {
        uint16_t ID;
        uint32_t length;
        uint32_t bytesRead;
    };

    // CLoad3DS handles all of the loading code (see NEHE's OpenGL tutorials)
    class CLoad3DS {
    public:
        BinaryFile* file;
        CLoad3DS();
        bool Import3DS(Model& model, const char* filename);

        // developer specific loading routines
    private:
        int GetString(char*);
        int GetString(std::string& string);
        void ReadChunk(Chunk*);
        void ProcessNextChunk(Model& model, Chunk*);
        void ProcessNextObjectChunk(Model& model, Mesh& object, Chunk*);
        void ProcessNextMaterialChunk(Model& model, Material& material, Chunk*);
        void ReadColorChunk(Material& material, Chunk* pChunk);
        void ReadVertices(Mesh& object, Chunk*);
        void ReadVertexIndices(Mesh& object, Chunk*);
        void ReadUVCoordinates(Mesh& object, Chunk*);
        void ReadMeshMatrix(Mesh& object, Chunk*);
        void ReadUScale(Material& material, Chunk*);
        void ReadVScale(Material& material, Chunk*);
        void ReadUOffset(Material& material, Chunk*);
        void ReadVOffset(Material& material, Chunk*);
        void ReadUVRotation(Material& material, Chunk*);
        void ReadObjectMaterial(Model& model, Mesh& object, Chunk* previousChunk);
        void ComputeNormals(Model& model);
        void ComputeColors(Model& model);
        void LoadTextures(Model& model);
        void CleanUp();
        FILE* filepointer;
        Chunk* currentChunk;
        Chunk* tempChunk;

        glm::vec3 ComputeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    };

}
