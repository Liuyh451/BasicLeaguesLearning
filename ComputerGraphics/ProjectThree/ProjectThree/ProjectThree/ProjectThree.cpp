#include <GL/glut.h>
#include <math.h>
#include <cstdio>

const GLfloat Pi = 3.1415926536f;  //����Piֵ
GLfloat X[5], Y[5], x[5], y[5];  //����������5������
float R = 0.8;  //����뾶
float r = 0.4;// ��Ȧ�뾶

void init() //��ʼ������
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  //���ñ�����ɫ
}
void myDisplay(void)  //��ʾ����

{

    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i <= 4; i++)
    {
        //��Բ�ϳ�ʼ��10�������
        X[i] = R * cos(2 * Pi * i / 5);
        Y[i] = R * sin(2 * Pi * i / 5);
        x[i] = r * cos(2 * Pi * (i + 0.5) / 5);
        y[i] = r * sin(2 * Pi * (i + 0.5) / 5);
    }
    glViewport(100, 200, 200, 200);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);  //����������ɫ
    for (int i = 0; i <= 4; i++) {
        glVertex2f(X[i], Y[i]);
        glVertex2f(x[i], y[i]);
    }
    glEnd();

    glViewport(300, 200, 200, 200);
    glBegin(GL_TRIANGLES);  //����˳��ʼ����.
    glColor3f(1.0, 0.0, 0.0);  //����������ɫ
    for (int j = 0; j <= 4; j++) {
        glVertex2f(X[j], Y[j]);
        glVertex2f(0, 0);
        glVertex2f(x[j], y[j]);
    }
    for (int i = 0; i <= 4; i++) {
        glVertex2f(x[i], y[i]);
        glVertex2f(0, 0);
        if (i == 4) {
            glVertex2f(X[0], Y[0]);
        }
        else {
            glVertex2f(X[i + 1], Y[i + 1]);
        }
    }
    glEnd();

    glViewport(500, 200, 200, 200);
    glBegin(GL_TRIANGLES);  //����˳��ʼ����.
    glColor3f(1.0, 0.0, 0.0);  //����������ɫ
    for (int j = 0; j <= 4; j++) {
        glVertex2f(X[j], Y[j]);
        glVertex2f(0, 0);
        glVertex2f(x[j], y[j]);
    }
    glColor3f(1.0, 0.5, 0.5);  //����������ɫ
    for (int i = 0; i <= 4; i++) {
        glVertex2f(x[i], y[i]);
        glVertex2f(0, 0);
        if (i == 4) {
            glVertex2f(X[0], Y[0]);
        }
        else {
            glVertex2f(X[i + 1], Y[i + 1]);
        }
    }
    glEnd();

    glutSwapBuffers();//�������壨˫����ʱʹ�ã�
}

