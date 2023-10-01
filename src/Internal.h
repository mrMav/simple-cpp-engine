#pragma once

#include <iostream>
#include "Typedefs.h"

#define _ENGINE_PASS_OR_RETURN(x) if (!(x)) { return; } else {};
#define _ENGINE_FAIL_WITH_MSG(x, message)	\
if (!(x))                          \
{                                  \
std::cout << message << std::endl; \
exit(EXIT_FAILURE);                \
} else {};
#define _ENGINE_LOG(SYSTEM, MESSAGE) std::cout << SYSTEM << ":: " << MESSAGE << std::endl;
