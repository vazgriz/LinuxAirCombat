cmake_minimum_required(VERSION 3.19)

project(ModelViewer)

add_executable(ModelViewer
    "main.cpp"
)
target_include_directories(ModelViewer PUBLIC ${LAC_Engine_include_all})
target_link_libraries(ModelViewer Engine ${LAC_Engine_bin_all})
set_target_properties(ModelViewer PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(ModelViewer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(CopyAssetsModelViewer
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)
add_dependencies(ModelViewer CopyAssetsModelViewer)