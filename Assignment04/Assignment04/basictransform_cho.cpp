#include "glCho.h"

//������ǥ��� ǥ����
static double P[12] = {
	0.3,0.2,0.1,1,
	0.7,0.2,0.1,1,
	0.5,0.7,0.1,1
};

//p�� ��ȯ�ؼ� q�� ���� ����.
static double Q[12];

//��ȯ ��Ʈ���� ������ ���� ������
double m1[16], m2[16], m3[16], m4[16];

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glChoTriangle4d(P);
	glColor3f(0.0, 0.0, 1.0);
	glChoTriangle4d(Q);
	glChoCoord();
	glFlush();						//����
}
void transformTri(double* m, double* p, double* q) {
	glChoTransform(m, p, q);
	glChoTransform(m, p + 4, q + 4);
	glChoTransform(m, p + 8, q + 8);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'i') {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (key == 't') {
		glChoMatTrans(m1, -1, -0.5, 0);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (key == 's') {
		glChoMatScale(m1, 1.5, 1.2, 1.4);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (key == 'x') {
		glChoMatRotateX(m1, 60);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (key == 'y') {
		glChoMatRotateY(m1, 60);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (key == 'z') {
		glChoMatRotateZ(m1, 60);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (key == 'Z') {
		glChoMatTrans(m1, -0.3, -0.2, 0);	//�������� �̵���Ű�� matrix
		glChoMatRotateZ(m2, 60);			//z���� �������� ȸ����Ű�� matrix
		glChoMatMult(m2, m1);
		glChoMatTrans(m3, 0.3, 0.2, 0);		//���ڸ��� �̵���Ű�� matrix
		glChoMatMult(m3, m2);
		transformTri(m3, P, Q);
		glChoMatPrint(m3, P, Q);
	}
	else if (key == 'c') {
		glChoMatTrans(m1, -0.3, -0.2, 0);	//�������� �̵���Ű�� matrix
		glChoMatScale(m2, 1.5, 1.2, 1.4);	//�����Ű�� matrix
		glChoMatMult(m2, m1);
		glChoMatTrans(m3, 0.3, 0.2, 0);		//���ڸ��� �̵���Ű�� matrix
		glChoMatMult(m3, m2);
		transformTri(m3, P, Q);				//��ȯ��� ����
		glChoMatPrint(m3, P, Q);
	}
	else if (key == 'h') {
		glChoMatShearX(m1, 0.1, 0.1);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	//�ڽŸ��� ���� ��ȯ
	else if (key == 'M') {
		glChoMatTrans(m1, -0.7, -0.2, 0);	//�������� �̵���Ű�� matrix
		glChoMatScale(m2, 1.5, 1.2, 1.4);	//�����Ű�� matrix
		glChoMatMult(m2, m1);
		glChoMatRotateX(m3, 180);			//x���� �������� ȸ����Ű�� matrix
		glChoMatMult(m3, m2);
		glChoMatTrans(m4, 0.7, 0.2, 0);		//���ڸ��� �̵���Ű�� matrix
		glChoMatMult(m4, m3);
		glChoMatPrint(m4, P, Q);
		transformTri(m4, P, Q);
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
	glRotated(x - PrevX, 0, 1, 0);
	glRotated(y - PrevY, 1, 0, 0);
	PrevX = x;
	PrevY = y;
	glutPostRedisplay();

}

//��ȯ�� ���� ���θ޴�
void choMainMenu(int entryID) {
	if (entryID == 'i') {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (entryID == 't') {
		glChoMatTrans(m1, -1, -0.5, 0);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	//�ڽŸ��� ���� ��ȯ
	else if (entryID == 'M') {
		glChoMatTrans(m1, -0.7, -0.2, 0);	//�������� �̵���Ű�� matrix
		glChoMatScale(m2, 1.5, 1.2, 1.4);	//�����Ű�� matrix
		glChoMatMult(m2, m1);
		glChoMatRotateX(m3, 180);			//x���� �������� ȸ����Ű�� matrix
		glChoMatMult(m3, m2);
		glChoMatTrans(m4, 0.7, 0.2, 0);		//���ڸ��� �̵���Ű�� matrix
		glChoMatMult(m4, m3);
		glChoMatPrint(m4, P, Q);
		transformTri(m4, P, Q);
	}
	else if (entryID == 'q')
		exit(0);
	glutPostRedisplay();
}
//Rotation�� ���� ����޴�
void choSubMenu(int entryID) {
	if (entryID == 'x') {
		glChoMatRotateX(m1, 60);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (entryID == 'y') {
		glChoMatRotateY(m1, 60);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (entryID == 'z') {
		glChoMatRotateZ(m1, 60);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (entryID == 'Z') {
		glChoMatTrans(m1, -0.3, -0.2, 0);	//�������� �̵���Ű�� matrix
		glChoMatRotateZ(m2, 60);			//z���� �������� ȸ����Ű�� matrix
		glChoMatMult(m2, m1);
		glChoMatTrans(m3, 0.3, 0.2, 0);		//���ڸ��� �̵���Ű�� matrix
		glChoMatMult(m3, m2);
		transformTri(m3, P, Q);
		glChoMatPrint(m3, P, Q);
	}
	glutPostRedisplay();
}
//Shearing�� ���� ����޴�
void choSubMenu2(int entryID) {
	if (entryID == 'x') {
		glChoMatShearX(m1, 0.1, 0.1);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (entryID == 'y') {
		glChoMatShearY(m1, 0.1, 0.1);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (entryID == 'z') {
		glChoMatShearZ(m1, 0.1, 0.1);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	glutPostRedisplay();
}
//Scaling�� ���� ����޴�
void choSubMenu3(int entryID) {
	if (entryID == 's') {
		glChoMatScale(m1, 1.5, 1.2, 1.4);
		glChoMatPrint(m1, P, Q);
		transformTri(m1, P, Q);
	}
	else if (entryID == 'c') {
		glChoMatTrans(m1, -0.3, -0.2, 0);	//�������� �̵���Ű�� matrix
		glChoMatScale(m2, 1.5, 1.2, 1.4);	//�����Ű�� matrix
		glChoMatMult(m2, m1);
		glChoMatTrans(m3, 0.3, 0.2, 0);		//���ڸ��� �̵���Ű�� matrix
		glChoMatMult(m3, m2);
		transformTri(m3, P, Q);				//��ȯ��� ����
		glChoMatPrint(m3, P, Q);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Geometric Transform");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutKeyboardFunc(keyboard);		//Ű���� �ݹ� ���
	glutMouseFunc(mouseClick);		//���콺 Ŭ�� �ݹ� ���
	glutMotionFunc(mouseMotion);	//���콺 ��� �ݹ� ���

	//Rotation ����޴� ���
	GLint MySubMenuID = glutCreateMenu(choSubMenu);
	glutAddMenuEntry("X", 'x');
	glutAddMenuEntry("Y", 'y');
	glutAddMenuEntry("Z", 'z');
	glutAddMenuEntry("with Fixed point", 'Z');
	//Shearing ����޴� ���
	GLint MySubMenuID2 = glutCreateMenu(choSubMenu2);
	glutAddMenuEntry("X", 'x');
	glutAddMenuEntry("Y", 'y');
	glutAddMenuEntry("Z", 'z');
	//Scaling ����޴� ���
	GLint MySubMenuID3 = glutCreateMenu(choSubMenu3);
	glutAddMenuEntry("o", 's');
	glutAddMenuEntry("with Fixed point", 'c');
	GLint MyMainMenuID = glutCreateMenu(choMainMenu);
	glutAddMenuEntry("Init", 'i');
	glutAddMenuEntry("Translation", 't');
	glutAddSubMenu("Rotation", MySubMenuID);
	glutAddSubMenu("Scaling", MySubMenuID3);
	glutAddSubMenu("Shearing", MySubMenuID2);
	glutAddMenuEntry("My own method", 'M');
	glutAddMenuEntry("Exit", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);		//���÷��� �ݹ� ���
	glutMainLoop();					//GLUT event processing loop.
	return 0;
}