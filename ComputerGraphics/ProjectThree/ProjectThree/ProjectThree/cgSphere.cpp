#include "cgSphere.h"
#include <math.h>
#include <GL/glew.h>//OpenGL库

cgSphere::cgSphere(void)
{
	ptPos = cgPoint3D();
}


cgSphere::~cgSphere(void)
{
}

void cgSphere::SetPos(cgPoint3D pos)
{
	ptPos = pos;
}

void cgSphere::InitData(float r)
{
	fR = r;

	vTris.clear();
	//生成球心在坐标原点的球面三角网
    int m = 20;//水平方向圆离散化多边形边数
	int n = 20;//垂直方向切片个数

	float dalpha = 2*PI/m;
	float dbeta  = PI/n;

	float beta = -PI/2.0f;
	for (int i=0; i<n;i++)
	{
		float alpha = 0.0f;

		float z1 = fR*sin(beta);
		float z2 = fR*sin(beta+dbeta);

		float r0 = fR*cos(beta);
		float r1 = fR*cos(beta+dbeta);

		beta += dbeta;
		for (int j=0; j<m; j++)
		{
			float x01 = r0*cos(alpha);
			float y01 = r0*sin(alpha);

			float x02 = r0*cos(alpha+dalpha);
			float y02 = r0*sin(alpha+dalpha);

			float x11 = r1*cos(alpha);
			float y11 = r1*sin(alpha);

			float x12 = r1*cos(alpha+dalpha);
			float y12 = r1*sin(alpha+dalpha);

			//构建三角形
			cgTriangle tri;
			tri.Pt[0] = cgPoint3D(x01,y01,z1);
			tri.Pt[1] = cgPoint3D(x02,y02,z1);
			tri.Pt[2] = cgPoint3D(x11,y11,z2);
			vTris.push_back(tri);

			tri.Pt[0] = cgPoint3D(x02,y02,z1);
			tri.Pt[1] = cgPoint3D(x12,y12,z2);
			tri.Pt[2] = cgPoint3D(x11,y11,z2);
			vTris.push_back(tri);

			alpha += dalpha;
		}
	}
}

void cgSphere::Render()
{
	vector<cgTriangle>::iterator it = vTris.begin();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(ptPos.x,ptPos.y,ptPos.z);
	for(; it != vTris.end(); it++)
	{
	   (*it).Render();
	}

	glPopMatrix();
}


