#pragma once
#include <iostream>
#include "Structures.h"
#include "Texture2D.h"
using namespace std;

namespace MeshLoader
{
	Mesh* Load(string path);
};