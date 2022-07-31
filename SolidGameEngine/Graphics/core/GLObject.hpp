#ifndef __SOLID_GRAPHICS_GLOBJECT_HPP__
#define __SOLID_GRAPHICS_GLOBJECT_HPP__
#include "gl.hpp"

namespace Solid
{
	namespace Graphics
	{
		class GLObject
		{
			private:
				GLuint m_objectID;
				
			public:
				GLObject()
				{
					m_objectID = 0; 
				}
				GLObject(GLuint id)
				{
					m_objectID = id;
				}
				GLObject(const GLObject& from)
				{
					m_objectID = from.m_objectID;
				}
				
			public:
				GLObject& operator=(const GLObject& from)
				{
					m_objectID = from.m_objectID;
					return *this;
				}
				
			public:
				GLObject& setGLObjectID(GLuint id)
				{
					m_objectID = id;
					return *this;
				}
				GLuint getGLObjectID() const
				{
					return m_objectID;
				}
				
			public:
				virtual bool object_is_null() const
				{
					return (m_objectID == 0);
				}
				
				bool objectID_is_zero() const
				{
					return (m_objectID == 0);
				}
				
			public:
				virtual GLObject& deleteGLObject()
				{
					return *this;
				}
		};
	}
}

#endif
