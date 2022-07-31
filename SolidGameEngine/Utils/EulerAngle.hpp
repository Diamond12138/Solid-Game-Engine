#ifndef __SOLID_UTILS_EULER_ANGLE_HPP__
#define __SOLID_UTILS_EULER_ANGLE_HPP__
#include "Equals.hpp"

namespace Solid
{
	namespace Utils
	{
		class EulerAngle
		{
			private:
				float m_yaw;
				float m_pitch;
				float m_roll;

			public:
				EulerAngle(float yaw = 0.0f, float pitch = 0.0f, float roll = 0.0f) : m_yaw(yaw), m_pitch(pitch), m_roll(roll) {}
				EulerAngle(const EulerAngle& from)
				{
					operator=(from);
				}

			public:
				EulerAngle& operator=(const EulerAngle& from)
				{
					m_yaw = from.m_yaw;
					m_pitch = from.m_pitch;
					m_roll = from.m_roll;
					return *this;
				}
				bool operator==(const EulerAngle& another)
				{
					bool yaw = equals(m_yaw, another.m_yaw);
					bool pitch = equals(m_pitch, another.m_pitch);
					bool roll = equals(m_roll, another.m_roll);
					return (yaw && pitch && roll);
				}

				EulerAngle operator+(const EulerAngle& another)
				{
					float yaw = m_yaw + another.m_yaw;
					float pitch = m_pitch + another.m_pitch;
					float roll = m_roll + another.m_roll;
					return EulerAngle(yaw, pitch, roll);
				}
				EulerAngle operator-(const EulerAngle& another)
				{
					float yaw = m_yaw - another.m_yaw;
					float pitch = m_pitch - another.m_pitch;
					float roll = m_roll - another.m_roll;
					return EulerAngle(yaw, pitch, roll);
				}
				EulerAngle operator+(const float value)
				{
					float yaw = m_yaw + value;
					float pitch = m_pitch + value;
					float roll = m_roll + value;
					return EulerAngle(yaw, pitch, roll);
				}
				EulerAngle operator-(const float value)
				{
					float yaw = m_yaw - value;
					float pitch = m_pitch - value;
					float roll = m_roll - value;
					return EulerAngle(yaw, pitch, roll);
				}

				EulerAngle operator*(const EulerAngle& another)
				{
					float yaw = m_yaw * another.m_yaw;
					float pitch = m_pitch * another.m_pitch;
					float roll = m_roll * another.m_roll;
					return EulerAngle(yaw, pitch, roll);
				}
				EulerAngle operator/(const EulerAngle& another)
				{
					float yaw = m_yaw / another.m_yaw;
					float pitch = m_pitch / another.m_pitch;
					float roll = m_roll / another.m_roll;
					return EulerAngle(yaw, pitch, roll);
				}
				EulerAngle operator*(const float value)
				{
					float yaw = m_yaw * value;
					float pitch = m_pitch * value;
					float roll = m_roll * value;
					return EulerAngle(yaw, pitch, roll);
				}
				EulerAngle operator/(const float value)
				{
					float yaw = m_yaw / value;
					float pitch = m_pitch / value;
					float roll = m_roll / value;
					return EulerAngle(yaw, pitch, roll);
				}

				EulerAngle& operator+=(const EulerAngle& another)
				{
					operator=(operator+(another));
					return *this;
				}
				EulerAngle& operator-=(const EulerAngle& another)
				{
					operator=(operator-(another));
					return *this;
				}
				EulerAngle& operator+=(const float value)
				{
					operator=(operator+(value));
					return *this;
				}
				EulerAngle& operator-=(const float value)
				{
					operator=(operator-(value));
					return *this;
				}

				EulerAngle& operator*=(const EulerAngle& another)
				{
					operator=(operator*(another));
					return *this;
				}
				EulerAngle& operator/=(const EulerAngle& another)
				{
					operator=(operator/(another));
					return *this;
				}
				EulerAngle& operator*=(const float value)
				{
					operator=(operator*(value));
					return *this;
				}
				EulerAngle& operator/=(const float value)
				{
					operator=(operator/(value));
					return *this;
				}

			public:
				EulerAngle& yaw(float angle)
				{
					m_yaw = angle;
					return *this;
				}
				float yaw() const
				{
					return m_yaw;
				}

				EulerAngle& pitch(float angle)
				{
					m_pitch = angle;
					return *this;
				}
				float pitch() const
				{
					return m_pitch;
				}

				EulerAngle& roll(float angle)
				{
					m_roll = angle;
					return *this;
				}
				float roll() const
				{
					return m_roll;
				}
		};
	}
}

#endif
