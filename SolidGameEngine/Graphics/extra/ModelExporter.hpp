#ifndef __SOLID_GRAPHICS_MODEL_EXPORTER_HPP__
#define __SOLID_GRAPHICS_MODEL_EXPORTER_HPP__
#include <map>
#include <iostream>
#include "../../Utils/StringLoader.hpp"
#include "Model.hpp"

namespace Solid
{
	namespace Graphics
	{
		class ModelExporter
		{
			public:
				bool operator()(std::istream& is,std::map<std::string, Model> models)
				{
					return loadFromStream(is,models);
				}
				bool operator()(std::string filename,std::map<std::string, Model> models)
				{
					return loadFromFile(filename,models);
				}

			public:
				virtual bool loadFromStream(std::istream& is,std::map<std::string, Model> models) = 0;
				virtual bool loadFromFile(std::string filename,std::map<std::string, Model> models) = 0;
		};
	}
}

#endif
