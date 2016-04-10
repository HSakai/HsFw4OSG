#include <iostream>
#include "Utils.h"


namespace HsEngine
{
	template <typename T, std::size_t N>
	std::size_t ArrayLength (const T (&array)[N])
	{
		return N;
	}

	void PutLog (const std::string& logText)
	{
		std::cout << logText << std::endl;
	}
}
