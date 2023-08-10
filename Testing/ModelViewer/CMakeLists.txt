cmake_minimum_required(VERSION 3.19)

project(ModelViewer)

add_executable(ModelViewer
    "main.cpp"
)
target_include_directories(ModelViewer PUBLIC ${LAC_Engine_include_all})
target_link_libraries(ModelViewer Engine ${LAC_Engine_bin_all})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_bin_dll}
        ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
)