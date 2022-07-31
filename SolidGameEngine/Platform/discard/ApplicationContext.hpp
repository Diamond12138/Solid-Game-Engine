#ifndef __SOLID_PLATFORM_APPLICATION_CONTEXT_HPP__
#define __SOLID_PLATFORM_APPLICATION_CONTEXT_HPP__
#include <memory>
#include "../Graphics/core/gl.hpp"

namespace Solid
{
	namespace Platform
	{
		class ApplicationContext
		{
			private:
				std::shared_ptr<void*> m_userData;

			public:
				ApplicationContext()
				{
					m_userData = nullptr;
				}

			public:
				ApplicationContext& setUserData(void* data)
				{
					m_userData = std::make_shared<void*>(data);
					return *this;
				}
				void* getUserData()
				{
					return m_userData.get();
				}
				template<typename T>
				T* getUserDataP()
				{
					return (T*)getUserData();
				}
				template<typename T>
				T& getUserDataR()
				{
					return *(T*)getUserData();
				}
		};
	}
}

#endif
