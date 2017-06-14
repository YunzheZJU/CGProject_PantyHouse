// System.cpp
// Processing system display and control

#include "head.h"

#pragma warning(disable:4996)

GLint listcode = 0;							// Listcode for display list
GLfloat camera[3] = { 0, 150, 400 };			// Position of camera
GLfloat target[3] = { 0, 150, 0 };		// Position of target of camera
GLfloat camera_polar[3] = { 400, 0, 0 };			// Polar coordinates of camera
GLboolean bcamera = GL_TRUE;
GLboolean bfps = GL_FALSE;
GLboolean bfocus = GL_TRUE;
int window[2] = { 1280, 720 };
int windowcenter[2];
//int mouse[2];
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
	// Initiate lighting
	initLight();
	cout << "initLight OK." << endl;
	// Initiate display list
	listcode = genDisplayList();
	cout << "genDisplayList OK." << endl;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();						// Reset The Current Modelview Matrix

	gluLookAt(camera[X], camera[Y], camera[Z],
		target[X], target[Y], target[Z],
		0, 1, 0);							// Define the view model

	drawTarget(target, 2);
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
	window[W] = width;
	window[H] = height;
	updateWindowcenter(window, windowcenter);
	updateView();
}

// I refined updateView() to make the viewport fit camera better.
// Thus you must make some changes in the text-drawing function.
// Because it relies on its position against the current window.
void updateView() {
	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	gluPerspective(45.0f, 1.7778f, 0.1f, 2000.0f);	// 1.7778 = 1280 / 720

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
}

void processMouseClick(int button, int state, int x, int y) {
	// TODO:processMouseClick()
	cout << "Window position (" << glutGet(GLUT_WINDOW_X) << ", " << glutGet(GLUT_WINDOW_Y) << ")" << endl;
	SetCursorPos(windowcenter[X], windowcenter[Y]);
}

void processMouseMove(int x, int y) {
	cout << "Mouse moves to (" << x << ", " << y << ")" << endl;
	if (!bfps) {
	}
	else {
		// Track target and reverse mouse moving to center point.
		// 将新坐标与屏幕中心的差值换算为polar的变化
		camera_polar[A] = -(x - window[W] / 2.0) / 101.9;			// 1 degree per 2 pixels
		camera_polar[T] = -(y - window[H] / 2.0) / 114.6;
		// 将鼠标放回窗口中心
		//SetCursorPos(windowcenter[X], windowcenter[Y]);
		// 更新摄像机目标
		updateTarget(camera, target, camera_polar);
	}
}

