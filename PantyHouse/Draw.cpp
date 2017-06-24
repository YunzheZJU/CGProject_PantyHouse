// Draw.cpp
// Drawing components of the scene

#include "head.h"

// Model objects
GLMmodel* model[80];

// NURBS object
GLUnurbsObj *nurbsobject;
static GLfloat ctlpoints[4][4][3];
static GLfloat tcoords[2][2][2] = { 0, 0, 0, 1, 1, 0, 1, 1 };

// Color to be used in drawGeometry()
const GLfloat coffee[4] = { 0.756f, 0.557f, 0.404f, 1.0f };

// Video frame counter
int videoframe = 0;

// Controlling parameter to be used in animation of door and curtain
GLfloat doorangle = 0;
GLfloat curtainratio = 1.0f;

// Initiate model objects
void initObj() {
	model[0] = glmReadOBJ("models/sofa2.obj");
	model[1] = glmReadOBJ("models/sofaleg.obj");
	model[2] = glmReadOBJ("models/plantleaf.obj");
	model[11] = glmReadOBJ("models/plantmain.obj");
	model[12] = glmReadOBJ("models/plantflower.obj");
	model[6] = glmReadOBJ("models/TVsurface.obj");
	model[7] = glmReadOBJ("models/door1_1.obj");
	model[3] = glmReadOBJ("models/door1_2.obj");
	model[4] = glmReadOBJ("models/door1_3.obj");
	model[8] = glmReadOBJ("models/squaredesk.obj");
	model[9] = glmReadOBJ("models/glassboard.obj");
	model[10] = glmReadOBJ("models/shelf.obj");
	model[13] = glmReadOBJ("models/gardenleaf.obj");
	model[14] = glmReadOBJ("models/gardenmain.obj");
	model[17] = glmReadOBJ("models/garden.obj");
	model[15] = glmReadOBJ("models/swing.obj");
	model[16] = glmReadOBJ("models/window.obj");
	model[18] = glmReadOBJ("models/wall.obj");
	model[19] = glmReadOBJ("models/sofatable.obj");
	model[20] = glmReadOBJ("models/table.obj");
	model[21] = glmReadOBJ("models/milk.obj");
	model[22] = glmReadOBJ("models/standingplate.obj");
	model[23] = glmReadOBJ("models/metal_swing.obj");
	model[24] = glmReadOBJ("models/check.obj");
	model[25] = glmReadOBJ("models/open.obj");
	model[26] = glmReadOBJ("models/drawing.obj");
	model[27] = glmReadOBJ("models/carpet.obj");
	model[28] = glmReadOBJ("models/rope.obj");
	model[29] = glmReadOBJ("models/cup.obj");
	model[30] = glmReadOBJ("models/strew.obj");
	model[31] = glmReadOBJ("models/tv.obj");
	model[32] = glmReadOBJ("models/cupboard.obj");
	model[33] = glmReadOBJ("models/light.obj");
	model[34] = glmReadOBJ("models/umbrella.obj");
	model[35] = glmReadOBJ("models/drawing2.obj");
	model[36] = glmReadOBJ("models/floor1.obj");
	model[37] = glmReadOBJ("models/shelf2.obj");
	model[38] = glmReadOBJ("models/taili.obj");
	model[39] = glmReadOBJ("models/paper_taili3.obj");
	model[40] = glmReadOBJ("models/paper_taili1.obj");
	model[41] = glmReadOBJ("models/metal_taili.obj");
	model[42] = glmReadOBJ("models/jam1.obj");
	model[43] = glmReadOBJ("models/jam2.obj");
	model[44] = glmReadOBJ("models/jam3.obj");
	model[45] = glmReadOBJ("models/jam4.obj");
	model[46] = glmReadOBJ("models/jam5.obj");
	model[47] = glmReadOBJ("models/cushion1.obj");
	model[48] = glmReadOBJ("models/cushion2.obj");
	model[49] = glmReadOBJ("models/cushion3.obj");
	model[50] = glmReadOBJ("models/windowglass.obj");
	model[51] = glmReadOBJ("models/glass.obj");
	model[52] = glmReadOBJ("models/doorglassright.obj");
	model[53] = glmReadOBJ("models/doorglassleft.obj");
	model[54] = glmReadOBJ("models/curtain1.obj");
	model[55] = glmReadOBJ("models/curtain2.obj");
	model[56] = glmReadOBJ("models/pangci.obj");
	model[57] = glmReadOBJ("models/floor2.obj");
	model[58] = glmReadOBJ("models/sky.obj");
	model[59] = glmReadOBJ("models/ground.obj");
	model[60] = glmReadOBJ("models/sofa3.obj");
	model[61] = glmReadOBJ("models/sofa.obj");
	model[62] = glmReadOBJ("models/door2.obj");
	model[63] = glmReadOBJ("models/metal1.obj");
	model[64] = glmReadOBJ("models/handleright.obj");
	model[65] = glmReadOBJ("models/handleleft.obj");
	model[66] = glmReadOBJ("models/metal_jam.obj");
	model[67] = glmReadOBJ("models/liushengji.obj");
	model[68] = glmReadOBJ("models/lamb.obj");
	model[69] = glmReadOBJ("models/lambglass.obj");
	model[70] = glmReadOBJ("models/piano1.obj");
	model[71] = glmReadOBJ("models/piano2.obj");
	model[72] = glmReadOBJ("models/piano3.obj");
	model[73] = glmReadOBJ("models/piano4.obj");
	model[74] = glmReadOBJ("models/piano5.obj");
	model[75] = glmReadOBJ("models/piano6.obj");
	model[76] = glmReadOBJ("models/piano7.obj");
	model[77] = glmReadOBJ("models/plate.obj");
	model[78] = glmReadOBJ("models/cake1.obj");
	model[79] = glmReadOBJ("models/cake5.obj");
}

