#include <iostream>
#include <memory>
#include "../SolidGameEngine/Utils/instances.hpp"
#include <GL/freeglut.h>

struct UserData
{
	GLuint vao;
};

void display()
{
	UserData* ud = (UserData*)glutGetWindowData();
	glClear(GL_COLOR_BUFFER_BIT);
	
	Solid::defaultProgram.useProgram();
	glBindVertexArray(ud->vao);
	glDrawArrays(GL_TRIANGLES,0,3);
	glBindVertexArray(0);
	
	glutSwapBuffers();
}

void init()
{
	
}

void term()
{
	UserData* ud = (UserData*)glutGetWindowData();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4,6);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("basic");

	std::shared_ptr<UserData> ud = std::make_shared<UserData>();
	glutSetWindowData(ud.get());
	
	if(!Solid::Graphics::initGL())
	{
		std::cout << "Failed to load GL." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	init(); 

	glutMainLoop();
	
	term();
	return 0;
}
