#ifndef __SOLID_GRAPHICS_VERTEX_ARRAY_OBJECT_GENERATOR_HPP__
#define __SOLID_GRAPHICS_VERTEX_ARRAY_OBJECT_GENERATOR_HPP__
#include <map>
#include <iostream>
#include "../../Utils/StringLoader.hpp"
#include "Model.hpp"

namespace Solid
{
	namespace Graphics
	{
		class VertexArrayObjectGenerator
		{
			public:
				GLuint operator()(Model model)
				{
					return generate(model);
				}

			public:
				static GLuint generate(Model model) {}
		};
	}
}

#endif
