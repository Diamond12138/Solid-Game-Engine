#ifndef __SOLID_GRAPHICS_BINDABLE_HPP__
#define __SOLID_GRAPHICS_BINDABLE_HPP__
#include "gl.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Bindable
		{
			public:
				virtual Bindable& bind() = 0;
				virtual Bindable& bindZero() = 0;
				virtual GLuint gen() = 0;
				virtual Bindable& genAndDelete() = 0;
		};
	}
}

#endif
