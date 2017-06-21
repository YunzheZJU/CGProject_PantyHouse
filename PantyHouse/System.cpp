// System.cpp
// Processing system display and control

#include "head.h"

#pragma warning(disable:4996)

GLint listcode_scene = 0;							// Listcode of scene for display list
GLint listcode_nurbs = 0;							// Listcode of nurbs for display list
GLint listcode_door = 0;							// Listcode of door for display list
GLfloat camera[3] = { 0, 150, 400 };			// Position of camera
GLfloat target[3] = { 0, 150, 0 };		// Position of target of camera
GLfloat camera_polar[3] = { 400, 0, 0 };			// Polar coordinates of camera
GLfloat camera_locator[3] = { 0, 0, 400 };
GLboolean bcamera = GL_TRUE;
GLboolean bfocus = GL_TRUE;
GLboolean bmouse = GL_FALSE;
GLboolean bnurbs = GL_FALSE;
GLboolean bmsaa = GL_FALSE;
GLboolean bmusic = GL_TRUE;
GLboolean bopening = GL_FALSE;
int fpsmode = 0;							// 0:off, 1:on, 2:waiting
int window[2] = { 1280, 720 };
int windowcenter[2];
char message[70] = "Welcome!";				// Message string to be shown
int focus = NONE;

void init() {
	// Initiate color
	glColor3f(1.0f, 1.0f, 1.0f);	// Maybe this is not important
	// Initiate collision map
	initMap();
	// Initiate texture
	initTexture();
	cout << "initTexture OK." << endl;
	// Initiate video
	initVideo();
	cout << "initVideo OK" << endl;
	// Initiate menu
	initMenu();
	// Initiate objects
	initObj();
	cout << "initObj OK." << endl;
	// Initiate NURBS
	init_nurbs_surface();
	cout << "init_nurbs_surface OK." << endl;
	// Initiate lighting
	initLight();
	cout << "initLight OK." << endl;
	// Initiate display list
	listcode_scene = genDisplayList(SCENE);
	listcode_nurbs = genDisplayList(NURBS);
	listcode_door = genDisplayList(DOOR);
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

	if (bmsaa)
	{
		glEnable(GL_MULTISAMPLE_ARB);
	}
	else
	{
		glDisable(GL_MULTISAMPLE_ARB);
	}

	updateLight();						// 更新光源信息并启用
	callList(listcode_scene);						// Draw scene with display List
	callList(listcode_door);						// Draw door with display List
	drawVideo();									// Draw video frames
	drawTransparentObject();						// AT LAST Draw transparent glass
	if (fpsmode == 1) {
		drawCrosshair();
		camera_locator[X] = camera[X];
		camera_locator[Z] = camera[Z];
		drawLocator(camera_locator, 2);
	}
	else {
		drawLocator(target, 2);
	}
	if (bnurbs) {
		callList(listcode_nurbs);
	}
	// Draw light
	drawLocator(light_pos0, 5);
	drawLocator(light_pos1, 5);
	drawLocator(light_pos2, 5);

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

void updateView() {
	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	gluPerspective(45.0f, 1.7778f, 0.1f, 3000.0f);	// 1.7778 = 1280 / 720

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
}

void processMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		bmsaa = !bmsaa;
		cout << "LMB pressed. Switch on/off multisampling anti-alias.\n" << endl;
		strcpy(message, "LMB pressed. Switch on/off multisampling anti-alias.");
		glutPostRedisplay();
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && fpsmode) {
		processpick(window);
	}
}

