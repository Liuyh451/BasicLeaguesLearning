#pragma once

#include "cgPoint3D.h"
#include "cgTriangle.h"
#include<vector>
using namespace std;

class cgSphere
{
public:
	cgSphere(void);
	~cgSphere(void);

	void InitData(float r);
	void Render();
	void SetPos(cgPoint3D pos);

private:
	float fR;
	cgPoint3D ptPos; 
	vector<cgTriangle> vTris;
};

