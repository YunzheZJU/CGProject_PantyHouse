// Utils.cpp
// Utility functions for changing global variables are defined here
// Write functions as less as possible in this file!

#include "head.h"

#pragma warning(disable:4996)

// TODO:You can move these two function to Draw.cpp or System.cpp
void callList() {
	glCallList(scene.List);
}

void updateList() {
	scene.List = genTableList();
}

void updateCamera() {
	scene.camera[X] = scene.camera_polar[R] * sin(scene.camera_polar[A]);
	scene.camera[Z] = scene.camera_polar[R] * cos(scene.camera_polar[A]);
}

void showSysStatus() {
	static int frame = 0, time, timebase = 0;
	static char fpstext[50];

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(fpstext, "FPS:%4.2f",
			frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	char *c;
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
	glRasterPos2f(-460, 460);
	for (c = fpstext; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glRasterPos2f(-460, -460);
	for (c = scene.message; *c != '\0'; c++) {
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