#pragma once

#include "GetShader.h"
#define SIZEMAKRO 200

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };
GL_Tri* tri = new GL_Tri();
Rect* rect = new Rect();

GLUquadricObj* qobj = gluNewQuadric();


GLvoid IsobjsProjed(bool proj) {
	if (proj) {
		tri->SetTranPos(SIZEMAKRO);
		rect->SetTranPos(SIZEMAKRO);
	}

}