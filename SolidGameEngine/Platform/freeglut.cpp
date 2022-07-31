#ifndef __SOLID_PLATFORM_FREEGLUT_HPP__
#define __SOLID_PLATFORM_FREEGLUT_HPP__
#include "Application.hpp"

namespace Solid
{
	namespace Platform
	{
#include <GL/freeglut.h>

		class FreeGLUT_Application : public Application
		{
			public:
				FreeGLUT_Application(int argc, char* argv[]) : Application()
				{
					glutInit(&argc, argv);
					glutInitContextVersion(4, 6);
					glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
					glutInitContextProfile(GLUT_CORE_PROFILE);
					glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
				}
		};
	}
}

int main(int argc,char* argv[])
{
	
	return EXIT_SUCCESS;
}

#endif
