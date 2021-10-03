#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
using namespace std;

/* 삼각형 초기화 */
GLfloat v[3][2] = { {-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15} };
int n = 10000;// 반복 횟수

void triangle(void) {
    GLfloat v1[2] = { -1.0, -0.58 };
    for (int i = 0; i < n; i++) {
        int j = rand() % 3;
        v1[0] = (v1[0] + v[j][0]) / 2;
        v1[1] = (v1[1] + v[j][1]) / 2;
        glVertex2fv(v1);
    }
}

/*
// 좌표와 몇번 반복할지 받는 변수 매개변수
void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m)
{
    GLfloat v0[2], v1[2], v2[2];
    int j;
    if (m > 0)
    {
        for (j = 0; j < 2; j++) {
            v0[j] = (a[j] + b[j]) / 2;
            v1[j] = (a[j] + c[j]) / 2;
            v2[j] = (b[j] + c[j]) / 2;
        }
        int r = rand() % 3;
        switch (r) {
        case 0:
            divide_triangle(a, v0, v1, m - 1);
            break;
        case 1:
            divide_triangle(b, v2, v0, m - 1);
            break;
        case 2:
            divide_triangle(c, v1, v2, m - 1);
            break;
        }             
    }
    else {
        glVertex2fv(a);
        glVertex2fv(b);
        glVertex2fv(c);
    }
}
*/
void display()
{
    if (n == 0) return;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    //divide_triangle(v[0], v[1], v[2], n);
    triangle();
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {

    //초기화
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski Gasket");
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    srand((unsigned int)time(NULL));
    glutDisplayFunc(display);
    glutMainLoop();
}