#pragma once
#include "Mesh.h"

class Robot {
public:
	Mesh Head, Body, RightArm, RightHand, LeftArm, LeftHand, RightLeg, RightFoot, LeftLeg, LeftFoot;
	double scale;

	Robot() {
		scale = 100;

		printf("Loading Robot Models....\n");
		Head.readAse("S_Head.ASE");					printf("	loading Head......... OK.\n");
		Body.readAse("S_Body.ASE");					printf("	loading Body......... OK.\n");
		RightArm.readAse("S_RightArm.ASE");			printf("	loading RightArm......... OK.\n");
		RightHand.readAse("S_RightHand.ASE");		printf("	loading RightHand......... OK.\n");
		LeftArm.readAse("S_LeftArm.ASE");			printf("	loading LeftArm......... OK.\n");
		LeftHand.readAse("S_LeftHand.ASE");			printf("	loading LeftHand......... OK.\n");
		RightLeg.readAse("S_RightLeg.ASE");			printf("	loading RightLeg......... OK.\n");
		RightFoot.readAse("S_RightFoot.ASE");		printf("	loading RightFoot......... OK.\n");
		LeftLeg.readAse("S_LeftLeg.ASE");			printf("	loading LeftLeg......... OK.\n");
		LeftFoot.readAse("S_LeftFoot.ASE");			printf("	loading LeftFoot......... OK.\n");
	}

	void draw() {
		//¸öÅë
		Body.draw(0.0, 0.0, 0.83, scale, true);

		//¸Ó¸®
		glPushMatrix();
			glTranslated(0.0, 0.45, -0.07);
			glScalef(1.1f, 1.1f, 1.1f);
			Head.draw(0.08, 0.08, 1.35, scale);
		glPopMatrix();

		//¿À¸¥ÂÊ ÆÈ, ¼Õ
		glPushMatrix();
			glTranslated(-0.25, 0.32, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			RightArm.draw(0, 0, 1.68, scale);

			glPushMatrix();
				glTranslated(-0.05, -0.3, 0.0);
				glScalef(1.0f, 1.0f, 1.0f);
				RightHand.draw(0.0, 0.35, 0.83, scale);
			glPopMatrix();
		glPopMatrix();

		//¿ÞÂÊ ÆÈ, ¼Õ
		glPushMatrix();
			glTranslated(0.25, 0.32, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			LeftArm.draw(0, 0, 1.68, scale);

			glPushMatrix();
				glTranslated(0.05, -0.3, 0.0);
				glScalef(1.0f, 1.0f, 1.0f);
				LeftHand.draw(0.0, 0.35, 0.83, scale);
			glPopMatrix();
		glPopMatrix();

		//¿À¸¥ÂÊ ´Ù¸®, ¹ß
		glPushMatrix();
		glTranslated(-0.1, -0.05, 0.0);
		glScalef(0.8f, 1.0f, 0.8f);
		RightLeg.draw(0.0, 0.35, 0.83, scale);

		glPushMatrix();
		glTranslated(0.0, -0.3, 0.0);
		glScalef(0.8f, 1.0f, 1.0f);
		RightFoot.draw(0.0, 0.0, 0.83, scale);
		glPopMatrix();
		glPopMatrix();

		//¿ÞÂÊ ´Ù¸®, ¹ß
		glPushMatrix();
			glTranslated(0.1, -0.05, 0.0);
			glScalef(0.8f, 1.0f, 0.8f);
			LeftLeg.draw(0.0, 0.35, 0.83, scale);

			glPushMatrix();
				glTranslated(0.0, -0.3, 0.0);
				glScalef(0.8f, 1.0f, 1.0f);
				LeftFoot.draw(0.0, 0.0, 0.83, scale);
			glPopMatrix();
		glPopMatrix();
	}

};