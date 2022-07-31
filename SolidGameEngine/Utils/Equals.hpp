#ifndef __SOLID_UTILS_EQUALS_HPP__
#define __SOLID_UTILS_EQUALS_HPP__
#include <cmath>

#define SOLID_EQUALS_MAXIMUM_DIFFERENCE (0.0001f)

namespace Solid
{
	namespace Utils
	{
		class Equals
		{
			private:
				float m_maximum_difference;
				
			public:
				Equals(float maximum_difference = SOLID_EQUALS_MAXIMUM_DIFFERENCE) : m_maximum_difference(maximum_difference) {}
				
			public:
				Equals& setMaximumDifference(float maximum_difference)
				{
					m_maximum_difference = maximum_difference;
					return *this;
				}
				float getMaximumDifference()
				{
					return m_maximum_difference;
				}
				
			public:
				bool operator()(float value1,float value2)
				{
					return (abs(value1 - value2) < m_maximum_difference);
				}
		};
		
		Equals equals;
	}
}

#endif