void initNurbsSurface() {
	int u, v;

	for (u = 0; u < 4; u++)
		for (v = 0; v < 4; v++) {
			ctlpoints[u][v][0] = 0.95f*(u - 1.5f);
			ctlpoints[u][v][2] = 0.95f*(v - 1.5f);
			ctlpoints[u][v][1] = ((rand() % 1000) / 1000.0F - 0.5F)*2.0f;
		}

	nurbsobject = gluNewNurbsRenderer();
	gluNurbsProperty(nurbsobject, GLU_SAMPLING_TOLERANCE, 10.0);
	gluNurbsProperty(nurbsobject, GLU_DISPLAY_MODE, GLU_FILL);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
}

void drawScene() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushName(SOFA1);
		drawModel(0, 39.169f, -93.1f, 340.861f, 44);
		drawModel(1, 39.169f, -43.131f, 340.861f, 5);
	glPopName();
	glPushName(PLANT);
		drawModel(2, 38.341f, -60.182f, 56.79f, 0, GL_REPLACE);
		drawModel(11, 35.509f, -48.121f, 61.799f, 6, GL_REPLACE);
		drawModel(12, 31.38f, -25.635f, 57.706f, 7, GL_REPLACE);
	glPopName();
	glPushName(SQUAREDESK);
		drawModel(8, 169.754f, -35.096f, -440.152f, 2);
		drawModel(8, 169.754f, -35.096f, -344.282f, 2);
		drawModel(8, 169.754f, -35.096f, -248.412f, 2);
	glPopName();
	glPushName(GLASSBOARD);
		drawModel(9, 128.44f, -43.75f, -43.47f, 3);
	glPopName();
	glPushName(SHELF);
		drawModel(10, -315.612f, -130.0f, 300.0f, 4);
		drawModel(37, -315.0f, -130.0f, 300.0f, 27);
	glPopName();
	glPushName(GARDEN);
		drawModel(13, -279.904f, -21.351f, -323.509f, 8, GL_REPLACE);
		drawModel(14, -275.286f, -15.766f, -322.688f, 9, GL_REPLACE);
		drawModel(17, -279.52f, -6.474f, -326.062f, 12);
	glPopName();
	glPushName(SWING);
		drawModel(15, -371.593f, -101.526f, -358.718f, 10);
	glPopName();
	glPushName(WINDOW);
		drawModel(16, 195.306f, -176.866f, 494.763f, 11, GL_MODULATE, 90);
		drawModel(16, -4.694f, -176.866f, 494.763f, 11, GL_MODULATE, 90);
		drawModel(16, -204.694f, -176.866f, 494.763f, 11, GL_MODULATE, 90);
		drawModel(16, -226.863f, -176.866f, -288.768f, 11);
	glPopName();
	glPushName(WALL);
		drawModel(18, 0.0f, -150.0f, -1.062f, 13);
	glPopName();
	glPushName(SOFATABLE);
		drawModel(19, -16.732f, -20.0f, -327.229f, 14);
	glPopName();
	glPushName(TABLE);
		drawModel(20, 209.309f, -68.194f, 335.534f, 15);
		drawModel(20, 39.03f, -68.194f, 335.534f, 15);
		drawModel(20, -131.25f, -68.194f, 335.534f, 15);
	glPopName();
	glPushName(MILK);
		drawModel(21, 264.654f, -114.421f, 28.376f, 16);
		drawModel(21, 264.654f, -114.421f, 16.376f, 16);
		drawModel(21, 264.654f, -114.421f, 4.376f, 16);
		drawModel(21, 264.654f, -114.421f, -7.624f, 16);
		drawModel(21, 264.654f, -114.421f, -19.624f, 16);
		drawModel(21, 264.654f, -114.421f, -31.624f, 16);
		drawModel(21, 249.654f, -114.421f, 28.376f, 16);
		drawModel(21, 249.654f, -114.421f, 16.376f, 16);
		drawModel(21, 249.654f, -114.421f, 4.376f, 16);
		drawModel(21, 249.654f, -114.421f, -7.624f, 16);
		drawModel(21, 249.654f, -114.421f, -19.624f, 16);
		drawModel(21, 249.654f, -114.421f, -31.624f, 16);
		drawModel(21, 261.443f, -114.421f, -61.348f, 16);
		drawModel(21, 250.679f, -114.421f, -83.816f, 16, GL_MODULATE, -22.308f);
	glPopName();
	glPushName(STANDINGPLATE);
		drawModel(22, -391.2f, -29.196f, -193.617f, 17, GL_MODULATE, 180.0f);
	glPopName();
	glPushName(METALSWING);
		drawModel(23, -360.581f, -180.24f, -343.365f);
	glPopName();
	glPushName(CHECK);
		drawModel(24, 122.562f, -101.406f, 48.416f, 18);
	glPopName();
	glPushName(DRAWING);
		drawModel(26, 321.348f, -193.038f, 337.094f, 20);
		drawModel(35, 321.348f, -193.038f, 337.094f, 24);
	glPopName();
	glPushName(CARPET);
		drawModel(27, -140.523f, -3.774f, -404.13f, 22, GL_MODULATE, 180);
	glPopName();
	glPushName(CUP);
		drawModel(29, 259.378f, -167.0f, -45.0f);
	glPopName();
	glPushName(TV);
		drawModel(31, -75.0f, -150.0f, -487.885f, 23);
	glPopName();
	glPushName(CUPBOARD);
		drawModel(32, 249.91f, -150.0f, -45.0f, 21);
	glPopName();
	glPushName(LIGHT);
		drawModel(33, 52.448f, -266.0f, -91.872f, 26, GL_REPLACE);
	glPopName();
	glPushName(UMBRELLA);
		drawModel(34, -290.15f, -29.981f, -128.367f, 28);
	glPopName();
	glPushName(FLOOR);
		drawModel(36, 0.0f, 0.0f, 0.0f, 25);
		drawModel(57, 0.0f, -15.0f, 280.914f, 41);
	glPopName();
	glPushName(TAILI);
		drawModel(41, 127.668f, -135.599f, -36.488f);
		drawModel(40, 127.68f, -127.094f, -36.467f);
		drawModel(39, 125.682f, -128.318f, -36.485f);
		drawModel(38, 125.024f, -127.154f, -36.485f, 29);
	glPopName();
	glPushName(JAM);
		drawModel(42, 258.599f, -229.854f, 19.408f, 30);
		drawModel(43, 258.599f, -229.854f, -2.733f, 31);
		drawModel(44, 258.599f, -229.854f, -24.875f, 32);
		drawModel(45, 258.599f, -233.104f, -73.041f, 33);
		drawModel(46, 258.599f, -233.104f, -104.3568f, 34);
		drawModel(66, 258.599f, -241.173f, -43.724f);
	glPopName();
	glPushName(CUSHION1);
		drawModel(47, -44.054f, -70.587f, -190.17f, 35);
	glPopName();
	glPushName(CUSHION2);
		drawModel(48, -133.802f, -83.721f, -196.468f, 36);
	glPopName();
	glPushName(CUSHION3);
		drawModel(49, -143.524f, -57.519f, -249.374f, 37);
	glPopName();
	glPushName(SOFA2);
		drawModel(60, 245.074f, -49.73f, -318.288f, 45);
	glPopName();
	glPushName(SOFA3);
		drawModel(61, -83.219f, -54.591f, -236.236f, 46);
	glPopName();
	glPushName(DOORSINGLE);
		drawModel(62, 266.0f, -141.5f, 147.009f, 47);
		drawModel(63, 268.5f, -140.0f, 181.311f);
	glPopName();
	glPushName(LIUSHENGJI);
		drawModel(67, -309.781f, -100.691f, 161.598f);
	glPopName();
	glPushName(LAMB);
		drawModel(68, -317.957f, -126.251f, 276.303f);
	glPopName();
	glPushName(PIANO);
		drawModel(70, -310.477f, -100.906f, 352.293f);
		drawModel(71, -310.47f, -100.159f, 354.563f);
		drawModel(72, -310.5f, -99.731f, 362.701f);
		drawModel(73, -310.499f, -99.872f, 362.402f);
		drawModel(74, -311.126f, -94.275f, 369.266f);
		drawModel(75, -311.152f, -96.838f, 369.278f);
		drawModel(76, -311.128f, -96.518f, 369.292f);
	glPopName();
	glPushName(TEAPOT);
		glPushMatrix();
			glTranslatef(-258.599f, 190.0f, 73.041f);
			glRotatef(-90.0f, 0, 1, 0);
			glutSolidTeapot(10.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-258.599f, 190.0f, 104.3568f);
			glRotatef(-90.0f, 0, 1, 0);
			glutSolidTeapot(10.0);
		glPopMatrix();
	glPopName();
	glPushName(PLATE);
		drawModel(77, 128.456f, -73.397f, -53.762f);
	glPopName();
	glPushName(CAKE);
		drawModel(78, 128.456f, -51.77f, -16.617f, 48);
		drawModel(78, 128.366f, -51.77f, -54.738f, 49);
		drawModel(78, 128.366f, -51.77f, -90.948f, 50);
		drawModel(78, 128.366f, -83.036f, -90.948f, 51);
		drawModel(79, 125.341f, -81.865f, -53.673f, 52);
		drawModel(79, 125.341f, -81.865f, -16.229f, 53);
		drawModel(79, 125.341f, -106.026f, -16.229f, 54);
	glPopName();

	drawGeometry();
}

