// Utils.cpp
// Utility functions for changing global variables are defined here
// Write functions as less as possible in this file!

#include "head.h"

#pragma warning(disable:4996)

BITMAPFILEHEADERnew fileHeader;
BITMAPINFOHEADERnew infoHeader;

void callList(GLint listcode) {
	glCallList(listcode);
}

void updateList(GLint listcode) {
	listcode = genDisplayList();
}

void updateCamera(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	camera[X] = target[X] +polar[R] * sin(polar[A]);
	camera[Z] = target[Z] + polar[R] * cos(polar[A]);
}

void updateCameraTarget(GLfloat* camera, GLfloat* target, GLfloat* polar) {
	int i;
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

void LongToByte(unsigned long value, unsigned char * outResult) {
	int i = 0;
	for (i = 0; i<4; i++) {
		outResult[i] = (unsigned char)(value % 16);
		value = value / 16;
		outResult[i] += (unsigned char)(value % 16) * 16;
		value = value / 16;
	}
	outResult[4] = '\0';
}

void screenshot(void) {
	GLint viewPort[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, viewPort);
	GLbyte * buffer = (GLbyte *)malloc(viewPort[2] * viewPort[3] * sizeof(GLbyte) * 3);
	glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3],
		GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	long fileSize = viewPort[2] * viewPort[3] * 3 + 54;
	//int i=0;  

	fileHeader.bfType[0] = 0x42;
	fileHeader.bfType[1] = 0x4d;
	LongToByte(fileSize, fileHeader.bfSize);
	LongToByte(54, fileHeader.bfOffBits);

	LongToByte(sizeof(infoHeader), infoHeader.biSize);
	LongToByte(viewPort[2], infoHeader.biWidth);
	LongToByte(viewPort[3], infoHeader.biHeight);

	infoHeader.biPlanes[0] = 0x01;
	infoHeader.biPlanes[1] = 0x00;
	infoHeader.biBitCount[0] = 0x18;
	infoHeader.biBitCount[1] = 0x00;
	LongToByte(0, infoHeader.biCompression);

	LongToByte((viewPort[2] * viewPort[3]), infoHeader.biSizeImage);

	char filename[25] = "images/screenshot.bmp";
	FILE * fp = fopen(filename, "w+");
	//cout << "1" << endl;
	fwrite(&fileHeader, sizeof(fileHeader), 1, fp);
	//cout << "2" << endl;
	fwrite(&infoHeader, sizeof(infoHeader), 1, fp);
	//cout << "3" << endl;
	fwrite(buffer, 1, (viewPort[2] * viewPort[3] * 3), fp);
	//cout << "4" << endl;
	fclose(fp);
	//cout << "5" << endl;

	free(buffer);
}