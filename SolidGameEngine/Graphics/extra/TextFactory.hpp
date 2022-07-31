#ifndef __SOLID_GRAPHICS_TEXT_FACTORY_HPP__
#define __SOLID_GRAPHICS_TEXT_FACTORY_HPP__
#include <string>
#include <sstream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Character.hpp"
#include "../../Utils/Log.hpp"
#include "../core/Texture.hpp"

namespace Solid
{
	namespace Graphics
	{
		class TextFactory
		{
			public:
				FT_Library library;
				FT_Face face;

			public:
				TextFactory(std::string filename)
				{
					if (FT_Init_FreeType(&library) != 0)
					{
						Utils::loge("text factory", "Failed to init FreeType");
					}

					if (FT_New_Face(library, filename.data(), 0, &face) != 0)
					{
						std::stringstream sstr;
						sstr << "Failed to create face from file:\"" << filename << "\"";
						Utils::loge("text factory", sstr.str());
					}
				}

			public:
				TextFactory& setPixelSizes(float width, float height)
				{
					FT_Set_Pixel_Sizes(face, width, height);
					return *this;
				}

				TextFactory& release()
				{
					FT_Done_Face(face);
					FT_Done_FreeType(library);
					return *this;
				}

				Character loadCharacter(char ch)
				{
					if (FT_Load_Char(face, ch, FT_LOAD_RENDER) != 0)
					{
						std::stringstream sstr;
						sstr << "Failed to load Character from character:\"" << ch << "\"";
						Utils::loge("text factory :: load character", sstr.str());
					}
					
					const int WIDTH = face->glyph->bitmap.width;
					const int HEIGHT = face->glyph->bitmap.rows;
					
					TextureDescriber describer;
					describer.texture_type = GL_TEXTURE_2D;
					describer.internal_format = describer.pixels_format = GL_RED;
					describer.width = WIDTH;
					describer.height = HEIGHT;
					describer.pixels = face->glyph->bitmap.buffer;
					
					glm::ivec2 size = glm::ivec2(WIDTH,HEIGHT);
					glm::ivec2 bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
					glm::ivec2 advance = glm::ivec2(face->glyph->advance.x,face->glyph->advance.y);
					
					Character result(describer,size,bearing,advance);
					return result;
				}
		};
	}
}

#endif
