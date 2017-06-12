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
	cout << sqrt(pow(3.0, 2.0) + pow(4.0, 2.0)) << endl;
	polar[R] = sqrt(pow((camera[X] - target[X]), 2.0) + pow((camera[Z] - target[Z]), 2.0));
	tempangle = atan2(abs(camera[X] - target[X]), abs(camera[Z] - target[Z]));
	for (i = 1; i; i++) {
		if ((polar[A] >= 0 && polar[A] - i * 2 * PI < 0) || (polar[A] < 0 && polar[A] + i * 2 * PI >= 0)) {
			break;
		}
		else {
			polar[A] >= 0 ? (polar[A] -= i * 2 * PI) : (polar[A] += i * 2 * PI);
			cout << polar[A] << endl;
		}
	}
	if (polar[A] - PI * 0.5 < 0) {
		polar[A] = tempangle;
	}
	else if (polar[A] - PI < 0) {
		polar[A] = PI - tempangle;
	}
	else if (polar[A] - PI *1.5 < 0) {
		polar[A] = PI + tempangle;
	}
	else if (polar[A] - PI * 2 < 0) {
		polar[A] = 2 * PI - tempangle;
	}
	else {
		cout << "Error in polar[A]" << endl;
		polar[A] = 0;
	}
	//updateCamera(camera, target, polar);
}