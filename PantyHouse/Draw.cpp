// Draw.cpp
// Drawing components of the scene

#include "head.h"

GLMmodel* model[10];

//Initiate objects
void initObj() {
	GLuint list;
	model[0] = glmReadOBJ("models/texturetest01.obj");
	model[1] = glmReadOBJ("models/texturetest04.obj");
	model[2] = glmReadOBJ("models/texturetest06.obj");
	model[3] = glmReadOBJ("models/texturetest07.obj");
	model[4] = glmReadOBJ("models/texturetest08.obj");
	model[5] = glmReadOBJ("models/texturetest09.obj");
}

void drawObject() {
	// TODO:drawObject
	glColor3f(1.0f, 0.0f, 1.0f);
	glScalef(0.01, 0.01, 0.01);
	cout << textureObjectCnt << endl;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (int ii = 0; ii < textureObjectCnt; ii++) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureObjects[ii]);
		glmDraw(model[ii], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		cout << ii << endl;
		glDisable(GL_TEXTURE_2D);
	}
	glmDraw(model[3], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glmDraw(model[4], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glmDraw(model[5], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
}

GLint genTableList() {
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
		drawObject();
	glEndList();

	return lid;
}