// Main.cpp
// Entrance of the project is defined here

#include "head.h"

#pragma warning(disable:4996)		// Disable warning about Security CRT functions
#pragma comment(lib, "winmm.lib")

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowSize(1280, 720);
	int windowHandle = glutCreateWindow("CG Project: Panty House");

	init();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutMouseFunc(processMouseClick);
	glutPassiveMotionFunc(processMouseMove);
	glutEntryFunc(processFocus);
	glutKeyboardFunc(processNormalKey);
	glutSpecialFunc(processSpecialKey);
	glutIdleFunc(idle);
	glutTimerFunc(2000, processMusic, 1);

	glutMainLoop();	
	
	return 0;
}