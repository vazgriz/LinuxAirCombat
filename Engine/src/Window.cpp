#include "Engine/Window.h"

#include <stdexcept>
#include <format>

LACEngine::Window::Window(const std::string& title, int32_t width, int32_t height, bool fullscreen) {
    uint32_t video_flags;
    if (fullscreen) {
        video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
    } else {
        video_flags = SDL_WINDOW_OPENGL;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, video_flags);

    if (m_window == nullptr) {
        throw std::runtime_error(std::format("Error creating SDL window: {}", SDL_GetError()));
    }

    m_context = SDL_GL_CreateContext(m_window);

    if (m_context == nullptr) {
        throw std::runtime_error(std::format("Error creating OpenGL context: {}", SDL_GetError()));
    }
}

SDL_Window* LACEngine::Window::GetWindow() const {
    return m_window;
}

void LACEngine::Window::MakeCurrent() {
    if (SDL_GL_MakeCurrent(m_window, m_context) != 0) {
        throw std::runtime_error(std::format("Error making OpenGL context current: {}", SDL_GetError()));
    }
}

void LACEngine::Window::SwapBuffers() {
    SDL_GL_SwapWindow(m_window);
}