#include "cgQuad.h"
#include <GL/glew.h>//OpenGL¿â

cgQuad::cgQuad(void)
{
}

cgQuad::~cgQuad(void)
{
}

void cgQuad::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTranslatef(ptPos.x,ptPos.y,ptPos.z);
	glBegin(GL_QUADS);
		for (int i=0; i<4; i++)
		{
			glTexCoord2f(Pts[i].s,Pts[i].t);
			glVertex3f(Pts[i].x,Pts[i].y,Pts[i].z);
		}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);//ÎÆÀíÎÞÐ§

	glPopMatrix();
}

void cgQuad::SetTexture(GLuint texture)
{
	textureID = texture;
}

void cgQuad::UpdateTextCoord(float* texcor)
{
	for (int i=0; i<4; i++)
	{
		Pts[i].s = texcor[2*i+0];
		Pts[i].t = texcor[2*i+1];
	}
}

void cgQuad::SetVertexData(cgPoint3D *v)
{
	for (int i=0; i<4; i++)
	{
		Pts[i].x = v[i].x;Pts[i].y = v[i].y;Pts[i].z = v[i].z;
		Pts[i].s = v[i].s; Pts[i].t = v[i].t; 
	}
}

void cgQuad::SetPos(cgPoint3D pos)
{
	ptPos = pos;
}