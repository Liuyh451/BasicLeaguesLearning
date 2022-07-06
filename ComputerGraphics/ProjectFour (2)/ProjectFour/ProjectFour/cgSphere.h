#pragma once
#include "cgPoint3D.h"
#include "cgTriangle.h"
#include<vector>
#include <GL\glew.h>

using namespace std;

class cgSphere
{
public:
	cgSphere(void);
	~cgSphere(void);

	void InitData(float r);
	void Render();
	void SetPos(cgPoint3D pos);
	void SetTexture(GLuint texture);
private:
	float fR;
	cgPoint3D ptPos; 
	vector<cgTriangle> vTris;
	GLuint textureID;
};

