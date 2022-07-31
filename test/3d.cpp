#define SOLID_GL_USE_GLEW
#define SOLID_DO_NOT_DEBUG
#include <iostream>
#include <memory>
#include "../SolidGameEngine/Graphics/core/gl.hpp"
#include "../SolidGameEngine/Graphics/core/Program.hpp"
#include "../SolidGameEngine/Graphics/core/Transform.hpp"
#include "../SolidGameEngine/Graphics/core/Projection.hpp"
#include "../SolidGameEngine/Graphics/core/View.hpp"
#include "../SolidGameEngine/Utils/GLError.hpp"
#include <GL/freeglut.h>

struct UserData
{
	Solid::Graphics::UsualProgram program;
	Solid::Graphics::Transform transform;
	Solid::Graphics::EulerAngleView view/*(glm::vec3(1, 1, 1), glm::vec3(-1, -1, -1), glm::vec3(0, 1, 0))*/;
	Solid::Graphics::PerspectiveProjection projection/*(60.0f, 1.0f, 0.1f, 100.0f)*/;
	GLuint vao;
	const GLfloat ver[9] =
	{
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	const GLfloat col[9] =
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
};

void outputVector(glm::vec3 vector)
{
	std::cout << vector.x << "," << vector.y << "," << vector.z << std::endl;
}

void outputMatrix(glm::mat4 matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << matrix[j][i] << "\t\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*glm::mat4 updateMatrix()
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, m_translate);
	matrix = glm::rotate(matrix, m_rotate.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, m_rotate.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, m_rotate.z, glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, m_scale);
	return matrix;
}*/

void display()
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glm::mat4 projection = glm::perspective(60.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, -1));

	outputMatrix(projection);
	outputMatrix(view);
	outputMatrix(model);*/

	ud->program.useProgram();
	ud->program.setUniform("u_projection", ud->projection.getMatrix()/*glm::mat4(1)projection*/);
	ud->program.setUniform("u_view", ud->view.getMatrix()/*glm::mat4(1)view*/);
	ud->program.setUniform("u_model", ud->transform.getMatrix()/*glm::mat4(1)model*/);
	glBindVertexArray(ud->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	//outputMatrix(ud->view.getMatrix());

	glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	if (key == 27)
	{
		exit(EXIT_SUCCESS);
	}
	else if (key == 'w')
	{
		ud->view.rotate(0, 1);
	}
	else if (key == 's')
	{
		ud->view.rotate(0, -1);
	}
	else if (key == 'a')
	{
		ud->view.rotate(-1, 0);
	}
	else if (key == 'd')
	{
		ud->view.rotate(1, 0);
	}
	else if (key == 'i')
	{
		outputVector(ud->view.getFront());
		ud->view.move(ud->view.getFront());
	}
	else if (key == 'k')
	{
		ud->view.move(-ud->view.getFront());
	}
	ud->view.updateMatrix();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	ud->projection.setAspect(float(w) / float(h));
	ud->projection.updateMatrix();
	glViewport(0, 0, w, h);
}

int main(int argc, char* argv[])
{
	std::shared_ptr<UserData> ud = std::make_shared<UserData>();

	glutInit(&argc, argv);
	glutInitContextVersion(4, 6);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("");
	glutSetWindowData(&ud);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);

	std::cout << "Solid::Graphics::initGL():" << Solid::Graphics::initGL() << std::endl;
	Solid::Utils::bindDebugCallback();

	glEnable(GL_DEPTH_TEST);

	ud->program.loadFromFile("shader/2.vert", "shader/2.frag");
	std::cout << "program.getGLObjectID():" << ud->program.getGLObjectID() << std::endl;

	glGenVertexArrays(1, &ud->vao);
	glBindVertexArray(ud->vao);
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->ver), ud->ver, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->col), ud->col, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, vbo);
	std::cout << "vao:" << ud->vao << std::endl;

	std::cout << "projection:" << std::endl;
	//outputMatrix(ud->projection.getMatrix());
	//ud->projection = Solid::Graphics::PerspectiveProjection(60.0f, 1.0f, 0.1f, 100.0f);
	ud->projection.updateMatrix();
	outputMatrix(ud->projection.getMatrix());

	std::cout << "transform:" << std::endl;
	//outputMatrix(ud->transform.getMatrix());
	//ud->transform = Solid::Graphics::Transform();
	ud->transform.loadIdentity();
	ud->transform.setTranslate(glm::vec3(0.1, 0.1, 0));
	ud->transform.updateMatrix();
	outputMatrix(ud->transform.getMatrix());

	std::cout << "view:" << std::endl;
	//outputMatrix(ud->view.getMatrix());
	//ud->view = Solid::Graphics::View(glm::vec3(1, 1, 1), glm::vec3(-1, -1, -1), glm::vec3(0, 1, 0));
	ud->view.setPosition(glm::vec3(1, 1, 1));
	//ud->view.setFront(glm::vec3(-1, -1, -1));
	ud->view.setUp(glm::vec3(0, 1, 0));
	Solid::Graphics::EulerAngle angle(225, -45);
	ud->view.setEulerAngle(angle);
	ud->view.updateMatrix();
	outputMatrix(ud->view.getMatrix());

	glutMainLoop();
	glDeleteVertexArrays(1, &ud->vao);
	ud->program.deleteGLObject();
	return 0;
}
