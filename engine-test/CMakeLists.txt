
add_executable(engine-test ${HEADERS} ${SOURCE} Main.cpp)

target_include_directories(engine-test
    PUBLIC ../src
)

target_link_directories(engine-test PRIVATE src/simple-cpp-engine)

target_link_libraries(engine-test simple-cpp-engine)

add_dependencies(engine-test simple-cpp-engine)

#copy the shader source to the target folder
#set(SHADERS_SOURCE
#    ${CMAKE_BINARY_DIR}/Shaders/vertex.vert
#    ${CMAKE_BINARY_DIR}/Shaders/fragment.frag
#    ${CMAKE_BINARY_DIR}/Shaders/texture.png
#)

#set(SHADERS_DIR_TEST ${CMAKE_CURRENT_BINARY_DIR}/Shaders)

#add_custom_target(COPY_SHADERS_TEST
#    COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DIR_TEST}            
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADERS_SOURCE} ${SHADERS_DIR_TEST}
#    COMMENT "Copying shaders source files to TEST build..."
#)

#add_dependencies(engine-test COPY_SHADERS_TEST)