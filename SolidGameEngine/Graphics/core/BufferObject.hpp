#ifndef __SOLID_GRAPHICS_BUFFER_OBJECT_HPP__
#define __SOLID_GRAPHICS_BUFFER_OBJECT_HPP__
#include <vector>
#include "GLObject.hpp"
#include "Bindable.hpp"

namespace Solid
{
	namespace Graphics
	{
		class BufferObject : public GLObject, public Bindable
		{
			private:
				GLenum m_buffer_type;

			public:
				BufferObject(GLenum buffer_type, GLuint buffer) : GLObject(buffer), m_buffer_type(buffer_type) {}
				BufferObject(BufferObject& from) : GLObject(from), m_buffer_type(from.m_buffer_type) {}
				BufferObject(GLenum buffer_type) : GLObject(), m_buffer_type(buffer_type)
				{
					genAndDelete();
				}

			public:
				BufferObject& setBufferType(GLenum buffer_type)
				{
					m_buffer_type = buffer_type;
					return *this;
				}
				GLenum getBufferType()
				{
					return m_buffer_type;
				}

			public:
				virtual BufferObject& bind()
				{
					if (!object_is_null())
					{
						glBindBuffer(m_buffer_type, getGLObjectID());
					}
					return *this;
				}

				virtual BufferObject& bindZero()
				{
					glBindBuffer(m_buffer_type, 0);
					return *this;
				}

				virtual GLuint gen()
				{
					GLuint buffer;
					glGenBuffers(1, &buffer);
					GLuint old = getGLObjectID();
					setGLObjectID(buffer);
					return old;
				}

				virtual BufferObject& genAndDelete()
				{
					GLuint old = gen();
					if (old != 0)
					{
						glDeleteBuffers(1, &old);
					}
					return *this;
				}

				virtual BufferObject& deleteGLObject()
				{
					if (!object_is_null())
					{
						GLuint buf = getGLObjectID();
						glDeleteBuffers(1, &buf);
						setGLObjectID(0);
					}
					return *this;
				}

			public:
				virtual BufferObject& bindData(GLsizeiptr size, const void* data, GLenum usage)
				{
					if (!object_is_null())
					{
						glBindBuffer(getBufferType(), getGLObjectID());
						glBufferData(getBufferType(), size, data, usage);
						glBindBuffer(getBufferType(), 0);
					}
					return *this;
				}
		};

		class VertexBufferObject : public BufferObject
		{
			public:
				VertexBufferObject() : BufferObject(GL_ARRAY_BUFFER) {}
				VertexBufferObject(VertexBufferObject& from) : BufferObject(from) {}
				VertexBufferObject(GLuint buffer) : BufferObject(GL_ARRAY_BUFFER, buffer) {}

			public:
				BufferObject& bindVertexAttrib(GLsizeiptr data_size, const void* data, GLsizei index, GLsizei vertex_size, GLenum usage = GL_STATIC_DRAW)
				{
					glBindBuffer(getBufferType(), getGLObjectID());
					glBufferData(getBufferType(), data_size, data, usage);
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index, vertex_size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), nullptr);
					return *this;
				}
		};
	}
}

#endif
