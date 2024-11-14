#pragma once


#include "LoadDiagram.h"




int CompareyPos(GLfloat y, GLfloat y2) {

	if (y2 > y) return 1;
	if (y2 == y) return 0;
	if (y2 < y) return -1;

	
	return INFINITY;
}




float GetTheta(GLPos linepos1, GLPos linepos2 ) {


	float theta = glm::atan((linepos2.y - linepos1.y), (linepos2.x - linepos1.x));


	return theta;
}


GLPos Spin(float theta, GLPos& pos, GLPos& pos2) {


	pos -= pos2;

	pos = { pos.x * glm::cos(theta) - pos.y * glm::sin(theta), 
		pos.x * glm::sin(theta) + pos.y * glm::cos(theta), 
		0.0f 
	};

	pos += pos2;

	return pos;
}

GLPos GetMax(GLPos pos1, GLPos pos2) {
	if (pos1.x >= pos2.x)
		return pos1;

	return pos2;
}

GLPos GetMin(GLPos pos1, GLPos pos2) {
	if (pos1.x <= pos2.x)
		return pos1;


	return pos2;
}


GLPos GetDot(GL_Rect line, float cnt) {
	GLPos result = { 0.0f };
	GLPos middlepos = { 0.0f, 0.0f, 0.0f };
	GLPos prevpos = { 1.0f, 1.0f, 1.0f };

	float xradius = line.pos2.x - line.pos2.x;
	float yradius = line.pos2.y - line.pos1.y;

	int judge[2] = { 0, 0 };

	for (float t = 0.0f; t < 1.0f; t += 0.01f) {
		middlepos = { line.pos1.x + xradius * t, line.pos1.y + yradius * t, 0.0f};

		judge[0] = CompareyPos(cnt, middlepos.y);
		judge[1] = CompareyPos(cnt, prevpos.y);


		if (judge[0] != judge[1]) {
			result = (middlepos - prevpos) / 2 + prevpos;
			return result;
		}

		prevpos = middlepos;
	}


	return { -2.0f, -2.0f, -2.0f };
}

GL_Rect GetCrossDots(GL_Rect line1, GL_Rect line2, float cnt) {
	GL_Rect result = { {0.0f}, {0.0f} };


	result.pos1 = GetDot(line1, cnt);
	result.pos2 = GetDot(line2, cnt);

	// 중간 검사 문항 넣기


	return result;
}


void CheckingLoop(float theta, GLPos line1, GLPos line2) {

	GLPos poses[5];
	GLPos token;
	GLPos linetoken;
	GLPos Opos = { 0.0f, 0.0f, 0.0f };
	int upordown[5];

	list<int> uplist;
	list<int> bottomlist;
	

	for (int i = 0; i < 3; i++) {


		if (playground[i].center.x >= -1.0f && playground[i].center.x <= 1.0f &&
			playground[i].center.y >= -1.0f && playground[i].center.y <= 1.0f);
		else continue;

		switch (playground[i].postype) {
		case ID_TRI:



			for (int j = 0; j < 3; j++) {
				poses[j] = {tri[0]->pos[j][0], tri[0]->pos[j][1], tri[0]->pos[j][2]};


				poses[j] *= tri[0]->Stretch;
				poses[j] += playground[i].center;
				poses[j] = Spin(-1 * theta, poses[j], line2);

				//if (poses[j].x <= GetMax(line1, line2).x && poses[j].x >= GetMin(line1, line2).x);
				//else continue;




				upordown[j] = CompareyPos(line1.y, poses[j].y);

				if (upordown[j] > 0)
					uplist.push_back(j);
				if (upordown[j] < 0)
					bottomlist.push_back(j);


			
			}


			break;
		case ID_RECT:
			for (int j = 0; j < 4; j++) {
				poses[j] = {rect[0]->pos[j][0], rect[0]->pos[j][1], rect[0]->pos[j][2]};
				poses[j] += playground[i].center;
				poses[j] = Spin(-1 * theta, poses[j], line2);


				//if (poses[j].x > GetMax(line1, line2).x || poses[j].x < GetMin(line1, line2).x)
				//	break;

				upordown[j] = CompareyPos(line1.y, poses[j].y);

				if (upordown[j] > 0)
					uplist.push_back(j);
				if (upordown[j] < 0)
					bottomlist.push_back(j);



			}
			break;
		case ID_PENTA:
			for (int j = 0; j < 5; j++) {
				poses[j] = {pent[0]->pos[j][0], pent[0]->pos[j][1], pent[0]->pos[j][2]};
				poses[j] *= pent[0]->Stretch;
				poses[j] += playground[i].center;
				poses[j] = Spin(-1 * theta, poses[j], line2);

				//if (poses[j].x > GetMax(line1, line2).x || poses[j].x < GetMin(line1, line2).x)
				//	break;

				upordown[j] = CompareyPos(line1.y, poses[j].y);

				if (upordown[j] > 0)
					uplist.push_back(j);
				else if (upordown[j] < 0)
					bottomlist.push_back(j);


			}
			break;
		default:
			break;
		}

		if (uplist.empty() || bottomlist.empty());
		else {

			cout << i + 1 << "번째 " << playground[i].postype + 3 << "각형 교차합니다" << endl;

			GL_Rect bline;
			GL_Rect eline;
			GL_Rect lineRect;

			bline = { poses[uplist.back()], poses[bottomlist.front()]};
			eline = { poses[bottomlist.back()], poses[uplist.front()] };
			
			//if (bottomlist.front() == 0) {
			//	lineRect = bline;
			//	bline = eline;
			//	eline = lineRect;

			//}


			lineRect = GetCrossDots(bline, eline, line1.y);

			cout << "(" << lineRect.pos1.x << ", " << lineRect.pos1.y << "), "
				<< "(" << lineRect.pos2.x << ", " << lineRect.pos2.y << ")" << endl;
			 
		}


		uplist.clear();
		bottomlist.clear();

	}

}

void CheckCollision() {

	GLPos newpos1, newpos2;


	newpos1 = {line->pos[0][0], line->pos[0][1], line->pos[0][2]};

	newpos2 = { line->pos[1][0], line->pos[1][1], line->pos[1][2] };
	
	float theta = GetTheta(newpos1, newpos2);





	newpos1 = Spin(-1 * theta, newpos1, newpos2);


	cout<< (float)(newpos1.y) << ", " <<  (float)(newpos2.y) << endl;


	CheckingLoop(theta, newpos1, newpos2);


}
