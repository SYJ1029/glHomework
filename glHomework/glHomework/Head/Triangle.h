#pragma once

#include "GetShader.h"

using namespace std;

#define TYPE_DOT 1
#define TYPE_LINE 2
#define CHANGESPIN 140

float basetheta = 20;



class Spiral {
private:
	int posType;
public:
	GLfloat pos[3];
	GLfloat col[3];
	GLfloat axis[3], Reverseaxis[3];
	int cnt;
	int nowcnt;
	int mulcount;
	float radian, theta;
	float r;
	bool maked;
	bool Reversed;


	bool Clear() {
		posType = TYPE_DOT;
		for (int j = 0; j < 3; j++) {
			pos[j] = 0;
			axis[j] = 0;
			Reverseaxis[j] = 0;
			col[j] = 0.5;
		}
		r = 0.0f;

		maked = false;
		Reversed = false;
		radian = 0, theta = 0;
		cnt = 1, mulcount = 1;
		nowcnt = 0;

		return true;
	}

	Spiral() {
		Clear();
	}

	int GetposType() {
		return posType;
	}

	void SetposType(int postype) {
		this->posType = postype;
	}

	void SetCol(MyObjCol col) {
		this->col[0] = col.R;
		this->col[1] = col.G;
		this->col[2] = col.B;
	}

	void SetVertex(GLPos newpos) {
		pos[0] = newpos.x;
		pos[1] = newpos.y;
		pos[2] = newpos.z;

		axis[0] = pos[0];
		axis[1] = pos[1];
		axis[2] = pos[2];


	}

	bool Settheta(float radian) {
		theta = radian;

		if (radian < 0)
			mulcount = -1;
		else
			mulcount = 1;

		cnt = 1;
		return true;
	}

	bool SetPos(GLPos newpos) {
		SetVertex(newpos);

		return true;
	}

	bool AdjustwithRadian() {
		if (nowcnt < CHANGESPIN) {
			pos[0] -= axis[0];
			pos[1] -= axis[1];

			pos[0] = r * cos(radian / 180);
			pos[1] = r * sin(radian / 180);

			pos[0] += axis[0];
			pos[1] += axis[1];
		}
		else if(Reverseaxis[0] != 0.0f || Reverseaxis[1] != 0.0f) {


			pos[0] -= Reverseaxis[0];
			pos[1] -= Reverseaxis[1];

			pos[0] = r * cos(radian / 180);
			pos[1] = r * sin(radian / 180);

			pos[0] += Reverseaxis[0];
			pos[1] += Reverseaxis[1];
		}

		return true;
	}


	float dist(float x1, float x2, float y1, float y2) {
		float token = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

		return sqrt(token);
	}

	bool Reverse() {
		if (Reversed)
			return false;

		if (nowcnt >= CHANGESPIN) {
			Reverseaxis[0] = axis[0];
			Reverseaxis[1] = axis[1];

			Reverseaxis[0] -= pos[0];
			Reverseaxis[1] -= pos[1];

			Reverseaxis[0] *= -1;
			Reverseaxis[1] *= -1;

			Reverseaxis[0] += pos[0];
			Reverseaxis[1] += pos[1];

			Reversed = true;
			return true;
		}


		return false;
	}

	float normalize(int num) {

		if (num <= 0)
			return -1;
		

		return 1;
	}

	void Move() {

		

		radian += theta * normalize(CHANGESPIN - nowcnt);

		r += theta * (normalize(CHANGESPIN - nowcnt) / 25000);

		if (normalize(CHANGESPIN - nowcnt) < 0) {
			radian += 570;
		}
		AdjustwithRadian();
		if (normalize(CHANGESPIN - nowcnt) < 0) {
			radian -= 570;
		}
		


		if (Reverse()) {
			cout << " is Reversed!!!" << endl << endl;
		}

		/*cout << "r: " << r << ", radian: " << radian << ", theta" << theta << endl << endl;*/
		nowcnt++;
		
	}

	void Revert() {
		for (int i = 0; i < 3; i++) {
			pos[i] = axis[i];
		}

		if (theta < 0)
			theta = basetheta * -1;
		else
			theta = basetheta;
		radian = theta;
		r = 0;
		nowcnt = 0;
	}

};