void processMouseMove(int x, int y) {
	cout << "Mouse moves to (" << x << ", " << y << ")" << endl;
	if (fpsmode) {
		// Track target and reverse mouse moving to center point.
		if (fpsmode == 2) {
			// 鼠标位置居中，为确保在glutPositionWindow()之后执行
			updateWindowcenter(window, windowcenter);
			SetCursorPos(windowcenter[X], windowcenter[Y]);
			glutSetCursor(GLUT_CURSOR_NONE);
			fpsmode = 1;
			return;
		}
		if (x < window[W] * 0.25) {
			x += window[W] * 0.5;
			bmouse = !bmouse;
		}
		else if (x > window[W] * 0.75) {
			x -= window[W] * 0.5;
			bmouse = !bmouse;
		}
		if (y < window[H] * 0.25) {
			y = window[H] * 0.25;
			bmouse = !bmouse;
		}
		else if (y > window[H] * 0.75) {
			y = window[H] * 0.75;
			bmouse = !bmouse;
		}
		// 将新坐标与屏幕中心的差值换算为polar的变化
		camera_polar[A] = -(x - window[W] / 2.0) / 101.9;			// 1 degree per 2 pixels
		camera_polar[T] = -(y - window[H] / 2.0) / 114.6;
		// 移动光标
		if (bmouse) {
			SetCursorPos(glutGet(GLUT_WINDOW_X) + x, glutGet(GLUT_WINDOW_Y) + y);
			bmouse = !bmouse;
		}
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
	switch (k) {
		// 退出程序
		case 27: {
			cout << "Bye." << endl;
			exit(0);
			break;
		}
		// 绘制NURBS开关
		case 'N':
		case 'n': {
			strcpy(message, "N pressed. Show/Hide NURBS object!");
			bnurbs = !bnurbs;
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
			// 摄像机归零
			cameraMakeZero(camera, target, camera_polar);
			if (!fpsmode) {
			// 调整窗口位置
				int windowmaxx = glutGet(GLUT_WINDOW_X) + window[W];
				int windowmaxy = glutGet(GLUT_WINDOW_Y) + window[H];
				if (windowmaxx >= glutGet(GLUT_SCREEN_WIDTH) || windowmaxy >= glutGet(GLUT_SCREEN_HEIGHT)) {
					// glutPositionWindow()并不会立即执行！
					glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH) - window[W], glutGet(GLUT_SCREEN_HEIGHT) - window[H]);
					fpsmode = 2;
					break;
				}
				// 鼠标位置居中
				updateWindowcenter(window, windowcenter);
				SetCursorPos(windowcenter[X], windowcenter[Y]);
				glutSetCursor(GLUT_CURSOR_NONE);
				fpsmode = 1;
			}
			else {
				glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
				fpsmode = 0;
			}
			break;
		}
		// 第一人称移动/摄像机本体移动/焦点移动
		case 'A':
		case 'a': {
			strcpy(message, "A pressed. Watch carefully!");
			if (fpsmode) {
				saveCamera(camera, target, camera_polar);
				camera[X] -= cos(camera_polar[A]) * PACE;
				camera[Z] += sin(camera_polar[A]) * PACE;
				target[X] -= cos(camera_polar[A]) * PACE;
				target[Z] += sin(camera_polar[A]) * PACE;
				if (detectCollision(camera)) {
					loadCamera(camera, target, camera_polar);
				}
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
			if (fpsmode) {
				saveCamera(camera, target, camera_polar);
				camera[X] += cos(camera_polar[A]) * PACE;
				camera[Z] -= sin(camera_polar[A]) * PACE;
				target[X] += cos(camera_polar[A]) * PACE;
				target[Z] -= sin(camera_polar[A]) * PACE;
				if (detectCollision(camera)) {
					loadCamera(camera, target, camera_polar);
				}
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
			if (fpsmode) {
				saveCamera(camera, target, camera_polar);
				camera[X] -= sin(camera_polar[A]) * PACE;
				camera[Z] -= cos(camera_polar[A]) * PACE;
				target[X] -= sin(camera_polar[A]) * PACE;
				target[Z] -= cos(camera_polar[A]) * PACE;
				if (detectCollision(camera)) {
					loadCamera(camera, target, camera_polar);
				}
			}
			else {
				if (bcamera) {
					camera[Y] += 10;
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
			if (fpsmode) {
				saveCamera(camera, target, camera_polar);
				camera[X] += sin(camera_polar[A]) * PACE;
				camera[Z] += cos(camera_polar[A]) * PACE;
				target[X] += sin(camera_polar[A]) * PACE;
				target[Z] += cos(camera_polar[A]) * PACE;
				if (detectCollision(camera)) {
					loadCamera(camera, target, camera_polar);
				}
			}
			else {
				if (bcamera) {
					if (camera[Y] >= 10) {
						camera[Y] -= 10;
					}
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
		// 光源颜色分量
		case 'R':
		case 'r': {
			cout << "R pressed." << endl;
			currentcolor[0] -= 0.1f;
			if (currentcolor[0] < 0) {
				currentcolor[0] = 1.0f;
			}
			break;
		}
		case 'G':
		case 'g': {
			cout << "G pressed." << endl;
			currentcolor[1] -= 0.1f;
			if (currentcolor[1] < 0) {
				currentcolor[1] = 1.0f;
			}
			break;
		}
		case 'B':
		case 'b': {
			cout << "B pressed." << endl;
			currentcolor[2] -= 0.1f;
			if (currentcolor[2] < 0) {
				currentcolor[2] = 1.0f;
			}
			break;
		}
		// 光源强度（衰减）
		case '+': {
			cout << "+ pressed." << endl;
			constantattenuation -= 0.1f;
			cout << constantattenuation << endl;
			break;
		}
		case '-': {
			cout << "- pressed." << endl;
			constantattenuation += 0.1f;
			cout << constantattenuation << endl;
			break;
		}
		// 屏幕截图
		case 'X':
		case 'x': {
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
		// 背景音乐
		case 'V':
		case 'v': {
			bmusic = !bmusic;
			if (bmusic) {
				processMusic(1);
			}
			else {
				processMusic(0);
			}
			break;
		}
		// 开门动画
		case 'O':
		case 'o': {
			cout << "O pressed." << endl;
			if (openangle == 0) {
				bopening = GL_TRUE;
				glutTimerFunc(33, timer, OPENING);
			}
			else if (openangle == 90) {
				bopening = GL_FALSE;
				glutTimerFunc(33, timer, CLOSING);
			}
			break;
		}
		// 缩放以适应
		case 'F':
		case 'f': {
			if (!fpsmode) {
				break;
			}
			cout << "F pressed." << endl;
			switch (focus) {
				case TV: {
					strcpy(message, "F pressed. Zoom to TV!");
					// 移动准心
					updateWindowcenter(window, windowcenter);
					SetCursorPos(windowcenter[X] + window[W] * 0.25, windowcenter[Y]);
					target[X] = 75.0f;target[Y] = 150.0f;target[Z] = 481.143f;
					camera[X] = 80.0f;camera[Y] = 150.0f;camera[Z] = 245.0f;
					break;
				}
				case CARPET: {
					strcpy(message, "F pressed. Zoom to Carpet!");
					// 移动准心
					updateWindowcenter(window, windowcenter);
					SetCursorPos(windowcenter[X] + window[W] * 0.25, windowcenter[Y] + window[H] * 0.174);
					target[X] = 146.7f; target[Y] = -204.8f; target[Z] = 496.6f;
					camera[X] = 148.7f; camera[Y] = 150.0f; camera[Z] = 311.8f;
					break;
				}
				case DRAWING: {
					strcpy(message, "F pressed. Zoom to drawing!");
					// 移动准心
					updateWindowcenter(window, windowcenter);
					SetCursorPos(windowcenter[X] - window[W] * 0.125, windowcenter[Y]);
					target[X] = -496.6f; target[Y] = 180.0f; target[Z] = -336.1f;
					camera[X] = -96.6f; camera[Y] = 180.0f; camera[Z] = -335.9f;
					break;
				}
				default: {
					strcpy(message, "Something selectable should be shooted by RMB!");
					break;
				}
			}
			break;
		}
		// 输出Obj
		case '.':
		{
			exportObj();
			break;
		}
	}
	// Go upstairs
	if (fpsmode == 1) {
		if (camera[Z] > -66.828) {
			camera[Y] = 150;
			camera_locator[Y] = 0;
		}
		else if (camera[Z] < -86.544) {
			camera[Y] = 180;
			camera_locator[Y] = 30;
		}
		else if (-86.544 <= camera[Z] && camera[Z] <= -66.828) {
			camera[Y] = 165;
			camera_locator[Y] = 15;
		}
	}

}

void processSpecialKey(int k, int x, int y) {
	switch (k) {
		case 101: {
			light_pos0[Y] += 5;
			break;
		}
		case 103: {
			if (light_pos0[Y] >= 10) {
				light_pos0[Y] -= 5;
			}
			break;
		}
	}
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

	sprintf(cameraposition, "Camera Position  %2.1f   %2.1f   %2.1f",
		camera[X], camera[Y], camera[Z]);
	sprintf(targetposition, "Target Position     %2.1f   %2.1f   %2.1f",
		target[X], target[Y], target[Z]);
	sprintf(camerapolar, "Camera Polar      %2.1f   %2.3f   %2.3f",
		camera_polar[R], camera_polar[A], camera_polar[T]);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);					// 不受灯光影响
	glMatrixMode(GL_PROJECTION);			// 选择投影矩阵
	glPushMatrix();							// 保存原矩阵
		glLoadIdentity();						// 装入单位矩阵
		glOrtho(-640, 640, -360, 360, -1, 1);	// 设置裁减区域
		glMatrixMode(GL_MODELVIEW);				// 选择Modelview矩阵
		glPushMatrix();							// 保存原矩阵
			glLoadIdentity();						// 装入单位矩阵
			glPushAttrib(GL_LIGHTING_BIT);
				glRasterPos2f(-620, 340);
				for (c = fpstext; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
				}
				glRasterPos2f(400, 340);
				for (c = cameraposition; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
				}
				glRasterPos2f(400, 305);
				for (c = targetposition; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
				}
				glRasterPos2f(400, 270);
				for (c = camerapolar; *c != '\0'; c++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
				}
				glRasterPos2f(-620, -340);
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
