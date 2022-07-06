#pragma once
#include "cgPoint3D.h"
#include "cgTriangle.h"
#include<vector>
#include <GL/glew.h>
using namespace std;

class cgLinder
{
public:
	cgLinder(void);
	~cgLinder(void);

	void InitData(float r,float height);
	void Render(GLuint texture);
	void SetPos(cgPoint3D pos);

private:
	float fR;
	float fHeight;
	cgPoint3D ptPos; 
	vector<cgTriangle> vTris;
	vector<cgPoint3D> texture_points;
};
