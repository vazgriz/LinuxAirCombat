#pragma once
#include <SDL/SDL.h>
#include <string>

namespace LACEngine {

class Window {
public:
    Window(const std::string& title, int32_t width, int32_t height, bool fullscreen);

    SDL_Window* GetWindow() const;
    void MakeCurrent();
    void SwapBuffers();

private:
    SDL_Window* m_window;
    SDL_GLContext m_context;
};

}