// Draw.cpp
// Drawing components of the scene

#include "head.h"

// Declare model objects
GLMmodel* model[10];

GLUnurbsObj *nurbsobject;

int videoframe = 1;

static GLfloat ctlpoints[4][4][3];
static GLfloat tcoords[2][2][2] = { 0, 0, 0, 1, 1, 0, 1, 1 };

// Set model objects
void initObj() {
	model[0] = glmReadOBJ("models/sofa.obj");
	model[1] = glmReadOBJ("models/sofaleg.obj");
	model[2] = glmReadOBJ("models/plantleaf.obj");
	model[3] = glmReadOBJ("models/shell.obj");
	model[4] = glmReadOBJ("models/floor1.obj");
	model[5] = glmReadOBJ("models/floor2.obj");
	model[6] = glmReadOBJ("models/TVsurface.obj");
	model[7] = glmReadOBJ("models/door1.obj");
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

void drawObject() {
	glColor3f(1.0f, 1.0f, 1.0f);
	cout << textureObjectCnt << endl;
	// Draw models with texture. One texture for one model.
	//for (int ii = 0; ii < textureObjectCnt; ii++) {
	//	glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, textureObjects[ii]);
	//	glmDraw(model[ii], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	//	cout << ii << endl;
	//	glDisable(GL_TEXTURE_2D);
	//}
	// Draw models without texture
	glPushMatrix();
	glTranslatef(-39.169f, 93.1f, -340.861f);
	glmDraw(model[0], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-39.169f, 43.131f, -340.861f);
	glmDraw(model[1], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-38.341f, 60.182f, -56.79f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObjects[0]);
	glmDraw(model[2], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 150.0f, 1.062f);
	glmDraw(model[3], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 0.1f, 0.0f);
	glmDraw(model[4], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 15.0f, -280.914f);
	glmDraw(model[5], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(337.0f, 0.0f, 20.403f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObjects[1]);
	glmDraw(model[7], GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawVideo() {
	static int currenttime;
	static int timebase = 0;
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	if (currenttime - timebase > 200) {
		timebase = currenttime;
		if (videoframe == 5) {
			videoframe = 1;
		}
		else {
			videoframe++;
		}
	}
	glPushMatrix();
		glTranslatef(75.0f, 122.482f, 481.143f);
		glRotated(180, 0, 1, 0);
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
		drawObject();
	}
	else if (type == NURBS) {
		drawNurbs();
	}
	glEndList();
	return lid;
}

void drawTarget(GLfloat* center, GLfloat radius) {
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
	glDisable(GL_LIGHTING);					// ���ܵƹ�Ӱ��
	glMatrixMode(GL_PROJECTION);			// ѡ��ͶӰ����
	glPushMatrix();							// ����ԭ����
		glLoadIdentity();						// װ�뵥λ����
		glOrtho(-640, 640, -360, 360, -1, 1);	// ���òü�����
		glMatrixMode(GL_MODELVIEW);				// ѡ��Modelview����
		glPushMatrix();							// ����ԭ����
			glLoadIdentity();						// װ�뵥λ����
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
			glMatrixMode(GL_PROJECTION);			// ѡ��ͶӰ����
		glPopMatrix();							// ����Ϊԭ�������
		glMatrixMode(GL_MODELVIEW);				// ѡ��Modelview����
	glPopMatrix();							// ����Ϊԭ�������
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