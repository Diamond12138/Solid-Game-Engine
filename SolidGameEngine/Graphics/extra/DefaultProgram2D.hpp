#ifndef __SOLID_GRAPHICS_EXTRA_DEFAULT_PROGRAM_2D_HPP__
#define __SOLID_GRAPHICS_EXTRA_DEFAULT_PROGRAM_2D_HPP__
#include "../core/Program.hpp"

namespace Solid
{
	namespace Graphics
	{
		namespace Extra
		{
			class DefaultProgram2D : public UsualProgram
			{
				public:
					DefaultProgram2D()
					{
						this->loadFromFile("assets/dp2d.vert","dp2d.frag");
					}
					
				public:
					virtual void initUniforms()
					{
						
					}
			};
		}
	}
}

#endif
