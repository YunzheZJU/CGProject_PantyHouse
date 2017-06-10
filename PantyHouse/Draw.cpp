// Draw.cpp
// Drawing components of the scene

#include "head.h"

GLMmodel* model[100];

//Initiate objects
void initObj()
{
	model[0] = glmReadOBJ("models/PantyHouse03.obj");
}


void drawObject() {
	// TODO:drawObject
	// !!Disable the lighting before you test with these code!!
	//glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.01, 0.01, 0.01);
	glmDraw(model[0], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
}

GLint genTableList() {
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
		drawObject();
	glEndList();

	return lid;
}