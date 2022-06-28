cmake_minimum_required(VERSION 3.22)

set (CMAKE_CXX_STANDARD 17)

project(new-game)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE})

#specifies that we also have work to do on this directory
add_subdirectory(src)
add_subdirectory(src/Engine)
add_subdirectory(src/Engine/OpenGL)
add_subdirectory(src/Engine/Render)
add_subdirectory(src/Engine/Input)
add_subdirectory(src/Engine/Utils)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glm
    PUBLIC external
    PUBLIC src/Engine
)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)

target_link_libraries(${PROJECT_NAME} glfw)

#copy the shader source to the target folder
set(SHADERS_SOURCE
    ${CMAKE_SOURCE_DIR}/src/Engine/Shaders/vertex.vert
    ${CMAKE_SOURCE_DIR}/src/Engine/Shaders/fragment.frag
)

set(SHADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/Shaders)

add_custom_target(COPY_SHADERS
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DIR}            
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADERS_SOURCE} ${SHADERS_DIR}
    COMMENT "Copying shaders source files to build..."
)

add_dependencies(${PROJECT_NAME} COPY_SHADERS)