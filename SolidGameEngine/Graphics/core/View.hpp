#ifndef __SOLID_GRAPHICS_VIEW_HPP__
#define __SOLID_GRAPHICS_VIEW_HPP__
#include <glm/gtc/matrix_transform.hpp>
#include "MatrixHolder.hpp"
#include "Transform.hpp"
#include "Transform.hpp"
#include "../../Utils/EulerAngle.hpp"

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
							value = -1.0f * m_front * movement_distance;
							break;
						case MovementDirection::LEFT:
							value = -1.0f * m_right * movement_distance;
							break;
						case MovementDirection::RIGHT:
							value = m_right * movement_distance;
							break;
						case MovementDirection::UP:
							value = m_up * movement_distance;
							break;
						case MovementDirection::DOWN:
							value = -1.0f * m_up * movement_distance;
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
					m_right = glm::normalize(glm::cross(m_front, m_up));
					return *this;
				}

				virtual View& updateMatrix()
				{
					updateVectors();
					setMatrix(glm::lookAt(m_position, m_center, m_up));
					return *this;
				}
		};

		class EulerAngleView : public View
		{
			public:
				static glm::vec3 calcFrontByAngle(Utils::EulerAngle angle)
				{
					float y = glm::sin(glm::radians(angle.pitch()));
					float h = glm::cos(glm::radians(angle.pitch()));
					float x = glm::cos(glm::radians(angle.yaw())) * h;
					float z = glm::sin(glm::radians(angle.yaw())) * h;
					return glm::normalize(glm::vec3(x, y, z));
				}

				static Utils::EulerAngle calcAngleByFront(glm::vec3 front)
				{
					glm::vec3 f = glm::normalize(front);
					float yaw = glm::degrees(glm::atan(f.z / f.x));
					float h = glm::sqrt(f.x * f.x + f.z * f.z);
					float pitch = glm::degrees(glm::atan(f.y / h));
					Utils::EulerAngle angle(yaw, pitch, 0.0f);
					return angle;
				}

			private:
				Utils::EulerAngle m_angle;
				bool m_enable_angle_constraint;

			public:
				EulerAngleView(bool enable_angle_constraint = true) : View(), m_enable_angle_constraint(enable_angle_constraint)
				{
					m_angle = Utils::EulerAngle();
				}
				EulerAngleView(EulerAngleView& from) : View(from), m_angle(from.m_angle), m_enable_angle_constraint(from.m_enable_angle_constraint) {}
				EulerAngleView(glm::vec3 position, glm::vec3 front, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : View(position, front, up), m_enable_angle_constraint(true)
				{
					m_angle = calcAngleByFront(front);
				}
				EulerAngleView(glm::vec3 position, float yaw, float pitch, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : View(position, glm::vec3(0.0f, 0.0f, 0.0f), up), m_enable_angle_constraint(true)
				{
					Utils::EulerAngle angle(yaw, pitch);
					setFront(calcFrontByAngle(angle));
					m_angle = angle;
				}

			public:
				EulerAngleView& setEulerAngle(Utils::EulerAngle angle)
				{
					m_angle = angle;
					return *this;
				}
				Utils::EulerAngle getEulerAngle()
				{
					return m_angle;
				}

				EulerAngleView& setIsEnableAngleConstraint(bool enable_angle_constraint)
				{
					m_enable_angle_constraint = enable_angle_constraint;
					return *this;
				}
				bool isEnableAngleConstraint()
				{
					return m_enable_angle_constraint;
				}

				EulerAngleView& rotate(float yaw, float pitch)
				{
					m_angle += Utils::EulerAngle(yaw,pitch);
					return *this;
				}
				EulerAngleView& rotateYaw(float angle)
				{
					m_angle += Utils::EulerAngle(angle,0.0f);
					return *this;
				}
				EulerAngleView& rotatePitch(float angle)
				{
					m_angle += Utils::EulerAngle(0.0f,angle);
					return *this;
				}

				EulerAngleView& angle_constrain()
				{
					m_angle = angle_constrain(m_angle);
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
					m_angle = Utils::EulerAngle(yaw, pitch);
					glm::vec3 front = calcFrontByAngle(m_angle);
					View::set(position, front, up);
					return *this;
				}

				virtual EulerAngleView& set(float yaw, float pitch)
				{
					m_angle = Utils::EulerAngle(yaw, pitch);
					return *this;
				}

				virtual Utils::EulerAngle angle_constrain(Utils::EulerAngle angle)
				{
					float yaw = angle.yaw();
					float pitch = angle.pitch();

					if (yaw >= 360.0f) yaw -= 360.0f;
					else if (yaw < 0.0f) yaw += 360.0f;

					if (pitch > 89.9f) pitch = 89.9f;
					else if (pitch < -89.9f) pitch = -89.9f;

					Utils::EulerAngle result(yaw, pitch);
					return result;
				}

				virtual EulerAngleView& updateMatrix()
				{
					if (m_enable_angle_constraint)
					{
						angle_constrain();
					}
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
				virtual FollowingTargetHolder& update()
				{
					if (m_target == nullptr)
					{
						Utils::loge("following target", "target is null");
					}
					return *this;
				}

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
					FollowingTargetHolder::update();
					glm::vec3 front = getTarget()->getTranslate() - getPosition();
					setFront(glm::normalize(front));
					View::updateMatrix();
					return *this;
				}

				virtual FollowingView& updateMatrix()
				{
					return update();
				}
		};

		class OrbitView : public EulerAngleView, public FollowingTargetHolder<Transform>
		{
			private:
				float m_target_distance;

			public:
				OrbitView(float yaw = 0.0f, float pitch = 0.0f, Transform* target = nullptr, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : EulerAngleView(glm::vec3(), yaw, pitch, up), FollowingTargetHolder(target), m_target_distance(1.0f) {}

			public:
				OrbitView& setTargetDistance(float target_distance)
				{
					m_target_distance = target_distance;
					return *this;
				}
				float getTargetDistance()
				{
					return m_target_distance;
				}

			public:
				virtual OrbitView& update()
				{
					FollowingTargetHolder::update();
					if (isEnableAngleConstraint())
					{
						EulerAngleView::angle_constrain();
					}

					Utils::EulerAngle angle;
					angle = getEulerAngle();
					glm::vec3 front = calcFrontByAngle(angle);

					setPosition(getTarget()->getTranslate() + front * m_target_distance);
					setFront(-front);

					updateVectors();
					View::updateMatrix();
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
