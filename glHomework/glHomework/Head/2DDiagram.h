#pragma once


#include "TimerProcedure.h"
#include "ProjMethod.h"
#include "CheckPointQue.h"

#define POINT 0

class Diagram {



public:
	int postype;
	glm::vec3 axis;
	glm::vec3 OrbitAxis;
	GLPos center;
	GLPos target;
	GLPos radian;
	int indexcnt;
	GLPos delta;
	GLPos speed;
	GLfloat gravity;
	bool ccw;


	GLfloat col[3];
	QuadSetting qset;


	queue<GLPos> fifo;

	Diagram() {

		postype = POINT;

		radian = { 0 };
		center = { 0, 0, 0 };
		target = { 0, 0, 0 };
		axis = glm::vec3(0.0f, 1.0f, 0.0f);
		OrbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		delta = { 0, 0, 0 };

		for (int i = 0; i < 3; i++) {
			col[i] = 0.0f;
		}

		indexcnt = 0;

		for (int i = 0; i < 3; i++) {
			speed = { 0.0f };
		}

		gravity = 1.0f;
		ccw = true;



		qset.drawstyle = GLU_FILL;
		qset.normals = GLU_SMOOTH;
		qset.orientation = GLU_OUTSIDE;
	}


	void Setother_center(GLPos center) {
		target = center;
	}

	GLfloat GetDist() {

		return dist(center, target);
	}

	GLPos AxisToGLPos() {
		return Vec3ToGLPos(axis);
	}




	bool GetCrash(GLPos token, GLPos target) {
		GLPos prev = center + token;
		GL_Rect newtoken = Getbb(prev, center);

		return (target.x >= newtoken.pos1.x && target.x <= newtoken.pos2.x) &&
			(target.y <= newtoken.pos2.y && target.y >= newtoken.pos1.y) &&
			(target.z >= newtoken.pos2.z && target.z <= newtoken.pos1.z);

	}

	void Revert() {
		delta = { 0, 0, 0 };
	}

	void Clear() {
		Revert();
		radian = { 0 };
		axis = { 0, 0, 0 };

		indexcnt = 0;
	}

	void Setcol(MyObjCol col) {
		this->col[0] = col.R;
		this->col[1] = col.G;
		this->col[2] = col.B;
	}

	void SetPos() {

	}

	int* AddIndexList() {

	}

	~Diagram() {
		cout << "Diagram is deleted" << endl << endl;
	}


	//void SetSpin(bool ccw, glm::vec3 axis) {

	//	this->axis = axis;

	//	if (ccw)
	//		indexcnt = 1;
	//	else
	//		radcnt = -1;
	//}

	void Spin() {

	}

	void Move(GLPos delta) {
		this->delta.x += delta.x;
		this->delta.y += delta.y;
		this->delta.z += delta.z;
	}



};


class GL_Tri : public Diagram{
public:
	GLfloat pos[3][3];
	GLPos center;
	GLPos radian;
	GLPos Stretch;
	GLfloat col[3][3];

	int mulcount;
	int start_index;