float alpha = 0.0f;
float move_x = 382.0f;
float move_y = 257.0f;
static int flag_x = 1;
static int flag_y = 1;
static int flag_R = 1;
static int flag_r = 1;
static int flag_a = 1;
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);//���֡����
    for (int i = 0; i <= 4; i++)
    {
        //��Բ�ϳ�ʼ��10�������
        X[i] = R * cos(2 * Pi * i / 5);
        Y[i] = R * sin(2 * Pi * i / 5);
        x[i] = r * cos(2 * Pi * (i + 0.5) / 5);
        y[i] = r * sin(2 * Pi * (i + 0.5) / 5);
    }
    //ģ�͹۲�����ʼ��
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(move_x, move_y, 0.0f);
    glRotatef(alpha, 0, 0, 1);
    glBegin(GL_TRIANGLES);  //����˳��ʼ����.
    glColor3f(1.0, 0.0, 0.0);  //����������ɫ
    for (int j = 0; j <= 4; j++) {
        glVertex2f(X[j] * 100, Y[j] * 100);
        glVertex2f(0, 0);
        glVertex2f(x[j] * 100, y[j] * 100);
    }
    glColor3f(1.0, 0.5, 0.5);  //����������ɫ
    for (int i = 0; i <= 4; i++) {
        glVertex2f(x[i] * 100, y[i] * 100);
        glVertex2f(0, 0);
        if (i == 4) {
            glVertex2f(X[0] * 100, Y[0] * 100);
        }
        else {
            glVertex2f(X[i + 1] * 100, Y[i + 1] * 100);
        }
    }
    glEnd();
    glPopMatrix();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(100.0f, 100.0f);
    glVertex2f(100.0f, 500.0f);
    glVertex2f(700.0f, 500.0f);
    glVertex2f(700.0f, 100.0f);
    glEnd();
    glutSwapBuffers();//�������壨˫����ʱʹ�ã�
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);//���������������ڻ�ͼ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);//����ͼ�����ݷ�Χ
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int judge_x(float move_x, int flag_x, float R) {
    if (move_x <= 100 + R * 100) {
        flag_x = 1;
    }
    else if (move_x >= 700 - R * 100) {
        flag_x = 2;
    }
    return flag_x;
}
int judge_y(float move_y, int flag_y, float R) {
    if (move_y <= 100 + R * 100) {
        flag_y = 1;
    }
    else if (move_y >= 500 - R * 100) {
        flag_y = 2;
    }
    return flag_y;
}
int judge_R(float R, int flag_R) {
    if (R >= 0.8) {
        flag_R = 1;
    }
    else if (R <= 0.2) {
        flag_R = 2;
    }
    return flag_R;
}
int judge_r(float r, int flag_r) {
    if (r >= 0.4) {
        flag_r = 1;
    }
    else if (r <= 0.1) {
        flag_r = 2;
    }
    return flag_r;
}
void change()
{
    if (flag_a == 1) {
        alpha += 2.0f;
        if (alpha > 360) alpha -= 360;
    }
    if (flag_a == 2) {
        alpha -= 2.0f;
        if (alpha < -360) alpha += 360;
    }
    flag_x = judge_x(move_x, flag_x, R);
    flag_y = judge_y(move_y, flag_y, R);
    if (flag_x == 1) {
        move_x += 1.0f;
    }
    else if (flag_x == 2) {
        move_x -= 1.0f;
    }
    if (flag_y == 1) {
        move_y += 1.0f;
    }
    else if (flag_y == 2) {
        move_y -= 1.0f;
    }
    flag_R = judge_R(R, flag_R);
    flag_r = judge_r(r, flag_r);
    if (flag_R == 1) {
        R -= 0.002;
    }
    else if (flag_R == 2) {
        R += 0.002;
    }
    if (flag_r == 1) {
        r -= 0.001;
    }
    else if (flag_r == 2) {
        r += 0.001;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case'W':   //����
    case 'w':
        move_y += 10.0f;

        break;
    case'S':   //����
    case's':
        move_y -= 10.0f;
        break;
    case'A':  //����
    case'a':
        move_x -= 10.0f;
        break;
    case'D':   //����
    case'd':
        move_x += 10.0f;
        break;
    case'R':
    case'r':
        R += 0.02;
        r += 0.01;
        break;
    case'T':
    case't':
        R -= 0.02;
        r -= 0.01;
        break;
    case'Q':
    case'q':
        flag_a = 1;
        break;
    case'E':
    case'e':
        flag_a = 2;
        break;
    case'H':
    case'h':
        flag_a = 0;
        break;
    case' ':
        static int flag = 0;
        if (flag == 0) {
            flag = 1;
            glutIdleFunc(NULL);
        }
        else if (flag == 1) {
            flag = 0;
            glutIdleFunc(change);
        }
    }
    glutPostRedisplay();
}


void OnMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glutIdleFunc(change);
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glutIdleFunc(NULL);
    }
}

int main(int argc, char* argv[])
{
    glutInitWindowPosition(200, 200);//Ӧ�ó��򴰿�λ��
    glutInitWindowSize(800, 600);//���ڴ�С
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//˫���壬������ΪGLUT_SINGLE
    glutCreateWindow("�����ͼ��");  //���ô��ڱ���
    init();                          //���г�ʼ������
    glutKeyboardFunc(&keyboard);//���̽���
    glutMouseFunc(&OnMouse);  //ע������¼�
    glutDisplayFunc(Display);     //������ʾ����
    glutReshapeFunc(reshape);//���ڴ�С�仯
    glutIdleFunc(change);//���̽���

    glutMainLoop();
    return 0;
}