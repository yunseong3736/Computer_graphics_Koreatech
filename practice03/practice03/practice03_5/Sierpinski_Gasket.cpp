#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

/* 삼각형 초기화 */
GLfloat v[3][2] = { {-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15} };
int n = 0;// 반복 횟수

// 좌표와 몇번 반복할지 받는 변수 매개변수
void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m)
{
    /* 꼭짓점 수를 이용한 삼각형 분할 */
    GLfloat v0[2], v1[2], v2[2];
    int j;
    if (m > 0)
    {
        for (j = 0; j < 2; j++) {
            v0[j] = (a[j] + b[j]) / 2;
            v1[j] = (a[j] + c[j]) / 2;
            v2[j] = (b[j] + c[j]) / 2;
        }
        divide_triangle(a, v0, v1, m - 1);
        divide_triangle(b, v2, v0, m - 1);
        divide_triangle(c, v1, v2, m - 1);        
    }
    else {
        glVertex2fv(a);
        glVertex2fv(b);
        glVertex2fv(c);
    }
}

void display()
{
    if (n == 0) return;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    divide_triangle(v[0], v[1], v[2], n);
    glEnd();
    glFlush();
}

void MyMainMenu(int entryID) {
    if (entryID == -1) exit(0);
    n = entryID;
    glutPostRedisplay();
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

    //메뉴 생성 (1 to 10 and Exit)
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("1", 1);
    glutAddMenuEntry("2", 2);
    glutAddMenuEntry("3", 3);
    glutAddMenuEntry("4", 4);
    glutAddMenuEntry("5", 5);
    glutAddMenuEntry("6", 6);
    glutAddMenuEntry("7", 7);
    glutAddMenuEntry("8", 8);
    glutAddMenuEntry("9", 9);
    glutAddMenuEntry("10", 10);
    glutAddMenuEntry("Exit", -1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutMainLoop();
}