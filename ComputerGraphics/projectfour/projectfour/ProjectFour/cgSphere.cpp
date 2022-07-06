#include "cgSphere.h"
#include <math.h>
#include <GL/glew.h>//OpenGL库
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgSphere::cgSphere(void)
{
	ptPos = cgPoint3D();

	textureID = 0;
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
    int m = 50;//水平方向圆离散化多边形边数
	int n = 50;//垂直方向切片个数

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
			//顶点几何坐标
			float x01 = r0*cos(alpha);
			float y01 = r0*sin(alpha);

			float x02 = r0*cos(alpha+dalpha);
			float y02 = r0*sin(alpha+dalpha);

			float x11 = r1*cos(alpha);
			float y11 = r1*sin(alpha);

			float x12 = r1*cos(alpha+dalpha);
			float y12 = r1*sin(alpha+dalpha);
			
			//顶点纹理坐标
			float s1,t1,s2,t2;
		
			s1 = alpha/(2*PI);  s2 = (alpha+dalpha)/(2*PI);
			t1 = (beta-dbeta)/PI+0.5; t2 = (beta)/PI+0.5;

			//构建三角形
			cgTriangle tri;
			tri.Pt[0] = cgPoint3D(x01,y01,z1);//顶点几何坐标
			tri.Pt[0].s = s1; tri.Pt[0].t = t1;//顶点纹理坐标
			glm::vec3 vnormal = glm::normalize(glm::vec3(x01,y01,z1));
			tri.Pt[0].nX = vnormal.x; tri.Pt[0].nY = vnormal.y; tri.Pt[0].nZ = vnormal.z;//顶点法向向量

			tri.Pt[1] = cgPoint3D(x02,y02,z1);
			tri.Pt[1].s = s2; tri.Pt[1].t = t1;
			vnormal = glm::normalize(glm::vec3(x02,y02,z1));
			tri.Pt[1].nX = vnormal.x; tri.Pt[1].nY = vnormal.y; tri.Pt[1].nZ = vnormal.z;

			tri.Pt[2] = cgPoint3D(x11,y11,z2);
			tri.Pt[2].s = s1; tri.Pt[2].t = t2;
			vnormal = glm::normalize(glm::vec3(x11,y11,z2));
			tri.Pt[2].nX = vnormal.x; tri.Pt[2].nY = vnormal.y; tri.Pt[2].nZ = vnormal.z;//顶点法向向量

			vTris.push_back(tri);

			tri.Pt[0] = cgPoint3D(x02,y02,z1);
			tri.Pt[0].s = s2; tri.Pt[0].t = t1;
			vnormal = glm::normalize(glm::vec3(x02,y02,z1));
			tri.Pt[0].nX = vnormal.x; tri.Pt[0].nY = vnormal.y; tri.Pt[0].nZ = vnormal.z;//顶点法向向量

			tri.Pt[1] = cgPoint3D(x12,y12,z2);
			tri.Pt[1].s = s2; tri.Pt[1].t = t2;
			vnormal = glm::normalize(glm::vec3(x12,y12,z2));
			tri.Pt[1].nX = vnormal.x; tri.Pt[1].nY = vnormal.y; tri.Pt[1].nZ = vnormal.z;

			tri.Pt[2] = cgPoint3D(x11,y11,z2);
			tri.Pt[2].s = s1; tri.Pt[2].t = t2;
			vnormal = glm::normalize(glm::vec3(x11,y11,z2));
			tri.Pt[2].nX = vnormal.x; tri.Pt[2].nY = vnormal.y; tri.Pt[2].nZ = vnormal.z;//顶点法向向量

			vTris.push_back(tri);

			alpha += dalpha;
		}
	}
}

void cgSphere::SetTexture(GLuint texture)
{
	textureID = texture;
}

void cgSphere::Render()
{
	vector<cgTriangle>::iterator it = vTris.begin();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTranslatef(ptPos.x,ptPos.y,ptPos.z);
	glRotatef(-90,0,1,0);
	glRotatef(90,1,0,0);
	for(; it != vTris.end(); it++)
	{
	   (*it).Render();
	}
	glBindTexture(GL_TEXTURE_2D, 0);//纹理无效

	glPopMatrix();
}


