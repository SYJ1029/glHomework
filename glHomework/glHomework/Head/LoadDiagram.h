#pragma once

#include "GetShader.h"
#define SIZEMAKRO 200


#define MAX_INDEX 12
#define MAX_PERDIAGRAM 3
#define MAX_SLICE 300

#define ID_TRI 3
#define ID_RECT 4
#define ID_PENTA 5
#define ID_OCTA 6

#define PROJED true

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };
GL_Tri** tri = (GL_Tri**)malloc(MAX_PERDIAGRAM * sizeof(GL_Tri*));
Rect** rect = (Rect**)malloc(MAX_PERDIAGRAM * sizeof(Rect*));
Pentagon** pent = (Pentagon**)malloc(MAX_PERDIAGRAM * sizeof(Pentagon*));
GL_Line* line = new GL_Line();

GLUquadricObj* qobj = gluNewQuadric();


Diagram playground[3];





GL_Tri** slicedtri = (GL_Tri**)malloc(MAX_SLICE * sizeof(GL_Tri*));
Rect** slicedrect = (Rect**)malloc(MAX_SLICE * sizeof(Rect*));
Pentagon** slicedpent = (Pentagon**)malloc(MAX_SLICE * sizeof(Pentagon*));

int tri_slicedcnt = 0;
int rect_slicedcnt = 0;
int pent_slicedcnt = 0;


GLvoid InitDiagram() {
	for (int i = 0; i < MAX_PERDIAGRAM; i++) {
		tri[i] = new GL_Tri();
		rect[i] = new Rect();
		pent[i] = new Pentagon();
	}
}

GLvoid SetGraph(int index) {

	playground[index].center += {0, ((float)((float)rand() / RAND_MAX) * 0.4f - 0.2f), 0.0f};

	playground[index].speed = { -0.012f, 0.01f, 0.0f };
	playground[index].gravity = 0.0001f;
}

GLvoid Setplayground() {

	for (int i = 0; i < 3; i++) {

		playground[i].center = { 1.5f, 0.0f, 0.0f };

		playground[i].radian = { 0.0f, 0.0f, 0.0f };

		playground[i].indexcnt = (int)((float)rand() / RAND_MAX * 2 + 0.5f);
		SetGraph(i);
	}

	playground[0].postype = ID_TRI;

	playground[1].postype = ID_RECT;

	playground[2].postype = ID_PENTA;

}

GLvoid SetNewplayground(int i) {
	playground[i].center = { 1.5f, 0.0f, 0.0f };

	playground[i].radian = { 0.0f, 0.0f, 0.0f };

	playground[i].indexcnt = (int)((float)rand() / RAND_MAX +0.5f) ;

	SetGraph(i);

	playground[i].postype = ((float)((float)rand() / RAND_MAX) * 2) + 3.5f;
}

GLvoid MyMove(int value) {

	playground[value].speed.y -= playground[value].gravity;
	playground[value].center += playground[value].speed;


	if (playground[value].center.x <= -1.0 || playground[value].center.y <= -1.0) {
		SetNewplayground(value);
	}
	else
		glutTimerFunc(10, MyMove, value);
	glutPostRedisplay();
}


GLvoid IsobjsProjed(bool proj) {
	if (proj) {
		tri[0]->SetTranPos(SIZEMAKRO);
		rect[0]->SetTranPos(SIZEMAKRO);
	}

}






