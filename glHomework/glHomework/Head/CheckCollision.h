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


GLPos GetDot(GL_Rect line, float cnt, float delta) {
	GLPos result = { 0.0f };
	GLPos middlepos = { 0.0f, 0.0f, 0.0f };
	GLPos prevpos = { 2.0f, 1.0f, 1.0f };

	float xradius = line.pos2.x - line.pos1.x;
	float yradius = line.pos2.y - line.pos1.y;

	int judge[2] = { 0, 0 };


	prevpos = line.pos1;
	for (float t = delta; t <= 1.0f; t += delta) {
		middlepos = { line.pos1.x + xradius * t, line.pos1.y + yradius * t, 0.0f};

		judge[0] = CompareyPos(cnt, middlepos.y);
		judge[1] = CompareyPos(cnt, prevpos.y);


		if (judge[0] != judge[1]) {
			result = (middlepos - prevpos) / 2 + prevpos;

			if (delta < 0.02)
				return result;
			else
				return GetDot({ prevpos, middlepos }, cnt, delta / 2);
		}

		prevpos = middlepos;
	}


	return GetDot(line, cnt, delta / 2);
}

GL_Rect GetCrossDots(GL_Rect line1, GL_Rect line2, float cnt) {

	GLPos pos1 = GetDot(line1, cnt, 0.1);
	GLPos pos2 = GetDot(line2, cnt, 0.1);





	return { pos1, pos2 };
}


