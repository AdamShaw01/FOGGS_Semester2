#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;
}

SceneObject::~SceneObject()
{
	delete _mesh;
	_mesh = nullptr;
	delete _texture;
	_texture = nullptr;
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}

