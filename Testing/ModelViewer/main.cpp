#include <iostream>
#include <memory>
#include <fstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#define SDL_MAIN_HANDLED
#include <Engine/Window.h>
#include <Engine/GLBackend.h>
#include <Engine/Mesh.h>
#include <Engine/Model.h>
#include <Engine/ModelLoader3ds.h>
#include <Engine/OpenGL/GLShader.h>
#include <Engine/OpenGL/GLProgram.h>

LACEngine::GLShader LoadShader(const std::string& path, uint32_t shaderType) {
    LACEngine::GLShader shader(shaderType);

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::vector<char> buffer;
    buffer.resize(file.tellg());
    file.seekg(0);
    file.read(buffer.data(), buffer.size());

    shader.LoadSource(buffer.size(), buffer.data());

    return shader;
}

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

    LACEngine::GLBackend backend;
    backend.SetWindowSize(window->GetWidth(), window->GetHeight());

    std::shared_ptr<LACEngine::VertexData> vertexData = std::make_shared<LACEngine::VertexData>(LACEngine::MeshData::Position, LACEngine::VertexFormat::Float32_Vec3);

    LACEngine::Model model;
    LACEngine::CLoad3DS loader;
    loader.Import3DS(model, "data/a6m2.3ds");

    for (size_t i = 0; i < model.GetMeshCount(); i++) {
        LACEngine::Mesh& mesh = *model.GetMesh(i);

        backend.LoadMesh(mesh);
    }

    LACEngine::GLProgram program;

    {
        LACEngine::GLShader vertexShader = LoadShader("data/shaders/test.vertex", GL_VERTEX_SHADER);
        LACEngine::GLShader fragmentShader = LoadShader("data/shaders/test.fragment", GL_FRAGMENT_SHADER);

        program.AttachShader(vertexShader);
        program.AttachShader(fragmentShader);
        program.Link();
    }

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

        program.Use();

        for (size_t i = 0; i < model.GetMeshCount(); i++) {
            LACEngine::Mesh& mesh = *model.GetMesh(i);
            static_cast<LACEngine::GLMesh*>(mesh.GetRenderData())->Bind();

            if (mesh.HasIndexData()) {
                glDrawElements(GL_TRIANGLES, mesh.GetIndexDataCount(), GL_UNSIGNED_SHORT, 0);
            } else {
                glDrawArrays(GL_TRIANGLES, 0, mesh.GetVertexData(0).GetVertexCount());
            }
        }

        window->SwapBuffers();
    }

    SDL_Quit();
    return 0;
}