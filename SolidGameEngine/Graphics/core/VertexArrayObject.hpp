#ifndef __SOLID_GRAPHICS_VERTEX_ARRAY_OBJECT_HPP__
#define __SOLID_GRAPHICS_VERTEX_ARRAY_OBJECT_HPP__
#include "GLObject.hpp"
#include "Bindable.hpp"

namespace Solid
{
	namespace Graphics
	{
		class VertexArrayObject : public GLObject, public Bindable
		{
			public:
				VertexArrayObject(GLuint id) : GLObject(id) {}
				VertexArrayObject(VertexArrayObject& from) : GLObject(from) {}
				VertexArrayObject() : GLObject()
				{
					genAndDelete();
				}

			public:
				virtual Bindable& bind()
				{
					if (!object_is_null())
					{
						glBindVertexArray(getGLObjectID());
					}
					return *this;
				}

				virtual Bindable& bindZero()
				{
					glBindVertexArray(0);
					return *this;
				}

				virtual GLuint gen()
				{
					GLuint vao;
					glGenVertexArrays(1, &vao);
					GLuint old = getGLObjectID();
					setGLObjectID(vao);
					return old;
				}

				virtual VertexArrayObject& genAndDelete()
				{
					GLuint old = gen();
					if (old != 0)
					{
						glDeleteVertexArrays(1, &old);
					}
					return *this;
				}

				virtual VertexArrayObject& deleteGLObject()
				{
					if (!object_is_null())
					{
						GLuint buf = getGLObjectID();
						glDeleteVertexArrays(1, &buf);
						setGLObjectID(0);
					}
					return *this;
				}
		};
	}
}

#endif
