#pragma once

#include "cgPoint3D.h"
#include "cgTriangle.h"
#include "cgCube.h"
#include<vector>
using namespace std;

class cgCube
{
public:
	cgCube(void);
	~cgCube(void);

	void Render();
	void SetPos(cgPoint3D pos);

private:
	cgPoint3D ptPos; 
};