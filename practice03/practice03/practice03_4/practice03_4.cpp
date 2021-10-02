#include <GL/glut.h>
#include <math.h>

void display_name() {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 300, 300);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(10.0);

    //조
    glBegin(GL_LINES);
    glVertex2d(-0.9, 0.6);
    glVertex2d(-0.4, 0.6);
    glVertex2d(-0.4, 0.6);
    glVertex2d(-0.9, 0.1);
    glVertex2d(-0.65, 0.35);
    glVertex2d(-0.4, 0.1);
    glVertex2d(-0.9, -0.3);
    glVertex2d(-0.4, -0.3);
    glVertex2d(-0.65, 0.1);
    glVertex2d(-0.65, -0.3);
    glEnd();
    
    //윤
    double rad = 0.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = rad * cos(angle);
        double y = rad * sin(angle);
        glVertex2f(x, y + 0.45);
    }
    glEnd(); 
    rad = 0.1;
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = rad * cos(angle);
        double y = rad * sin(angle);
        glVertex2f(x, y + 0.45);
    }
    glEnd();
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(-0.25, 0.1);
    glVertex2d(0.25, 0.1);
    glVertex2d(-0.07, 0.1);
    glVertex2d(-0.07, -0.17);
    glVertex2d(0.07, 0.1);
    glVertex2d(0.07, -0.17);
    glVertex2d(-0.2, -0.1);
    glVertex2d(-0.2, -0.3);
    glVertex2d(-0.2, -0.3);
    glVertex2d(0.2, -0.3);
    glEnd();

    //성
    glBegin(GL_LINES);
    glVertex2d(0.6, 0.6);
    glVertex2d(0.4, 0.1);
    glVertex2d(0.55, 0.4);
    glVertex2d(0.65, 0.1);
    glVertex2d(0.65, 0.4);
    glVertex2d(0.8, 0.4);
    glVertex2d(0.8, 0.6);
    glVertex2d(0.8, 0.1);
    glEnd();
    rad = 0.17;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = rad * cos(angle);
        double y = rad * sin(angle);
        glVertex2f(x + 0.65, y - 0.2);
    }
    glEnd();
    rad = 0.1;
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = rad * cos(angle);
        double y = rad * sin(angle);
        glVertex2f(x + 0.65, y - 0.2);
    }
    glEnd();
    glColor3f(1, 1, 1);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);              //GLUT 윈도우 함수
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Display name");

    glClearColor(0.0, 0.0, 0.0, 1.0);   //GL 상태변수 설정
    glutDisplayFunc(display_name);      //GLUT 콜백함수 등록
    glutMainLoop();                     //이벤트 루프 진입
    return 0;
}
