#ifndef __SOLID_GRAPHICS_SPRITE_HPP__
#define __SOLID_GRAPHICS_SPRITE_HPP__
#include "Transform.hpp"
#include "Renderable.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Sprite : public Transform, public Renderable
		{
			public:
				enum DrawMode
				{
					POINTS = GL_POINTS,
					LINES = GL_LINES,
					LINE_LOOP = GL_LINE_LOOP,
					LINE_STRIP = GL_LINE_STRIP,
					TRIANGLES = GL_TRIANGLES,
					TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
					TRIANGLE_FAN = GL_TRIANGLE_FAN
				};
				enum DrawMethod
				{
					ARRAYS,
					ELEMENTS,
					ARRAYS_INDIRECT,
					ELEMENTS_INDIRECT,
					ARRAYS_INSTANCED,
					ELEMENTS_INSTANCED,
					ARRAYS_INSTANCED_BASE_INSTANCE,
					ELEMENTS_INSTANCED_BASE_INSTANCE
				};

			private:
				DrawMode m_draw_mode;
				DrawMethod m_draw_method;
				GLint m_vertex_first;
				GLsizei m_vertex_count;
				GLenum m_elements_type;

			public:
				Sprite(GLsizei vertex_count = 0,DrawMode draw_mode = DrawMode::TRIANGLES,DrawMethod draw_method = DrawMethod::ARRAYS,GLint vertex_first = 0,GLenum elements_type = GL_UNSIGNED_INT)
				: Transform(), Renderable() ,m_draw_mode(draw_mode),m_draw_method(draw_method),m_vertex_first(vertex_first),m_vertex_count(vertex_count),m_elements_type(elements_type) {}
				Sprite(Sprite& from)
				: Transform(from), Renderable(from),m_draw_mode(from.m_draw_mode),m_draw_method(from.m_draw_method),m_vertex_first(from.m_vertex_first),m_vertex_count(from.m_vertex_count),m_elements_type(from.m_elements_type) {}
				Sprite(Transform& transform, GLuint vao,GLsizei vertex_count = 0,DrawMode draw_mode = DrawMode::TRIANGLES,DrawMethod draw_method = DrawMethod::ARRAYS,GLint vertex_first = 0,GLenum elements_type = GL_UNSIGNED_INT)
				: Transform(transform), Renderable(vao),m_draw_mode(draw_mode),m_draw_method(draw_method),m_vertex_first(vertex_first),m_vertex_count(vertex_count),m_elements_type(elements_type) {}
				Sprite(Transform& transform, Renderable& renderable,GLsizei vertex_count = 0,DrawMode draw_mode = DrawMode::TRIANGLES,DrawMethod draw_method = DrawMethod::ARRAYS,GLint vertex_first = 0,GLenum elements_type = GL_UNSIGNED_INT)
				: Transform(transform), Renderable(renderable),m_draw_mode(draw_mode),m_draw_method(draw_method),m_vertex_first(vertex_first),m_vertex_count(vertex_count),m_elements_type(elements_type) {}
				Sprite(GLuint vao,GLsizei vertex_count = 0,DrawMode draw_mode = DrawMode::TRIANGLES,DrawMethod draw_method = DrawMethod::ARRAYS,GLint vertex_first = 0,GLenum elements_type = GL_UNSIGNED_INT)
				: Transform(), Renderable(vao),m_draw_mode(draw_mode),m_draw_method(draw_method),m_vertex_first(vertex_first),m_vertex_count(vertex_count),m_elements_type(elements_type) {}

			public:
				Sprite& setDrawMode(DrawMode draw_mode)
				{
					m_draw_mode = draw_mode;
					return *this;
				}
				DrawMode getDrawMode()
				{
					return m_draw_mode;
				}

				Sprite& setDrawMethod(DrawMethod draw_method)
				{
					m_draw_method = draw_method;
					return *this;
				}
				DrawMethod getDrawMethod()
				{
					return m_draw_method;
				}

				Sprite& setVertexFirst(GLsizei vertex_first)
				{
					m_vertex_first = vertex_first;
					return *this;
				}
				GLint getVertexFirst()
				{
					return m_vertex_first;
				}

				Sprite& setVertexCount(GLsizei vertex_count)
				{
					m_vertex_count = vertex_count;
					return *this;
				}
				GLsizei getVertexCount()
				{
					return m_vertex_count;
				}

				Sprite& setElementsType(GLenum elements_type)
				{
					m_elements_type = elements_type;
					return *this;
				}
				GLenum getElementsType()
				{
					return m_elements_type;
				}

			public:
				virtual Sprite& beRendered(Program& program, const void* elements_ptr)
				{
					program.setUniform("u_model", Transform::getMatrix());
					glBindVertexArray(getVAO());
					switch (m_draw_method)
					{
						case DrawMethod::ARRAYS:
							glDrawArrays((GLenum)m_draw_mode, m_vertex_first, m_vertex_count);
							break;
						case DrawMethod::ELEMENTS:
							glDrawElements((GLenum)m_draw_mode, m_vertex_first, m_elements_type, elements_ptr);
							break;
						default:
							break;
					}
					glBindVertexArray(0);
					return *this;
				}
				virtual Sprite& beRendered(Program& program)
				{
					return beRendered(program, nullptr);
				}
		};
	}
}

#endif
