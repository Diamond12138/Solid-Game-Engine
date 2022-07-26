#ifndef __SOLID_GRAPHICS_VIEW_HPP__
#define __SOLID_GRAPHICS_VIEW_HPP__
#include <glm/gtc/matrix_transform.hpp>
#include "MatrixHolder.hpp"
#include "Transform.hpp"

namespace Solid
{
	namespace Graphics
	{
		class View : public MatrixHolder<glm::mat4>
		{
			private:
				glm::vec3 m_position;
				glm::vec3 m_front;
				glm::vec3 m_up;

			public:
				View() : MatrixHolder(), m_position(glm::vec3(0.0f, 0.0f, 0.0f)), m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f)) {}
				View(View& from) : MatrixHolder(from), m_position(from.m_position), m_front(from.m_front), m_up(from.m_up) {}
				View(glm::vec3 position, glm::vec3 front, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : MatrixHolder(), m_position(position), m_front(front), m_up(up) {}

			public:
				View& setPosition(glm::vec3 position)
				{
					m_position = position;
					return *this;
				}
				glm::vec3 getPosition()
				{
					return m_position;
				}

				View& setFront(glm::vec3 front)
				{
					m_front = front;
					return *this;
				}
				glm::vec3 getFront()
				{
					return m_front;
				}

				View& setUp(glm::vec3 up)
				{
					m_up = up;
					return *this;
				}
				glm::vec3 getUp()
				{
					return m_up;
				}

			public:
				virtual View& loadIdentity()
				{
					setMatrix(glm::mat4(1.0f));
					return *this;
				}

				virtual View& updateMatrix()
				{
					setMatrix(glm::lookAt(m_position, m_position + m_front, m_up));
					return *this;
				}
		};

		class EulerAngle
		{
			private:
				float m_yaw;
				float m_pitch;
				float m_roll;//I can't do it

			public:
				EulerAngle(float yaw = 0.0f, float pitch = 0.0f) : m_yaw(yaw), m_pitch(pitch) {}
				EulerAngle(EulerAngle& from) : m_yaw(from.m_yaw), m_pitch(from.m_pitch) {}

			public:
				EulerAngle& setYaw(float yaw)
				{
					m_yaw = yaw;
					return *this;
				}
				float getYaw()
				{
					return m_yaw;
				}

				EulerAngle& setPitch(float pitch)
				{
					m_pitch = pitch;
					return *this;
				}
				float getPitch()
				{
					return m_pitch;
				}

			public:
				EulerAngle& addYaw(float angle)
				{
					m_yaw += angle;
					return *this;
				}

				EulerAngle& addPitch(float angle)
				{
					m_pitch += angle;
					return *this;
				}

				EulerAngle& subYaw(float angle)
				{
					m_yaw -= angle;
					return *this;
				}

				EulerAngle& subPitch(float angle)
				{
					m_pitch -= angle;
					return *this;
				}
		};

		class EulerAngleView : public View
		{
			public:
				static glm::vec3 calcFrontByAngle(EulerAngle angle)
				{
					float y = glm::sin(glm::radians(angle.getPitch()));
					float h = glm::cos(glm::radians(angle.getPitch()));
					float x = glm::cos(glm::radians(angle.getYaw())) * h;
					float z = glm::sin(glm::radians(angle.getYaw())) * h;
					return glm::normalize(glm::vec3(x, y, z));
				}

				static EulerAngle calcAngleByFront(glm::vec3 front)
				{
					glm::vec3 f = glm::normalize(front);
					float yaw = glm::degrees(glm::atan(f.z / f.x));
					float h = glm::sqrt(f.x * f.x + f.z * f.z);
					float pitch = glm::degrees(glm::atan(f.y / h));
					EulerAngle angle(yaw,pitch);
					return angle;
				}

			private:
				EulerAngle m_angle;

			public:
				EulerAngleView() : View()
				{
					m_angle = EulerAngle();
				}
				EulerAngleView(EulerAngleView& from) : View(from), m_angle(from.m_angle) {}
				EulerAngleView(glm::vec3 position, glm::vec3 front, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : View(position, front, up)
				{
					m_angle = calcAngleByFront(front);
				}
				EulerAngleView(float yaw, float pitch, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : View(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), up)
				{
					EulerAngle angle(yaw,pitch);
					setFront(calcFrontByAngle(angle));
				}

			public:
				EulerAngleView& setEulerAngle(EulerAngle angle)
				{
					m_angle = angle;
					return *this;
				}
				EulerAngle getEulerAngle()
				{
					return m_angle;
				}
				
				EulerAngleView& rotate(float yaw,float pitch)
				{
					m_angle.addYaw(yaw);
					m_angle.addPitch(pitch);
					return *this;
				}
				EulerAngleView& move(glm::vec3 value)
				{
					glm::vec3 position = getPosition();
					setPosition(position + value);
					return *this;
				}
				
			public:
				virtual EulerAngleView& updateMatrix()
				{
					setFront(calcFrontByAngle(m_angle));
					//View::updateMatrix();
					setMatrix(glm::lookAt(getPosition(), getPosition() + getFront(),getUp()));
					return *this;
				}
		};
	}
}

#endif
