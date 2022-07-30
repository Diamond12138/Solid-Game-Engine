#define SOLID_GL_USE_GLEW
#define SOLID_DO_NOT_DEBUG
#include "../SolidGameEngine/Graphics/core/Program.hpp"
#include "../SolidGameEngine/Graphics/core/BufferObject.hpp"
#include "../SolidGameEngine/Graphics/core/VertexArrayObject.hpp"
#include "../SolidGameEngine/Utils/GLError.hpp"
#include <iostream>
#include <GL/freeglut.h>
#include <memory>

struct UserData
{
	Solid::Graphics::UsualProgram program;
	Solid::Graphics::VertexArrayObject vao;
	//GLuint vao;

	float ver[6] =
	{
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};
	float col[9] =
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
};


void display()
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	glClear(GL_COLOR_BUFFER_BIT);

	ud->program.useProgram();
	ud->vao.bind();
	//glBindVertexArray(ud->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	ud->vao.bindZero();
	//glBindVertexArray(0);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
	std::shared_ptr<UserData> ud = std::make_shared<UserData>();

	glutInit(&argc, argv);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextVersion(3, 3);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("");
	glutSetWindowData(&ud);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	std::cout << "Solid::Graphics::initGL():" << Solid::Graphics::initGL() << std::endl;
	Solid::Utils::bindDebugCallback();

	std::cout << "ver:";
	for (float i : ud->ver) std::cout << i << ",";
	std::cout << std::endl;
	std::cout << "col:";
	for (float i : ud->col) std::cout << i << ",";
	std::cout << std::endl;

	ud->program.loadFromFile("shader/1.vert", "shader/1.frag");
	std::cout << "ud->program.getGLObjectID():" << ud->program.getGLObjectID() << std::endl;

	Solid::Graphics::VertexBufferObject vbo1;
	Solid::Graphics::VertexBufferObject vbo2;
	ud->vao.bind();
	vbo1.bindVertexAttrib(sizeof(ud->ver),ud->ver,0,2);
	vbo2.bindVertexAttrib(sizeof(ud->col),ud->col,1,3);
	ud->vao.bindZero();
	vbo1.deleteGLObject();
	vbo2.deleteGLObject();
	/*glGenVertexArrays(1, &ud->vao);
	glBindVertexArray(ud->vao);
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->ver.data()), ud->ver.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->col.data()), ud->col.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, vbo);*/

	glutMainLoop();
	ud->program.deleteGLObject();
	ud->vao.deleteGLObject();
	//glDeleteVertexArrays(1, &ud->vao);
	return 0;
}
