#include <iostream>

#include <Engine/Texture.h>

int main() {
    LACEngine::Texture texture = LACEngine::LoadFromTGA("data/cactus1.tga", LACEngine::TextureAlphaType::None);
    std::cout << "Loaded TGA file\n";
}