/*	drawModel：调用glmDraw绘制模型
*
*	modelnum	- 模型序号
*	x, y, z		- (0, 0, 0)相对于当前模型中心点的坐标
*	texturenum	- 贴图纹理在.mtl文件中的序号，缺省值-1（无贴图）
*	mode		- GL_MODULATE或GL_REPLACE，前者为缺省值，后者用于解决盆栽贴图过暗的问题
*	rotate		- 模型绕(0, 1, 0)按右手定则旋转角度，缺省值为0
*/
void drawModel(int modelnum, GLfloat x, GLfloat y, GLfloat z, int texturenum, int mode, GLfloat rotate) {
	glPushMatrix();
	glTranslatef(-x, -y, -z);
	glRotatef(rotate, 0, 1, 0);
	if (texturenum == -1) {
		glmDraw(model[modelnum], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureObjects[texturenum]);
		glmDraw(model[modelnum], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

// Change the texture of screen every 1000ms
void drawVideo() {
	static int timebase = 0;
	static int currenttime;

	currenttime = glutGet(GLUT_ELAPSED_TIME);
	if (currenttime - timebase > 1000) {
		timebase = currenttime;
		videoframe++;
		if (videoframe == 32) {
			videoframe = 0;
		}
	}
	glPushMatrix();
		glTranslatef(75.0f, 150.0f, 481.143f);
		glRotated(180, 0, 1, 0);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texturevideo[videoframe]);
			glmDraw(model[6], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

// Draw an ugly NURBS surface above the house
// By default it is not shown...Hahaha
// Until you press 'N'
void drawNurbs() {
	glPushMatrix();
	glTranslatef(0.0f, 500.0f, 0.0f);
	glScalef(100.0f, 100.0f, 100.0f);
	drawNurbsSurface();
	glPopMatrix();
}

void drawDoor() {
	glPushName(DOORDOUBLE);
	drawModel(7, -337.0f, 0.0f, -20.403f, 1);
	drawModel(4, -337.0f, 0.0f, 60.403f, 1, GL_MODULATE, doorangle);
	drawModel(3, -337.0f, 0.0f, -100.403f, 1, GL_MODULATE, -doorangle);
	drawModel(64, -337.0f, -93.89f, -100.403f, -1, GL_MODULATE, -doorangle);
	drawModel(65, -337.0f, -88.304f, 59.597f, -1, GL_MODULATE, doorangle);
	glPopName();
	glPushName(OPEN);
	drawModel(25, -337.0f, -146.535f, -100.403f, 19, GL_MODULATE, -doorangle);
	glPopName();
	glPushName(ROPE);
	drawModel(28, -337.0f, -153.456f, -100.403f, -1, GL_MODULATE, -doorangle);
	glPopName();
	glPushName(STREW);
	drawModel(30, -337.0f, -165.745f, -100.403f, -1, GL_MODULATE, -doorangle);
	glPopName();
	glPushName(PANGCI);
	if (bout) {
		drawModel(56, -117.39f, -100.402f, -342.882f, 40);
	}
	else {
		drawModel(56, -117.39f, -1.402f, -342.882f, 40);
	}
	glPopName();
	glPushName(DOORGLASS);
	glPushMatrix();
	glTranslatef(337.0f, 153.75f, 100.403f);
	glRotatef(-doorangle, 0, 1, 0);
	glmDrawTransparency(model[52], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(337.0f, 153.75f, -60.597f);
	glRotatef(doorangle, 0, 1, 0);
	glmDrawTransparency(model[53], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.4);
	glPopMatrix();
	glPopName();
}

GLint genDisplayList(int type) {
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
	if (type == SCENE) {
		drawScene();
	}
	else if (type == NURBS) {
		drawNurbs();
	}
	else if (type == DOOR) {
		drawDoor();
	}
	glEndList();
	return lid;
}

void drawLocator(GLfloat* center, GLfloat radius) {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glLineWidth(1);
		glTranslatef(center[X], center[Y], center[Z]);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 20; i++) {
			glVertex3f(2 * radius * cos(2 * PI / 20 * i), radius * sin(2 * PI / 20 * i), 0);
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 20; i++) {
			glVertex3f(2 * radius * cos(2 * PI / 20 * i), 0, radius * sin(2 * PI / 20 * i));
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 20; i++) {
			glVertex3f(0, radius * sin(2 * PI / 20 * i), radius * cos(2 * PI / 20 * i));
		}
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawCrosshair() {
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
			glColor3f(0.1f, 1.0f, 0.1f);
				glLineWidth(3);
				glBegin(GL_LINES);
					glVertex2f(-11.0f, 0.0f);
					glVertex2f(10.0f, 0.0f);
				glEnd();
				glBegin(GL_LINES);
					glVertex2f(0.0f, -10.0f);
					glVertex2f(0.0f, 10.0f);
				glEnd();
			glPopAttrib();
			glMatrixMode(GL_PROJECTION);			// 选择投影矩阵
		glPopMatrix();							// 重置为原保存矩阵
		glMatrixMode(GL_MODELVIEW);				// 选择Modelview矩阵
	glPopMatrix();							// 重置为原保存矩阵
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void drawNurbsSurface() {
	GLfloat knots[8] = { 0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0 };
	glEnable(GL_TEXTURE_2D);
	gluBeginSurface(nurbsobject);

	gluNurbsSurface(nurbsobject, 8, knots, 8, knots, 4 * 3, 3, &ctlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);

	gluEndSurface(nurbsobject);
	glDisable(GL_TEXTURE_2D);
}

// Draw a cube with texture coordinate
void drawCube() {
	glScalef(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2i(1, 1); glVertex3i(1, 1, 1);
		glTexCoord2i(0, 1); glVertex3i(-1, 1, 1);
		glTexCoord2i(0, 0); glVertex3i(-1, -1, 1);
		glTexCoord2i(1, 0); glVertex3i(1, -1, 1);

		glNormal3f(0, 1, 0);
		glTexCoord2i(1, 1); glVertex3i(1, 1, 1);
		glTexCoord2i(0, 1); glVertex3i(1, 1, -1);
		glTexCoord2i(0, 0); glVertex3i(-1, 1, -1);
		glTexCoord2i(1, 0); glVertex3i(-1, 1, 1);

		glNormal3f(1, 0, 0);
		glTexCoord2i(1, 1); glVertex3i(1, -1, 1);
		glTexCoord2i(0, 1); glVertex3i(1, -1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, 1, -1);
		glTexCoord2i(1, 0); glVertex3i(1, 1, 1);

		glNormal3f(-1, 0, 0);
		glTexCoord2i(1, 1); glVertex3i(-1, 1, 1);
		glTexCoord2i(0, 1); glVertex3i(-1, 1, -1);
		glTexCoord2i(0, 0); glVertex3i(-1, -1, -1);
		glTexCoord2i(1, 0); glVertex3i(-1, -1, 1);

		glNormal3f(0, -1, 0);
		glTexCoord2i(1, 1); glVertex3i(-1, -1, 1);
		glTexCoord2i(0, 1); glVertex3i(-1, -1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, -1, -1);
		glTexCoord2i(1, 0); glVertex3i(1, -1, 1);

		glNormal3f(0, 0, -1);
		glTexCoord2i(1, 1); glVertex3i(-1, 1, -1);
		glTexCoord2i(0, 1); glVertex3i(1, 1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, -1, -1);
		glTexCoord2i(1, 0); glVertex3i(-1, -1, -1);
	glEnd();
}

// Draw transparent objects
void drawTransparentObject() {
	glPushName(WINDOW);
		glPushMatrix();
			glTranslatef(4.483f, 170.0f, -79.011f);
			glmDrawTransparency(model[50], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, 0.5);
		glPopMatrix();
	glPopName();
	glPushName(LAMB);
		glPushMatrix();
			glTranslatef(317.957f, 127.396f, -276.303f);
			glmDrawTransparency(model[69], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, 0.3);
		glPopMatrix();
	glPopName();
	glPushName(GLASSBOARD);
		glPushMatrix();
			glTranslatef(-129.69f, 82.0f, 53.47f);
			glmDrawTransparency(model[51], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.2);
		glPopMatrix();
	glPopName();
	glPushName(CURTAIN);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
			glPushMatrix();
				glTranslatef(-270.061f, 178.254f, -487.622f);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[38]);
				glmDrawTransparency(model[54], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-120.306f, 179.044f, -487.633f);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[39]);
				glmDrawTransparency(model[55], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-70.061f, 178.254f, -487.622f);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[38]);
				glmDrawTransparency(model[54], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(80.306f, 179.044f, -487.633f);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[39]);
				glmDrawTransparency(model[55], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(129.939f, 178.254f, -487.622f);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[38]);
				glmDrawTransparency(model[54], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(279.694f, 179.044f, -487.633f);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[39]);
				glmDrawTransparency(model[55], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(217.889f, 178.254f, 214.012f);
				glRotatef(-90.0f, 0, 1, 0);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[38]);
				glmDrawTransparency(model[54], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(217.9f, 179.044f, 363.765f);
				glRotatef(-90.0f, 0, 1, 0);
				glScalef(curtainratio, 1.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, textureObjects[39]);
				glmDrawTransparency(model[55], GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE, 0.9);
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glPopName();
}

// Draw geometries
void drawGeometry() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, coffee);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glPushMatrix();
		glTranslatef(-189.69f, 50.0f, -81.53f);
		glScalef(160, 100, 30);
		drawCube();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-189.69f, 50.0f, 168.47f);
		glScalef(160, 100, 30);
		drawCube();
	glPopMatrix();
}