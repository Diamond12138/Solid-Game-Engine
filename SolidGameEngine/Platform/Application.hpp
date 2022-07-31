#ifndef __SOLID_PLATFORM_APPLICATION_HPP__
#define __SOLID_PLATFORM_APPLICATION_HPP__
#include <string>
#include "../Utils/Time.hpp"

namespace Solid
{
	namespace Platform
	{
		class Application
		{
			private:
				float m_lastDrawTime;
				float m_deltaDrawTime;
				
			public:
				Application() {}
				
			public:
				virtual void updateTime() = 0;
				virtual void createWindow(std::string title,int width = -1,int height = -1) = 0;
				virtual void createWindow_Fullscreen(std::string title) = 0;
				
			public:
				virtual void onCreate() {}
				virtual void onDraw() {}
				virtual void onDestroy() {}
		};
	}
}

extern void Main(int argc,char* argv[]);

#endif
