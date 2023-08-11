cmake_minimum_required(VERSION 3.19)

project(LinuxAirCombat)

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(LAC_include "src")
set(LAC_Engine_include "${CMAKE_CURRENT_LIST_DIR}/Engine/include/")
set(LAC_Engine_include_all ${LAC_include} ${LAC_Engine_include} ${CONAN_INCLUDE_DIRS})
set(LAC_Engine_bin_all Engine ${CONAN_LIBS})

add_subdirectory("Engine")
add_subdirectory("Testing")

add_library(Common
    "src/common.cpp"
)
target_include_directories(Common PUBLIC ${LAC_Engine_include_all})
target_link_libraries(Common ${LAC_Engine_bin_all})
set_property(TARGET Common PROPERTY CXX_STANDARD 20)

add_library(ModelLoader3DS
    "src/3ds.cpp"
)
target_link_libraries(ModelLoader3DS Common)
set_property(TARGET ModelLoader3DS PROPERTY CXX_STANDARD 20)

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
set_property(TARGET LinuxAirCombat PROPERTY CXX_STANDARD 20)
target_include_directories(LinuxAirCombat PUBLIC ${LAC_Engine_include})
target_link_libraries(LinuxAirCombat ModelLoader3DS Common)
set_target_properties(LinuxAirCombat PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/LAC)
set_target_properties(LinuxAirCombat PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LAC)

add_custom_target(CopyAssets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/LAC/data
)
add_dependencies(LinuxAirCombat CopyAssets)