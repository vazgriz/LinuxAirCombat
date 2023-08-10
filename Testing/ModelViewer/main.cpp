#include <iostream>

#define SDL_MAIN_HANDLED
#include <Engine/Window.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Error: Failed to init SDL\n";
        return EXIT_FAILURE;
    }

    std::unique_ptr<LACEngine::Window> window = std::make_unique<LACEngine::Window>("Model Viewer", 1280, 720, false);

    SDL_Event event;

    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    SDL_Quit();
    return 0;
}