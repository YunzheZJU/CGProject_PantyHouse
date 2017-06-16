// Draw.cpp
// Drawing components of the scene

#include "head.h"

// Declare model objects
GLMmodel* model[50];

GLUnurbsObj *nurbsobject;

int videoframe = 0;

static GLfloat ctlpoints[4][4][3];
static GLfloat tcoords[2][2][2] = { 0, 0, 0, 1, 1, 0, 1, 1 };

// Set model objects
void initObj() {
	model[0] = glmReadOBJ("models/sofa.obj");
	model[1] = glmReadOBJ("models/sofaleg.obj");
	model[2] = glmReadOBJ("models/plantleaf.obj");
	model[11] = glmReadOBJ("models/plantmain.obj");
	model[12] = glmReadOBJ("models/plantflower.obj");
	model[3] = glmReadOBJ("models/shell.obj");
	model[4] = glmReadOBJ("models/floor1.obj");
	model[5] = glmReadOBJ("models/floor2.obj");
	model[6] = glmReadOBJ("models/TVsurface.obj");
	model[7] = glmReadOBJ("models/door1.obj");
	model[8] = glmReadOBJ("models/squaredesk.obj");
	model[9] = glmReadOBJ("models/glassboard.obj");
	model[10] = glmReadOBJ("models/shelf.obj");
	model[13] = glmReadOBJ("models/gardenleaf.obj");
	model[14] = glmReadOBJ("models/gardenmain.obj");
	model[15] = glmReadOBJ("models/swing.obj");
	model[16] = glmReadOBJ("models/window.obj");
	model[17] = glmReadOBJ("models/garden.obj");
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
	cout << "textureObjectCnt: " << textureObjectCnt << endl;

	drawModel(0, 39.169f, -93.1f, 340.861f);

	drawModel(1, 39.169f, -43.131f, 340.861f, 5);

	drawModel(2, 38.341f, -60.182f, 56.79f, 0, GL_REPLACE);
	drawModel(11, 35.509f, -48.121f, 61.799f, 6, GL_REPLACE);
	drawModel(12, 31.38f, -25.635f, 57.706f, 7, GL_REPLACE);

	drawModel(3, 0.0f, -150.0f, -1.062f);

	drawModel(4, -1.0f, -0.1f, 0.0f);

	drawModel(5, 0.0f, -15.0f, 280.914f);

	drawModel(7, -337.0f, 0.0f, -20.403f, 1);

	drawModel(8, 169.754f, -35.096f, -440.152f, 2);
	drawModel(8, 169.754f, -35.096f, -344.282f, 2);
	drawModel(8, 169.754f, -35.096f, -248.412f, 2);

	drawModel(9, 128.44f, -43.75f, -43.47f, 3);

	drawModel(10, -315.612f, -130.0f, 300.0f, 4);

	drawModel(13, -279.904f, -21.351f, -323.509f, 8, GL_REPLACE);
	drawModel(14, -275.286f, -15.766f, -322.688f, 9, GL_REPLACE);

	drawModel(15, -371.593f, -101.526f, -358.718f, 10);

	glPushMatrix();
	drawModel(16, 195.306f, -176.866f, 494.763f, 11, GL_MODULATE, 90);
	glPopMatrix();
	drawModel(16, -4.694f, -176.866f, 494.763f, 11, GL_MODULATE, 90);
	drawModel(16, -204.694f, -176.866f, 494.763f, 11, GL_MODULATE, 90);
	drawModel(16, -226.863f, -176.866f, -288.768f, 11);

	drawModel(17, -279.52f, -6.474f, -326.062f, 12);
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
		glTranslatef(75.0f, 122.482f, 481.143f);
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

GLint genDisplayList(int type) {
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
	if (type == SCENE) {
		drawScene();
	}
	else if (type == NURBS) {
		drawNurbs();
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