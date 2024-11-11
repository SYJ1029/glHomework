#pragma once

#include "../ObjStruct.h"

#define PROJ_ORTHO 0
#define PROJ_PERSPECTIVE 1

class Projection {

public:
	int projType;

	float left; 
	float right;
	float bottom; 
	float top; 
	float nearOrtho;
	float farOrtho;

	float fovy;
	float aspect;
	float nearper;
	float farper;


	Projection() {
		projType = PROJ_PERSPECTIVE;

		left = 0.0f;
		right = 0.0f;
		bottom = 0.0f;
		top = 0.0f;
		nearOrtho = 0.0f;
		farOrtho = 0.0f;

		fovy = 0.0f;
		aspect = 0.0f;
		nearper = 0.0f;
		farper = 0.0f;
	}



	GLvoid InitOrtho(float left, float right, float top, float bottom, float nearOrtho, float farOrtho) {
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
		this->nearOrtho = nearOrtho;
		this->farOrtho = farOrtho;

		projType = PROJ_ORTHO;
	}

	GLvoid InitPerspective(float fovy, float aspect, float nearper, float farper) {
		this->fovy = fovy;
		this->aspect = aspect;
		this->nearper = nearper;
		this->farper = farper;

		projType = PROJ_PERSPECTIVE;
	}


	glm::mat4 GetProjMatrix() {
		glm::mat4 projection = glm::mat4(1.0f);
		if (projType == PROJ_ORTHO) {
			projection = glm::ortho(left, right, bottom, top, nearOrtho, farOrtho);
		}
		else {
			projection = glm::perspective(fovy, aspect, nearper, farper);
		}

		return projection;
	}

};
