#pragma once

#include <iostream>
#include "Typedefs.h"

#define _ENGINE_FAIL_WITH_MSG(CONDITION, MESSAGE)	\
if (!(CONDITION))                          \
{                                  \
std::cout << MESSAGE << std::endl; \
exit(EXIT_FAILURE);                \
} else {};
#define _ENGINE_LOG(SYSTEM, MESSAGE) std::cout << SYSTEM << ":: " << MESSAGE << std::endl;
#define _ENGINE_PASS_OR_RETURN_MSG(CONDITION, SYSTEM, MESSAGE) if (!(CONDITION)) { return; } else { _ENGINE_LOG(SYSTEM, MESSAGE) };
#define _ENGINE_PASS_OR_RETURN(CONDITION) if (!(CONDITION)) { return; } else {};
