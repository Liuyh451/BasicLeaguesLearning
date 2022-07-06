#include<Windows.h>
#include<GL\glut.h>
//̫�������������
//����ÿ���¶���30��
//һ��12���£�����360��
static int day = 200; // day�ı仯:��0��359
void myDisplay(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -200, 200, 0, 0, 0, 0, 0, 1);
	//���ƺ�ɫ�ġ�̫����
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(69.6, 100, 100);

	//������ɫ�ġ�����
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(150, 0.0f, 0.0f);
	glutSolidSphere(15.945, 100, 100);

	//���ƻ�ɫ�ġ�������
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0 * 360.0 - day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
	glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38, 0.0f, 0.0f);
	glutSolidSphere(4.345, 100, 100);
	glFlush();
	glutSwapBuffers();
}
void myIdle(void)
{
	Sleep(50);
	++day;
	if (day >= 360)
		day = 0;
	myDisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("I love OpenGL");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}