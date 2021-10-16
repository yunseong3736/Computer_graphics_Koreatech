#include "glCho.h"

//동차좌표계로 표시함
static double P[12] = { 0.3,0.2,0.1,1,   0.7,0.2,0.1,1,   0.5,0.7,0.1,1 };
static double Q[12];

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glChoTriangle4d(P);
	glColor3f(0.0, 0.0, 1.0);
	glChoTriangle4d(Q);
	glChoCoord();
	glFlush();
}
void transformTri(double* m, double* p, double* q) {
	glChoTransform(m, p, q);
	glChoTransform(m, p + 4, q + 4);
	glChoTransform(m, p + 8, q + 8);
}

void keyboard(unsigned char key, int x, int y) {
	double m1[16], m2[16], m3[16];

	if (key == 'i') {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (key == 't') {
		glChoMatTrans(m1, -1, -0.5, 0);
		glChoMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 's') {
		glChoMatScale(m1, 1.5, 1.2, 1.4);
		glChoMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'x') {
		glChoMatRotateX(m1, 60);
		glChoMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'y') {
		glChoMatRotateY(m1, 60);
		glChoMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'z') {
		glChoMatRotateZ(m1, 60);
		glChoMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'Z') {
		glChoMatTrans(m1, -0.3, -0.2, 0); //원점으로 이동시키는 matrix
		glChoMatRotateZ(m2, 60); //z축을 기준으로 회전시키는 matrix
		glChoMatMult(m2, m1);
		glChoMatTrans(m3, 0.3, 0.2, 0); //제자리로 이동시키는 matrix
		glChoMatMult(m3, m2);
		transformTri(m3, P, Q);
		glChoMatPrint(m3);
	}
	else if (key == 'c') {
		glChoMatTrans(m1, -0.3, -0.2, 0); //원점으로 이동시키는 matrix
		glChoMatScale(m2, 1.5, 1.2, 1.4); //신축시키는 matrix
		glChoMatMult(m2, m1);
		glChoMatTrans(m3, 0.3, 0.2, 0); //제자리로 이동시키는 matrix
		glChoMatMult(m3, m2);
		transformTri(m3, P, Q); //변환행렬 적용
		glChoMatPrint(m3);
	}
	else if (key == 'h') {
		glChoMatShearX(m1, 0.1, 0.1);
		glChoMatPrint(m1);
		transformTri(m1, P, Q);
	}
	else if (key == 'q')
		exit(0);
	glutPostRedisplay();
}

static double PrevX, PrevY;
void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		PrevX = x;
		PrevY = y;
	}
}
void mouseMotion(GLint x, GLint y) {
	glMatrixMode(GL_MODELVIEW);
	glRotated(x - PrevX, 0, 0.1, 0);
	glRotated(y - PrevY, 0.1, 0, 0);
	PrevX = x;
	PrevY = y;
	glutPostRedisplay();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Geometric Transform");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutMainLoop();
	return 0;
}