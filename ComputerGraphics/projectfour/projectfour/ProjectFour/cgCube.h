#pragma once
#include "cgPoint3D.h"
#include "cgTriangle.h"
#include<vector>
#include <GL/glew.h>
using namespace std;

class cgCube
{
public:
	cgCube(void);
	~cgCube(void);

	void InitData(float width);
	void Render(GLuint texture);
	void SetPos(cgPoint3D pos);
	void push_plane(float left,float right,float up,float down,float height);
	void push_plane_lr(float x,float y_down,float y_up,float z_down,float z_up);
	void push_plane_nf(float y,float x_left,float x_right,float z_down,float z_up);

private:
	float width;
	cgPoint3D ptPos; 
	vector<cgTriangle> vTris;
	vector<cgPoint3D> texture_points;

};

