#pragma once
#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Constants.h"
#include "Cube.h"

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]); //Constructor definition
	~HelloGL(void); //Destructor

	void Display();
	void Update();
	void Timer();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();

private:
	Camera* camera;
	SceneObject* objects[OBJECT_NUM];
	Vector4* _lightPosition;
	Lighting* _lightData;
};

