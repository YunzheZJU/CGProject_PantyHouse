// Light.cpp
// Functions related with lighting are defined here

#include "head.h"

GLfloat gray[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_pos0[] = { 0.0f, 400.0f, 0.0f, 1.0f };
GLfloat light_pos1[] = { 0.0f, -400.0f, 0.0f, 1.0f };

void initLight() {
	glEnable(GL_NORMALIZE);
	// You should comment the next two lines if there is no light in the scene.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	// Initiate Light 0
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	// Set global ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	// Set mirror reflection target to camera instead of infinity
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// Apply mirror reflection after texturing
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT);
	// Set mix mode for texture and lighting
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}