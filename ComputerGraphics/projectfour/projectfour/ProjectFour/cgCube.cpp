#include "cgCube.h"

cgCube::cgCube(void)
{
    ptPos = cgPoint3D();
}

cgCube::~cgCube(void)
{
}
void cgCube::SetPos(cgPoint3D pos)
{
    this->ptPos = pos;
}

void cgCube::push_plane(float left, float right, float up, float down, float height)
{
    cgTriangle left_down;
    cgTriangle right_up;

    left_down.Pt[0] = cgPoint3D(left, down, height);
    left_down.Pt[1] = cgPoint3D(left, up, height);
    left_down.Pt[2] = cgPoint3D(right, down, height);
    right_up.Pt[0] = cgPoint3D(left, up, height);
    right_up.Pt[1] = cgPoint3D(right, up, height);
    right_up.Pt[2] = cgPoint3D(right, down, height);
    this->vTris.push_back(left_down);
    this->vTris.push_back(right_up);
    
}
void cgCube::push_plane_lr(float x, float y_down, float y_up, float z_down, float z_up)
{
    cgTriangle left_down;
    cgTriangle right_up;
    left_down.Pt[0] = cgPoint3D(x, y_up, z_up);
    left_down.Pt[1] = cgPoint3D(x, y_up, z_down);
    left_down.Pt[2] = cgPoint3D(x, y_down, z_down);
    right_up.Pt[0] = cgPoint3D(x, y_up, z_up);
    right_up.Pt[1] = cgPoint3D(x, y_down, z_up);
    right_up.Pt[2] = cgPoint3D(x, y_down, z_down);
    this->vTris.push_back(left_down);
    this->vTris.push_back(right_up);
}
void cgCube::push_plane_nf(float y, float x_left, float x_right, float z_down, float z_up)
{
    cgTriangle left_down;
    cgTriangle right_up;
    left_down.Pt[0] = cgPoint3D(x_left, y, z_up);
    left_down.Pt[1] = cgPoint3D(x_left, y, z_down);
    left_down.Pt[2] = cgPoint3D(x_right, y, z_down);
    right_up.Pt[0] = cgPoint3D(x_right, y, z_up);
    right_up.Pt[1] = cgPoint3D(x_right, y, z_down);
    right_up.Pt[2] = cgPoint3D(x_left, y, z_up);
    this->vTris.push_back(left_down);
    this->vTris.push_back(right_up);
}
void cgCube::InitData(float width)
{
    this->width = width;
    vTris.clear();
    float x_left = -this->width / 2;
    float x_right = this->width / 2;
    float y_down = -this->width / 2;
    float y_up = this->width / 2;
    float z_up = this->width / 2;
    float z_down = -this->width / 2;
    for(int i = 0 ; i < 6;i++)
    {
        this->texture_points.push_back(cgPoint3D(0.0,0.0,0.0));
        this->texture_points.push_back(cgPoint3D(0.0,1.0,0.0));
        this->texture_points.push_back(cgPoint3D(1.0,0.0,0.0));
        this->texture_points.push_back(cgPoint3D(0.0,1.0,0.0));
        this->texture_points.push_back(cgPoint3D(1.0,1.0,0.0));
        this->texture_points.push_back(cgPoint3D(1.0,0.0,0.0));
    }
    this->push_plane(x_left, x_right, y_up, y_down, z_up);   //top plane
    this->push_plane(x_left, x_right, y_up, y_down, z_down); //bottom plane
    this->push_plane_lr(x_left, y_down, y_up, z_down, z_up);
    this->push_plane_lr(x_right, y_down, y_up, z_down, z_up);
    this->push_plane_nf(y_up, x_left, x_right, z_down, z_up);
    this->push_plane_nf(y_down, x_left, x_right, z_down, z_up);
}
void cgCube::Render(GLuint texture)
{
    vector<cgTriangle>::iterator it = vTris.begin();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(ptPos.x, ptPos.y, ptPos.z);
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
