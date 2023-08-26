#include "Engine/BinaryFile.h"

#include <stdexcept>

using namespace LACEngine;

const int STDSIZE = 1024;

BinaryFile::BinaryFile(const char* filename) {
    in = fopen(filename, "rb");

    if (in == NULL) {
        throw std::runtime_error("Cannot open file: " + std::string(filename));
    }

    fseek(in, 0, SEEK_END);
    size = ftell(in);
    fseek(in, 0, SEEK_SET);
    data.resize(size);
    uint32_t z = 0;
    while (z < size) {
        if (size - z >= 4096) {
            fread(&data[z], 1, 4096, in);
        } else {
            fread(&data[z], 1, size - z, in);
        }

        z += 4096;
    }
    fclose(in);
    filepointer = 0;
}

int BinaryFile::readFloat(float* f) {
    * f = *((float*)&data[filepointer]);
    filepointer += 4;
    return 4;
}

int BinaryFile::readFloat(float* f, int n) {
    int i;

    for (i = 0; i < n; i++) {
        readFloat(&f[i]);
    }

    return n * 4;
}

int BinaryFile::readString(char* ptr, int ptrmax, int n) {

    if (n <= 0) {
        return 0;
    }
    if (filepointer + n > size) {
        n = size - filepointer;
    }
    if (n > ptrmax) {
        throw std::runtime_error("Error reading string");
    }
    memcpy(ptr, &data[filepointer], n);
    filepointer += n;
    return n;
}

int BinaryFile::readString(char* ptr, int n) {

    if (n <= 0) {
        return 0;
    }
    if (filepointer + n > size) {
        n = size - filepointer;
    }
    memcpy(ptr, &data[filepointer], n);
    filepointer += n;
    return n;
}

int BinaryFile::readString(char* ptr) {
    int i = 0;
    while (data[filepointer] != 0 && filepointer < size) {
        ptr[i] = data[filepointer];
        i++;
        filepointer++;
    }
    ptr[i] = 0;
    filepointer++;
    i++;
    return i;
}

int BinaryFile::readString(std::string& str) {
    char buffer[STDSIZE];
    int count = 0;
    while (data[filepointer] != 0 && filepointer < size) {
        buffer[count] = data[filepointer];
        count++;
        filepointer++;
    }

    str.resize(count);

    memcpy(str.data(), buffer, count);

    filepointer++;
    count++;
    return count;
}

int BinaryFile::readUInt16(uint16_t* i) {
    * i = *((uint16_t*)&data[filepointer]);
    filepointer += 2;
    return 2;
}

int BinaryFile::readUInt32(uint32_t* i) {
    * i = *((uint32_t*)&data[filepointer]);
    filepointer += 4;
    return 4;
}

int BinaryFile::readBinary(char* dest, int size) {
    memcpy(dest, &data[filepointer], size);
    filepointer += size;
    return size;
}

int BinaryFile::skip(int n) {
    if (filepointer + n > size) {
        n = size - filepointer;
    }
    filepointer += n;
    return n;
}