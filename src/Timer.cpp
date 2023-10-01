
#include "Timer.h"

namespace Engine
{
	double Timer::Get()
	{
		return glfwGetTime();
	}
}