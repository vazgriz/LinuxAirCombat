#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#define SDL_MAIN_HANDLED
#include <Engine/Window.h>
#include <Engine/OpenGLBackend.h>
#include <Engine/Mesh.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Error: Failed to init SDL\n";
        return EXIT_FAILURE;
    }

    std::unique_ptr<LACEngine::Window> window = std::make_unique<LACEngine::Window>("Model Viewer", 1280, 720, false);

    window->MakeCurrent();
    window->SetResizeable(true);
    window->SetSwapInterval(1);

    if (gladLoadGLLoader(&SDL_GL_GetProcAddress) == 0) {
        std::cout << "Error: Failed to load OpenGL functions\n";
        return EXIT_FAILURE;
    }

    LACEngine::OpenGLBackend backend;
    backend.SetWindowSize(window->GetWidth(), window->GetHeight());

    std::shared_ptr<LACEngine::VertexData> vertexData = std::make_shared<LACEngine::VertexData>(LACEngine::MeshData::Position, LACEngine::VertexFormat::Float32_Vec3);

    glm::vec3 vertexDataRaw[] = {
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(1, 0, 0)
    };

    vertexData->LoadLocalData(sizeof(vertexDataRaw), &vertexDataRaw);

    LACEngine::Mesh mesh;
    mesh.AddVertexData(vertexData);

    backend.LoadMesh(mesh);

    SDL_Event event;
    bool shouldExit = false;

    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                shouldExit = true;
            }

            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int32_t width = window->GetWidth();
                    int32_t height = window->GetHeight();
                    backend.SetWindowSize(window->GetWidth(), window->GetHeight());
                }
            }
        }

        if (shouldExit) {
            break;
        }

        window->SwapBuffers();
    }

    SDL_Quit();
    return 0;
}