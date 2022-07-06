#pragma once
#include "cgPoint3D.h"
#include "cgTriangle.h"
#include <GL/glew.h>//OpenGL¿â

#include<vector>
using namespace std;

class cgCylinder
{
public:
	cgCylinder(void);
	~cgCylinder(void);

	void InitData(float r,float h);
	void Render();
	void SetPos(cgPoint3D pos);	
	void SetTexture(GLuint texture);
private:
	float fR;
	float fH;

	cgPoint3D ptPos;
	vector<cgTriangle> vTris;
	GLuint textureID;
		
	int iCount0;
	int iCount1;
};