void CheckingLoop(float theta, GLPos line1, GLPos line2) {

	GLPos poses[5];
	GLPos token;
	GLPos linetoken;
	GLPos Opos = { 0.0f, 0.0f, 0.0f };
	int upordown[5];

	list<int> uplist;
	list<int> bottomlist;
	
	int cnt;

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

			cout << i + 1 << "번째 " << playground[i].postype << "각형 교차합니다" << endl;

			GL_Rect bline;
			GL_Rect eline;
			GL_Rect lineRect;

			if ((uplist.front() == 0 && bottomlist.front() == 1) ||
				bottomlist.front() == 0 && uplist.front() == 1) {
				eline = { poses[uplist.back()], poses[bottomlist.back()] };
				bline = { poses[bottomlist.front()], poses[uplist.front()] };
			}
			else {
				eline = { poses[uplist.back()], poses[bottomlist.front()] };
				bline = { poses[bottomlist.back()], poses[uplist.front()] };
			}
			
			//if (bottomlist.front() == 0) {
			//	lineRect = bline;
			//	bline = eline;
			//	eline = lineRect;

			//}

		

			lineRect = GetCrossDots(bline, eline, line1.y);

			if (lineRect.pos1 > 1.0f || lineRect.pos1 < -1.0f || lineRect.pos2 > 1.0f || lineRect.pos2 < -1.0f) {
				cout << "<<<<<somthing wrong>>>>>" << endl;
			}
			else {



				if (lineRect.pos1.x > lineRect.pos2.x) {
					token = lineRect.pos1;
					lineRect.pos1 = lineRect.pos2;
					lineRect.pos2 = token;
				}

				lineRect.pos1 = Spin(theta, lineRect.pos1, line2);
				lineRect.pos2 = Spin(theta, lineRect.pos2, line2);

				lineRect.pos1 -= playground[i].center;
				lineRect.pos2 -= playground[i].center;

				cout << "(" << lineRect.pos1.x << ", " << lineRect.pos1.y << "), "
					<< "(" << lineRect.pos2.x << ", " << lineRect.pos2.y << ")" << endl;

				GLPos* uppos;
				GLPos* bottompos;
				
				switch (uplist.size() + 2) {
				case ID_TRI:
					cout << "3" << endl;
					uppos = (GLPos*)malloc(3 * sizeof(GLPos));

					for (cnt = 0; uplist.empty() == false; cnt++) {
						uppos[cnt].x = tri[0]->pos[uplist.front()][0];
						uppos[cnt].y = tri[0]->pos[uplist.front()][1];
						uppos[cnt].z = tri[0]->pos[uplist.front()][2];

						uplist.pop_front();
					}

					uppos[cnt] = lineRect.pos1;
					uppos[cnt + 1] = lineRect.pos2;

					for (cnt = 0; cnt < tri_slicedcnt; cnt++) {
						if (slicedtri[cnt]->draw == false)
							break;
					}

					slicedtri[cnt] = new GL_Tri(uppos);
					slicedtri[cnt]->Setcol(tri[playground[i].indexcnt]->col);
					
					slicedtri[cnt]->center = playground[i].center;

					slicedtri[cnt]->speed = { -0.01f, 0.005f, 0.0f };
					slicedtri[cnt]->gravity = 0.0001f;

					if(cnt >= tri_slicedcnt)
						tri_slicedcnt++;


					glutTimerFunc(system_time, MoveSlicedtri, cnt);
					break;
				case ID_RECT:
					cout << "4" << endl;
					uppos = (GLPos*)malloc(4 * sizeof(GLPos));

					for (cnt = 0; uplist.empty() == false; cnt++) {
						uppos[cnt].x = rect[0]->pos[uplist.front()][0];
						uppos[cnt].y = rect[0]->pos[uplist.front()][1];
						uppos[cnt].z = rect[0]->pos[uplist.front()][2];

						uplist.pop_front();
					}

					uppos[cnt] = lineRect.pos1;
					uppos[cnt + 1] = lineRect.pos2;

					for (cnt = 0; cnt < rect_slicedcnt; cnt++) {
						if (slicedrect[cnt]->draw == false)
							break;
					}

					slicedrect[cnt] = new Rect(uppos);
					slicedrect[cnt]->Setcol(rect[playground[i].indexcnt]->col);

					slicedrect[cnt]->center = playground[i].center;

					slicedrect[cnt]->speed = { -0.01f, 0.005f, 0.0f };
					slicedrect[cnt]->gravity = 0.0001f;

					if(cnt >= rect_slicedcnt)
						rect_slicedcnt++;

					glutTimerFunc(system_time, MoveSlicedrect, cnt);
					break;
				case ID_PENTA:
					cout << "5" << endl;
					uppos = (GLPos*)malloc(5 * sizeof(GLPos));

					for (cnt = 0; uplist.empty() == false; cnt++) {
						uppos[cnt].x = pent[0]->pos[uplist.front()][0];
						uppos[cnt].y = pent[0]->pos[uplist.front()][1];
						uppos[cnt].z = pent[0]->pos[uplist.front()][2];

						uplist.pop_front();
					}

					uppos[cnt] = lineRect.pos1;
					uppos[cnt + 1] = lineRect.pos2;
					

					for (cnt = 0; cnt < pent_slicedcnt; cnt++){
						if (slicedpent[cnt]->draw == false)
							break;
					}



					slicedpent[cnt] = new Pentagon(uppos);
					slicedpent[cnt]->Setcol(pent[playground[i].indexcnt]->col);
					
					slicedpent[cnt]->center = playground[i].center;

					slicedpent[cnt]->speed = { -0.01f, 0.005f, 0.0f };
					slicedpent[cnt]->gravity = 0.0001f;


					if(cnt >= pent_slicedcnt)
						pent_slicedcnt++;

					glutTimerFunc(system_time, MoveSlicedpent, cnt);

					break;
				case ID_OCTA:
					cout << "6" << endl;
					uppos = (GLPos*)malloc(6 * sizeof(GLPos));


					break;
				default:					
					cout << "<<< Strange ID >>>" << endl;
					break;
				}




				switch (bottomlist.size() + 2) {
				case ID_TRI:
					cout << "3" << endl;
					bottompos = (GLPos*)malloc(3 * sizeof(GLPos));

					for (cnt = 0; bottomlist.empty() == false; cnt++) {
						bottompos[cnt] = { tri[0]->pos[bottomlist.front()][0], tri[0]->pos[bottomlist.front()][1], tri[0]->pos[bottomlist.front()][2] };


						bottomlist.pop_front();
					}

					bottompos[cnt] = lineRect.pos2;
					bottompos[cnt + 1] = lineRect.pos1;

					for (cnt = 0; cnt < tri_slicedcnt; cnt++) {
						if (slicedtri[cnt]->draw == false)
							break;
					}

					slicedtri[cnt] = new GL_Tri(bottompos);
					slicedtri[cnt]->Setcol(tri[playground[i].indexcnt]->col);

					slicedtri[cnt]->center = playground[i].center;

					slicedtri[cnt]->speed = { 0.01f, 0.005f, 0.0f };
					slicedtri[cnt]->gravity = 0.0001f;

					if (cnt >= tri_slicedcnt)
						tri_slicedcnt++;

					glutTimerFunc(system_time, MoveSlicedtri, cnt);
					break;
				case ID_RECT:
					cout << "4" << endl;
					bottompos = (GLPos*)malloc(4 * sizeof(GLPos));

					for (cnt = 0; bottomlist.empty() == false; cnt++) {
						bottompos[cnt] = { rect[0]->pos[bottomlist.front()][0], rect[0]->pos[bottomlist.front()][1], rect[0]->pos[bottomlist.front()][2] };


						bottomlist.pop_front();
					}

					bottompos[cnt] = lineRect.pos2;
					bottompos[cnt + 1] = lineRect.pos1;

					for (cnt = 0; cnt < rect_slicedcnt; cnt++) {
						if (slicedrect[cnt]->draw == false)
							break;
					}

					slicedrect[cnt] = new Rect(bottompos);
					slicedrect[cnt]->Setcol(rect[playground[i].indexcnt]->col);

					slicedrect[cnt]->center = playground[i].center;

					slicedrect[cnt]->speed = { 0.01f, 0.005f, 0.0f };
					slicedrect[cnt]->gravity = 0.0001f;

					if (cnt >= rect_slicedcnt)
						rect_slicedcnt++;

					glutTimerFunc(system_time, MoveSlicedrect, cnt);
					break;
				case ID_PENTA:
					cout << "5" << endl;
					bottompos = (GLPos*)malloc(5 * sizeof(GLPos));

					for (cnt = 0; bottomlist.empty() == false; cnt++) {
						bottompos[cnt] = { pent[0]->pos[bottomlist.front()][0], pent[0]->pos[bottomlist.front()][1], pent[0]->pos[bottomlist.front()][2] };

						bottomlist.pop_front();
					}

					for (cnt = 0; cnt < pent_slicedcnt; cnt++) {
						if (slicedpent[cnt]->draw == false)
							break;
					}

					bottompos[cnt] = lineRect.pos2;
					bottompos[cnt + 1] = lineRect.pos1;

					slicedpent[cnt] = new Pentagon(bottompos);
					slicedpent[cnt]->Setcol(pent[playground[i].indexcnt]->col);

					slicedpent[cnt]->center = playground[i].center;

					slicedpent[cnt]->speed = { -0.01f, 0.005f, 0.0f };
					slicedpent[cnt]->gravity = 0.0001f;


					if (cnt >= pent_slicedcnt)
						pent_slicedcnt++;

					glutTimerFunc(system_time, MoveSlicedpent, cnt);
					break;
				case ID_OCTA:
					cout << "6" << endl;
					bottompos = (GLPos*)malloc(6 * sizeof(GLPos));


					break;
				default:
					cout << "<<< Strange ID >>>" << endl;
					break;

					free(uppos);
					free(bottompos);
				}


				playground[i].center = { -1.5f, -1.5f, 0.0f };
			}
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
