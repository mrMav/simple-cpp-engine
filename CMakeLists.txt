cmake_minimum_required(VERSION 3.22)

set (CMAKE_CXX_STANDARD 17)

project(simple-cpp-engine)

# options
option(BUILD_TESTS "Build the sample tests that show case the engine usage." ON)
option(COPY_SHADERS "Copy the engine sample shaders folder to the build folder." ON)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCE})

#specifies that we also have work to do on this directory
add_subdirectory(src)
add_subdirectory(src/OpenGL)
add_subdirectory(src/Render)
add_subdirectory(src/Input)
add_subdirectory(src/Utils)

# build librarires
add_subdirectory(external)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

if(BUILD_TESTS)
    add_subdirectory(engine-test)
endif(BUILD_TESTS)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glm
    PUBLIC external/imgui
    PUBLIC external
    PUBLIC src
)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src PRIVATE external/imgui)

target_link_libraries(${PROJECT_NAME} glfw imgui)

if(COPY_SHADERS)

    #copy the shader source to the target folder
    set(SHADERS_SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/src/Shaders/vertex.vert
        ${CMAKE_CURRENT_LIST_DIR}/src/Shaders/fragment.frag
        ${CMAKE_CURRENT_LIST_DIR}/src/Shaders/texture.png
        ${CMAKE_CURRENT_LIST_DIR}/src/Shaders/dude1.png
        ${CMAKE_CURRENT_LIST_DIR}/src/Shaders/mbf_small_00.png
    )

    set(SHADERS_DIR ${CMAKE_BINARY_DIR}/Shaders)

    add_custom_target(COPY_SHADERS
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DIR}            
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADERS_SOURCE} ${SHADERS_DIR}
        COMMENT "Copying shaders source files to build..."
    )

    add_dependencies(simple-cpp-engine COPY_SHADERS)

endif(COPY_SHADERS)