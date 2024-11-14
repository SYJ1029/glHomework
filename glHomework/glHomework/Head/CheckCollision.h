#pragma once


#include "LoadDiagram.h"




int CompareyPos(GLfloat y, GLPos pos) {

	if (pos.y > y) return 1;
	if (pos.y == y) return 0;
	if (pos.y < y) return -1;

	
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

void CheckingLoop(float theta, GLPos line1, GLPos line2) {

	GLPos poses[5];
	GLPos token;
	GLPos linetoken;
	GLPos Opos = { 0.0f, 0.0f, 0.0f };
	int upordown[5];

	list<GLPos> uplist;
	list<GLPos> bottomlist;

	for (int i = 0; i < 3; i++) {



		switch (playground[i].postype) {
		case ID_TRI:



			for (int j = 0; j < 3; j++) {
				token = { tri[0]->pos[j][0], tri[0]->pos[j][1], tri[0]->pos[j][2] };



				poses[j] = Spin(-1 * theta, token, Opos);
				linetoken = line1 + playground[i].center;
				poses[j] *= tri[0]->Stretch;

				//if (poses[j].x <= GetMax(line1, line2).x && poses[j].x >= GetMin(line1, line2).x);
				//else continue;




				upordown[j] = CompareyPos(linetoken.y, poses[j]);

				if (upordown[j] < 0)
					uplist.push_back(poses[j]);
				if (upordown[j] > 0)
					bottomlist.push_back(poses[j]);


			
			}


			break;
		case ID_RECT:
			for (int j = 0; j < 4; j++) {
				token = { rect[0]->pos[j][0], rect[0]->pos[j][1], rect[0]->pos[j][2] };
				poses[j] = Spin(-1 * theta, token, Opos);
				linetoken = line1 + playground[i].center;
				poses[j] *= rect[0]->Stretch;


				//if (poses[j].x > GetMax(line1, line2).x || poses[j].x < GetMin(line1, line2).x)
				//	break;

				upordown[j] = CompareyPos(linetoken.y, poses[j]);

				if (upordown[j] > 0)
					uplist.push_back(poses[j]);
				if (upordown[j] < 0)
					bottomlist.push_back(poses[j]);



			}
			break;
		case ID_PENTA:
			for (int j = 0; j < 5; j++) {
				token = { pent[0]->pos[i][0], pent[0]->pos[i][1], pent[0]->pos[i][2] };
				poses[j] = Spin(-1 * theta, token, Opos);
				linetoken = line1 + playground[i].center;
				poses[j] *= pent[0]->Stretch;

				//if (poses[j].x > GetMax(line1, line2).x || poses[j].x < GetMin(line1, line2).x)
				//	break;

				upordown[i] = CompareyPos(linetoken.y, poses[i]);

				if (upordown[i] > 0)
					uplist.push_back(poses[i]);
				else if (upordown[i] < 0)
					bottomlist.push_back(poses[i]);



			}
			break;
		default:
			break;
		}

		if (uplist.empty() || bottomlist.empty());
		else {
			cout << i+1 << "번째 " << playground[i].postype + 3 << "각형 교차합니다" << endl;
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
