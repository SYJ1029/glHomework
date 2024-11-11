#pragma once

#include "../ObjStruct.h"


class Camera {
private:
	glm::vec3 EYE;
	glm::vec3 AT;
	glm::vec3 UP;
public:


	Camera() {
		EYE = glm::vec3(0.0f);
		AT = glm::vec3(0.0f);
		UP = glm::vec3(0.0f);
	}

	Camera(glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP) {
		this->EYE = EYE;
		this->AT = AT;
		this->UP = UP;
	}


	glm::mat4 GetViewMatix() {
		glm::mat4 view = glm::lookAt(EYE, AT, UP);

		return view;
	}

	void MoveViewPos(glm::vec3 EYE) {
		this->EYE += EYE;
	}

	void MoveViewDirect(glm::vec3 AT) {
		this->AT += AT;
	}

	void MoveUpVector(glm::vec3 UP) {
		this->UP += UP;
	}
};