#pragma once

#include "GetShader.h"
#define SIZEMAKRO 200


#define MAX_INDEX 12
#define MAX_PERDIAGRAM 3

#define ID_TRI 0
#define ID_RECT 1
#define ID_PENTA 2
#define ID_OCTA 3

#define PROJED true

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };
GL_Tri** tri = (GL_Tri**)malloc(MAX_PERDIAGRAM * sizeof(GL_Tri*));
Rect** rect = (Rect**)malloc(MAX_PERDIAGRAM * sizeof(Rect*));
Pentagon** pent = (Pentagon**)malloc(MAX_PERDIAGRAM * sizeof(Pentagon*));

GLUquadricObj* qobj = gluNewQuadric();



Diagram playground[3];

GLvoid InitDiagram() {
	for (int i = 0; i < MAX_PERDIAGRAM; i++) {
		tri[i] = new GL_Tri();
		rect[i] = new Rect();
		pent[i] = new Pentagon();
		//tri[i]->SetTranPos(200);
		//rect[i]->SetTranPos(200);
		//pent[i]->SetTranPos(200);
	}
}

GLvoid SetGraph(int index) {

	playground[index].center += {(float)((float)rand() / RAND_MAX) * 400, ((float)((float)rand() / RAND_MAX) * 800) - 150.0f, 0.0f};

	playground[index].speed = { -20.0f, 10.0f, 0.0f };
	playground[index].gravity = 0.2f;
}

GLvoid Setplayground() {

	for (int i = 0; i < 3; i++) {

		playground[i].center = { 1300.0f, 0.0f, 0.0f };

		playground[i].radian = { 0.0f, 0.0f, 0.0f };

		playground[i].indexcnt = (int)((float)rand() / RAND_MAX * 2 + 0.5f);
		SetGraph(i);
	}

	playground[0].postype = ID_TRI;

	playground[1].postype = ID_RECT;

	playground[2].postype = ID_TRI;

}

GLvoid SetNewplayground(int i) {
	playground[i].center = { 1200.0f, 0.0f, 0.0f };

	playground[i].radian = { 0.0f, 0.0f, 0.0f };

	playground[i].indexcnt = (int)((float)rand() / RAND_MAX + 0.5f);

	SetGraph(i);

	playground[i].postype = ((float)((float)rand() / RAND_MAX) * 2) + 0.5;
}

GLvoid MyMove(int value) {

	playground[value].speed.y -= playground[value].gravity;
	playground[value].center += playground[value].speed;


	if (playground[value].center.x <= -1300 || playground[value].center.y <= -1300);
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


