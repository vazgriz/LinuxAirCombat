#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace LACEngine {

class Window {
public:
    Window(const std::string& title, int32_t width, int32_t height, bool fullscreen);

    SDL_Window* GetWindow() const;
    void MakeCurrent();
    void SwapBuffers();

    void SetSwapInterval(int32_t value);

    void SetResizeable(bool value);

    int32_t GetWidth() const;
    int32_t GetHeight() const;

private:
    SDL_Window* m_window;
    SDL_GLContext m_context;
};

}