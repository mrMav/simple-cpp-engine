
set(TESTNAME bitmapfont)

add_executable(${TESTNAME} BitmapFontRendering.cpp BitmapFontRendering.h)

# Setup links and includes
setup_test(${TESTNAME})