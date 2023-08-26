#pragma once
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string>

namespace LACEngine {

// abstract binary file representation in memory
class BinaryFile {
    FILE* in; // file struct
    uint32_t size; // file size
    uint32_t filepointer; // pointer to char in memory
    std::vector<char> data; // file data in memory

public:
    // data type conversation
    BinaryFile(const char* filename);
    int readFloat(float* f);
    int readFloat(float* f, int n);
    int readUInt32(uint32_t* i);
    int readUInt16(uint16_t* i);
    int readString(char* ptr, int ptrmax, int n);
    int readString(char* ptr, int n);
    int readString(char* ptr);
    int readString(std::string& str);
    int readString(std::string& str, int n);
    int readBinary(char* dest, int n);
    int skip(int n);
};

}