	GL_Tri() : Diagram(){
		float r = glm::sqrt(3.0f) / 3.0f;


		this->pos[0][0] = 0.0f,this->pos[0][1] = r, this->pos[0][2] = 0.0f;
		this->pos[1][0] = -0.5f, this->pos[1][1] =  -0.288f, this->pos[1][2] = 0.0f;
		this->pos[2][0] = 0.5f, this->pos[2][1] =  -0.288f, this->pos[2][2] =  0.0f;

		this->center = { 0.0f, 0.0f, 0.0f };
		this->radian = { 0.0f, 0.0f, 0.0f };
		this->Stretch = { 1.0f, 1.0f, 1.0f };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = 0.0f;
				this->pos[i][j] *= 0.2f;
			}
		}

		mulcount = 1;
		start_index = 0;
	}

	GL_Tri(GLPos* pos) : Diagram() {
		for (int i = 0; i < 3; i++) {
			this->pos[i][0] = pos[i].x;
			this->pos[i][1] = pos[i].y;
			this->pos[i][2] = pos[i].z;
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = 0.0f;
			}
		}

		this->center = { 0.0f, 0.0f, 0.0f };
		this->radian = { 0.0f, 0.0f, 0.0f };
		this->Stretch = { 1.0f, 1.0f, 1.0f };


		mulcount = 1;
		start_index = 0;
	}

	void Setcol(MyObjCol col[3]) {
		for (int i = 0; i < 3; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;
		}
	}

	void Setcol(GLfloat col[3][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = col[i][j];
			}
		}
	}


	void SetTranPos(int mulcount) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] /= this->mulcount;
				pos[i][j] *= mulcount;
			}
		}

		center = center / this->mulcount;
		center = center * mulcount;

		this->mulcount = mulcount;
	}


	void Move(GLPos Delta) {
		center += Delta;
	}

	void Spin(GLPos Delta) {
		// 회전축의 기준을 정할 때는 각 축 기준으로 쪼개서 각 radian 에게 넣어준다.

		radian += Delta;
	}

	void InitScale(GLPos Delta) {

		Stretch += Delta;
	}

	//bool GetCrash(GLPos token, GLPos target) {
	//	GLPos prev = center + token;
	//	GL_Rect newtoken = Getbb(prev, center);

	//	return (target.x >= newtoken.pos1.x && target.x <= newtoken.pos2.x) &&
	//		(target.y <= newtoken.pos2.y && target.y >= newtoken.pos1.y) &&
	//		(target.z >= newtoken.pos2.z && target.z <= newtoken.pos1.z);

	//}

	glm::mat4 GetWorldTransMatrix() {
		glm::mat4 result = glm::mat4(1.0f);

		result *= InitMoveProj(center);
		result *= InitRotateProj(radian, center);
		result *= ChangeScale(Stretch, center);

		return result;
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * sizeof(int));


		p[0] = 0;
		p[1] = 1;
		p[2] = 2;


		return p;
	}

};


class Rect : public Diagram{
public:
	GLfloat pos[4][3];
	GLPos center;
	GLfloat col[4][3];
	GLPos Stretch;

	int mulcount;
	int start_index;


	Rect() : Diagram(){		
		this->pos[0][0] = -0.5f, this->pos[0][1] =  -0.5f, this->pos[0][2] = 0.0f;
		this->pos[1][0] = 0.5f, this->pos[1][1] =  -0.5f, this->pos[1][2] =  0.0f;
		this->pos[2][0] = 0.5f, this->pos[2][1] = 0.5f, this->pos[2][2] =  0.0f;
		this->pos[3][0] = -0.5f, this->pos[3][1] = 0.5f, this->pos[3][2] =  0.0f;


		this->center = { 0.0f, 0.0f, 0.0f };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = 0.0f;
				this->pos[i][j] *= 0.2f;
			}
		}


		Stretch = { 1.0f, 1.0f, 1.0f };
		mulcount = 1;
		start_index = 0;
	}

	Rect(GLPos* pos) : Diagram() {
		for (int i = 0; i < 4; i++) {
			this->pos[i][0] = pos[i].x;
			this->pos[i][1] = pos[i].y;
			this->pos[i][2] = pos[i].z;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = 0.0f;
			}
		}

		this->center = { 0.0f, 0.0f, 0.0f };
		Stretch = { 1.0f, 1.0f, 1.0f };
		mulcount = 1;
		start_index = 0;
	}

	void Setcol(MyObjCol col[4]) {
		for (int i = 0; i < 4; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;
		}
	}

	void Setcol(GLfloat col[4][3]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = col[i][j];
			}
		}
	}

	void SetTranPos(int mulcount) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] /= this->mulcount;
				pos[i][j] *= mulcount;
			}
		}

		center = center / this->mulcount;
		center = center * mulcount;

		this->mulcount = mulcount;
	}

	void Move(GLPos Delta) {
		center += Delta;
	}

	void Spin(GLPos Delta) {
		// 회전축의 기준을 정할 때는 각 축 기준으로 쪼개서 각 radian 에게 넣어준다.

		radian += Delta;
	}

	void InitScale(GLPos Delta) {

		Stretch += Delta;
	}

	//bool GetCrash(GLPos token, GLPos target) {
	//	GLPos prev = center + token;
	//	GL_Rect newtoken = Getbb(prev, center);

	//	return (target.x >= newtoken.pos1.x && target.x <= newtoken.pos2.x) &&
	//		(target.y <= newtoken.pos2.y && target.y >= newtoken.pos1.y) &&
	//		(target.z >= newtoken.pos2.z && target.z <= newtoken.pos1.z);

	//}

	glm::mat4 GetWorldTransMatrix() {
		glm::mat4 result = glm::mat4(1.0f);

		result *= InitMoveProj(center);
		result *= InitRotateProj(radian, center);
		result *= ChangeScale(Stretch, center);

		return result;
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 2 * sizeof(int));


		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;


		return p;
	}
};


