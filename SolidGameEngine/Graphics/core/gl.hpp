#ifndef __SOLID_GL_HPP__
#define __SOLID_GL_HPP__

#ifdef SOLID_GL_USE_GLEW
	#include <GL/glew.h>
#else
	#ifdef SOLID_GL_USE_EXTTA
		#include "../../Include/gl_core_46_ext/glad.h"
		#include "../../Include/gl_core_46_ext/glad.c"
	#else
		#include "../../Include/gl_core_46/glad.h"
		#include "../../Include/gl_core_46/glad.c"
	#endif
#endif

namespace Solid
{
	namespace Graphics
	{
		//It is the same as gladGLversionStruct, but considering that someone will use GLEW, it is defined.
		struct Solid_GLVersion
		{
			unsigned int major;
			unsigned int minor;
		};
			
		const Solid_GLVersion getGLVersion()
		{
			const unsigned char* version_str = glGetString(GL_VERSION);
			Solid_GLVersion version;
			version.major = int(version_str[0]) - int('0');
			version.minor = int(version_str[2]) - int('0');
			return version;
		}
		
		bool initGL()
		{
			#ifdef SOLID_GL_USE_GLEW
				if(glewInit() != GLEW_OK) return false;
			#else
				if(!gladLoadGL()) return false;
			#endif
			return true;
		}
	}
}

#endif
