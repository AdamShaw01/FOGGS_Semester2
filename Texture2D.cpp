#include "Texture2D.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
using namespace std;

Texture2D::Texture2D()
{
	_ID = 0;
	_height = 0;
	_width = 0;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(TEXTURE_SIZE, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file" << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char[fileSize];
	inFile.seekg(0, ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	cout << path << " loaded." << endl;

	glGenTextures(TEXTURE_SIZE, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	return true;
}