void processFocus(int state) {
	if (state == GLUT_LEFT) {
		bfocus = GL_FALSE;
		cout << "Focus is on other window." << endl;
	}
	else if (state == GLUT_ENTERED) {
		bfocus = GL_TRUE;
		cout << "Focus is on this window." << endl;
	}
	else {
		cout << state << endl;
	}
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
		// 切换第一人称控制
		case 'C':
		case 'c': {
			strcpy(message, "C pressed. Switch fps control!");
			bfps = !bfps;
			// 摄像机归零
			cameraMakeZero(camera, target, camera_polar);
			// 调整窗口位置
			int windowmaxx = glutGet(GLUT_WINDOW_X) + window[W];
			int windowmaxy = glutGet(GLUT_WINDOW_Y) + window[H];
			if (windowmaxx >= glutGet(GLUT_SCREEN_WIDTH) || windowmaxy >= glutGet(GLUT_SCREEN_HEIGHT)) {
				glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH) - window[W], glutGet(GLUT_SCREEN_HEIGHT) - window[H]);
			}
			// 鼠标位置居中
			updateWindowcenter(window, windowcenter);
			SetCursorPos(windowcenter[X], windowcenter[Y]);
			break;
		}
		// 第一人称移动/摄像机本体移动/焦点移动
		case 'A':
		case 'a': {
			strcpy(message, "A pressed. Watch carefully!");
			if (bfps) {
				camera[X] -= cos(camera_polar[A]) * 10;
				camera[Z] += sin(camera_polar[A]) * 10;
				target[X] -= cos(camera_polar[A]) * 10;
				target[Z] += sin(camera_polar[A]) * 10;
			}
			else {
				if (bcamera) {
					camera_polar[A] -= 0.1;
					updateCamera(camera, target, camera_polar);
					cout << fixed << setprecision(1) << "A pressed.\n\tPosition of camera is set to (" <<
						camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
				}
				else {
					target[X] -= 10;
					updatePolar(camera, target, camera_polar);
					cout << fixed << setprecision(1) << "A pressed.\n\tPosition of camera target is set to (" <<
						target[X] << ", " << target[Y] << ", " << target[Z] << ")." << endl;
				}
			}
			break;
		}
		case 'D':
		case 'd': {
			strcpy(message, "D pressed. Watch carefully!");
			if (bfps) {
				camera[X] += cos(camera_polar[A]) * 10;
				camera[Z] -= sin(camera_polar[A]) * 10;
				target[X] += cos(camera_polar[A]) * 10;
				target[Z] -= sin(camera_polar[A]) * 10;
			}
			else {
				if (bcamera) {
					camera_polar[A] += 0.1;
					updateCamera(camera, target, camera_polar);
					cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera is set to (" <<
						camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
				}
				else {
					target[X] += 10;
					updatePolar(camera, target, camera_polar);
					cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera target is set to (" <<
						target[X] << ", " << target[Y] << ", " << target[Z] << ")." << endl;
				}
			}
			break;
		}
		case 'W':
		case 'w': {
			strcpy(message, "W pressed. Watch carefully!");
			if (bfps) {
				camera[X] -= sin(camera_polar[A]) * 10;
				camera[Z] -= cos(camera_polar[A]) * 10;
				target[X] -= sin(camera_polar[A]) * 10;
				target[Z] -= cos(camera_polar[A]) * 10;
			}
			else {
				if (bcamera) {
					camera[Y] += 5;
					cout << fixed << setprecision(1) << "W pressed.\n\tPosition of camera is set to (" <<
						camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
				}
				else {
					target[Y] += 10;
					updatePolar(camera, target, camera_polar);
					cout << fixed << setprecision(1) << "W pressed.\n\tPosition of camera target is set to (" <<
						target[X] << ", " << target[Y] << ", " << target[Z] << ")." << endl;
				}
			}
			break;
		}
		case 'S':
		case 's': {
			strcpy(message, "S pressed. Watch carefully!");
			if (bfps) {
				camera[X] += sin(camera_polar[A]) * 10;
				camera[Z] += cos(camera_polar[A]) * 10;
				target[X] += sin(camera_polar[A]) * 10;
				target[Z] += cos(camera_polar[A]) * 10;
			}
			else {
				if (bcamera) {
					camera[Y] -= 5;
					cout << fixed << setprecision(1) << "S pressed.\n\tPosition of camera is set to (" <<
						camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
					strcpy(message, "S pressed. Watch carefully!");
				}
				else {
					target[Y] -= 10;
					updatePolar(camera, target, camera_polar);
					cout << fixed << setprecision(1) << "D pressed.\n\tPosition of camera target is set to (" <<
						target[X] << ", " << target[Y] << ", " << target[Z] << ")." << endl;
				}
			}
			break;
		}
		case 'Q':
		case 'q': {
			if (bcamera) {
				strcpy(message, "Q pressed. Camera is moved...nearer!");
				camera_polar[R] *= 0.95;
				updateCamera(camera, target, camera_polar);
				cout << fixed << setprecision(1) << "Q pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				strcpy(message, "Q pressed. Camera target is moving towards +Z!");
				target[Z] += 5;
				updatePolar(camera, target, camera_polar);
				cout << fixed << setprecision(1) << "Q pressed.\n\tPosition of camera target is set to (" <<
					target[X] << ", " << target[Y] << ", " << target[Z] << ")." << endl;
			}
			break;
		}
		case 'E':
		case 'e': {
			if (bcamera) {
				strcpy(message, "E pressed. Camera is moved...farther!");
				camera_polar[R] *= 1.05;
				updateCamera(camera, target, camera_polar);
				cout << fixed << setprecision(1) << "E pressed.\n\tPosition of camera is set to (" <<
					camera[X] << ", " << camera[Y] << ", " << camera[Z] << ")." << endl;
			}
			else {
				strcpy(message, "E pressed. Camera target is moving towards -Z!");
				target[Z] -= 5;
				updatePolar(camera, target, camera_polar);
				cout << fixed << setprecision(1) << "E pressed.\n\tPosition of camera target is set to (" <<
					target[X] << ", " << target[Y] << ", " << target[Z] << ")." << endl;
			}
			break;
		}
		// 屏幕截图
		case 'X':
		case 'x':
			cout << "X pressed." << endl;
			if (screenshot(window[W], window[H])) {
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
		target[X], target[Y], target[Z]);
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