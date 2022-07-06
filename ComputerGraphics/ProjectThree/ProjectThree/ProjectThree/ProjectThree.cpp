#include <GL/glut.h>
#include <math.h>
#include <cstdio>

const GLfloat Pi = 3.1415926536f;  //定义Pi值
GLfloat X[5], Y[5], x[5], y[5];  //用数组声明5组坐标
float R = 0.8;  //定义半径
float r = 0.4;// 内圈半径

void init() //初始化函数
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  //设置背景颜色
}
void myDisplay(void)  //显示函数

{

    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i <= 4; i++)
    {
        //在圆上初始化10个坐标点
        X[i] = R * cos(2 * Pi * i / 5);
        Y[i] = R * sin(2 * Pi * i / 5);
        x[i] = r * cos(2 * Pi * (i + 0.5) / 5);
        y[i] = r * sin(2 * Pi * (i + 0.5) / 5);
    }
    glViewport(100, 200, 200, 200);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);  //设置线条颜色
    for (int i = 0; i <= 4; i++) {
        glVertex2f(X[i], Y[i]);
        glVertex2f(x[i], y[i]);
    }
    glEnd();

    glViewport(300, 200, 200, 200);
    glBegin(GL_TRIANGLES);  //按照顺序开始画线.
    glColor3f(1.0, 0.0, 0.0);  //设置线条颜色
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
    glBegin(GL_TRIANGLES);  //按照顺序开始画线.
    glColor3f(1.0, 0.0, 0.0);  //设置线条颜色
    for (int j = 0; j <= 4; j++) {
        glVertex2f(X[j], Y[j]);
        glVertex2f(0, 0);
        glVertex2f(x[j], y[j]);
    }
    glColor3f(1.0, 0.5, 0.5);  //设置线条颜色
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

    glutSwapBuffers();//交换缓冲（双缓冲时使用）
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
    glClear(GL_COLOR_BUFFER_BIT);//清除帧缓存
    for (int i = 0; i <= 4; i++)
    {
        //在圆上初始化10个坐标点
        X[i] = R * cos(2 * Pi * i / 5);
        Y[i] = R * sin(2 * Pi * i / 5);
        x[i] = r * cos(2 * Pi * (i + 0.5) / 5);
        y[i] = r * sin(2 * Pi * (i + 0.5) / 5);
    }
    //模型观察矩阵初始化
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(move_x, move_y, 0.0f);
    glRotatef(alpha, 0, 0, 1);
    glBegin(GL_TRIANGLES);  //按照顺序开始画线.
    glColor3f(1.0, 0.0, 0.0);  //设置线条颜色
    for (int j = 0; j <= 4; j++) {
        glVertex2f(X[j] * 100, Y[j] * 100);
        glVertex2f(0, 0);
        glVertex2f(x[j] * 100, y[j] * 100);
    }
    glColor3f(1.0, 0.5, 0.5);  //设置线条颜色
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
    glutSwapBuffers();//交换缓冲（双缓冲时使用）
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
    case'W':   //上移
    case 'w':
        move_y += 10.0f;

        break;
    case'S':   //下移
    case's':
        move_y -= 10.0f;
        break;
    case'A':  //左移
    case'a':
        move_x -= 10.0f;
        break;
    case'D':   //右移
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
    glutInitWindowPosition(200, 200);//应用程序窗口位置
    glutInitWindowSize(800, 600);//窗口大小
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//双缓冲，单缓冲为GLUT_SINGLE
    glutCreateWindow("五角星图案");  //设置窗口标题
    init();                          //运行初始化函数
    glutKeyboardFunc(&keyboard);//键盘交互
    glutMouseFunc(&OnMouse);  //注册鼠标事件
    glutDisplayFunc(Display);     //调用显示窗口
    glutReshapeFunc(reshape);//窗口大小变化
    glutIdleFunc(change);//键盘交互

    glutMainLoop();
    return 0;
}