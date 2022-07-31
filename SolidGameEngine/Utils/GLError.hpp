#ifndef __SOLID_UTILS_GLERROR_HPP__
#define __SOLID_UTILS_GLERROR_HPP__
#include "../Graphics/core/gl.hpp"
#include "Log.hpp"
#include <string>
#include <sstream>

namespace Solid
{
	namespace Utils
	{
		template<typename T>
		std::string toStringHex(T value)
		{
			std::stringstream sstr;
			sstr << "0x" << std::hex << value << std::dec;
			return sstr.str();
		}

		class GLMessage
		{
			public:
				static std::string getSource(GLenum source)
				{
					std::string result;
					if (source == GL_DEBUG_SOURCE_API) result = "GL_DEBUG_SOURCE_API";
					else if (source == GL_DEBUG_SOURCE_APPLICATION) result = "GL_DEBUG_SOURCE_APPLICATION";
					else if (source == GL_DEBUG_SOURCE_OTHER) result = "GL_DEBUG_SOURCE_OTHER";
					else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER) result = "GL_DEBUG_SOURCE_SHADER_COMPILER";
					else if (source == GL_DEBUG_SOURCE_THIRD_PARTY) result = "GL_DEBUG_SOURCE_THIRD_PARTY";
					else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM) result = "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
					else result = toStringHex(source);
					return result;
				}

