// System.cpp
// Processing system display and control

#include "head.h"

#pragma warning(disable:4996)

GLint listcode = 0;							// Listcode for display list
GLfloat camera[3] = { 0, 150, 400 };			// Position of camera
GLfloat camera_target[3] = { 0, 150, 0 };		// Position of target of camera
GLfloat camera_polar[2] = { 400, 0 };			// Polar coordinates of camera
GLboolean bcamera = GL_TRUE;
int windowwidth = 1280;
int windowheight = 720;
char message[70] = "Welcome!";				// Message string to be shown

void init() {
	// Initiate color
	glColor3f(1.0f, 1.0f, 1.0f);	// Maybe this is not important
	// Initiate texture
	initTexture();
	cout << "initTexture OK." << endl;
	// Initiate menu
	initMenu();
	//Initiate objects
	initObj();
	cout << "initObj OK." << endl;
	// Initiate display list
	listcode = genDisplayList();
	cout << "genDisplayList OK." << endl;
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

	gluLookAt(camera[X], camera[Y], camera[Z],
		camera_target[X], camera_target[Y], camera_target[Z],
		0, 1, 0);							// Define the view model

	drawTarget(camera_target, 2);
	callList(listcode);						// Draw Scene with display List
	//drawLights();
	showSysStatus();

	glutSwapBuffers();
}

void reshape(int width, int height) {
	if (height == 0) {						// Prevent A Divide By Zero By
		height = 1;							// Making Height Equal One
	}
	glViewport(width / 2.0 - 640, height / 2.0 - 360, 1280, 720);
	windowwidth = width;
	windowheight = height;
	updateView();
}

// I refined updateView() to make the viewport fit camera better.
// Thus you must make some changes in the text-drawing function.
// Because it relies on its position against the current window.
void updateView() {
	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	gluPerspective(45.0f, 1.7778f, 0.1f, 1000.0f);	// 1.7778 = 1280 / 720

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
}

void processMouse(int button, int state, int x, int y) {
	// TODO:processMouse()
}

