#pragma once

#include <stdio.h>
#include <memory.h>
#include <gl/glut.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // M_PI 등을 사용하기 위함.
#include <math.h>
#define SIN(x) sin(x * M_PI / 180. ) // degree 각을 이용한 sin 함수
#define COS(x) cos(x * M_PI / 180. ) // degree 각을 이용한 cos 함수

inline void glChoMatSet(double* m,
	double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
{
	double mat[16] = { m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33 };
	memcpy(m, mat, sizeof(double) * 16);

}

inline void glChoMatMult(double* m1, double* m2) {
	double n[16];
	for (int k = 0; k < 16; k++) {
		n[k] = 0;
		double* p = m1 + (k / 4) * 4;
		double* q = m2 + (k % 4);
		for (int i = 0; i < 4; i++)
			n[k] += p[i] * q[i * 4];
	}
	memcpy(m1, n, sizeof(double) * 16);
}

//콘솔창에 행렬들을 깨끗하게 출력하는 함수
inline void glChoMatPrint(double* m, double* p, double* q) {
	system("cls");
	printf("변환 행렬\n");
	for (int i = 0; i < 4; i++) {
		printf("\t[");
		for (int j = 0; j < 4; j++)
			printf("%6.2f", m[i * 4 + j]);
		printf("]\n");
	}
	printf("\n");
	printf("P\n");
	for (int i = 0; i < 3; i++) {
		printf("\t[");
		for (int j = 0; j < 4; j++)
			printf("%6.2f", p[i * 4 + j]);
		printf("]\n");
	}
	printf("\n");
	printf("Q\n");
	for (int i = 0; i < 3; i++) {
		printf("\t[");
		for (int j = 0; j < 4; j++)
			printf("%6.2f", q[i * 4 + j]);
		printf("]\n");
	}
	printf("\n");
}

inline void glChoMatTrans(double* m, double tx, double ty, double tz) {
	glChoMatSet(m, 1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1);
}
inline void glChoMatScale(double* m, double sx, double sy, double sz) {
	glChoMatSet(m, sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
}

inline void glChoMatRotateX(double* m, double a) {
	glChoMatSet(m,
		1, 0, 0, 0,
		0, COS(a), -SIN(a), 0,
		0, SIN(a), COS(a), 0,
		0, 0, 0, 1);
}
inline void glChoMatRotateY(double* m, double a) {
	glChoMatSet(m,
		COS(a), 0, SIN(a), 0,
		0, 1, 0, 0,
		-SIN(a), 0, COS(a), 0,
		0, 0, 0, 1);
}
inline void glChoMatRotateZ(double* m, double a) {
	glChoMatSet(m,
		COS(a), -SIN(a), 0, 0,
		SIN(a), COS(a), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

inline void glChoMatShearX(double* m, double dy, double dz)
{
	glChoMatSet(m,
		1, dy, dz, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
inline void glChoMatShearY(double* m, double dx, double dz) {
	glChoMatSet(m,
		1, 0, 0, 0,
		dx, 1, dz, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
inline void glChoMatShearZ(double* m, double dx, double dy) {
	glChoMatSet(m,
		1, 0, 0, 0,
		0, 1, 0, 0,
		dx, dy, 1, 0,
		0, 0, 0, 1);
}

//변환함수, [q] = [M][p]
inline void glChoTransform(double* m, double* p, double* q) {
	q[0] = q[1] = q[2] = q[3] = 0;
	for (int i = 0; i < 4; i++) {
		q[0] += m[i] * p[i];
		q[1] += m[i + 4] * p[i];
		q[2] += m[i + 8] * p[i];
		q[3] += m[i + 12] * p[i];
	}
}
//간단한 그리기 함수들 : 선분, 삼각형, 좌표축
inline void glChoLine(double x1, double y1, double z1, double x2, double y2, double z2) {
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}
inline void glChoTriangle4d(double* p) {
	glBegin(GL_TRIANGLES);
	glVertex4dv(p);
	glVertex4dv(p + 4);
	glVertex4dv(p + 8);
	glEnd();
}
inline void glChoCoord(float target = 1) {
	glBegin(GL_LINES);
	
	//로봇의 부품과 동일한 색깔을 가지게 되는 현상 해결
	//Red line
	float color[4] = { 1.0, 0, 0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color); 
	glVertex3d(-0.1, 0, 0); glVertex3d(target, 0, 0);
	
	//Green line
	color[0] = 0.0;
	color[1] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color); 
	glVertex3d(0, -0.1, 0); glVertex3d(0, target, 0);
	//Blue line
	color[1] = 0.0;
	color[2] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color); 
	glVertex3d(0, 0, -0.1); glVertex3d(0, 0, -target);
	glEnd();

	//글자 X
	color[0] = 1.0;
	color[2] = 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glRasterPos3f(target, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');

	//글자 Y
	color[1] = 1.0;
	color[0] = 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glRasterPos3f(0, target, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');

	//글자 Z
	color[2] = 1.0;
	color[1] = 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glRasterPos3f(0, 0, -target);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
}