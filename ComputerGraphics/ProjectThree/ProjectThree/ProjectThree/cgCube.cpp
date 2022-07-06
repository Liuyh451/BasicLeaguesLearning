#include "cgCube.h"
#include <math.h>
#include <GL/glew.h>//OpenGL¿â

cgCube::cgCube(void)
{
	ptPos = cgPoint3D();
}


cgCube::~cgCube(void)
{
}

void cgCube::SetPos(cgPoint3D pos)
{
	ptPos = pos;
}

void cgCube::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(ptPos.x,ptPos.y,ptPos.z);

	glPopMatrix();
}


