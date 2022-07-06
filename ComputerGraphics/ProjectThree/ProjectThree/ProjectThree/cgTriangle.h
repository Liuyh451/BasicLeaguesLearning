#pragma once

#include <GL/glew.h>//OpenGL¿â
#include "cgPoint3D.h"
using namespace std;

class cgTriangle
{
public:
	cgTriangle(void);
	~cgTriangle(void);

	cgPoint3D Pt[3];

	void Render();
};

