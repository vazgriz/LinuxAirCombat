#include <iostream>

#include <Engine/Texture.h>

int main() {
    std::shared_ptr<LACEngine::Texture> texture = LACEngine::TryLoadFromTGA("data/cactus1.tga", LACEngine::TextureAlphaType::None);
    std::cout << "Loaded TGA file\n";
}