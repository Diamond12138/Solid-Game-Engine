#ifndef __SOLID_GRAPHICS_CHARACTER_HPP__
#define __SOLID_GRAPHICS_CHARACTER_HPP__
#include <glm/glm.hpp>
#include "../core/Texture.hpp"
#include "TextFactory.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Character
		{
			public:
				Texture2D texture;
				glm::ivec2 size;
				glm::ivec2 bearing;
				glm::ivec2 advance;
				
			public:
				Character() {}
				Character(Character& from)
				{
					operator=(from);
				}
				Character(TextureDescriber describer,glm::ivec2 s,glm::ivec2 b,glm::ivec2 a)
				: texture(describer),size(s),bearing(b),advance(a)
				{
					texture.bindByDescriber();
				}
				
			public:
				Character& operator=(Character& from)
				{
					texture = from.texture;
					size = from.size;
					bearing = from.bearing;
					advance = from.advance;
					return *this;
				}
				
			public:
				Character& bind()
				{
					texture.bind();
					return *this;
				}
				
				Character& release()
				{
					texture.deleteGLObject();
					return *this;
				}
		};
	}
}

#endif
