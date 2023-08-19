cmake_minimum_required(VERSION 3.19)

project(TGALoader)

add_executable(TGALoader
    "main.cpp"
)
target_include_directories(TGALoader PUBLIC ${LAC_Engine_include_all})
target_link_libraries(TGALoader Engine ${LAC_Engine_bin_all})
set_target_properties(TGALoader PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(TGALoader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(CopyAssetsTGALoader
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)
add_dependencies(TGALoader CopyAssetsTGALoader)