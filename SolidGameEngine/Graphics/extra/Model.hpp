#ifndef __SOLID_GRAPHICS_MODEL_HPP__
#define __SOLID_GRAPHICS_MODEL_HPP__
#include <vector>
#include <map>
#include "Material.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Model
		{
			public:
				std::vector<float> vertices;
				std::vector<float> colors;
				std::vector<float> normals;
				std::vector<unsigned int> indices;
				Material material;

			public:
				Model() {}
				Model(const Model& from)
				{
					operator=(from);
				}

			public:
				Model& operator=(const Model& from)
				{
					vertices = from.vertices;
					colors = from.colors;
					normals = from.normals;
					indices = from.indices;
					return *this;
				}
		};

		typedef std::map<std::string, Model> ModelArray;
	}
}

#endif
