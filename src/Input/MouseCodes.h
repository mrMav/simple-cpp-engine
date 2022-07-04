#pragma once

#include <iostream>
#include <string>

namespace Engine
{
	using MouseCode = uint16_t;

	struct Cursor
	{
		uint32_t x, y;

		std::string ToString() const
		{
			return std::string(std::to_string(x) + ", " + std::to_string(y));
		}

	};

	namespace Mouse
	{
		enum : MouseCode
		{
			MouseButtonLeft   = 0,
			MouseButtonRight  = 1,
			MouseButtonMiddle = 2
		};

	}
}
