// Utils.cpp
// Utility functions for setting variables are defined here

#include "head.h"

#pragma warning(disable:4996)

GLfloat cameramatrix[3][3];
boolean collisionflag[134][200];

void callList(GLint listcode) {
	glCallList(listcode);
}

void updateList(GLint listcode, int type) {
	listcode = genDisplayList(type);
}

void initMap() {
	int i = 0;
	int j = 0;
	FILE* fp;
	char c;
	fp = fopen("map/collapsing table.txt", "r");
	if (!fp) {
		cout << "Fail to open collapsing map!";
		exit(1);
	}
	while ((c = fgetc(fp)) != EOF) {
		switch (c) {
			case '0': {
				collisionflag[i][j] = 0;
				break;
			}
			case '1': {
				collisionflag[i][j] = 1;
				break;
			}
			case '\t': {
				j++;
				break;
			}
			case '\n': {
				i++;
				j = 0;
				break;
			}
		}
	}
	fclose(fp);
}

void cameraMakeZero(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	camera[X] = camera[Z] = target[X] = target[Z] = polar[A] = 0;
	camera[Y] = target[Y] = 150;
	camera[Z] = polar[R] = 400;
}

void updateCamera(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	camera[X] = target[X] + polar[R] * sin(polar[A]);
	camera[Z] = target[Z] + polar[R] * cos(polar[A]);
}

void updatePolar(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	float tempangle;
	polar[R] = sqrt(pow((camera[X] - target[X]), 2.0) + pow((camera[Z] - target[Z]), 2.0));
	tempangle = atan2(abs(camera[X] - target[X]), abs(camera[Z] - target[Z]));
	if (abs(camera[X] - target[X]) < 0.0001) {
		if (camera[Z] > target[Z]) {
			polar[A] = 0;
		}
		else if (camera[Z] < target[Z]) {
			polar[A] = PI;
		}
		else {
			cout << "Error occurred in polar[A]" << endl;
		}
	}
	else if (camera[X] > target[X]) {
		if (camera[Z] > target[Z]) {
			polar[A] = tempangle;
		}
		else if(camera[Z] < target[Z]) {
			polar[A] = PI - tempangle;
		}
		else {
			polar[A] = PI / 2;
		}
	}
	else if (camera[X] < target[X]) {
		if (camera[Z] > target[Z]) {
			polar[A] = -tempangle;
		}
		else if (camera[Z] < target[Z]) {
			polar[A] = tempangle - PI;
		}
		else {
			polar[A] = -PI / 2;
		}
	}
}

void updateTarget(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	target[X] = -polar[R] * cos(polar[T]) * sin(polar[A]) + camera[X];
	target[Y] = polar[R] * sin(polar[T]) + camera[Y];
	target[Z] = -polar[R] * cos(polar[T]) * cos(polar[A]) + camera[Z];
}

void saveCamera(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	cameramatrix[0][0] = camera[X];
	cameramatrix[0][1] = camera[Y];
	cameramatrix[0][2] = camera[Z];
	cameramatrix[1][0] = target[X];
	cameramatrix[1][1] = target[Y];
	cameramatrix[1][2] = target[Z];
	cameramatrix[2][0] = polar[R];
	cameramatrix[2][1] = polar[A];
	cameramatrix[2][2] = polar[T];
}

void loadCamera(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	camera[X] = cameramatrix[0][0];
	camera[Y] = cameramatrix[0][1];
	camera[Z] = cameramatrix[0][2];
	target[X] = cameramatrix[1][0];
	target[Y] = cameramatrix[1][1];
	target[Z] = cameramatrix[1][2];
	polar[R] = cameramatrix[2][0];
	polar[A] = cameramatrix[2][1];
	polar[T] = cameramatrix[2][2];
}

bool detectCollision(GLfloat* camera) {
	int i = (camera[X] + 335) / 5;
	int j = (501 - camera[Z]) / 5;
	if (collisionflag[i][j]) {
		return false;
	}
	else {
		return true;
	}
}

void updateWindowcenter(int* window, int* windowcenter) {
	windowcenter[X] = glutGet(GLUT_WINDOW_X) + window[W] / 2.0;
	windowcenter[Y] = glutGet(GLUT_WINDOW_Y) + window[H] / 2.0;
}

bool screenshot(int width, int height) {
	static int screenshotnum = 1;	// Construct filename
	char filename[50];				// File name to be written
	byte* image;					// Store pixels
	FILE* fp;						// Pointer to the file to be written
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;

	// 4-bit align
	int bmpwidth;
	bmpwidth = width * 3;
	while (bmpwidth % 4 != 0) {
		bmpwidth++;
	}

	// Define parameters in fileheader
	fileheader.bfType = BITMAP_ID;
	fileheader.bfOffBits = 14 + sizeof(BITMAPINFOHEADER);
	fileheader.bfReserved1 = fileheader.bfReserved2 = 0;
	fileheader.bfSize = height * bmpwidth * 8 + fileheader.bfOffBits;

	// Define parameters in infoheader
	infoheader.biXPelsPerMeter = infoheader.biYPelsPerMeter = 0;
	infoheader.biClrUsed = 0;
	infoheader.biClrImportant = 0;
	infoheader.biPlanes = 1;
	infoheader.biCompression = 0;
	infoheader.biBitCount = 24;
	infoheader.biSize = sizeof(BITMAPINFOHEADER);
	infoheader.biHeight = height;
	infoheader.biWidth = width;
	infoheader.biSizeImage = height * bmpwidth;

	// Get enough memory for storing pixels
	image = (byte *)malloc(sizeof(byte)*infoheader.biSizeImage);
	if (image == NULL) {
		free(image);
		cout << "Fail to get enough memory!" << endl;
		return false;
	}

	// Read pixels in window
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image);

	// Open a new file
	sprintf(filename, "images/ScreenShot%03d.bmp", screenshotnum++);
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		cout << "Fail to open a new file!" << endl;
		free(image);
		return false;
	}

	// Write file
	fwrite(&fileheader.bfType, 2, 1, fp);
	fwrite(&fileheader.bfSize, 4, 1, fp);
	fwrite(&fileheader.bfReserved1, 2, 1, fp);
	fwrite(&fileheader.bfReserved2, 2, 1, fp);
	fwrite(&fileheader.bfOffBits, 4, 1, fp);
	fwrite(&infoheader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(image, infoheader.biSizeImage, 1, fp);

	// Free memory and close file
	free(image);
	fclose(fp);

	return true;
}

void processMusic(int value) {
	if (value) {
		PlaySound(TEXT("music/CandyAMine.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	else {
		PlaySound(NULL, NULL, 0);
	}
}