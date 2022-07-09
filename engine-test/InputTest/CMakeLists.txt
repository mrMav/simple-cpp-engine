
set(TESTNAME input-test)

add_executable(${TESTNAME} InputTest.cpp)

target_include_directories(${TESTNAME}
    PUBLIC ../../src
)

target_link_directories(${TESTNAME} PRIVATE src/simple-cpp-engine)

target_link_libraries(${TESTNAME} simple-cpp-engine)

add_dependencies(${TESTNAME} simple-cpp-engine)
