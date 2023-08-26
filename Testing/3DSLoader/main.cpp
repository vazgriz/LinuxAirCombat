#include <iostream>

#include <Engine/Texture.h>
#include <Engine/ModelLoader3ds.h>

int main() {
    LACEngine::Model model;
    LACEngine::CLoad3DS loader;
    loader.Import3DS(model, "data/a6m2.3ds");
    std::cout << "Loaded 3DS file\n";
}