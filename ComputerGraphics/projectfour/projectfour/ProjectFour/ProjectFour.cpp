// OpenGLOld.cpp : 定义控制台应用程序的入口点。
//
#include <Windows.h>
#include <GL/glew.h>//OpenGL库
#include <GL/glut.h>//OpenGL辅助库

#include <math.h>
#include "SOIL/SOIL.h"

#include "cgSphere.h"
#include "cgCylinder.h"
#include "cgCube.h"
#include "cgQuad.h"

#include "Bitmap.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) //这句是不让控制台窗体出现，如果想要出现，去掉即可。

float alpha=0.0f;
float pos[]={3,2.0,5};
float headdir[]={0.0f,0.0f,-1.0f};
float rightdir[]={0.1f,0.0f,0.0f};

float step = 0.10f;
float beta = 180.0f;//与z轴正向夹角
float betastep = 0.5f;

cgSphere sphere;
cgLinder linder;
cgCube cube;

//光照变量
GLfloat light_position[] = { 0.0, 2.0, 1.0, 0.1 };
GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat aMaterial[] = { .20, 0.20, 0.20, 1.0 };//环境光反射系数
GLfloat dMaterial[] = { .60, 0.60, 0.60, 1.0 };//漫反射光反射系数
GLfloat sMaterial[] = { 0.8, 0.8,0.8, 1 };//镜面反射光反射系数
GLfloat shiniess = 20;//高光指数
float headdir_buffer[] = {0.0,0.0,0.0};
int rendermode = 0;//0:填充； 1:线框；2：纹理
float turn_step = 0.025f;
GLuint textureID;
GLuint texture2;
GLuint texture3;
GLuint texture4;
int  frames=0;
void turnHri(int right)
{
	double len = sqrt(headdir[0] * headdir[0] + headdir[2] * headdir[2]);
	headdir_buffer[0] = headdir[0];
	headdir_buffer[1] = headdir[1];
	headdir_buffer[2] = headdir[2];
	float dif_vector[] = {-headdir_buffer[2],0,headdir_buffer[0]};
	for(int i = 0 ; i < 3;i++)
		headdir[i] += (right == 1?dif_vector[i] * turn_step:-dif_vector[i]*turn_step);
	
}
void turnVer(int up)
{
	headdir[1] += (up == 1?turn_step:-turn_step);
}
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

		//生成纹理
		glGenTextures(1, &tID);
		glBindTexture(GL_TEXTURE_2D, tID);
	
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//这个函数居然不能用
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
	glClearColor(0.5, 1.0, 1.0, 1.0);//设置背景色
	glEnable(GL_DEPTH_TEST);

	//光照
	
	///////////////////////////

	//球
	sphere.InitData(1.0f);
	sphere.SetPos(cgPoint3D(1.0f,1.0f,0.0f));
	sphere.SetTexture(LoadTexture("Textures/3.jpg"));
	//正方体
	cube.InitData(1.0f);
	cube.SetPos(cgPoint3D(-1.0f,1.0f,3.0f));
	//圆柱
	linder.InitData(1.0f,2.0f);
	linder.SetPos(cgPoint3D(5.0f,1.0f,1.0f));
	
	
	textureID = LoadTexture("Textures/1.bmp");//圆柱	
	texture2 = LoadTexture("Textures/5.png");//地面
	texture3 = LoadTexture("Textures/4.jpg");//正方体
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );//清除帧缓存和深度缓存
	
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
	//模型观察矩阵初始化
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

	//地面
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);//指定顶点纹理坐标
		glNormal3f(0,1,0);//指定顶点法向量
		glVertex3f(-50.0f,0.0f,50.0f);//指定顶点坐标

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

	sphere.Render();

	cube.Render(texture3);
	linder.Render(textureID);
	
	glutSwapBuffers();//交换缓冲（双缓冲时使用）
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);//设置视区（窗口内绘图区域）

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
		case 'W':   //上移
		case 'w':
			for (int i=0; i<3; i++)
				pos[i] += step*headdir[i];
			break;
		case 'S':   //下移
		case 's':
			for (int i=0; i<3; i++)
				pos[i] -= step*headdir[i];
			break;
		case 'A':  //左移
		case 'a':
			for (int i=0; i<3; i++)
				pos[i] -= step*rightdir[i]*5;	
			break;
		case 'D':   //右移
		case 'd':
			for (int i=0; i<3; i++)
				pos[i] += step*rightdir[i]*5;
			break;

		case 'Z':   
		case 'z':
			//̧光源
	         //pos[1] += .30f;
			 light_position[1] += 1.0;
			break;

		case 'X':   
		case 'x':
			//光源
	         //pos[1] -= .30f;
			 light_position[1] -= 1.0;
			break;

		case 'N':   //蓝
		case 'n':
			light_color[0] = 0.0;
			light_color[1] = 0.0;
			light_color[2] = 1.0;
			break;	
		case 'M':   //黄
		case 'm':
			light_color[0] = 1.0;
			light_color[1] = 1.0;
			light_color[2] = 0.0;
			break;
		case 'i'://原来颜色
			light_color[0] = 1.0;
			light_color[1] = 1.0;
			light_color[2] = 1.0;
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
			for (int i=0; i<4; i++)
				pos[i] -= step*rightdir[i];	
			break;


		case GLUT_KEY_RIGHT:
			for (int i=0; i<4; i++)
				pos[i] += step*rightdir[i];	
			break;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInitWindowPosition(200, 200);//应用程序窗口位置
	glutInitWindowSize(800, 600);//窗口大小
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH );//双缓冲，单缓冲为GLUT_SINGLE，深度缓存
	glutCreateWindow("Project Four");//创建窗口，参数为窗口标题
	init();

	glutDisplayFunc(display);//图形绘制
	glutReshapeFunc(reshape);//窗口大小变化
	glutKeyboardFunc(keyboard);//键盘交互
	glutSpecialFunc(&SpecialKey);//方向键
	glutIdleFunc(change);//空闲时间执行

	glutMainLoop();//必须，进入GLUT事件处理循环

	return 0;
}
