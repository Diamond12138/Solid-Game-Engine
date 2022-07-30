#ifndef __SOLID_GRAPHICS_PROGRAM_HPP__
#define __SOLID_GRAPHICS_PROGRAM_HPP__
#include <glm/glm.hpp>
//#include <glm/ext.hpp>
#include "Shader.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Program : public GLObject
		{
			public:
				Program() : GLObject() {}
				Program(GLuint id) : GLObject(id) {}
				Program(Program& from) : GLObject(from.getGLObjectID()) {}

			public:
				virtual Program& deleteGLObject()
				{
					GLuint id = getGLObjectID();
					if (id != 0)
					{
						glDeleteProgram(id);
						setGLObjectID(0);
					}
					return *this;
				}

			public:
				GLuint getUniformLocation(std::string name)
				{
					return glGetUniformLocation(getGLObjectID(), name.data());
				}
				Program& useProgram()
				{
					GLuint id = getGLObjectID();
					if (id != 0)
					{
						glUseProgram(id);
						initUniforms();
					}
					return *this;
				}
				virtual void initUniforms() {}

			public:
				virtual bool loadFromFile(std::string file_prefix) = 0;

			public:
				//scalar 1
				Program& setUniform(std::string name, int value)
				{
					GLuint location = getUniformLocation(name);
					glUniform1i(location, value);
					return *this;
				}
				Program& setUniform(GLuint location, int value)
				{
					glUniform1i(location, value);
					return *this;
				}
				Program& setUniform(std::string name, bool value)
				{
					GLuint location = getUniformLocation(name);
					glUniform1i(location, value);
					return *this;
				}
				Program& setUniform(GLuint location, bool value)
				{
					glUniform1i(location, value);
					return *this;
				}
				Program& setUniform(std::string name, float value)
				{
					GLuint location = getUniformLocation(name);
					glUniform1i(location, value);
					return *this;
				}
				Program& setUniform(GLuint location, float value)
				{
					glUniform1f(location, value);
					return *this;
				}
				Program& setUniform(std::string name, double value)
				{
					GLuint location = getUniformLocation(name);
					glUniform1d(location, value);
					return *this;
				}
				Program& setUniform(GLuint location, double value)
				{
					glUniform1d(location, value);
					return *this;
				} Program& setUniform(std::string name, unsigned int value)
				{
					GLuint location = getUniformLocation(name);
					glUniform1ui(location, value);
					return *this;
				}
				Program& setUniform(GLuint location, unsigned int value)
				{
					glUniform1ui(location, value);
					return *this;
				}

				//vector 2
				Program& setUniform(std::string name, glm::ivec2 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform2i(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(GLuint location, glm::ivec2 value)
				{
					glUniform2i(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(std::string name, glm::vec2 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform2f(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(GLuint location, glm::vec2 value)
				{
					glUniform2f(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(std::string name, glm::dvec2 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform2d(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(GLuint location, glm::dvec2 value)
				{
					glUniform2d(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(std::string name, glm::uvec2 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform2ui(location, value.x, value.y);
					return *this;
				}
				Program& setUniform(GLuint location, glm::uvec2 value)
				{
					glUniform2ui(location, value.x, value.y);
					return *this;
				}

				//vector 3
				Program& setUniform(std::string name, glm::ivec3 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform3i(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(GLuint location, glm::ivec3 value)
				{
					glUniform3i(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(std::string name, glm::vec3 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform3f(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(GLuint location, glm::vec3 value)
				{
					glUniform3f(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(std::string name, glm::dvec3 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform3d(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(GLuint location, glm::dvec3 value)
				{
					glUniform3d(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(std::string name, glm::uvec3 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform3ui(location, value.x, value.y, value.z);
					return *this;
				}
				Program& setUniform(GLuint location, glm::uvec3 value)
				{
					glUniform3ui(location, value.x, value.y, value.z);
					return *this;
				}

				//vector 4
				Program& setUniform(std::string name, glm::ivec4 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform4i(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(GLuint location, glm::ivec4 value)
				{
					glUniform4i(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(std::string name, glm::vec4 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform4f(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(GLuint location, glm::vec4 value)
				{
					glUniform4f(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(std::string name, glm::dvec4 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform4d(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(GLuint location, glm::dvec4 value)
				{
					glUniform4d(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(std::string name, glm::uvec4 value)
				{
					GLuint location = getUniformLocation(name);
					glUniform4ui(location, value.x, value.y, value.z, value.w);
					return *this;
				}
				Program& setUniform(GLuint location, glm::uvec4 value)
				{
					glUniform4ui(location, value.x, value.y, value.z, value.w);
					return *this;
				}

				//matrix 2
				Program& setUniform(std::string name, glm::dmat2 value, GLboolean transpose = GL_FALSE)
				{
					GLuint location = getUniformLocation(name);
					glUniformMatrix2dv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(GLuint location, glm::dmat2 value, GLboolean transpose = GL_FALSE)
				{
					glUniformMatrix2dv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(std::string name, glm::mat2 value, GLboolean transpose = GL_FALSE)
				{
					GLuint location = getUniformLocation(name);
					glUniformMatrix2fv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(GLuint location, glm::mat2 value, GLboolean transpose = GL_FALSE)
				{
					glUniformMatrix2fv(location, 1, transpose, &value[0][0]);
					return *this;
				}

				//matrix 3
				Program& setUniform(std::string name, glm::dmat3 value, GLboolean transpose = GL_FALSE)
				{
					GLuint location = getUniformLocation(name);
					glUniformMatrix3dv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(GLuint location, glm::dmat3 value, GLboolean transpose = GL_FALSE)
				{
					glUniformMatrix3dv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(std::string name, glm::mat3 value, GLboolean transpose = GL_FALSE)
				{
					GLuint location = getUniformLocation(name);
					glUniformMatrix3fv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(GLuint location, glm::mat3 value, GLboolean transpose = GL_FALSE)
				{
					glUniformMatrix3fv(location, 1, transpose, &value[0][0]);
					return *this;
				}

				//matrix 4
				Program& setUniform(std::string name, glm::dmat4 value, GLboolean transpose = GL_FALSE)
				{
					GLuint location = getUniformLocation(name);
					glUniformMatrix4dv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(GLuint location, glm::dmat4 value, GLboolean transpose = GL_FALSE)
				{
					glUniformMatrix4dv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(std::string name, glm::mat4 value, GLboolean transpose = GL_FALSE)
				{
					GLuint location = getUniformLocation(name);
					glUniformMatrix4fv(location, 1, transpose, &value[0][0]);
					return *this;
				}
				Program& setUniform(GLuint location, glm::mat4 value, GLboolean transpose = GL_FALSE)
				{
					glUniformMatrix4fv(location, 1, transpose, &value[0][0]);
					return *this;
				}
		};

		class UsualProgram : public Program
		{
			public:
				UsualProgram() : Program() {}
				UsualProgram(GLuint id) : Program(id) {}
				UsualProgram(UsualProgram& from) : Program(from) {}

			public:
				static GLuint linkProgram(GLuint vshader, GLuint fshader)
				{
					GLuint program = glCreateProgram();
					glAttachShader(program, vshader);
					glAttachShader(program, fshader);
					glLinkProgram(program);
					int success;
					if (!success)
					{
						int length;
						glGetProgramiv(program, GL_LINK_STATUS, &success);

#ifndef SOLID_DO_NOT_DEBUG
						char* infoLog = new char[length];
						glGetProgramInfoLog(program, length, nullptr, infoLog);
						Solid::Utils::loge("Compile Shader", infoLog);
						//Solid::loge("Compile Shader", infoLog);
						delete[] infoLog;
#endif

						glDeleteProgram(program);
						return 0;
					}
					return program;
				}

			public:
				bool linkProgramAndDelete(Shader& vshader, Shader& fshader)
				{
					GLuint program = linkProgram(vshader.getGLObjectID(), fshader.getGLObjectID());
					if (program == 0) return false;
					GLuint old = getGLObjectID();
					setGLObjectID(program);
					glDeleteShader(old);
					vshader.deleteGLObject();
					fshader.deleteGLObject();
					return true;
				}

			public:
				bool loadFromString(std::string vsource, std::string fsource)
				{
					Shader vshader(GL_VERTEX_SHADER);
					vshader.loadFromString(vsource);
					Shader fshader(GL_FRAGMENT_SHADER);
					fshader.loadFromString(fsource);
					return linkProgramAndDelete(vshader, fshader);
				}
				bool loadFromStream(std::istream& vis, std::istream& fis)
				{
					Shader vshader(GL_VERTEX_SHADER);
					vshader.loadFromStream(vis);
					Shader fshader(GL_FRAGMENT_SHADER);
					fshader.loadFromStream(fis);
					return linkProgramAndDelete(vshader, fshader);
				}
				bool loadFromFile(std::string vfilename, std::string ffilename)
				{
					Shader vshader(GL_VERTEX_SHADER);
					vshader.loadFromFile(vfilename);
					Shader fshader(GL_FRAGMENT_SHADER);
					fshader.loadFromFile(ffilename);
					return linkProgramAndDelete(vshader, fshader);
				}

				virtual bool loadFromFile(std::string file_prefix)
				{
					std::string vfilename = std::string(file_prefix).append(".vert");
					std::string ffilename = std::string(file_prefix).append(".frag");
					std::cout << vfilename << std::endl << ffilename << std::endl;
					return loadFromFile(vfilename, ffilename);
				}
		};

		class GeometryProgram : public UsualProgram {};
		class ComputeProgram : public Program {};
	}
}

#endif
