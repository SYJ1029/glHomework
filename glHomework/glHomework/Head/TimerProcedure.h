#pragma once

#include "VertexMethod.h"



GLPos InitDelta(GLPos pos, GLPos target) {
	GLPos result = { 0 };
	GLPos line = (target - pos) / dist(pos, target);

	line = line / 50.0f;
	result += line;


	return result;
}

GL_Rect Getbb(GLPos center, GLPos target) {
	GL_Rect result = { {0}, {0} };

	if (center.x >= target.x)
		result.pos1.x = target.x, result.pos2.x = center.x;
	else
		result.pos2.x = target.x, result.pos1.x = center.x;

	if (center.y >= target.y)
		result.pos1.y = target.y, result.pos2.y = center.y;
	else
		result.pos2.y = target.y, result.pos1.y = center.y;

	if (center.z >= target.z)
		result.pos1.z = target.z, result.pos2.z = center.z;
	else
		result.pos2.z = target.z, result.pos1.z = center.z;


	return result;
}