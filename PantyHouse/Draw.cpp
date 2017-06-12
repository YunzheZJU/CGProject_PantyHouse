// Draw.cpp
// Drawing components of the scene

#include "head.h"

GLMmodel* model[10];

// Initiate objects
void initObj() {
	model[0] = glmReadOBJ("models/texturetest01.obj");
	model[1] = glmReadOBJ("models/texturetest04.obj");
	model[2] = glmReadOBJ("models/texturetest06.obj");
	model[3] = glmReadOBJ("models/texturetest07.obj");
	model[4] = glmReadOBJ("models/texturetest08.obj");
	model[5] = glmReadOBJ("models/texturetest09.obj");
}

void drawObject() {
	glColor3f(1.0f, 1.0f, 1.0f);
	cout << textureObjectCnt << endl;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Draw models with texture. One texture for one model.
	for (int ii = 0; ii < textureObjectCnt; ii++) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureObjects[ii]);
		glmDraw(model[ii], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		cout << ii << endl;
		glDisable(GL_TEXTURE_2D);
	}
	// Draw models without texture
	glmDraw(model[3], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glmDraw(model[4], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glmDraw(model[5], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
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