#include "platform.hpp"
#include "ApplicationContext.hpp"
#include <memory>
#include <GL/freeglut.h>

void display()
{
	std::shared_ptr<Solid::ApplicationContext>* ptr = (std::shared_ptr<Solid::ApplicationContext>*)glutGetWindowData();
	Solid::ApplicationContext* context = ptr->get();
	onDraw(context);
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	std::shared_ptr<Solid::ApplicationContext> context = std::make_shared<Solid::ApplicationContext>();
	glutSetWindowData(&context);
	
	if(!Solid::Graphics::initGL())
	{
		std::cout << "Failed to load GL." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	onCreate(*(Solid::ApplicationContext*)context.get());

	glutMainLoop();

	onDestroy(*(Solid::ApplicationContext*)context.get());

	return 0;
}

void start(std::string title, int w, int h, int x, int y, int major, int minor)
{
	glutInitContextVersion(major, minor);
	if (x != -1 && y != -1)
	{
		glutInitWindowPosition(x, y);
	}
	if (w != -1 && h != -1)
	{
		glutInitWindowSize(w, h);
	}
	glutCreateWindow(title.data());
}
