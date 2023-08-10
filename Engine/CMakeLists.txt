cmake_minimum_required(VERSION 3.19)

set(GLUT_include)
set(GLUT_bin)
set(GL_include)
set(GL_bin)
set(SDL_include)
set(SDL_bin)
set(SDL_bin_dll)
set(SDL_mixer_include)
set(SDL_mixer_bin)
set(SDL_mixer_bin_dll)

add_library(Engine
    "src/Window.cpp"
    "src/Mesh.cpp"
    "src/Model.cpp"
    "src/Material.cpp"
)
target_include_directories(Engine PUBLIC ${LAC_include} ${GLUT_include} ${GL_include} ${SDL_include} ${SDL_mixer_include} "include")
target_link_libraries(Engine ${GLUT_bin} ${GL_bin} ${SDL_bin} ${SDL_mixer_bin})
set_property(TARGET Engine PROPERTY CXX_STANDARD 20)