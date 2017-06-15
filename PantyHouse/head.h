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

// Using namespace std for cout
using namespace std;

// Define shortcuts for coordinate in location array
#define X 0
#define Y 1
#define Z 2

// Define abbreviate
#define R 0		// Radius
#define A 1		// Alpha
#define T 2		// Theta
#define W 0		// Width
#define H 1		// Height

// Define Pi in math
#define PI 3.1415926

// Define BITMAP_ID
#define BITMAP_ID 0x4D42

// Define moving pace in fps mode
#define PACE 5

// Define variables for texturing
extern int textureObjectCnt;
extern GLuint textureObjects[400];
extern char texFileName[400][100];
extern unsigned int texturevideo[10];
extern GLfloat light_pos0[4];
extern GLfloat light_pos1[4];
extern GLfloat spot[4];

// TODO:Define enum for menu items
enum {
	EXIT
};

// Define enum for display list
enum {
	SCENE, 
	NURBS
};

// These functions are defined in Draw.cpp
void initObj();
void init_nurbs_surface();
void drawScene();
void drawModel(int modelnum, GLfloat x, GLfloat y, GLfloat z, int texturenum = -1, int mode = GL_MODULATE);
GLint genDisplayList(int type);
void drawLocator(GLfloat* center, GLfloat radius);
void drawCrosshair();
void draw_nurbs_surface();

// These functions are defined in Texture.cpp
void initTexture();
void initVideo();
void drawVideo();
void readMTL(char * fileName);
unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void loadTexture(int i, char* filename, bool type);
void loadObjectTextures();

// These functions are defined in Light.cpp
void initLight();
void initLight0();
void initLight1();

// These functions are defined in Util.cpp
void callList(GLint listcode);
void updateList(GLint listcode, int type);
void initMap();
void cameraMakeZero(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updateCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updateTarget(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updatePolar(GLfloat* camera, GLfloat* target, GLfloat* polar);
void saveCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
void loadCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
bool detectCollision(GLfloat* camera);
void updateWindowcenter(int* window, int* windowcenter);
bool screenshot(int width, int height);

// These functions are defined in System.cpp
void init();
void idle();
void initMenu(void);
void processMenu(int value);
void redraw();
void reshape(int width, int height);
void updateView();
void processMouseClick(int button, int state, int x, int y);
void processMouseMove(int x, int y);
void processFocus(int state);
void processNormalKey(unsigned char k, int x, int y);
void processSpecialKey(int k, int x, int y);
void showSysStatus();