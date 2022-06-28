
#include <iostream>

#include "Utils.h"

namespace Engine
{
	std::string Utils::BreakString(const std::string& str, int lineWidth)
	{
        std::string result;

        int i = 0;
        while (i < str.size())
        {
            if (i % lineWidth == 0 && i)
                result.push_back('\n');

            result.push_back(str[i]);
            i++;
        }

		return result;
	}

}




