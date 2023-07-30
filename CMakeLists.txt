cmake_minimum_required(VERSION 3.8)

project(LinuxAirCombat)

set(GLUT_include)
set(GLUT_bin)
set(GL_include)
set(GL_bin)
set(SDL_include)
set(SDL_bin)
set(SDL_mixer_include)
set(SDL_mixer_bin)

set(LAC_include "src")

add_library(Common
    "src/common.cpp"
)
target_include_directories(Common PUBLIC ${LAC_include} ${GLUT_include} ${GL_include} ${SDL_include} ${SDL_mixer_include})
target_link_libraries(Common ${GLUT_bin} ${GL_bin} ${SDL_bin} ${SDL_mixer_bin})

add_library(ModelLoader3DS
    "src/3ds.cpp"
)
target_link_libraries(ModelLoader3DS Common)

add_executable(LinuxAirCombat
    "src/main.cpp"
)
target_link_libraries(LinuxAirCombat ModelLoader3DS)