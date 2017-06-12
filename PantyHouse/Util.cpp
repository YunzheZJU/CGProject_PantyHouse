// Utils.cpp
// Utility functions for changing global variables are defined here
// Write functions as less as possible in this file!

#include "head.h"

#pragma warning(disable:4996)

// TODO:You can move these two function to Draw.cpp or System.cpp
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