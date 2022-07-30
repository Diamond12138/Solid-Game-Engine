#ifndef __SOLID_GRAPHICS_SHADER_HPP__
#define __SOLID_GRAPHICS_SHADER_HPP__
#include <string>
#include <memory>
#include <fstream>
#include "GLObject.hpp"
#include "../../Utils/Log.hpp"
#include "../../Utils/StringLoader.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Shader : public GLObject
		{
			public:
				static const GLenum UNKNOW_SHADER = 0;
				static const GLenum VERTEX_SHADER = GL_VERTEX_SHADER;
				static const GLenum FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
				static const GLenum GEOMETRY_SHADER = GL_GEOMETRY_SHADER;
				static const GLenum COMPUTE_SHADER = GL_COMPUTE_SHADER;

			private:
				GLenum m_shader_type;

			public:
				Shader(GLenum type) : GLObject(), m_shader_type(type) {}
				Shader(GLenum type, GLuint id) : GLObject(id), m_shader_type(type) {}
				Shader(Shader& from) : GLObject(from.getGLObjectID()), m_shader_type(from.getShaderType()) {}
				Shader(GLenum type, std::string source) : GLObject(), m_shader_type(type)
				{
					compileShaderAndDelete(source);
				}

			public:
				Shader& setShaderType(GLenum type)
				{
					m_shader_type = type;
					return *this;
				}
				GLenum getShaderType() const
				{
					return m_shader_type;
				}

			public:
				static GLuint compileShader(GLenum type,std::string source)
				{
					if (type != UNKNOW_SHADER)
					{
						const char* source_ref = source.data();
						GLuint shader = glCreateShader(type);
						glShaderSource(shader, 1, &source_ref, nullptr);
						glCompileShader(shader);
						int success;
						glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							int length;
							glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
							
							#ifndef SOLID_DO_NOT_DEBUG
								char* infoLog = new char[length];
								glGetShaderInfoLog(shader, length, nullptr, infoLog);
								Solid::Utils::loge("Compile Shader", infoLog);
								//Solid::loge("Compile Shader", infoLog);
								delete[] infoLog;
							#endif
							
							glDeleteShader(shader);
							return 0;
						}
						return shader;
					}
					else
					{
						return 0;
					}
				}
				
			public:
				bool compileShaderAndDelete(std::string source)
				{
					GLuint shader = compileShader(m_shader_type,source);
					if(shader == 0) return false;
					GLuint old = getGLObjectID();
					setGLObjectID(shader);
					glDeleteShader(old);
					return true;
				} 
				
			public:
				bool loadFromString(std::string source)
				{
					return compileShaderAndDelete(source);
				}
				bool loadFromStream(std::istream& is)
				{
					return compileShaderAndDelete(Utils::StringLoader()(is));
				}
				bool loadFromFile(std::string filename)
				{
					return compileShaderAndDelete(Utils::StringLoader()(filename));
				}

			public:
				virtual Shader& deleteGLObject()
				{
					GLuint id = getGLObjectID();
					if (id != 0)
					{
						glDeleteShader(id);
						setGLObjectID(0);
					}
					return *this;
				}
		};
	}
}

#endif
