#ifndef __SOLID_GRAPHICS_RENDERABLE_HPP__
#define __SOLID_GRAPHICS_RENDERABLE_HPP__
#include "gl.hpp"
#include "Program.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Renderable
		{
			private:
				GLuint m_vao;

			public:
				Renderable() : m_vao(0) {}
				Renderable(GLuint vao) : m_vao(vao) {}
				Renderable(Renderable& from) : m_vao(from.m_vao) {}

			public:
				Renderable& setVAO(GLuint vao)
				{
					m_vao = vao;
					return *this;
				}
				GLuint getVAO()
				{
					return m_vao;
				}
				Renderable& deleteVAO()
				{
					if (m_vao != 0)
					{
						glDeleteVertexArrays(1, &m_vao);
						m_vao = 0;
					}
					return *this;
				}

			public:
				virtual void beRendered(Program& program)
				{
					glBindVertexArray(0);
				}
		};
	}
}

#endif
