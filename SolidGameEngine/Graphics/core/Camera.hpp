#ifndef __SOLID_GRAPHICS_CAMERA_HPP__
#define __SOLID_GRAPHICS_CAMERA_HPP__
#include "View.hpp"
#include "Projection.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Camera
		{
			public:
				virtual glm::mat4 getViewMatrix() = 0;
				virtual glm::mat4 getProjectionMatrix() = 0;
				virtual Camera& updateViewMatrix() = 0;
				virtual Camera& updateProjectionMatrix() = 0;
		};

		class EulerAngleCamera : public Camera, public EulerAngleView, public PerspectiveProjection
		{
			public:
				EulerAngleCamera(glm::vec3 position = glm::vec3(0.0f,0.0f,1.0f),float yaw = 270.0f,float pitch = 0.0f,float fovy = 60.0f,float aspect = 1.0f,float zNear = 0.1f,float zFar = 100.0f,glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f))
				: EulerAngleView(position,yaw,pitch,up) , PerspectiveProjection(fovy,aspect,zNear,zFar)
				{
					updateViewMatrix();
					updateProjectionMatrix();
				}

			public:
				virtual glm::mat4 getViewMatrix()
				{
					return Solid::Graphics::EulerAngleView::getMatrix();
				}
				virtual glm::mat4 getProjectionMatrix()
				{
					return Solid::Graphics::PerspectiveProjection::getMatrix();
				}
				virtual EulerAngleCamera& updateViewMatrix()
				{
					Solid::Graphics::EulerAngleView::updateMatrix();
					return *this;
				}
				virtual EulerAngleCamera& updateProjectionMatrix()
				{
					Solid::Graphics::PerspectiveProjection::updateMatrix();
					return *this;
				}
		};
	}
}

#endif
