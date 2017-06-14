// Draw.cpp
// Drawing components of the scene

#include "head.h"

// Declare model objects
GLMmodel* model[10];

// Set model objects
void initObj() {
	model[0] = glmReadOBJ("models/sofa.obj");
	model[1] = glmReadOBJ("models/sofaleg.obj");
	model[2] = glmReadOBJ("models/plantleaf.obj");
	model[3] = glmReadOBJ("models/shell.obj");
	model[4] = glmReadOBJ("models/floor1.obj");
	model[5] = glmReadOBJ("models/floor2.obj");
}

void drawObject() {
	glColor3f(1.0f, 1.0f, 1.0f);
	cout << textureObjectCnt << endl;
	// Draw models with texture. One texture for one model.
	//for (int ii = 0; ii < textureObjectCnt; ii++) {
	//	glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, textureObjects[ii]);
	//	glmDraw(model[ii], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	//	cout << ii << endl;
	//	glDisable(GL_TEXTURE_2D);
	//}
	// Draw models without texture
	glPushMatrix();
	glTranslatef(-39.169f, 93.1f, -340.861f);
	glmDraw(model[0], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-39.169f, 43.131f, -340.861f);
	glmDraw(model[1], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-38.341f, 60.182f, -56.79f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObjects[0]);
	glmDraw(model[2], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 150.0f, 1.062f);
	glmDraw(model[3], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 0.1f, 0.0f);
	glmDraw(model[4], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 15.0f, -280.914f);
	glmDraw(model[5], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}

GLint genDisplayList() {
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
		drawObject();
	glEndList();

	return lid;
}

void drawTarget(GLfloat* center, GLfloat radius) {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(center[X], center[Y], center[Z]);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 20; i++) {
			glVertex3f(2 * radius * cos(2 * PI / 20 * i), radius * sin(2 * PI / 20 * i), 0);
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 20; i++) {
			glVertex3f(2 * radius * cos(2 * PI / 20 * i), 0, radius * sin(2 * PI / 20 * i));
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 20; i++) {
			glVertex3f(0, radius * sin(2 * PI / 20 * i), radius * cos(2 * PI / 20 * i));
		}
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}