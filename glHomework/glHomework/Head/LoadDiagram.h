#pragma once

#include "GetShader.h"
#define SIZEMAKRO 200

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };
GL_Cube* cube = new GL_Cube;
GL_Tetrahedron* tri = new GL_Tetrahedron;
GL_Pyramid* pyr = new GL_Pyramid;
GL_Sphere* sphere = new GL_Sphere;
GL_Cylinder* cyl = new GL_Cylinder;
GL_Cylinder* cone = new GL_Cylinder;

GLUquadricObj* qobj = gluNewQuadric();


GLvoid IsobjsProjed(bool proj) {
	if (proj) {
		cube->SetTranPos(SIZEMAKRO);
		tri->SetTranPos(SIZEMAKRO);
		pyr->SetTranPos(SIZEMAKRO);
	}



}