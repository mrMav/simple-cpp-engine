#pragma once

#define _ENGINE_PASS_OR_RETURN(x) if (!(x)) { return; };

#define _ENGINE_LOG(SYSTEM, MESSAGE) std::cout << SYSTEM << ":: " << MESSAGE << std::endl;