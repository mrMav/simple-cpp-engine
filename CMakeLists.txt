cmake_minimum_required(VERSION 3.23.2)

set (CMAKE_CXX_STANDARD 17)

project(new-game)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE})

#specifies that we also have work to do on this directory
add_subdirectory(src)
add_subdirectory(src/engine)
add_subdirectory(src/engine/OpenGL)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glm
    PUBLIC external
)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)

target_link_libraries(${PROJECT_NAME} glfw)

file(COPY src/engine/Shaders DESTINATION .)