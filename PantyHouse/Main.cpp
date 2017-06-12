// Main.cpp
// Entrance of the project is defined here

#include "head.h"

#pragma warning(disable:4996)		// Disable warning about Security CRT functions
// Uncomment if you want to enable multitexturing
//#pragma comment (lib, "glew32.lib")

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowSize(1280, 720);
	int windowHandle = glutCreateWindow("CG Project: Panty House");

	init();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(processNormalKey);
	glutSpecialFunc(processSpecialKey);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}