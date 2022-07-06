#include <GL/glew.h>//OpenGL库
#include <GL/glut.h>//OpenGL辅助库
#include <math.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//设置背景色白色
}
float alpha = 180;
float a=0.0f, b=0.0f;
float x, y;
void DrawPentagramOutline(int XCenterP, int YCenterP, float LongRadius, float ShortRadius)//(中心点横坐标，中心点纵坐标，五角星长边长度，五角星短边长度)
{
	//glClear(GL_COLOR_BUFFER_BIT);//清除帧缓存
	glBegin(GL_LINE_LOOP);//图形类型
	float R = LongRadius, r = ShortRadius;
	float x = XCenterP, y = YCenterP, s = 3.1415926 / 5;
	float xlength[10], ylength[10];
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			xlength[i] = R * sin(s * (double)i), ylength[i] = R * cos((double)i * s);
		else
			xlength[i] = r * sin(s * (double)i), ylength[i] = r * cos((double)i * s);
	}
	for (int i = 0; i < 10; i++)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x + xlength[i % 10], y + ylength[i % 10]);
	}
	glEnd();
	//glFlush();//单缓冲时必须要，说明绘图命令（函数）结束
	//glutSwapBuffers();//交换缓冲（双缓冲时使用）
}

void DrawPentagramMonochromatic(int XCenterP, int YCenterP, float LongRadius, float ShortRadius)
{
	//glClear(GL_COLOR_BUFFER_BIT);//清除帧缓存
	glBegin(GL_TRIANGLES);//图形类型
	float R = LongRadius, r = ShortRadius;
	float x = XCenterP, y = YCenterP, s = 3.1415926 / 5;
	float xlength[10], ylength[10];
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			xlength[i] = R * sin(s * (double)i), ylength[i] = R * cos((double)i * s);
		else
			xlength[i] = r * sin(s * (double)i), ylength[i] = r * cos((double)i * s);
	}
	for (int i = 0; i < 10; i++)
	{
		glColor3f(1, 0, 0);
		glVertex2f(x, y);
		glVertex2f(x + xlength[i % 10], y + ylength[i % 10]);
		glVertex2f(x + xlength[(i + 1) % 10], y + ylength[(i + 1) % 10]);
	}
	glEnd();
	//glFlush();//单缓冲时必须要，说明绘图命令（函数）结束
	//glutSwapBuffers();//交换缓冲（双缓冲时使用）
}

void func() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(100.0, 100.0);
	glVertex2f(100.0, 500.0);
	glVertex2f(500.0, 500.0);
	glVertex2f(500.0, 100.0);
	glEnd();
}
void DrawPentagram(int XCenterP, int YCenterP, float LongRadius, float ShortRadius)
{
	
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(a, b, 0.0f);
	glPushMatrix();
	
	glTranslatef(200.0f, 200.0f, 0.0f);
	glRotatef(alpha, 0, 0, 1);
	
	glScaled(0.5, 0.5, 0);
	x = LongRadius/2;
	glTranslatef(-200.0f, -200.0f, 0.0f);

	
	glBegin(GL_TRIANGLES);//图形类型
	float R = LongRadius, r = ShortRadius;
	float x = XCenterP, y = YCenterP, s = 3.1415926 / 5;
	float xlength[10], ylength[10];
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			xlength[i] = R * sin(s * (double)i), ylength[i] = R * cos((double)i * s);
		else
			xlength[i] = r * sin(s * (double)i), ylength[i] = r * cos((double)i * s);
	}
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			glColor3f(1, 0, 0);
			glVertex2f(x, y);
			glColor3f(1, 1, 1);
			glVertex2f(x + xlength[i % 10], y + ylength[i % 10]);
			glColor3f(0, 0, 0);
			glVertex2f(x + xlength[(i + 1) % 10], y + ylength[(i + 1) % 10]);
		}
		else
		{
			glColor3f(0, 0, 1);
			glVertex2f(x, y);
			glColor3f(1, 1, 1);
			glVertex2f(x + xlength[i % 10], y + ylength[i % 10]);
			glColor3f(0, 0, 0);
			glVertex2f(x + xlength[(i + 1) % 10], y + ylength[(i + 1) % 10]);
		}

	}
	glEnd();
	glPopMatrix();
	//glFlush();//单缓冲时必须要，说明绘图命令（函数）结束
	
	glutSwapBuffers();//交换缓冲（双缓冲时使用）
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//DrawPentagramOutline(200, 300, 100.0f, 40.0f);
	//DrawPentagramMonochromatic(400, 300, 100.0f, 40.0f);
	func();
	DrawPentagram(200, 200, 100.0f, 40.0f);
}
int countx = 0,county=0;
float c = 1.0,d=1.0;

void change()
{
	
	alpha += 1.f;

	if (alpha > 360) alpha -= 360;
	a = a;
	b = b + c;
	if (b+200+x > 500||b+200<100+x) {
		c = -c;
	}
	/*county++;
	if (county > 250) {
		county = 0;
		c = -c;

	}
	countx++;
	if (countx > 300)
	{	
		countx = 0;
		d = -d;
		
	}*/


	glutPostRedisplay();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);//设置视区（窗口内绘图区域）
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);//设置图形数据范围
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
}


int main(int argc, char* argv[])
{	glutInit(&argc, argv);
	glutInitWindowPosition(200, 200);//应用程序窗口位置
	glutInitWindowSize(800, 600);//窗口大小
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("OpenGL Old");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(change);

	glutMainLoop();

	return 0;
}
