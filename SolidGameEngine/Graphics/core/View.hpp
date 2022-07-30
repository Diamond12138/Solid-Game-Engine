#ifndef __SOLID_GRAPHICS_VIEW_HPP__
#define __SOLID_GRAPHICS_VIEW_HPP__
#include <glm/gtc/matrix_transform.hpp>
#include "MatrixHolder.hpp"
#include "Transform.hpp"
#include "Transform.hpp"

namespace Solid
{
	namespace Graphics
	{
		class View : public MatrixHolder<glm::mat4>
		{
			public:
				enum MovementDirection
				{
					FORWARD,
					BACKWARD,
					LEFT,
					RIGHT,
					UP,
					DOWN
				};

			private:
				glm::vec3 m_position;
				glm::vec3 m_front;
				glm::vec3 m_up;
				glm::vec3 m_center;
				glm::vec3 m_right;
				float m_movement_speed;

			public:
				View(View& from) : MatrixHolder(from), m_position(from.m_position), m_front(from.m_front), m_up(from.m_up), m_center(from.m_center), m_right(from.m_right), m_movement_speed(from.m_movement_speed) {}
				View(glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : MatrixHolder(), m_position(position), m_front(front), m_up(up), m_movement_speed(1.0f)
				{
					updateVectors();
				}

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

				View& setCenter(glm::vec3 center)
				{
					m_center = center;
					return *this;
				}
				glm::vec3 getCenter()
				{
					return m_center;
				}

				View& setRight(glm::vec3 right)
				{
					m_right = right;
					return *this;
				}
				glm::vec3 getRight()
				{
					return m_right;
				}

				View& setMovementSpeed(float movement_speed)
				{
					m_movement_speed = movement_speed;
					return *this;
				}
				float getMovementSpeed()
				{
					return m_movement_speed;
				}

			public:
				View& move(glm::vec3 value)
				{
					m_position += value;
					return *this;
				}

				View& move(MovementDirection movement_direction, float delta_time)
				{
					glm::vec3 value = glm::vec3(0.0f, 0.0f, 0.0f);
					const float movement_distance = delta_time * m_movement_speed;
					switch (movement_direction)
					{
						case MovementDirection::FORWARD:
							value = m_front * movement_distance;
							break;
						case MovementDirection::BACKWARD:
							value = -m_front * movement_distance;
							break;
						case MovementDirection::LEFT:
							value = -m_right * movement_distance;
							break;
						case MovementDirection::RIGHT:
							value = m_right * movement_distance;
							break;
						case MovementDirection::UP:
							value = m_up * movement_distance;
							break;
						case MovementDirection::DOWN:
							value = -m_up * movement_distance;
							break;
						default:
							break;
					}
					move(value);
					return *this;
				}

			public:
				virtual View& set(glm::vec3 position, glm::vec3 front, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
				{
					m_position = position;
					m_front = front;
					m_up = up;
					return *this;
				}

				virtual View& loadIdentity()
				{
					setMatrix(glm::mat4(1.0f));
					return *this;
				}

				virtual View& updateVectors()
				{
					m_front = glm::normalize(m_front);
					m_up = glm::normalize(m_up);

					m_center = m_position + m_front;
					glm::vec3 PU = m_up - m_position;
					glm::vec3 CP = m_position - m_center;
					m_right = glm::normalize(glm::cross(PU, CP));
					return *this;
				}

				virtual View& updateMatrix()
				{
					updateVectors();
					setMatrix(glm::lookAt(m_position, m_center, m_up));
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
				EulerAngle& operator=(const EulerAngle& from)
				{
					m_yaw = from.m_yaw;
					m_pitch = from.m_pitch;
					return *this;
				}

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
					EulerAngle angle(yaw, pitch);
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
				EulerAngleView(glm::vec3 position, float yaw, float pitch, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : View(position, glm::vec3(0.0f, 0.0f, 0.0f), up)
				{
					EulerAngle angle(yaw, pitch);
					setFront(calcFrontByAngle(angle));
					m_angle = angle;
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

				EulerAngleView& rotate(float yaw, float pitch)
				{
					m_angle.addYaw(yaw);
					m_angle.addPitch(pitch);
					return *this;
				}

			public:
				virtual EulerAngleView& set(glm::vec3 position, glm::vec3 front, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
				{
					View::set(position, front, up);
					m_angle = calcAngleByFront(front);
					return *this;
				}

				virtual EulerAngleView& set(glm::vec3 position, float yaw, float pitch, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
				{
					m_angle = EulerAngle(yaw, pitch);
					glm::vec3 front = calcFrontByAngle(m_angle);
					View::set(position, front, up);
					return *this;
				}

				virtual EulerAngleView& updateMatrix()
				{
					setFront(calcFrontByAngle(m_angle));
					View::updateMatrix();
					return *this;
				}
		};

		template<typename m_TargetType>
		class FollowingTargetHolder
		{
			private:
				m_TargetType* m_target;

			public:
				FollowingTargetHolder(m_TargetType* target) : m_target(target) {}

			public:
				FollowingTargetHolder& setTarget(m_TargetType* target)
				{
					m_target = target;
					return *this;
				}
				m_TargetType* getTarget()
				{
					return m_target;
				}

			public:
				virtual FollowingTargetHolder& update() = 0;

			public:
				typedef m_TargetType TargetType;
		};

		class FollowingView : public View, public FollowingTargetHolder<Transform>
		{
			public:
				FollowingView(glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f), Transform* target = nullptr, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : View(position, glm::vec3(), up), FollowingTargetHolder(target) {}

			public:
				virtual FollowingView& update()
				{
					glm::vec3 front = getTarget()->getTranslate() - getPosition();
					setFront(glm::normalize(front));
					View::updateMatrix();
					return *this;
				}
		};

		class OrbitView : public EulerAngleView, public FollowingTargetHolder<Transform>
		{
			public:
				OrbitView(float yaw = 0.0f, float pitch = 0.0f, Transform* target = nullptr, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : EulerAngleView(glm::vec3(), yaw, pitch, up), FollowingTargetHolder(target) {}

			public:
				virtual OrbitView& update()
				{
					EulerAngle angle;
					angle = getEulerAngle();
					glm::vec3 front = calcFrontByAngle(angle);

					setPosition(getTarget()->getTranslate() + front);
					setFront(-front);

					updateVectors();
					View::updateMatrix();
					return *this;
				}

				virtual OrbitView& updateVectors()
				{
					setFront(glm::normalize(getFront()));
					setUp(glm::normalize(getUp()));
					
					setCenter(getTarget()->getTranslate());
					glm::vec3 PU = getUp() - getPosition();
					glm::vec3 CP = getPosition() - getCenter();
					setRight(glm::normalize(glm::cross(PU, CP)));
					return *this;
				}

				virtual OrbitView& updateMatrix()
				{
					return update();
				}
		};
	}
}

#endif
