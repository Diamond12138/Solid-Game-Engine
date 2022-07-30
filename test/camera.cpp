#define SOLID_GL_USE_GLEW
#define SOLID_DO_NOT_DEBUG
#include <iostream>
#include <memory>
#include "../SolidGameEngine/Graphics/core/gl.hpp"
#include "../SolidGameEngine/Graphics/core/Program.hpp"
#include "../SolidGameEngine/Graphics/core/Transform.hpp"
#include "../SolidGameEngine/Graphics/core/Camera.hpp"
#include "../SolidGameEngine/Utils/GLError.hpp"
#include <GL/freeglut.h>

class MyCamera : public Solid::Graphics::Camera, public Solid::Graphics::EulerAngleView, public Solid::Graphics::PerspectiveProjection
{
	public:
		MyCamera() : Solid::Graphics::EulerAngleView(glm::vec3(1, 1, 1),glm::vec3(-1, -1, -1)), Solid::Graphics::PerspectiveProjection(60.0f, 1.0f, 0.1f, 100.0f)
		{
			updateViewMatrix();
			updateProjectionMatrix();
		}

	public:
		virtual glm::mat4 getViewMatrix()
		{
			return Solid::Graphics::EulerAngleView::getMatrix();
		}
		virtual glm::mat4 getProjectionMatrix()
		{
			return Solid::Graphics::PerspectiveProjection::getMatrix();
		}
		virtual MyCamera& updateViewMatrix()
		{
			Solid::Graphics::EulerAngleView::updateMatrix();
			return *this;
		}
		virtual MyCamera& updateProjectionMatrix()
		{
			Solid::Graphics::PerspectiveProjection::updateMatrix();
			return *this;
		}
};

/*class MyCamera : public Solid::Graphics::Camera
{
	public:
		Solid::Graphics::EulerAngleView view;
		Solid::Graphics::PerspectiveProjection projection;
		
	public:
		MyCamera& updateProjectionMatrix()
		{
			projection.updateMatrix();
			return *this;
		}
		MyCamera& updateViewMatrix()
		{
			view.updateMatrix();
			return *this;
		}
		glm::mat4 getProjectionMatrix()
		{
			return projection.getMatrix();
		}
		glm::mat4 getViewMatrix()
		{
			return view.getMatrix();
		}
		
};*/

struct UserData
{
	Solid::Graphics::UsualProgram program;
	Solid::Graphics::Transform transform;
	MyCamera camera;
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
	ud->program.setUniform("u_model", ud->transform.getMatrix());
	glBindVertexArray(ud->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	if (key == 27)
	{
		exit(EXIT_SUCCESS);
	}
	else if(key == 'd')
	{
		ud->camera.rotate(1,0);
		//ud->camera.view.rotate(1,0);
		ud->camera.updateViewMatrix();
		outputMatrix(ud->camera.getViewMatrix());
		glutPostRedisplay();
	}
}

void reshape(int w, int h)
{
	UserData* ud = ((std::shared_ptr<UserData>*)glutGetWindowData())->get();

	ud->camera.setAspect(float(w) / float(h));
	//ud->camera.projection.setAspect(float(w) / float(h));
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
	
	Solid::Graphics::EulerAngleView(ud->camera).set(glm::vec3(1,1,1),glm::vec3(-1,-1,-1));
	//ud->camera.view.set(glm::vec3(1,1,1),glm::vec3(-1,-1,-1));
	ud->camera.updateViewMatrix();
	
	Solid::Graphics::PerspectiveProjection(ud->camera).set(60,1,0.1,100);
	//ud->camera.projection.set(60,1,0.1,100);
	ud->camera.updateProjectionMatrix();
	
	ud->transform.loadIdentity();
	//ud->transform.setTranslate(glm::vec3(0.1, 0.1, 0.1));
	ud->transform.updateMatrix();
	
	std::cout << "projection:" << std::endl;
	outputMatrix(ud->camera.getProjectionMatrix());
	std::cout << "view:" << std::endl;
	outputMatrix(ud->camera.getViewMatrix());
	//ud->camera.updateViewMatrix();
	outputMatrix(ud->camera.getViewMatrix());
	std::cout << "model:" << std::endl;
	outputMatrix(ud->transform.getMatrix());

	glutMainLoop();
	glDeleteVertexArrays(1, &ud->vao);
	ud->program.deleteGLObject();
	return 0;
}
