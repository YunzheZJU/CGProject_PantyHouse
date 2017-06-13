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
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <memory.h>

// Include glew.h and glut.h
#include <gl/glew.h>
#include <gl/glut.h>
#include "glm.h"

// Using namespace std for cin and cout
using namespace std;

// TODO:Define MACROs
// Define shortcuts for coordinate in location array
#define X 0
#define Y 1
#define Z 2

// Define abbreviate for "radius" and "angle"
#define R 0
#define A 1

// Define Pi in math
#define PI 3.1415926

// Define BITMAP_ID
#define BITMAP_ID 0x4D42

// Define model list
extern GLMmodel* model[10];

// Define variables for texturing
extern int textureObjectCnt;
extern GLuint textureObjects[400];
extern char texFileName[400][100];
extern unsigned int textureVideo[30];

// TODO:Define classes

// TODO:Define enum for menu items
enum {
	EXIT
};

typedef struct tagBITMAPFILEHEADERnew {

	unsigned char bfType[2];

	unsigned char bfSize[4];

	unsigned char bfReserved1[2];

	unsigned char bfReserved2[2];

	unsigned char bfOffBits[4];

} BITMAPFILEHEADERnew;

typedef struct tagBITMAPINFOHEADERnew {

	unsigned char biSize[4];

	unsigned char biWidth[4];

	unsigned char biHeight[4];

	unsigned char biPlanes[2];

	unsigned char biBitCount[2];

	unsigned char biCompression[4];

	unsigned char biSizeImage[4];

	unsigned char biXPelsPerMeter[4];

	unsigned char biYPelsPerMeter[4];

	unsigned char biClrUsed[4];

	unsigned char biClrImportant[4];

} BITMAPINFOHEADERnew;

// TODO:Claim every function in cpp files here
// These functions are defined in Draw.cpp
void initObj();
void drawObject();
GLint genDisplayList();
void drawTarget(GLfloat* center, GLfloat radius);

// These functions are defined in Texture.cpp
void initTexture();
void readMTL(char * fileName);
unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void loadTexture(int i, char* filename, bool type);
void loadObjectTextures();

// These functions are defined in Light.cpp
void initLight();

// These functions are defined in Util.cpp
void callList(GLint listcode);
void updateList(GLint listcode);
void updateCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updateCameraTarget(GLfloat* camera, GLfloat* target, GLfloat* polar);
bool screenshot(int width, int height);

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
void showSysStatus();