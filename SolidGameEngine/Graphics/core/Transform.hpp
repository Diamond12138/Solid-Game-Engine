#ifndef __SOLID_GRAPHICS_TRANSFORM_HPP__
#define __SOLID_GRAPHICS_TRANSFORM_HPP__
#include <glm/gtc/matrix_transform.hpp>
#include "MatrixHolder.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Transform : public MatrixHolder<glm::mat4>
		{
			private:
				glm::vec3 m_translate;
				glm::vec3 m_rotate;
				glm::vec3 m_scale;

			public:
				Transform() : MatrixHolder(), m_translate(glm::vec3(0.0f,0.0f,0.0f)), m_rotate(glm::vec3(0.0f,0.0f,0.0f)), m_scale(glm::vec3(1.0f,1.0f,1.0f)) {}
				Transform(Transform& from) : MatrixHolder(from), m_translate(from.m_translate), m_rotate(from.m_rotate), m_scale(from.m_scale) {}
				Transform(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) : MatrixHolder(), m_translate(translate), m_rotate(rotate), m_scale(scale) {}

			public:
				virtual Transform& loadIdentity()
				{
					setMatrix(glm::mat4(1.0f));
					return *this;
				}

				virtual Transform& updateMatrix()
				{
					glm::mat4 matrix = glm::mat4(1.0f);
					matrix = glm::translate(matrix, m_translate);
					matrix = glm::rotate(matrix, m_rotate.x, glm::vec3(1, 0, 0));
					matrix = glm::rotate(matrix, m_rotate.y, glm::vec3(0, 1, 0));
					matrix = glm::rotate(matrix, m_rotate.z, glm::vec3(0, 0, 1));
					matrix = glm::scale(matrix, m_scale);
					setMatrix(matrix);
					return *this;
				}

			public:
				Transform& setTranslate(glm::vec3 value)
				{
					m_translate = value;
					return *this;
				}
				glm::vec3 getTranslate()
				{
					return m_translate;
				}
				Transform& setRotate(glm::vec3 value)
				{
					m_rotate = value;
					return *this;
				}
				glm::vec3 getRotate()
				{
					return m_rotate;
				}
				Transform& setScale(glm::vec3 value)
				{
					m_scale = value;
					return *this;
				}
				glm::vec3 getScale()
				{
					return m_scale;
				}

			public:
				virtual Transform& translate(glm::vec3 value)
				{
					m_translate += value;
					return *this;
				}
				virtual Transform& rotate(glm::vec3 value)
				{
					m_rotate += value;
					return *this;
				}
				virtual Transform& scale(glm::vec3 value)
				{
					m_scale += value;
					return *this;
				}
		};
	}
}

#endif
