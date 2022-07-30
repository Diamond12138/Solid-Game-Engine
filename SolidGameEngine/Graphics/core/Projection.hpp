#ifndef __SOLID_GRAPHICS_PROJECTION_HPP__
#define __SOLID_GRAPHICS_PROJECTION_HPP__
#include <glm/gtc/matrix_transform.hpp>
#include "MatrixHolder.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Projection : public MatrixHolder<glm::mat4>
		{
			private:
				float m_zNear;
				float m_zFar;

			public:
				Projection() : MatrixHolder(), m_zNear(0.1f), m_zFar(100.0f) {}
				Projection(Projection& from) : MatrixHolder(from), m_zNear(from.m_zNear), m_zFar(from.m_zFar) {}
				Projection(float zNear, float zFar) : MatrixHolder(), m_zNear(zNear), m_zFar(zFar) {}

			public:
				Projection& setZNear(float zNear)
				{
					m_zNear = zNear;
					return *this;
				}
				float getZNear()
				{
					return m_zNear;
				}

				Projection& setZFar(float zFar)
				{
					m_zFar = zFar;
					return *this;
				}
				float getZFar()
				{
					return m_zFar;
				}

			public:
				virtual Projection& loadIdentity()
				{
					setMatrix(glm::mat4(1.0f));
					return *this;
				}
				virtual Projection& set(float zNear,float zFar)
				{
					m_zNear = zNear;
					m_zFar = zFar;
					return *this;
				}
		};

		class PerspectiveProjection : public Projection
		{
			private:
				float m_fovy;
				float m_aspect;

			public:
				PerspectiveProjection() : Projection(), m_fovy(60.0f), m_aspect(1.0f) {}
				PerspectiveProjection(PerspectiveProjection& from) : Projection(from), m_fovy(from.m_fovy), m_aspect(from.m_aspect) {}
				PerspectiveProjection(float fovy, float aspect, float zNear = 0.1f, float zFar = 100.0f) : Projection(zNear, zFar), m_fovy(fovy), m_aspect(aspect) {}

			public:
				PerspectiveProjection& setFovy(float fovy)
				{
					m_fovy = fovy;
					return *this;
				}
				float getFovy()
				{
					return m_fovy;
				}

				PerspectiveProjection& setAspect(float aspect)
				{
					m_aspect = aspect;
					return *this;
				}
				float getAspect()
				{
					return m_aspect;
				}

			public:
				virtual PerspectiveProjection& updateMatrix()
				{
					setMatrix(glm::perspective(m_fovy, m_aspect, getZNear(), getZFar()));
					return *this;
				}
				
				virtual PerspectiveProjection& set(float fovy,float aspect,float zNear,float zFar)
				{
					m_fovy = fovy;
					m_aspect = aspect;
					setZNear(zNear);
					setZFar(zFar);
					return *this;
				}
		};

		class RectProjection : public Projection
		{
			private:
				float m_left;
				float m_right;
				float m_top;
				float m_bottom;

			public:
				RectProjection() : Projection(), m_left(-1.0f), m_right(1.0f), m_top(1.0f), m_bottom(-1.0f) {}
				RectProjection(RectProjection& from) : Projection(from), m_left(from.m_left), m_right(from.m_right), m_top(from.m_top), m_bottom(from.m_bottom) {}
				RectProjection(float left, float right, float top, float bottom) : Projection(), m_left(left), m_right(right), m_top(top), m_bottom(bottom) {}
				RectProjection(float left, float right, float top, float bottom, float zNear, float zFar) : Projection(zNear, zFar), m_left(left), m_right(right), m_top(top), m_bottom(bottom) {}

			public:
				RectProjection& setLeft(float left)
				{
					m_left = left;
					return *this;
				}
				float getLeft()
				{
					return m_left;
				}

				RectProjection& setRight(float right)
				{
					m_right = right;
					return *this;
				}
				float getRight()
				{
					return m_right;
				}

				RectProjection& setTop(float top)
				{
					m_top = top;
					return *this;
				}
				float getTop()
				{
					return m_top;
				}

				RectProjection& setBottom(float bottom)
				{
					m_bottom = bottom;
					return *this;
				}
				float getBottom()
				{
					return m_bottom;
				}
		};

		class FrustumProjection : public RectProjection
		{
			public:
				FrustumProjection() : RectProjection() {}
				FrustumProjection(FrustumProjection& from) : RectProjection(from) {}
				FrustumProjection(float left, float right, float top, float bottom, float zNear = 0.1f, float zFar = 100.0f) : RectProjection(left, right, top, bottom, zNear, zFar) {}

			public:
				virtual FrustumProjection& updateMatrix()
				{
					setMatrix(glm::frustum(getLeft(), getRight(), getBottom(), getTop(), getZNear(), getZFar()));
					return *this;
				}
		};

		class OrthoProjection : public RectProjection
		{
			public:
				OrthoProjection() : RectProjection() {}
				OrthoProjection(FrustumProjection& from) : RectProjection(from) {}
				OrthoProjection(float left, float right, float top, float bottom, float zNear = 0.1f, float zFar = 100.0f) : RectProjection(left, right, top, bottom, zNear, zFar) {}

			public:
				virtual OrthoProjection& updateMatrix()
				{
					setMatrix(glm::ortho(getLeft(), getRight(), getBottom(), getTop(), getZNear(), getZFar()));
					return *this;
				}
		};
	}
}

#endif
