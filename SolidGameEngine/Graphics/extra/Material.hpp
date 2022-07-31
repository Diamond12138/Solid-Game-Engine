#ifndef __SOLID_GRAPHICS_MATERIAL_HPP__
#define __SOLID_GRAPHICS_MATERIAL_HPP__
#include <glm/glm.hpp>
#include "../core/Texture.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Material
		{
			public:
				glm::vec3 ambient_color = glm::vec3(1.0f,1.0f,1.0f);
				glm::vec3 diffuse_color = glm::vec3(1.0f,1.0f,1.0f);
				glm::vec3 specular_color = glm::vec3(1.0f,1.0f,1.0f);
				
				Texture2D diffuse_texture;
				Texture2D specular_texture;
				
				float shininess = 1.0f;
				float dissolve = 1.0f;
				
			public:
				Material() {}
				Material(Material& from)
				{
					operator=(from);
				}
				
			public:
				Material& operator=(Material& from)
				{
					ambient_color = from.ambient_color;
					diffuse_color = from.ambient_color;
					specular_color = from.specular_color;
					diffuse_texture = from.diffuse_texture;
					specular_texture = from.specular_texture;
					shininess = from.shininess;
					dissolve = from.dissolve;
					return *this;
				}
		};
	}
}

#endif
