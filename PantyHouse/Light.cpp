// Light.cpp
// Functions related with lighting are defined here

#include "head.h"

// Define colors
GLfloat gray[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat gray2[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat red[4] = { 1.0f, 0.1f, 0.1f, 1.0f };
GLfloat green[4] = { 0.1f, 1.0f, 0.1f, 1.0f };
GLfloat blue[4] = { 0.1f, 0.0f, 1.1f, 1.0f };
GLfloat yellow[4] = { 1.0f, 1.0f, 0.1f, 1.0f };
GLfloat turquoise[4] = { 0.1f, 1.0f, 1.0f, 1.0f };
GLfloat golden[4] = { 1.0f, 0.843f, 0.1f, 1.0f };
GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light_pos0[4] = { 0.0f, 300.0f, 0.0f, 1.0f };
GLfloat light_pos1[4] = { 0.0f, 100.0f, 0.0f, 1.0f };
GLfloat spot[4] = { 226.9f, 150.0f, 124.1f, 1.0f };			// Position of spot light
GLfloat direction[] = { 0, -1, 0 };
GLfloat currentcolor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat constantattenuation = 1.0f;

void initLight() {
	glEnable(GL_NORMALIZE);
	// You should comment the next two lines if there is no light in the scene.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	// Set up Light 0
	initLight0();
	glEnable(GL_LIGHT0);
	// Set up Light 1
	initLight1();
	glEnable(GL_LIGHT1);
	// Set global ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	// Set mirror reflection target to camera instead of infinity
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// Apply mirror reflection after texturing
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT);
	// Set mix mode for texture and lighting
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void initLight0() {
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);	// 防止环境色过多影响光照与纹理的混合
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentcolor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantattenuation);
}

void initLight1() {
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, black);	// 防止环境色过多影响光照与纹理的混合
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 5.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);
}