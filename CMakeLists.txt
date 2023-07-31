cmake_minimum_required(VERSION 3.19)

project(LinuxAirCombat)

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

set(LAC_include "src")

add_library(Common
    "src/common.cpp"
)
target_include_directories(Common PUBLIC ${LAC_include} ${GLUT_include} ${GL_include} ${SDL_include} ${SDL_mixer_include})
target_link_libraries(Common ${GLUT_bin} ${GL_bin} ${SDL_bin} ${SDL_mixer_bin})
set_property(TARGET Common PROPERTY CXX_STANDARD 17)

add_library(ModelLoader3DS
    "src/3ds.cpp"
)
target_link_libraries(ModelLoader3DS Common)
set_property(TARGET ModelLoader3DS PROPERTY CXX_STANDARD 17)

add_executable(LinuxAirCombat
    "src/main.cpp"
    "src/FlightModel.cpp"
    #"src/NetworkApi.cpp"
    #"src/NetworkApi.h"
    "src/aiobject.cpp"
    "src/aiobject.h"
    "src/audio.cpp"
    "src/audio.h"
    "src/cockpit.cpp"
    "src/cockpit.h"
    "src/common.cpp"
    "src/common.h"
    "src/conf.cpp"
    "src/conf.h"
    "src/config.h"
    "src/dirs.cpp"
    "src/dirs.h"
    "src/effects.cpp"
    "src/effects.h"
    "src/fileloader.cpp"
    "src/fileloader.h"
    "src/gl.cpp"
    "src/gl.h"
    "src/glland.cpp"
    "src/glland.h"
    "src/land.cpp"
    "src/land.h"
    "src/loader_tga.cpp"
    "src/mathtab.cpp"
    "src/mathtab.h"
    "src/menu.cpp"
    "src/menu.h"
    "src/mission.cpp"
    "src/mission.h"
    "src/model.cpp"
    "src/model.h"
    "src/object.cpp"
    "src/object.h"
    "src/objload.cpp"
    "src/objload.h"
    "src/pilots.cpp"
    "src/pilots.h"
    "src/PlatformFolders.cpp"
    "src/PlatformFolders.h"
    "src/vertexarray.cpp"
    "src/vertexarray.h"
)
set_property(TARGET LinuxAirCombat PROPERTY CXX_STANDARD 17)
target_link_libraries(LinuxAirCombat ModelLoader3DS Common)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_bin_dll}
        ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_mixer_bin_dll}
        ${CMAKE_CURRENT_BINARY_DIR}/SDL2_mixer.dll
)