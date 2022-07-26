#ifndef __SOLID_UTILS_TIME_HPP__
#define __SOLID_UTILS_TIME_HPP__
#include <chrono>

namespace Solid
{
	namespace Utils
	{
		typedef std::chrono::duration<float> Duration;
		typedef std::chrono::time_point<std::chrono::high_resolution_clock,Duration> Time;
	}
}

#endif
