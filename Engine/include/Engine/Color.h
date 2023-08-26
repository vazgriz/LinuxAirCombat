#pragma once
#include <stdint.h>
#include <cstring>
#include <array>

namespace LACEngine {
class Color {
public:
    union {
        std::array<uint8_t, 4> elements; // color information as vector, 32 bpp (floats would be faster for the vertex arrays)
        struct {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        };
    };

    Color();

    Color(const Color& other) {
        memcpy(&elements, &other.elements, sizeof(elements));
    }

    Color(uint8_t cr, uint8_t cg, uint8_t cb) {
        r = cr;
        g = cg;
        b = cb;
        a = 0;
    }

    Color(uint8_t cr, uint8_t cg, uint8_t cb, uint8_t ca) {
        r = cr;
        g = cg;
        b = cb;
        a = ca;
    }

    Color& operator =(const Color& other) {
        memcpy(&elements, &other.elements, sizeof(elements));
        return *this;
    }
};

inline bool operator == (const Color& left, const Color& right) {
    return left.r == right.r
        && left.g == right.g
        && left.b == right.b
        && left.a == right.a;
}

}