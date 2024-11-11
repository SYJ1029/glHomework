#pragma once

#include "../VertexMethod.h"


glm::mat4 InitMoveProj(GLPos delta) {
	glm::mat4 result = glm::mat4(1.0);

	result *= GetMove(delta);

	return result;
}


glm::mat4 InitRotateProj(GLPos radian, GLPos center) {
	glm::mat4 result = glm::mat4(1.0);

	result *= GetSpin(center, radian.x, glm::vec3(1.0f, 0.0f, 0.0f));
	result *= GetSpin(center, radian.y, glm::vec3(0.0f, 1.0f, 0.0f));
	result *= GetSpin(center, radian.z, glm::vec3(0.0f, 0.0f, 1.0f));


	return result;
}


glm::mat4 InitScaleProj(GLPos Stretch) {
	glm::mat4 result = glm::mat4(1.0);


	result *= ChangeScale(Stretch, { 0.0f, 0.0f, 0.0f });


	return result;
}