#define SOLID_GL_USE_GLEW
#define SOLID_DO_NOT_DEBUG
#include <iostream>
#include <memory>
#include "../SolidGameEngine/Graphics/core/gl.hpp"
#include "../SolidGameEngine/Graphics/core/Program.hpp"
#include "../SolidGameEngine/Graphics/core/Sprite.hpp"
#include "../SolidGameEngine/Graphics/core/Camera.hpp"
#include "../SolidGameEngine/Utils/GLError.hpp"
#include "../SolidGameEngine/Utils/Time.hpp"
#include <GL/freeglut.h>

struct UserData
{
	Solid::Graphics::UsualProgram program;
	Solid::Graphics::EulerAngleCamera camera;
	Solid::Graphics::Sprite sprite;
	float lastTime;
	float deltaTime;

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
			std::cout << matrix[j][i] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void display()
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ud->program.useProgram();
	ud->program.setUniform("u_projection", ud->camera.getProjectionMatrix());
	ud->program.setUniform("u_view", ud->camera.getViewMatrix());
	ud->sprite.beRendered(ud->program);

	glutSwapBuffers();
}

void idle()
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	float currentTime = Solid::Utils::getCurrentTime();
	float deltaTime = currentTime - ud->lastTime;

	const float FPS = 60.0f;
	const float SPF = 1.0f / FPS;

	if (deltaTime > SPF)
	{
		ud->deltaTime = deltaTime;
		display();
		ud->lastTime = currentTime;
	}
}

void keyboard(unsigned char key, int, int)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	switch (key)
	{
		case 27:
			exit(EXIT_SUCCESS);
			break;
		case 'w':
			ud->camera.rotate(0, 1);
			break;
		case 's':
			ud->camera.rotate(0, -1);
		case 'a':
			ud->camera.rotate(-1, 0);
			break;
		case 'd':
			ud->camera.rotate(1, 0);
			break;
		case 'i':
			ud->sprite.translate(glm::vec3(0,0.01,0));
			break;
		case 'k':
			ud->sprite.translate(glm::vec3(0,-0.01,0));
		case 'j':
			ud->sprite.translate(glm::vec3(-0.01,0,0));
			break;
		case 'l':
			ud->sprite.translate(glm::vec3(0.01,0,0));
			break;
		default:
			break;
	}

	outputVector(ud->camera.getFront());
	ud->camera.updateViewMatrix();
	ud->sprite.updateMatrix();
}

void special(int key, int, int)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	switch (key)
	{
		case GLUT_KEY_UP:
			ud->camera.move(Solid::Graphics::View::MovementDirection::FORWARD, ud->deltaTime);
			break;
		case GLUT_KEY_DOWN:
			ud->camera.move(Solid::Graphics::View::MovementDirection::BACKWARD, ud->deltaTime);
		case GLUT_KEY_LEFT:
			ud->camera.move(Solid::Graphics::View::MovementDirection::LEFT, ud->deltaTime);
			break;
		case GLUT_KEY_RIGHT:
			ud->camera.move(Solid::Graphics::View::MovementDirection::RIGHT, ud->deltaTime);
			break;
		default:
			break;
	}

	outputVector(ud->camera.getFront());
	ud->camera.updateViewMatrix();
}

void reshape(int w, int h)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	ud->camera.setAspect(float(w) / float(h));
	ud->camera.updateProjectionMatrix();
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
	glutSpecialFunc(special);
	glutIdleFunc(idle);

	std::cout << "Solid::Graphics::initGL():" << Solid::Graphics::initGL() << std::endl;
	Solid::Utils::bindDebugCallback();

	glEnable(GL_DEPTH_TEST);

	ud->program.loadFromFile("shader/2.vert", "shader/2.frag");
	std::cout << "program.getGLObjectID():" << ud->program.getGLObjectID() << std::endl;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
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
	std::cout << "vao:" << vao << std::endl;

	ud->camera.setMovementSpeed(1.0f);

	ud->sprite.setVAO(vao);
	ud->sprite.setVertexCount(3);

	ud->lastTime = Solid::Utils::getCurrentTime();

	glutMainLoop();
	glDeleteVertexArrays(1, &vao);
	ud->program.deleteGLObject();
	return 0;
}
