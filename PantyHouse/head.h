// head.h
// Global variables and other things are claimed here

#pragma once

// Include related head files and IO classes
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

// Include glew.h and glut.h
#include <gl/glew.h>
#include <gl/glut.h>

// Include glm.h
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

// Define buffer size for picking stack
#define BUFSIZE 512

// Define global variables
extern int textureobjectcount;
extern GLuint textureobjects[60];
extern char texturefilename[60][100];
extern unsigned int texturevideo[32];
extern GLfloat light_pos0[4];
extern GLfloat light_pos1[4];
extern GLfloat light_pos2[4];
extern GLfloat spot[4];
extern GLMmodel* model[80];
extern GLfloat black[4];
extern GLfloat currentcolor[4];
extern GLfloat constantattenuation;
extern GLboolean bdooropening;
extern GLboolean bcurtainopening;
extern GLboolean bout;
extern GLfloat doorangle;
extern GLfloat curtainratio;
extern GLint listcode_door;
extern char message[70];
extern int focus;

// Define enum for display list
enum {
	SCENE, 
	NURBS, 
	DOOR
};

// Define emun for pick name
enum {
	NONE, 
	SOFA1, PLANT, SHELL, FLOOR, TV, DOORDOUBLE, 
	SQUAREDESK, GLASSBOARD, SHELF, GARDEN, 
	SWING, WINDOW, WALL, SOFATABLE, TABLE, 
	MILK, STANDINGPLATE, METALSWING, CHECK, 
	OPEN, DRAWING, CUPBOARD, CUP, CARPET, 
	STREW, ROPE, LIGHT, UMBRELLA, TAILI, JAM, 
	CUSHION1, CUSHION2, CUSHION3, DOORGLASS, 
	CURTAIN, PANGCI, GROUND, SOFA2, SOFA3, 
	DOORSINGLE, TEAPOT, LIUSHENGJI, LAMB, PIANO, 
	PLATE, CAKE
};

// Define status for animation of door and curtain
enum {
	DOOROPENING, 
	DOORCLOSING, 
	CURTAINOPENING, 
	CURTAINCLOSING
};

// These functions are defined in Draw.cpp
void initObj();
void initNurbsSurface();
GLint genDisplayList(int type);
void drawScene();
void drawModel(int modelnum, GLfloat x, GLfloat y, GLfloat z, 
	int texturenum = -1, int mode = GL_MODULATE, GLfloat rotate = 0.0f);
void drawVideo();
void drawNurbs();
void drawDoor();
void drawLocator(GLfloat* center, GLfloat radius);
void drawCrosshair();
void drawNurbsSurface();
void drawCube();
void drawTransparentObject();
void drawGeometry();

// These functions are defined in Texture.cpp
void initTexture();
void readMTL(char * fileName);
void loadObjectTextures();
void initVideo();
unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void loadTexture(int i, char* filename, bool type);

// These functions are defined in Light.cpp
void initLight();
void initLight0();
void initLight1();
void initLight2();

// These functions are defined in Util.cpp
void callList(GLint listcode);
void updateList(GLint* listcode, int type);
void initMap();
void cameraMakeZero(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updateCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updateTarget(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updatePolar(GLfloat* camera, GLfloat* target, GLfloat* polar);
void saveCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
void loadCamera(GLfloat* camera, GLfloat* target, GLfloat* polar);
void updateLight();
bool detectCollision(GLfloat* camera);
void updateWindowcenter(int* window, int* windowcenter);
bool screenshot(int width, int height);
void processMusic(int value);
void processPick(GLint* window);
void startPicking(GLint * window);
void stopPicking();
void processHits(GLint hits, GLuint buffer[]);
void animationTimer(int value);
void exportObj();

// These functions are defined in System.cpp
void init();
void idle();
void redraw();
void reshape(int width, int height);
void processMouseClick(int button, int state, int x, int y);
void processMouseMove(int x, int y);
void processFocus(int state);
void processNormalKey(unsigned char k, int x, int y);
void processSpecialKey(int k, int x, int y);
void showSysStatus();
