#define SOLID_GL_USE_GLEW
#define SOLID_DO_NOT_DEBUG
#include <iostream>
#include <memory>
#include <map> 
#include "../SolidGameEngine/Graphics/core/gl.hpp"
#include "../SolidGameEngine/Graphics/core/Program.hpp"
#include "../SolidGameEngine/Graphics/core/Sprite.hpp"
#include "../SolidGameEngine/Graphics/core/Camera.hpp"
#include "../SolidGameEngine/Utils/GLError.hpp"
#include "../SolidGameEngine/Utils/Time.hpp"
#include "../SolidGameEngine/Graphics/extra/TextFactory.hpp"
#include <GL/freeglut.h>

struct UserData
{
	Solid::Graphics::UsualProgram program;
	Solid::Graphics::OrbitView view;
	Solid::Graphics::OrthoProjection projection;
	Solid::Graphics::Sprite sprite;
	std::map<char,Solid::Graphics::Character> characters;

	float lastTime;
	float deltaTime;

	const GLfloat ver[4 * 3] =
	{
		-1, 1, 0,
		    -1, -1, 0,
		    1, -1, 0,
		    1, 1, 0
	    };
	const GLfloat tex[4 * 2] =
	{
		0, 0,
		0, 1,
		1, 1,
		1, 0
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
	ud->program.setUniform("u_view", ud->view.getMatrix());
	ud->characters.at('a').bind();
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
			ud->view.rotate(0, 1);
			break;
		case 's':
			ud->view.rotatePitch(-1);
		case 'a':
			ud->view.rotate(-1, 0);
			break;
		case 'd':
			ud->view.rotate(1, 0);
			break;
		default:
			break;
	}

	std::cout << "yaw:" << ud->view.getEulerAngle().yaw() << std::endl
	          << "pitch:" << ud->view.getEulerAngle().pitch() << std::endl
	          << std::endl;
	ud->view.updateMatrix();
}

void special(int key, int, int)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	switch (key)
	{
		case GLUT_KEY_UP:
			ud->view.move(Solid::Graphics::View::MovementDirection::FORWARD, ud->deltaTime);
			break;
		case GLUT_KEY_DOWN:
			ud->view.move(Solid::Graphics::View::MovementDirection::BACKWARD, ud->deltaTime);
		case GLUT_KEY_LEFT:
			ud->view.move(Solid::Graphics::View::MovementDirection::LEFT, ud->deltaTime);
			break;
		case GLUT_KEY_RIGHT:
			ud->view.move(Solid::Graphics::View::MovementDirection::RIGHT, ud->deltaTime);
			break;
		default:
			break;
	}

	ud->view.updateMatrix();
}

void reshape(int w, int h)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	ud->projection.set(-1,1,1,-1);
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
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	
	glutSetWindowData(&ud);
	glutFullScreen();

	std::cout << "Solid::Graphics::initGL():" << Solid::Graphics::initGL() << std::endl;
	Solid::Utils::bindDebugCallback();

	glEnable(GL_DEPTH_TEST);

	ud->program.loadFromFile("shader/texture.vert", "shader/texture.frag");
	std::cout << "program.getGLObjectID():" << ud->program.getGLObjectID() << std::endl;

	Solid::Graphics::TextFactory factory("resources/arial.ttf");
	Solid::Graphics::Character c = factory.loadCharacter('a');
	ud->characters.insert(std::pair<char, Solid::Graphics::Character>('a', c));
	factory.release();

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(ud->tex), ud->tex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, vbo);
	std::cout << "vao:" << vao << std::endl;
	
	ud->view.set(90,0);
	ud->view.setMovementSpeed(1.0f);
	ud->view.setTargetDistance(3.0f);
	ud->view.setTarget(&ud->sprite);
	ud->view.setIsEnableAngleConstraint(true);
	ud->view.update();

	ud->sprite.setVAO(vao);
	ud->sprite.setVertexCount(4);
	ud->sprite.setDrawMode(Solid::Graphics::Sprite::DrawMode::TRIANGLE_FAN);

	ud->lastTime = Solid::Utils::getCurrentTime();

	glutMainLoop();
	glDeleteVertexArrays(1, &vao);
	ud->program.deleteGLObject();
	ud->characters.at('a').release();
	return 0;
}
