// Draw.cpp
// Drawing components of the scene

#include "head.h"

// Declare model objects
GLMmodel* model[50];

GLUnurbsObj *nurbsobject;

static GLfloat ctlpoints[4][4][3];
static GLfloat tcoords[2][2][2] = { 0, 0, 0, 1, 1, 0, 1, 1 };

int videoframe = 0;

GLfloat openangle = 0;

// Set model objects
void initObj() {
	model[0] = glmReadOBJ("models/sofa.obj");
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
}

void init_nurbs_surface() {
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
	//cout << "textureObjectCnt: " << textureObjectCnt << endl;
	glPushName(SOFA);
	drawModel(0, 39.169f, -93.1f, 340.861f);
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
	drawModel(33, 52.448f, -266.0f, -91.872f, 26);
	glPopName();
	glPushName(UMBRELLA);
	drawModel(34, -290.15f, -29.981f, -128.367f, 28);
	glPopName();
	glPushName(FLOOR);
	drawModel(36, 0.0f, 0.0f, 0.0f, 25);
	glPopName();
}

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
		//GLfloat emission[4] = { 0.9f, 0.9f, 0.2f, 0.0f };
		//GLfloat noemission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
		glBindTexture(GL_TEXTURE_2D, textureObjects[texturenum]);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noemission);
		glmDraw(model[modelnum], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

void drawVideo() {
	static int currenttime;
	static int timebase = 0;
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	if (currenttime - timebase > 1000) {
		timebase = currenttime;
		if (videoframe == 5) {
			videoframe = 0;
		}
		else {
			videoframe++;
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

void drawNurbs() {
	glPushMatrix();
	glTranslatef(0.0f, 500.0f, 0.0f);
	glScalef(100.0f, 100.0f, 100.0f);
	draw_nurbs_surface();
	glPopMatrix();
}

void drawDoor() {
	cout << "openangle: " << openangle << endl;
	glPushName(DOORDOUBLE);
	drawModel(7, -337.0f, 0.0f, -20.403f, 1);
	drawModel(3, -337.0f, 0.0f, -100.403f, 1, GL_MODULATE, -openangle);
	drawModel(4, -337.0f, 0.0f, 60.403f, 1, GL_MODULATE, openangle);
	glPopName();
	if (openangle == 0) {
		glPushName(OPEN);
		drawModel(25, -340.608f, -146.535f, -28.236f, 19);
		glPopName();
		glPushName(ROPE);
		drawModel(28, -340.599f, -153.456f, -27.728f);
		glPopName();
		glPushName(STREW);
		drawModel(30, -339.517f, -165.745f, -28.184f);
		glPopName();
	}
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
	glDisable(GL_DEPTH_TEST);
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
	glEnable(GL_DEPTH_TEST);
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

void draw_nurbs_surface() {
	GLfloat knots[8] = { 0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0 };
	glEnable(GL_TEXTURE_2D);
	gluBeginSurface(nurbsobject);

	gluNurbsSurface(nurbsobject, 8, knots, 8, knots, 4 * 3, 3, &ctlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);

	gluEndSurface(nurbsobject);
	glDisable(GL_TEXTURE_2D);
}