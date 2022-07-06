#include "cgCylinder.h"
#include <math.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgCylinder::cgCylinder(void)
{
}


cgCylinder::~cgCylinder(void)
{
}

void cgCylinder::SetPos(cgPoint3D pos)
{
	ptPos = pos;
}

void cgCylinder::SetTexture(GLuint texture)
{
	textureID = texture;
}

void cgCylinder::InitData(float r,float h)
{
	
}

void cgCylinder::Render()
{
	vector<cgTriangle>::iterator it = vTris.begin();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();




	glPopMatrix();
}