void processNormalKey(unsigned char k, int x, int y) {
	// TODO:processNormalKey()

	switch (k) {
		// 退出程序
		case 27: {
			cout << "Bye." << endl;
			exit(0);
			break;
		}
		// 切换摄像机本体/焦点控制
		case 'Z':
		case 'z': {
			strcpy(message, "Z pressed. Switch camera control!");
			bcamera = !bcamera;
			break;
		}
		// 摄像机本体/焦点移动
		case 'A':
		case 'a': {
			strcpy(message, "A pressed. Watch carefully!");
			if (bcamera) {
				camera_polar[A] -= 0.1;
				updateCamera(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "A pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				camera_target[X] -= 10;
				updateCameraTarget(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "A pressed.\n\tPosition of camera target is set to (" <<
					camera_target[X] << ", " << camera_target[Y] << ", " << camera_target[Z] << ")." << endl;
			}
			break;
		}
		case 'D':
		case 'd': {
			strcpy(message, "D pressed. Watch carefully!");
			if (bcamera) {
				camera_polar[A] += 0.1;
				updateCamera(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				camera_target[X] += 10;
				updateCameraTarget(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera target is set to (" <<
					camera_target[X] << ", " << camera_target[Y] << ", " << camera_target[Z] << ")." << endl;
			}
			break;
		}
		case 'W':
		case 'w': {
			strcpy(message, "W pressed. Watch carefully!");
			if (bcamera) {
				camera[Y] += 5;
				cout << fixed << setprecision(1) << "W pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				camera_target[Y] += 10;
				updateCameraTarget(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "W pressed.\n\tPosition of camera target is set to (" <<
					camera_target[X] << ", " << camera_target[Y] << ", " << camera_target[Z] << ")." << endl;
			}
			break;
		}
		case 'S':
		case 's': {
			strcpy(message, "S pressed. Watch carefully!");
			if (bcamera) {
				camera[Y] -= 5;
				cout << fixed << setprecision(1) << "S pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
				strcpy(message, "S pressed. Watch carefully!");
			}
			else {
				camera_target[Y] -= 10;
				updateCameraTarget(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera target is set to (" <<
					camera_target[X] << ", " << camera_target[Y] << ", " << camera_target[Z] << ")." << endl;
			}
			break;
		}
		case 'Q':
		case 'q': {
			if (bcamera) {
				strcpy(message, "Q pressed. Camera is moved...nearer!");
				camera_polar[R] *= 0.95;
				updateCamera(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "Q pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				strcpy(message, "Q pressed. Camera target is moving towards +Z!");
				camera_target[Z] += 5;
				updateCameraTarget(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "Q pressed.\n\tPosition of camera target is set to (" <<
					camera_target[X] << ", " << camera_target[Y] << ", " << camera_target[Z] << ")." << endl;
			}
			break;
		}
		case 'E':
		case 'e': {
			if (bcamera) {
				strcpy(message, "E pressed. Camera is moved...farther!");
				camera_polar[R] *= 1.05;
				updateCamera(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "E pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				strcpy(message, "E pressed. Camera target is moving towards -Z!");
				camera_target[Z] -= 5;
				updateCameraTarget(camera, camera_target, camera_polar);
				cout << fixed << setprecision(1) << "E pressed.\n\tPosition of camera target is set to (" <<
					camera_target[X] << ", " << camera_target[Y] << ", " << camera_target[Z] << ")." << endl;
			}
			break;
		}
		// 屏幕截图
		case 'X':
		case 'x':
			cout << "X pressed." << endl;
			if (screenshot(windowwidth, windowheight)) {
				cout << "Screenshot is saved." << endl;
				strcpy(message, "X pressed. Screenshot is Saved.");
			}
			else {
				cout << "Screenshot failed." << endl;
				strcpy(message, "X pressed. Screenshot failed.");
			}
			break;
	}
}

void processSpecialKey(int k, int x, int y) {
	// TODO:processSpecialKey()
}

void showSysStatus() {
	static int frame = 0;
	static int currenttime;
	static int timebase = 0;
	static char fpstext[50];
	char *c;
	char cameraposition[50];
	char targetposition[50];
	char camerapolar[50];

	frame++;
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	if (currenttime - timebase > 1000) {
		sprintf(fpstext, "FPS:%4.2f",
			frame * 1000.0 / (currenttime - timebase));
		timebase = currenttime;
		frame = 0;
	}

	sprintf(cameraposition, "camera position  %2.1f   %2.1f   %2.1f",
		camera[X], camera[Y], camera[Z]);
	sprintf(targetposition, "target position     %2.1f   %2.1f   %2.1f",
		camera_target[X], camera_target[Y], camera_target[Z]);
	sprintf(camerapolar, "camera polar      %2.3f   %2.3f",
		camera_polar[A], camera_polar[R]);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);					// 不受灯光影响
	glMatrixMode(GL_PROJECTION);			// 选择投影矩阵
	glPushMatrix();							// 保存原矩阵
		glLoadIdentity();						// 装入单位矩阵
		glOrtho(-480, 480, -480, 480, -1, 1);	// 设置裁减区域
		glMatrixMode(GL_MODELVIEW);				// 选择Modelview矩阵
		glPushMatrix();							// 保存原矩阵
			glLoadIdentity();						// 装入单位矩阵
			glPushAttrib(GL_LIGHTING_BIT);
				glRasterPos2f(-460, 452);
				for (c = fpstext; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
				}
				glRasterPos2f(280, 440);
				for (c = cameraposition; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
				}
				glRasterPos2f(280, 415);
				for (c = targetposition; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
				}
				glRasterPos2f(280, 390);
				for (c = camerapolar; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
				}
				glRasterPos2f(-460, -460);
				for (c = message; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
				}
			glPopAttrib();
			glMatrixMode(GL_PROJECTION);			// 选择投影矩阵
		glPopMatrix();							// 重置为原保存矩阵
		glMatrixMode(GL_MODELVIEW);				// 选择Modelview矩阵
	glPopMatrix();							// 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}