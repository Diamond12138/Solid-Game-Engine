#ifndef __SOLID_GRAPHICS_SHAPE_HPP__
#define __SOLID_GRAPHICS_SHAPE_HPP__
#include <vector>
#include "Sprite.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Shape : public Sprite
		{
			public:
				Shape() : Sprite()
				{
					bindVAO();
				}
				Shape(Shape& from) : Sprite(from)
				{
					bindVAO();
				}
				Shape(Transform& transform) : Sprite(transform, 0)
				{
					bindVAO();
				}

			public:
				virtual void bindVAO()
				{
					setVAO(0);
				};
		};
		
		class VertexShape : public Shape
		{
			private:
				std::vector<float> m_vertices;
				std::vector<float> m_colors;
				std::vector<float> m_normals;
				std::vector<float> m_texCoords;
				
			public:
				VertexShape() : Shape(),m_vertices(std::vector<float>()),m_colors(std::vector<float>()),m_normals(std::vector<float>()),m_texCoords(std::vector<float>()) {}
				VertexShape(VertexShape& from) {}
		};

		class RectangleShape : public Shape
		{
			private:
				glm::vec2 m_size;

			public:
				RectangleShape() : Shape(), m_size(glm::vec2(1.0f)) {}
				RectangleShape(glm::vec2 size) : Shape(), m_size(size) {}
				RectangleShape(RectangleShape& from) : Shape(from),m_size(glm::vec2(1.0f)) {}
				
			public:
				RectangleShape& setSize(glm::vec2 size)
				{
					m_size = size;
					bindVAO();
					return *this;
				}
				glm::vec2 getSize()
				{
					return m_size;
				}
				
			public:
				virtual void bindVAO()
				{
					
				}
		};
	}
}

#endif
