// OpenGLOld.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <Windows.h>
#include <GL/glew.h>//OpenGL��
#include <GL/glut.h>//OpenGL������

#include <math.h>
#include "SOIL/SOIL.h"

#include "cgSphere.h"
#include "cgCylinder.h"
#include "cgCube.h"
#include "cgQuad.h"

#include "Bitmap.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) //����ǲ��ÿ���̨������֣������Ҫ���֣�ȥ�����ɡ�

float alpha=0.0f;
float pos[]={3,2.0,5};
float headdir[]={0.0f,0.0f,-1.0f};
float rightdir[]={0.1f,0.0f,0.0f};

float step = 0.10f;
float beta = 180.0f;//��z������н�
float betastep = 0.5f;

cgSphere sphere;
cgCylinder cylinder;
cgCube cube;

//���ձ���
GLfloat light_position[] = { 0.0, 2.0, 1.0, 0.1 };
GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat aMaterial[] = { .20, 0.20, 0.20, 1.0 };//�����ⷴ��ϵ��
GLfloat dMaterial[] = { .60, 0.60, 0.60, 1.0 };//������ⷴ��ϵ��
GLfloat sMaterial[] = { 0.4, 0.4,0.4, 1 };//���淴��ⷴ��ϵ��
GLfloat shiniess = 20;//�߹�ָ��

int rendermode = 0;//0:��䣻 1:�߿�2������

GLuint textureID;
int  frames=0;

GLuint LoadTexture(char* fname)
{
	GLuint tID;
	
	int width, height, nrComponents;
	unsigned char *data;
	
	data = SOIL_load_image(fname, &width, &height, &nrComponents,SOIL_LOAD_RGB);// 
	
	if (data)
	{
		GLenum internalFormat;
		GLenum dataFormat;
		bool gammaCorrection = false;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		//��������
		glGenTextures(1, &tID);
		glBindTexture(GL_TEXTURE_2D, tID);
	
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//���������Ȼ������
		gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
			
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	
		glBindTexture(GL_TEXTURE_2D, 0);

		SOIL_free_image_data(data);

		return tID;
	}

	return -1;	
}

void init(void)
{
	glClearColor(0.5, 1.0, 1.0, 1.0);//���ñ���ɫ��ɫ
	glEnable(GL_DEPTH_TEST);

	//����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , aMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , dMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, sMaterial);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &shiniess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	///////////////////////////

	//������
	sphere.InitData(1.0f);
	sphere.SetPos(cgPoint3D(0.0f,1.0f,0.0f));
	sphere.SetTexture(LoadTexture("Textures/earth2.jpg"));
	
	
	//��������
	textureID = LoadTexture("Textures/timg.jpg");	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );//���֡�������Ȼ���
	
	//ģ�͹۲�����ʼ��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float at[3];
	for (int i=0; i<3; i++)
		at[i] = pos[i] + headdir[i];

	gluLookAt (pos[0], pos[1], pos[2], at[0], at[1], at[2], 0.0, 1.0, 0.0);

	if (rendermode==1)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	//����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);//ָ��������������
		glNormal3f(0,1,0);//ָ�����㷨����
		glVertex3f(-50.0f,0.0f,50.0f);//ָ����������

		glTexCoord2f(10.0f,0.0f);
		glNormal3f(0,1,0);
		glVertex3f(50.0f,0.0f,50.0f);

		glTexCoord2f(10.0f,10.0f);
		glNormal3f(0,1,0);
		glVertex3f(50.0f,0.0f,-50.0f);
		
		glTexCoord2f(0.0f,10.0f);
		glNormal3f(0,1,0);
		glVertex3f(-50.0f,0.0f,-50.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.25,0.5,0.5);
	sphere.Render();

	glColor3f(0.0,0.0,1.0);
	cylinder.Render();

	glColor3f(1.0,0.0,0.0);
	cube.Render();
	
	glutSwapBuffers();//�������壨˫����ʱʹ�ã�
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);//���������������ڻ�ͼ����

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60,(GLfloat) width/(GLfloat)height, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void change()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'W':   //����
		case 'w':
			for (int i=0; i<3; i++)
				pos[i] += step*headdir[i];
			break;
		case 'S':   //����
		case 's':
			for (int i=0; i<3; i++)
				pos[i] -= step*headdir[i];
			break;
		case 'A':  //����
		case 'a':
			for (int i=0; i<3; i++)
				pos[i] -= step*rightdir[i];	
			break;
		case 'D':   //����
		case 'd':
			for (int i=0; i<3; i++)
				pos[i] += step*rightdir[i];
			break;

		case 'Z':   
		case 'z':
			//̧�����
	         pos[1] += .30f;
			break;

		case 'X':   
		case 'x':
			//�������
	         pos[1] -= .30f;
			break;

		case 'T':   //�޸Ļ���ģʽ
		case 't':
			rendermode = (++rendermode)%2;
			break;	
		case '1':
			light_position[0] += 0.1f;
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			break;
		case '2':
			light_position[0] -= 0.1f;
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			break;
	}

	glutPostRedisplay();
}

void SpecialKey(GLint key,GLint x,GLint y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			for (int i=0; i<3; i++)
				pos[i] += step*headdir[i];
			break;

		case GLUT_KEY_DOWN:
			for (int i=0; i<3; i++)
				pos[i] -= step*headdir[i];
			break;

		case GLUT_KEY_LEFT:
			//�޸�ǰ������


			//�޸�������

			break;

		case GLUT_KEY_RIGHT:
			//�޸�ǰ������


			//�޸�������

			break;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInitWindowPosition(200, 200);//Ӧ�ó��򴰿�λ��
	glutInitWindowSize(800, 600);//���ڴ�С
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH );//˫���壬������ΪGLUT_SINGLE����Ȼ���
	glutCreateWindow("Project Four");//�������ڣ�����Ϊ���ڱ���
	init();

	glutDisplayFunc(display);//ͼ�λ���
	glutReshapeFunc(reshape);//���ڴ�С�仯
	glutKeyboardFunc(keyboard);//���̽���
	glutSpecialFunc(&SpecialKey);//�����
	glutIdleFunc(change);//����ʱ��ִ��

	glutMainLoop();//���룬����GLUT�¼�����ѭ��

	return 0;
}
