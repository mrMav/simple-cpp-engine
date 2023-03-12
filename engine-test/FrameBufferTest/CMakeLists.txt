
set(TESTNAME framebuffer-test)

add_executable(${TESTNAME} FrameBufferTestApp.cpp FrameBufferTest.cpp FrameBufferTest.h)

target_include_directories(${TESTNAME}
    PUBLIC ../../src
)

target_link_directories(${TESTNAME} PRIVATE src/simple-cpp-engine)

target_link_libraries(${TESTNAME} simple-cpp-engine)

add_dependencies(${TESTNAME} simple-cpp-engine)