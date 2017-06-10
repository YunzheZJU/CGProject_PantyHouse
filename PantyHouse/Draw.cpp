// Draw.cpp
// Drawing components of the scene

#include "head.h"

GLMmodel* model[10];

//Initiate objects
void initObj() {
	GLuint list;
	model[0] = glmReadOBJ("models/Cushion.obj");
}

void drawObject() {
	// TODO:drawObject
	// !!Disable the lighting before you test with these code!!
	//glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.01, 0.01, 0.01);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glmDraw(model[0], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	for (int ii = 0; ii < textureObjectCnt; ii++) {
		glBindTexture(GL_TEXTURE_2D, textureObjects[textureObjectCnt - 1 - ii]);
		GLMmodel *stage2 = model[0];
		glmDrawGroup(stage2, ii, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	}
}

GLint genTableList() {
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
		drawObject();
	glEndList();

	return lid;
}