				static std::string getType(GLenum type)
				{
					std::string result;
					if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) result = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
					else if (type == GL_DEBUG_TYPE_ERROR) result = "GL_DEBUG_TYPE_ERROR";
					else if (type == GL_DEBUG_TYPE_MARKER) result = "GL_DEBUG_TYPE_MARKER";
					else if (type == GL_DEBUG_TYPE_OTHER) result = "GL_DEBUG_TYPE_OTHER";
					else if (type == GL_DEBUG_TYPE_PERFORMANCE) result = "GL_DEBUG_TYPE_PERFORMANCE";
					else if (type == GL_DEBUG_TYPE_POP_GROUP) result = "GL_DEBUG_TYPE_POP_GROUP";
					else if (type == GL_DEBUG_TYPE_PORTABILITY) result = "GL_DEBUG_TYPE_PORTABILITY";
					else if (type == GL_DEBUG_TYPE_PUSH_GROUP) result = "GL_DEBUG_TYPE_PUSH_GROUP";
					else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) result = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
					else result = toStringHex(type);
					return result;
				}

				static std::string getID(GLenum id)
				{
					std::string result;
					switch (id)
					{
						case GL_NO_ERROR:
							result = "GL_NO_ERROR";
							break;
						case GL_INVALID_ENUM:
							result = "GL_INVALID_ENUM";
							break;
						case GL_INVALID_VALUE:
							result = "GL_INVALID_VALUE";
							break;
						case GL_INVALID_OPERATION:
							result = "GL_INVALID_OPERATION";
							break;
						case GL_STACK_OVERFLOW:
							result = "GL_STACK_OVERFLOW";
							break;
						case GL_STACK_UNDERFLOW:
							result = "GL_STACK_UNDERFLOW";
							break;
						case GL_OUT_OF_MEMORY:
							result = "GL_OUT_OF_MEMORY";
							break;
						case GL_INVALID_FRAMEBUFFER_OPERATION:
							result = "GL_INVALID_FRAMEBUFFER_OPERATION";
							break;
						default:
							result = toStringHex(id);
							break;
					}
					return result;
				}

				static std::string getSeverity(GLenum severity)
				{
					std::string result;
					if (severity == GL_DEBUG_SEVERITY_HIGH) result = "GL_DEBUG_SEVERITY_HIGH";
					else if (severity == GL_DEBUG_SEVERITY_MEDIUM) result = "GL_DEBUG_SEVERITY_MEDIUM";
					else if (severity == GL_DEBUG_SEVERITY_LOW) result = "GL_DEBUG_SEVERITY_LOW";
					else result = toStringHex(severity);
					return result;
				}
		};

		void GLAPIENTRY m_onMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			std::stringstream sstr;
			sstr << std::endl
			     << std::hex
			     << "source:" << GLMessage::getSource(source) << std::endl
			     << "type:" << GLMessage::getType(type) << std::endl
			     << "id:" << GLMessage::getID(id) << std::endl
			     << "severity:" << GLMessage::getSeverity(severity) << std::endl
			     << std::dec
			     << "length:" << length << std::endl
			     << "message:" << message << std::endl
			     << "user param:" << userParam << std::endl;

			logu("GL Error", sstr.str());
		}

		void bindDebugCallback(void* user_param = nullptr)
		{
			glDebugMessageCallback(m_onMessage, user_param);
		}

		class GLError
		{
			public:
				static std::string parse(GLenum error)
				{
					std::string result;
					switch (error)
					{
						case GL_NO_ERROR:
							result = "GL_NO_ERROR";
							break;
						case GL_INVALID_ENUM:
							result = "GL_INVALID_ENUM";
							break;
						case GL_INVALID_VALUE:
							result = "GL_INVALID_VALUE";
							break;
						case GL_INVALID_OPERATION:
							result = "GL_INVALID_OPERATION";
							break;
						case GL_STACK_OVERFLOW:
							result = "GL_STACK_OVERFLOW";
							break;
						case GL_STACK_UNDERFLOW:
							result = "GL_STACK_UNDERFLOW";
							break;
						case GL_OUT_OF_MEMORY:
							result = "GL_OUT_OF_MEMORY";
							break;
						case GL_INVALID_FRAMEBUFFER_OPERATION:
							result = "GL_INVALID_FRAMEBUFFER_OPERATION";
							break;
						default:
							result = "Unknow";
							break;
					}
					return result;
				}

				//https://learnopengl.com/In-Practice/Debugging
				static std::string describe(GLenum error)
				{
					std::string result;
					switch (error)
					{
						case GL_NO_ERROR:
							result = "No user error reported since the last call to glGetError.";
							break;
						case GL_INVALID_ENUM:
							result = "Set when an enumeration parameter is not legal.";
							break;
						case GL_INVALID_VALUE:
							result = "Set when a value parameter is not legal.";
							break;
						case GL_INVALID_OPERATION:
							result = "Set when the state for a command is not legal for its given parameters.";
							break;
						case GL_STACK_OVERFLOW:
							result = "Set when a stack pushing operation causes a stack overflow.";
							break;
						case GL_STACK_UNDERFLOW:
							result = "Set when a stack popping operation occurs while the stack is at its lowest point.";
							break;
						case GL_OUT_OF_MEMORY:
							result = "Set when a memory allocation operation cannot allocate (enough) memory.";
							break;
						case GL_INVALID_FRAMEBUFFER_OPERATION:
							result = "Set when reading or writing to a framebuffer that is not complete.";
							break;
						default:
							result = "Unknown enumeration.";
							break;
					}
					return result;
				}

			private:
				GLenum m_lastError;

			public:
				GLError() : m_lastError(GL_NO_ERROR) {}

			public:
				std::string operator()(GLenum error)
				{
					std::stringstream sstr;
					sstr << "Error:" << parse(error) << std::endl << "Description:" << describe(error);
					return sstr.str();
				}

				GLError& log(std::string position = "")
				{
					if (position.length() != 0)
						Solid::Utils::logi("GL Error", "when " + position);
					Solid::Utils::loge("GL Error", operator()(m_lastError));
					return *this;
				}

				bool checkError()
				{
					m_lastError = glGetError();
					return (m_lastError == GL_NO_ERROR);
				}

				void checkAndLog(std::string position = "")
				{
					m_lastError = glGetError();
					if (m_lastError != GL_NO_ERROR)
					{
						log(position);
					}
				}

				GLenum getLastError()
				{
					return m_lastError;
				}
		};
	}
}

#endif
