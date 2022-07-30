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
	Solid::Graphics::FollowingView view1;
	Solid::Graphics::OrbitView view2;
	Solid::Graphics::PerspectiveProjection projection;
	Solid::Graphics::Sprite sprite;
	Solid::Graphics::Sprite axis;

	float lastTime;
	float deltaTime;

	const GLfloat ver1[3 * 3] =
	{
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	const GLfloat col1[3 * 3] =
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	const GLfloat ver2[6 * 3] =
	{
		-100, 0, 0,
		    100, 0, 0,
		    0, -100, 0,
		    0, 100, 0,
		    0, 0, -100,
		    0, 0, 100
	    };
	const GLfloat col2[6 * 3] =
	{
		0, 0, 0,
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		0, 0, 0,
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
	ud->program.setUniform("u_projection", ud->projection.getMatrix());
	ud->program.setUniform("u_view", ud->view2.getMatrix());
	ud->sprite.beRendered(ud->program);
	ud->axis.beRendered(ud->program);

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
		
		ud->sprite.translate(glm::vec3(0.5, 0.5, 0.5) * SPF);
		ud->sprite.updateMatrix();
		
		ud->view1.update();
		ud->view2.update();
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
			ud->view2.rotate(0, 1);
			break;
		case 's':
			ud->view2.rotate(0, -1);
			break;
		case 'a':
			ud->view2.rotate(1, 0);
			break;
		case 'd':
			ud->view2.rotate(-1, 0);
			break;
		default:
			break;
	}
	
	ud->view2.update();
}

void special(int key, int, int)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	switch (key)
	{
		default:
			break;
	}
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
	glutSpecialFunc(special);
	glutIdleFunc(idle);

	std::cout << "Solid::Graphics::initGL():" << Solid::Graphics::initGL() << std::endl;
	Solid::Utils::bindDebugCallback();

	glEnable(GL_DEPTH_TEST);

	ud->program.loadFromFile("shader/2.vert", "shader/2.frag");
	std::cout << "program.getGLObjectID():" << ud->program.getGLObjectID() << std::endl;

	GLuint vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
	GLuint vbo1[2];
	glGenBuffers(2, vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->ver1), ud->ver1, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->col1), ud->col1, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, vbo1);
	std::cout << "vao1:" << vao1 << std::endl;

	GLuint vao2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	GLuint vbo2[2];
	glGenBuffers(2, vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->ver2), ud->ver2, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->col2), ud->col2, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, vbo2);
	std::cout << "vao2:" << vao2 << std::endl;

	ud->sprite.setVAO(vao1);
	ud->sprite.setVertexCount(3);

	ud->axis.setVAO(vao2);
	ud->axis.setVertexCount(6);
	ud->axis.setDrawMode(Solid::Graphics::Sprite::LINES);

	ud->view1.setTarget(&ud->sprite);
	ud->view1.update();

	ud->view2.setTarget(&ud->sprite);
	ud->view2.update();
	
	ud->projection.setFovy(120);
	ud->projection.updateMatrix();

	ud->lastTime = Solid::Utils::getCurrentTime();

	glutMainLoop();
	glDeleteVertexArrays(1, &vao1);
	glDeleteVertexArrays(1, &vao2);
	ud->program.deleteGLObject();
	return 0;
}
