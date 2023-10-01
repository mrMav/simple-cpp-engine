# Set the test name. This will be used as a target name.
set(TESTNAME framebuffer-test)

# Add the executable with all the source files.
add_executable(${TESTNAME}
    FrameBufferTestApp.cpp
    FrameBufferTest.cpp
    FrameBufferTest.h
)

# Setup links and includes
setup_test(${TESTNAME})
