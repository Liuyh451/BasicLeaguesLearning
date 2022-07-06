#pragma once
#include "cgPoint3D.h"
#include <GL\glew.h>

class cgQuad
{
public:
	cgQuad(void);
	~cgQuad(void);

	void Render();
	void SetTexture(GLuint texture);
	
	void SetVertexData(cgPoint3D *v);	
	void SetPos(cgPoint3D pos);

	void UpdateTextCoord(float* texcor);
private:
	cgPoint3D ptPos; 
	GLuint textureID;
	cgPoint3D Pts[4];
};

