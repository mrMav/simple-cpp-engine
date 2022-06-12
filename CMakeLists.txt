cmake_minimum_required(VERSION 3.23.2)

project(new-game)

add_executable(${PROJECT_NAME}    
    src/glad.c
    src/main.cpp
)

#specifies that we also have work to do on this directory
add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external
)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)

target_link_libraries(${PROJECT_NAME} glfw)