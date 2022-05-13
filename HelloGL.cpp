#include "HelloGL.h"
#include <iostream>
#include "Cube.h"
#include "Structures.h"
#include "MeshLoader.h"
using namespace std;

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();
	InitLighting();
	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		objects[i]->Draw();
	}
	
	//Draws text to screen
	glColor3f(1, 0, 0);
	glRasterPos3f(camera->center.x - 4.2, camera->center.y - 4.2, camera->center.z);
	const char* score = "Score:";
	int stringLength = (int)strlen(score);
	for (int i = 0; i < stringLength; i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		objects[i]->Update();
	}
	glutPostRedisplay();

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glutPostRedisplay();
}

void HelloGL::Timer()
{

}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 40.0f; camera->eye.y = 40.0f; camera->eye.z = 20.0f;
	camera->center.x = 40.0f; camera->center.y = 40.0f; camera->center.z = 10.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	Mesh* cubeMesh = MeshLoader::Load("cube.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", TEXTURE_WIDTH, TEXTURE_HEIGHT);

	for (int i = 0; i < OBJECT_NUM; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 1000) / 10.0f) - 10.0f, ((rand() % 1000) / 10.0f) - 10.0f, -(rand() % 2000) / 10.0f);
	}
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My OpenGL Program");
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Sets the viewport to be the entire window
	glViewport(0, 0, 1, 1000);
	//Sets the correct perspective
	//FOV, aspect ratio, near clipping distance, far clipping distance
	gluPerspective(50, 1, 0.3, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = camera->eye.x; _lightPosition->y = camera->eye.y; _lightPosition->z = camera->eye.z; _lightPosition->w = 1.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.0; _lightData->Ambient.y = 1.0; _lightData->Ambient.z = 1.0; _lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.1; _lightData->Diffuse.y = 0.0; _lightData->Diffuse.z = 1.0; _lightData->Diffuse.w = 1.0; 
	_lightData->Specular.x = 1.0; _lightData->Specular.y = 0.0; _lightData->Specular.z = 1.0; _lightData->Specular.w = 1.0;
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		camera->eye.z -= 1;
		camera->center.z -= 1;
	}
	if (key == 's')
	{
		camera->eye.z += 1;
		camera->center.z += 1;
	}
	if (key == 'a')
	{
		camera->eye.x -= 1;
		camera->center.x -= 1;
	}
	if (key == 'd')
	{
		camera->eye.x += 1;
		camera->center.x += 1;
	}
}

HelloGL::~HelloGL(void)
{
	delete camera;
	camera = nullptr;
	delete _lightData;
	_lightData = nullptr;
	delete _lightPosition;
	_lightPosition = nullptr;
	delete[] objects;
}