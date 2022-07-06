#include "cgCube.h"
#include <math.h>
#include <GL/glew.h>//OpenGL¿â

cgCube::cgCube(void)
{
	iFrames = 0;
}


cgCube::~cgCube(void)
{
}

void cgCube::SetPos(cgPoint3D pos)
{
	ptPos = pos;
}

void cgCube::SetTexture(GLuint texture)
{
	textureID = texture;
}

void cgCube::InitData(float length)
{
	fLength = length;

}

void cgCube::UpdateTexCord()
{

}

void cgCube::Render()
{
	vector<cgTriangle>::iterator it = vTris.begin();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();



	glPopMatrix();
}
