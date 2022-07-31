#ifndef __SOLID_GRAPHICS_TEXTURE_HPP__
#define __SOLID_GRAPHICS_TEXTURE_HPP__
#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include <sstream>
#include <stb/stb_image.h>
#include "GLObject.hpp"
#include "Bindable.hpp"
#include "../../Utils/Log.hpp"

namespace Solid
{
	namespace Graphics
	{
		class TextureDescriber
		{
			public:
				GLenum texture_type;
				GLenum wrap_s = GL_REPEAT;
				GLenum wrap_t = GL_REPEAT;
				GLenum wrap_r = GL_REPEAT;
				GLenum min_filter = GL_NEAREST;
				GLenum mag_filter = GL_NEAREST;

				GLint level = 0;
				GLint internal_format;
				GLint border = 0;
				GLenum pixels_format;
				GLenum pixels_type = GL_UNSIGNED_BYTE;

				int width = 0;
				int height = 0;
				int channels_in_file = 0;
				int desired_channels = 0;
				void* pixels = nullptr;

			public:
				TextureDescriber() {}
				TextureDescriber(TextureDescriber& from)
				{
					operator=(from);
				}
				TextureDescriber& operator=(TextureDescriber& from)
				{
					texture_type = from.texture_type;
					wrap_s = from.wrap_s;
					wrap_t = from.wrap_t;
					wrap_r = from.wrap_r;
					min_filter = from.min_filter;
					mag_filter = from.mag_filter;

					level = from.level;
					internal_format = from.internal_format;
					border = from.border;
					pixels_format = from.pixels_format;
					pixels_type = from.pixels_type;

					width = from.width;
					height = from.height;
					channels_in_file = from.channels_in_file;
					desired_channels = from.desired_channels;
					pixels = from.pixels;

					return *this;
				}

			public:
				bool load_pixels_from_file(std::string filename)
				{
					pixels = (void*)stbi_load(filename.data(), &width, &height, &channels_in_file, desired_channels);
					internal_format = pixels_format = getFormatByChannels(channels_in_file);;

					bool success = (pixels != nullptr);
					if (!success)
					{
						std::stringstream sstr;
						sstr << "Failed to load from file:\"" << filename << "\"";
						Utils::loge("load texture from file", sstr.str());
					}
					return success;
				}

				GLuint gen_and_bind()
				{
					GLuint texture;
					glGenTextures(1, &texture);
					glBindTexture(texture_type, texture);
					glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, wrap_s);
					glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, wrap_t);
					glTexParameteri(texture_type, GL_TEXTURE_WRAP_R, wrap_r);
					glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, min_filter);
					glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, mag_filter);
					glTexImage2D(texture_type, level, internal_format, width, height, border, pixels_format, pixels_type, pixels);
					glGenerateMipmap(texture_type);
					return texture;
				}

				void release_pixels()
				{
					if (pixels != nullptr)
					{
						stbi_image_free(pixels);
						pixels = nullptr;
					}
				}

			public:
				static GLenum getFormatByChannels(int channels)
				{
					GLenum result;
					switch (channels)
					{
						case 1:
							result = GL_RED;
							break;
						case 2:
							result = GL_RG;
							break;
						case 3:
							result = GL_RGB;
							break;
						case 4:
							result = GL_RGBA;
							break;
						default:
							break;
					}
					return result;
				}
		};

		class Texture : public GLObject, public Bindable
		{
			private:
				TextureDescriber m_describer;

			public:
				Texture(GLenum texture_type) : GLObject(), m_describer()
				{
					m_describer.texture_type = texture_type;
				}
				Texture(GLenum texture_type, GLuint id) : GLObject(id), m_describer()
				{
					m_describer.texture_type = texture_type;
				}
				Texture(Texture& from) : GLObject(from), m_describer(from.m_describer) {}
				Texture(GLuint id, TextureDescriber describer) : GLObject(id), m_describer(describer) {}
				Texture(TextureDescriber describer) : GLObject(), m_describer(describer) {}

			public:
				Texture& operator=(Texture& from)
				{
					GLObject::operator=(from);
					m_describer = from.m_describer;
					return *this;
				}

			public:
				Texture& setTetureDescriber(TextureDescriber describer)
				{
					m_describer = describer;
					return *this;
				}
				TextureDescriber getTextureDescriber()
				{
					return m_describer;
				}

			public:
				bool loadFromFile(std::string filename, bool release_pixels = true)
				{
					bool success = m_describer.load_pixels_from_file(filename);
					if (success)
					{
						setGLObjectID(m_describer.gen_and_bind());
					}
					if (release_pixels)
					{
						m_describer.release_pixels();
					}
					return success;
				}

				Texture& bindByDescriber()
				{
					setGLObjectID(m_describer.gen_and_bind());
					m_describer.release_pixels();
					return *this;
				}

			public:
				virtual void bind() const
				{
					if (!object_is_null())
					{
						glBindTexture(m_describer.texture_type, getGLObjectID());
					}
				}

				virtual void bindZero() const
				{
					glBindTexture(m_describer.texture_type, 0);
				}

				virtual GLuint gen()
				{
					GLuint old = getGLObjectID();
					setGLObjectID(m_describer.gen_and_bind());
					return old;
				}

				virtual Texture& genAndDelete()
				{
					GLuint old = gen();
					if (old != 0)
					{
						glDeleteTextures(1, &old);
					}
					return *this;
				}

				virtual Texture& deleteGLObject()
				{
					if (!object_is_null())
					{
						GLuint id = getGLObjectID();
						glDeleteTextures(1, &id);
						setGLObjectID(0);
					}
					return *this;
				}
		};

		class Texture2D : public Texture
		{
			public:
				Texture2D() : Texture(GL_TEXTURE_2D) {}
				Texture2D(GLuint id) : Texture(GL_TEXTURE_2D, id) {}
				Texture2D(Texture2D& from) : Texture(from) {}
				Texture2D(TextureDescriber describer) : Texture(describer) {}
				Texture2D(GLuint id, TextureDescriber describer) : Texture(id, describer) {}
		};
	}
}

#endif
