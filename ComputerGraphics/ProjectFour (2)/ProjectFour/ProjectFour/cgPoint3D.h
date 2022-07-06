#pragma once

#define PI 3.14259

class cgPoint3D
{
public:
	cgPoint3D(void);
	cgPoint3D(float xx,float yy,float zz);
	~cgPoint3D(void);

	//坐标
	float x;
	float y;
	float z;

	//法向量
	float nX;
	float nY;
	float nZ;

	//纹理坐标
	float s;
	float t;
};

