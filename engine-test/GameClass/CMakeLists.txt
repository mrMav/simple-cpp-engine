
set(TESTNAME game-class)

add_executable(${TESTNAME} GameClass.cpp TestGame.h)

# Setup links and includes
setup_test(${TESTNAME})
