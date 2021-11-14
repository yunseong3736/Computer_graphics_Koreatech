#include "robot.h"
#include <gl/glut.h>
static Robot robot;
static bool bRobotRun = false;

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	robot.draw();
	glutSwapBuffers();
	glFlush();
}

static int PrevX, PrevY;
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		PrevX = x;
		PrevY = y;
	}
}
void mouseMotion(GLint x, GLint y) {
	glMatrixMode(GL_MODELVIEW);
	glRotated(x - PrevX, 0, -1, 0);
	glRotated(y - PrevY, -1, 0, 0);
	PrevX = x;
	PrevY = y;
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {

	if (key == 'i') {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (key == 'w') {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
	}
	else if (key == 's') {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (key == 'q')
		exit(0);
	glutPostRedisplay();
}

void initRendering()
{
	//����ó��
	GLfloat light_specular[] = { 0.8,0.5,0.8,1.0 };
	GLfloat light_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat light_ambient[] = { 0.5,0.5,0.5,1.0 };
	GLfloat light_position[] = { 0.f,-2.5f,2.5f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	//Mesh�� ����
	GLfloat mat_specular[] = { 0.5,1.0,0.5,1.0 };
	GLfloat mat_shininess[] = { 70.0 };
	GLfloat mat_color[] = { 0.5,0.5,0.5,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING); // ���� ��� ����
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE); // ����ȭ
	glEnable(GL_DEPTH_TEST); //depth �˻�(z-���� ���)
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Cho Robot");

	glutDisplayFunc(display); // ���÷��� �ݹ� ���
	glutKeyboardFunc(keyboard); // Ű���� �ݹ� ���
	glutMouseFunc(mouseClick); // ���콺 Ŭ�� �ݹ� ���
	glutMotionFunc(mouseMotion); // ���콺 ��� �ݹ� ���

	initRendering(); // ���� ����

	glutMainLoop();
	return 0;
}