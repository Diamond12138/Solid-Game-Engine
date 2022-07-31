#ifndef __SOLID_GRAPHICS_MODEL_LOADER_HPP__
#define __SOLID_GRAPHICS_MODEL_LOADER_HPP__
#include <map>
#include <iostream>
#include "../../Utils/StringLoader.hpp"
#include "Model.hpp"

namespace Solid
{
	namespace Graphics
	{
		class ModelLoader
		{
			public:
				std::map<std::string, Model> operator()(std::istream& is)
				{
					return loadFromStream(is);
				}
				std::map<std::string, Model> operator()(std::string filename)
				{
					return loadFromFile(filename);
				}

			public:
				virtual std::map<std::string, Model> loadFromStream(std::istream& is) = 0;
				virtual std::map<std::string, Model> loadFromFile(std::string filename) = 0;
		};
	}
}

#endif
