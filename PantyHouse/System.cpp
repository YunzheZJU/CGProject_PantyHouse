// System.cpp
// Processing system display and control

#include "head.h"

void init() {
	// Initiate color
	glColor3f(1.0f, 1.0f, 1.0f);	// Maybe this is not important
	// Initiate texture
	initTexture();
	// Initiate menu
	initMenu();
	// Initiate display list
	scene.List = genTableList();
	// Initiate lighting
	initLight();
}

void idle() {
	glutPostRedisplay();
}

void initMenu() {
	// TODO:initMenu()
}

void processMenu(int value) {
	// TODO:processMenu()
}

void redraw() {
	// TODO:redraw()
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();						// Reset The Current Modelview Matrix

	gluLookAt(scene.camera[X], scene.camera[Y], scene.camera[Z],
		scene.camera_target[X], scene.camera_target[Y], scene.camera_target[Z],
		0, 1, 0);							// Define the view model

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	callList();								// Draw Scene with display List

	glutSwapBuffers();
}

void reshape(int width, int height) {
	if (height == 0) {						// Prevent A Divide By Zero By
		height = 1;							// Making Height Equal One
	}
	glViewport(width / 2.0 - 640, height / 2.0 - 360, 1280, 720);

	updateView();
}

// I refined updateView() to make the viewport fit camera better.
// Thus you must make some changes in the text-drawing function.
// Because it relies on its position against the current window.
void updateView() {
	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	gluPerspective(45.0f, 1.7778f, 0.1f, 100.0f);	// 1.7778 = 1280 / 720

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
}

void processMouse(int button, int state, int x, int y) {
	// TODO:processMouse()
}

void processNormalKey(unsigned char k, int x, int y) {
	// TODO:processNormalKey()
}

void processSpecialKey(int k, int x, int y) {
	// TODO:processSpecialKey()
}