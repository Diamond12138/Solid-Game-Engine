#define SOLID_GL_USE_GLEW
#define SOLID_DO_NOT_DEBUG
#include <iostream>
#include "../SolidGameEngine/Graphics/core/gl.hpp"
#include "../SolidGameEngine/Graphics/core/Program.hpp"
#include "../SolidGameEngine/Utils/StringLoader.hpp"
#include "../SolidGameEngine/Utils/GLError.hpp"
#include <GL/freeglut.h>

//GLuint program;
Solid::Graphics::UsualProgram program;
Solid::Utils::StringLoader string_load;
GLuint vao;
/*GLfloat ver[] =
{
	0.0f, 0.5f,
	-0.5f, -0.5f,
	0.5f, -0.5f
};*/
GLfloat col[] =
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};
std::vector<float> ver
{
	0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program.useProgram();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glutSwapBuffers();
}

void idle()
{
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 6);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//glutIdleFunc(idle);

	std::cout << Solid::Graphics::initGL() << std::endl;
	Solid::Utils::bindDebugCallback();
	
	program.loadFromFile("shader/1.vert","shader/1.frag");
	std::cout << program.getGLObjectID() << std::endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(float), ver.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, vbo);

	glutMainLoop();
	glDeleteVertexArrays(1, &vao);
	program.deleteGLObject();
	return 0;
}