class Pentagon : public Diagram {
public:
	GLfloat pos[5][3];
	GLPos center;
	GLfloat col[5][3];
	GLPos Stretch;

	int mulcount;
	int start_index;

	Pentagon() : Diagram() {
		this->pos[0][0] = -0.5f, this->pos[0][1] = -0.6882f, this->pos[0][2] = 0.0f;
		this->pos[1][0] = 0.5f, this->pos[1][1] = -0.6882f, this->pos[1][2] = 0.0f;
		this->pos[2][0] = 0.809f, this->pos[2][1] = 0.2629f, this->pos[2][2] = 0.0f;
		this->pos[3][0] = -0.0f, this->pos[3][1] = 0.8507f, this->pos[3][2] = 0.0f;
		this->pos[4][0] = -0.809f, this->pos[4][1] = 0.2629f, this->pos[4][2] = 0.0f;


		this->center = { 0.0f, 0.0f, 0.0f };
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = 0.0f;
				this->pos[i][j] *= 0.2f;
			}
		}


		Stretch = { 1.0f, 1.0f, 1.0f };
		mulcount = 1;
		start_index = 0;
	}

	Pentagon(GLPos* pos) : Diagram() {
		for (int i = 0; i < 5; i++) {
			this->pos[i][0] = pos[i].x;
			this->pos[i][1] = pos[i].y;
			this->pos[i][2] = pos[i].z;
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = 0.0f;
			}
		}

		this->center = { 0.0f, 0.0f, 0.0f };
		Stretch = { 1.0f, 1.0f, 1.0f };
		mulcount = 1;
		start_index = 0;
	}

	void Setcol(MyObjCol col[5]) {
		for (int i = 0; i < 5; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;
		}
	}

	void Setcol(GLfloat col[5][3]) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				this->col[i][j] = col[i][j];
			}
		}
	}

	void SetTranPos(int mulcount) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] /= this->mulcount;
				pos[i][j] *= mulcount;
			}
		}

		center = center / this->mulcount;
		center = center * mulcount;

		this->mulcount = mulcount;
	}

	void Move(GLPos Delta) {
		center += Delta;
	}

	void Spin(GLPos Delta) {
		// 회전축의 기준을 정할 때는 각 축 기준으로 쪼개서 각 radian 에게 넣어준다.

		radian += Delta;
	}

	void InitScale(GLPos Delta) {

		Stretch += Delta;
	}

	//bool GetCrash(GLPos token, GLPos target) {
	//	GLPos prev = center + token;
	//	GL_Rect newtoken = Getbb(prev, center);

	//	return (target.x >= newtoken.pos1.x && target.x <= newtoken.pos2.x) &&
	//		(target.y <= newtoken.pos2.y && target.y >= newtoken.pos1.y) &&
	//		(target.z >= newtoken.pos2.z && target.z <= newtoken.pos1.z);

	//}

	glm::mat4 GetWorldTransMatrix() {
		glm::mat4 result = glm::mat4(1.0f);

		result *= InitMoveProj(center);
		result *= InitRotateProj(radian, center);
		result *= ChangeScale(Stretch, center);

		return result;
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 3 * sizeof(int));


		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 0;
		p[7] = 3;
		p[8] = 4;


		return p;
	}
};




class GL_Line {
public:
	bool draw;

	GLfloat pos[2][3];
	GLfloat col[2][3];
	int start_index;

	GL_Line() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0.0f;
				pos[i][j] = 0.0f;
			}
		}

		draw = false;
		start_index = 0;
	}

	void Setcol(MyObjCol col[2]) {
		for (int i = 0; i < 2; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;
		}
	}

	void InitFirstPos(GLPos pos) {
		this->pos[0][0] = pos.x;
		this->pos[0][1] = pos.y;
		this->pos[0][2] = pos.z;

		cout << "(" << this->pos[0][0] << ", " << this->pos[0][1] << ", " << this->pos[0][2] << ")" << endl << endl;
	}

	void UpdateEndPos(GLPos pos) {

		this->pos[1][0] = pos.x;
		this->pos[1][1] = pos.y;
		this->pos[1][2] = pos.z;
		draw = true;
	}

	void EndSetPos() {
		cout << "(" << this->pos[1][0] << ", " << this->pos[1][1] << ", " << this->pos[1][2] << ")" << endl << endl;

		draw = false;
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(2 * sizeof(int));


		p[0] = 0;
		p[1] = 1;


		return p;
	}

};