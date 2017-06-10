// System.cpp
// Processing system display and control

#include "head.h"

#pragma warning(disable:4996)

void init() {
	// Initiate color
	glColor3f(1.0f, 1.0f, 1.0f);	// Maybe this is not important
	// Initiate texture
	initTexture();
	// Initiate menu
	initMenu();
	//Initiate objects
	initObj();
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

	callList();								// Draw Scene with display List
	showSysStatus();

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

	switch (k) {
	// 退出程序
	case 27:
	case 'Q':
	case 'q': {
		cout << "Bye." << endl;
		exit(0);
		break;
	}
	// 摄像机移动
	case 'A':
	case 'a': {
		scene.camera_polar[A] -= 0.1;
		updateCamera();
		cout << fixed << setprecision(1) << "A pressed.\n\tPosition of camera is set to (" <<
			scene.camera[X] << ", " << scene.camera[Y] << ", " << scene.camera[Z] << ")." << endl;
		strcpy(scene.message, "A pressed. Watch carefully!");
		break;
	}
	case 'D':
	case 'd': {
		scene.camera_polar[A] += 0.1;
		updateCamera();
		cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera is set to (" <<
			scene.camera[X] << ", " << scene.camera[Y] << ", " << scene.camera[Z] << ")." << endl;
		strcpy(scene.message, "D pressed. Watch carefully!");
		break;
	}
	case 'W':
	case 'w': {
		scene.camera_target[Y] += 0.05;
		scene.camera[Y] += 0.05;
		cout << fixed << setprecision(1) << "W pressed.\n\tPosition of camera is set to (" <<
			scene.camera[X] << ", " << scene.camera[Y] << ", " << scene.camera[Z] << ")." << endl;
		strcpy(scene.message, "W pressed. Watch carefully!");
		break;
	}
	case 'S':
	case 's': {
		scene.camera_target[Y] -= 0.05;
		scene.camera[Y] -= 0.05;
		cout << fixed << setprecision(1) << "S pressed.\n\tPosition of camera is set to (" <<
			scene.camera[X] << ", " << scene.camera[Y] << ", " << scene.camera[Z] << ")." << endl;
		strcpy(scene.message, "S pressed. Watch carefully!");
		break;
	}
	case 'Z':
	case 'z': {
		scene.camera_polar[R] *= 0.95;
		updateCamera();
		cout << fixed << setprecision(1) << "Z pressed.\n\tPosition of camera is set to (" <<
			scene.camera[X] << ", " << scene.camera[Y] << ", " << scene.camera[Z] << ")." << endl;
		strcpy(scene.message, "Z pressed. Camera is moved...nearer!");
		break;
	}
	case 'C':
	case 'c': {
		scene.camera_polar[R] *= 1.05;
		updateCamera();
		cout << fixed << setprecision(1) << "C pressed.\n\tPosition of camera is set to (" <<
			scene.camera[X] << ", " << scene.camera[Y] << ", " << scene.camera[Z] << ")." << endl;
		strcpy(scene.message, "C pressed. Camera is moved...farther!");
		break;
	}

	}
}

void processSpecialKey(int k, int x, int y) {
	// TODO:processSpecialKey()
}