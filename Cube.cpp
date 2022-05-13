#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_material = 0;
	_rotation = 0.0f;
	_mesh = mesh;
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Cube::Update()
{
	_rotation += rand() % 20;
	_rotation -= rand() % 20;
}

void Cube::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 1.0; _material->Ambient.y = 0.0; _material->Ambient.z = 0.0; _material->Ambient.w = 0.0;
	_material->Diffuse.x = 1.0; _material->Diffuse.y = 0.0; _material->Diffuse.z = 0.0; _material->Diffuse.w = 0.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 0.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		InitMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess));

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisable(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

Cube::~Cube()
{
	delete _material;
	_material = nullptr;
}