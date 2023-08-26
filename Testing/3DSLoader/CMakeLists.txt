cmake_minimum_required(VERSION 3.19)

project(3DSLoader)

add_executable(3DSLoader
    "main.cpp"
)
target_include_directories(3DSLoader PUBLIC ${LAC_Engine_include_all})
target_link_libraries(3DSLoader Engine ${LAC_Engine_bin_all})
set_target_properties(3DSLoader PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(3DSLoader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(CopyAssets3DSLoader
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)
add_dependencies(3DSLoader CopyAssets3DSLoader)