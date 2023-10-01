
set(TESTNAME input-test)

add_executable(${TESTNAME} InputTest.cpp)

# Setup links and includes
setup_test(${TESTNAME})
