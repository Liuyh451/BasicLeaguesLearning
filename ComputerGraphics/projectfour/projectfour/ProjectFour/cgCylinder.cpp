#include "cgCylinder.h"
#include <math.h>
#include <GL/glew.h>//OpenGL??

using namespace std;

cgLinder::cgLinder(void)
{
    ptPos = cgPoint3D();
}
cgLinder::~cgLinder(void)
{
}
void cgLinder::SetPos(cgPoint3D pos)
{
    ptPos = pos;    
}

void cgLinder::InitData(float r,float height)
{
    fR = r;

	vTris.clear();
	//生成球心在坐标原点的球面三角??
    int m = 200;//水平方向圆离散化多边形边??
	int n = 200;//垂直方向切片个数

	float dalpha = 2*PI/m;
	float dh  = height/n;

	float h = - height / 2;
	for (int i=0; i<n;i++)
	{
		float alpha = 0.0f;

		float z1 = h;
		float z2 = h + dh;

		float r0 = fR;
		float t = i * 1.0/n;
		float t_u = t + 1.0/n;

		h += dh;
		for (int j=0; j<m; j++)
		{
			float s = j * 1.0/m;
			float s_u = s + 1.0/m;
			float x01 = r0*cos(alpha);
			float y01 = r0*sin(alpha);

			float x02 = r0*cos(alpha+dalpha);
			float y02 = r0*sin(alpha+dalpha);

			float x11 = r0*cos(alpha);
			float y11 = r0*sin(alpha);

			float x12 = r0*cos(alpha+dalpha);
			float y12 = r0*sin(alpha+dalpha);

			//构建三角??
			cgTriangle tri;
			this->texture_points.push_back(cgPoint3D(s,t,0.0));
			tri.Pt[0] = cgPoint3D(x01,y01,z1); //left down
			this->texture_points.push_back(cgPoint3D(s_u,t,0.0));
			tri.Pt[1] = cgPoint3D(x02,y02,z1); //right down
			this->texture_points.push_back(cgPoint3D(s,t_u,0.0));
			tri.Pt[2] = cgPoint3D(x11,y11,z2); //left up
			vTris.push_back(tri);
			this->texture_points.push_back(cgPoint3D(s_u,t,0.0));
			tri.Pt[0] = cgPoint3D(x02,y02,z1); //right down
			this->texture_points.push_back(cgPoint3D(s_u,t_u,0.0));
			tri.Pt[1] = cgPoint3D(x12,y12,z2); //right up
			this->texture_points.push_back(cgPoint3D(s,t_u,0.0));
			tri.Pt[2] = cgPoint3D(x11,y11,z2); //left up
			vTris.push_back(tri);
			//一次拼接一个平行四边形
			alpha += dalpha;
			if(i == 0 || i == n - 1)
			{
				cgTriangle tri;
				this->texture_points.push_back(cgPoint3D(1.0 * cos(alpha + dalpha),sin(alpha + dalpha),0.0));
				tri.Pt[0] = cgPoint3D(x01,y01,z1);
				this->texture_points.push_back(cgPoint3D(1.0 * cos(alpha + dalpha),1.0 * sin(alpha + dalpha),0.0));
				tri.Pt[1] = cgPoint3D(x02,y02,z1);
				this->texture_points.push_back(cgPoint3D(0.5,0.5,0.0));
				tri.Pt[2] = cgPoint3D(0,0,z2);
				vTris.push_back(tri);
			}
		}
	}
	//draw cirle

}
void cgLinder::Render(GLuint texture)
{
	vector<cgTriangle>::iterator it = vTris.begin();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(ptPos.x,ptPos.y,ptPos.z);
	int counter = 0;

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
    for (; it != vTris.end(); it++)
    {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; i++)
        {
            glTexCoord2f(this->texture_points[counter].x,this->texture_points[counter].y);
            glVertex3f((*it).Pt[i].x, (*it).Pt[i].y, (*it).Pt[i].z);
            counter++;
        }
            
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}