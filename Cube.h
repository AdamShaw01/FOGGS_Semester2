#pragma once
#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "GL\freeglut.h" //freeglut library
#include "MeshLoader.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void InitMaterial();

private:
	GLfloat _rotation;
	Vector3 _position;
	Material* _material;
};