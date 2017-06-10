// head.h
// Global variables, classes and other things are claimed here

// When naming, please use lowercase for all variables 
// and set first letter to lowercase for functions.
// Names of functions are composed by a verb or a verb and a noun, 
// like init(),  initLight() and genTableList().

#pragma once

// TODO:Include related head files and IO classes
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <memory.h>

// Include glew.h and glut.h
#include <gl/glew.h>
#include <gl/glut.h>
#include"glm.h"
#include"global.h"

// Using namespace std for cin and cout
using namespace std;

// TODO:Define MACROs
// Define shortcuts for coordinate in location array
#define X 0
#define Y 1
#define Z 2

// Define Pi in math
#define PI 3.1415926

// Define BITMAP_ID
#define BITMAP_ID 0x4D42

/*
TODO:Define global variables
Here I use an extern struct to avoid duplicated defination of these variables.
Thus I must use "scene.XXX" every where.
Please reconstruct these codes to more C++ like ones.
*/
typedef struct {
	GLfloat camera[3] = { 0, 0, 5 };			// Position of camera
	GLfloat camera_target[3] = { 0, 0, 0 };		// Position of target of camera

	// Initiate list num for display list
	GLint List = 0;								// List num of display list

	// Array for storing signatures of different textures
	unsigned int texture[4];
}Myscene;

extern Myscene scene;

// TODO:Define classes

// TODO:Define enum for menu items
enum {
	EXIT
};

// TODO:Claim every function in cpp files here
// These functions are defined in Draw.cpp
void initObj();
void drawObject();
GLint genTableList();

// These functions are defined in Texture.cpp
void initTexture();
void readMTL(char * fileName);

// These functions are defined in Light.cpp
void initLight();

// These functions are defined in Util.cpp
void callList();
void updateList();

// These functions are defined in System.cpp
void init();
void idle();
void initMenu(void);
void processMenu(int value);
void redraw();
void reshape(int width, int height);
void updateView();
void processMouse(int button, int state, int x, int y);
void processNormalKey(unsigned char k, int x, int y);
void processSpecialKey(int k, int x, int y);