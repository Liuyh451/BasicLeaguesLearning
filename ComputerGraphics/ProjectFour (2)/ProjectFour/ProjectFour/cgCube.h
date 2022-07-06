#pragma once
#include "cgPoint3D.h"
#include "cgTriangle.h"
#include<vector>
using namespace std;
#include <GL\glew.h>

class cgCube
{
public:
	cgCube(void);
	~cgCube(void);

	void InitData(float length);
	void Render();
	void SetPos(cgPoint3D pos);	
	void SetTexture(GLuint texture);
	void UpdateTexCord();
private:
	float fLength;
	cgPoint3D ptPos;
	vector<cgTriangle> vTris;

	GLuint textureID;
	int iFrames;
};

