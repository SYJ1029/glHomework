#pragma once

#include "TimerProcedure.h"
#include "ProjMethod.h"
#include "CheckPointQue.h"


#define POINT 1
#define CUBE 8

class Diagram {



public:
	int postype;
	glm::vec3 axis;
	glm::vec3 OrbitAxis;
	GLPos center;
	GLPos target;
	GLPos radian;
	int radcnt;
	GLPos delta;
	GLPos Stretch;
	GLPos Orbit;
	bool ccw, orbitccw;

	QuadSetting qset;


	queue<GLPos> fifo;

	Diagram() {

		postype = POINT;

		radian = { 0 };
		center = { 0, 0, 0 };
		target = { 0, 0, 0 };
		axis = glm::vec3( 0.0f, 1.0f, 0.0f );
		OrbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		delta = { 0, 0, 0 };

		radcnt = 1;

		for (int i = 0; i < 3; i++) {
			Stretch = { 1.0f };
		}

		ccw = true;
		orbitccw = true;



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
		
		radcnt = 1;
	}

	void Setcol(MyObjCol col[]) {

	}

	void SetPos(){

	}

	int* AddIndexList(){

	}

	~Diagram() {
		cout << "Diagram is deleted" << endl << endl;
	}


	void SetSpin(bool ccw, glm::vec3 axis) {

		this->axis = axis;

		if (ccw)
			radcnt = 1;
		else
			radcnt = -1;
	}

	void Spin() {

	}

	void Move(GLPos delta) {
		this->delta.x += delta.x;
		this->delta.y += delta.y;
		this->delta.z += delta.z;
	}



};


class GL_Cube : public Diagram {

public:
	GLfloat col[8][3];
	GLfloat pos[8][3];
	bool maked[6];
	bool spin[6];
	bool endspin[6];
	bool ccw[6];
	int start_index;
	int mulcount;

	GLPos center[6];
	GLPos Delta[6];
	GLPos radian[6];
	GLPos Stretch[6];
	GLPos StretchDelta[6];
	glm::vec3 axis[6];

	queue<GLPos> fifo[6];

	GL_Cube() : Diagram() {
		postype = CUBE;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] = 0;
				col[i][j] = 0;
			}

			if (i < 6) {
				maked[i] = false;
				spin[i] = false;
				endspin[i] = false;
				ccw[i] = true;
			}
		}	

		for (int i = 0; i < 6; i++) {
			center[i] = { 0.0f, 0.0f, 0.0f };
			Delta[i] = { 0.0f, 0.0f, 0.0f };
			radian[i] = { 0.0f, 0.0f, 0.0f };
			Stretch[i] = { 1.0f, 1.0f, 1.0f };
			StretchDelta[i] = { -0.02f, -0.02f, -0.02f };
			axis[i] = glm::vec3(0.0f);
			
		}

		start_index = 0;
		mulcount = 1;
	}

	void Setcol(MyObjCol col[8]) {
		for (int i = 0; i < 8; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;

		}
	}

	void SetPos() {
		pos[0][0] = -0.5f; pos[0][1] = -0.5f; pos[0][2] = -0.5f;
		pos[1][0] = 0.5f; pos[1][1] = -0.5f;  pos[1][2] = -0.5f;
		pos[2][0] = 0.5f; pos[2][1] = 0.5f; pos[2][2] = -0.5f;
		pos[3][0] = -0.5f; pos[3][1] = 0.5f; pos[3][2] = -0.5f;
		pos[4][0] = 0.5f; pos[4][1] = -0.5f; pos[4][2] = 0.5f;
		pos[5][0] = -0.5f; pos[5][1] = -0.5f;  pos[5][2] = 0.5f;
		pos[6][0] = -0.5f; pos[6][1] = 0.5f; pos[6][2] = 0.5f;
		pos[7][0] = 0.5f; pos[7][1] = 0.5f; pos[7][2] = 0.5f;


		Delta[0] = { 0.0f, 0.0f, -0.5f };
		Delta[1] = { 0.0f, 0.0f, 0.5f }; 
		Delta[2] = { 0.5f, -0.5f, 0.0f }; 
		Delta[3] = { 0.5f, 0.0f, 0.25f }; 
		Delta[4] = { 0.0f, 0.5f, 0.0f }; 
		Delta[5] = { 0.0f, -0.5f, 0.0f };


		
	}

	void SetTranform() {

	}

	void SetTranPos(int mulcount) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] *= mulcount;
			}
		}

		for (int i = 0; i < 6; i++) {
			center[i] = center[i] * mulcount;
			Delta[i] = Delta[i] * mulcount;
		}
		this->mulcount = mulcount;
	}

	void Move(GLPos Delta, int index) {
		center[index] += Delta;
	}

	void Spin(GLPos Delta, int index) {
		// 회전축의 기준을 정할 때는 각 축 기준으로 쪼개서 각 radian 에게 넣어준다.

		radian[index] += Delta;
	}

	void InitScale(GLPos Delta, int index) {

		Stretch[index] += Delta;
	}

	bool GetCrash(GLPos token, GLPos target, int index) {
		GLPos prev = center[index] + token;
		GL_Rect newtoken = Getbb(prev, center[index]);

		return (target.x >= newtoken.pos1.x && target.x <= newtoken.pos2.x) &&
			(target.y <= newtoken.pos2.y && target.y >= newtoken.pos1.y) &&
			(target.z >= newtoken.pos2.z && target.z <= newtoken.pos1.z);

	}

	glm::mat4 GetWorldTransMatrix(glm::mat4 projection, glm::mat4 view,int index) {
		glm::mat4 result = glm::mat4(1.0f);

		result *= InitMoveProj(center[index] / mulcount);
		result *= InitRotateProj(radian[index], Delta[index] / mulcount);
		result *= ChangeScale(Stretch[index], Delta[index] / mulcount);

		return result;
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 12 * sizeof(int));

		cout << sizeof(*p) << endl << endl;

		int index_num = 0;
		int index_array_cnt = 0;
		int i = 1;

		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 4;
		p[7] = 5;
		p[8] = 6;

		p[9] = 4;
		p[10] = 6;
		p[11] = 7;


		p[12] = 1;
		p[13] = 4;
		p[14] = 7;

		p[15] = 1;
		p[16] = 7;
		p[17] = 2;

		p[18] = 5;
		p[19] = 0;
		p[20] = 3;

		p[21] = 5;
		p[22] = 3;
		p[23] = 6;

		p[24] = 2;
		p[25] = 7;
		p[26] = 6;

		p[27] = 2;
		p[28] = 6;
		p[29] = 3;

		p[30] = 0;
		p[31] = 5;
		p[32] = 4;

		p[33] = 0;
		p[34] = 4;
		p[35] = 1;


		return p;
	}
};



class GL_Tetrahedron : public Diagram {


public:

	GLfloat col[4][3];
	GLfloat pos[4][3];
	bool maked[4];
	int start_index;

	GL_Tetrahedron() : Diagram() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0;
				pos[i][j] = 0;
			}

			if (i < 4)
				maked[i] = false;
		}

		start_index = 0;
	}

	void Setcol(MyObjCol col[8]) {
		for (int i = 0; i < 4; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;

		}
	}

	void SetPos() {
		pos[0][0] = 0.0f, pos[0][1] = 0.5f, pos[0][2] = 0.0f;
		pos[1][0] = 0.0f, pos[1][1] = 0.0f, pos[1][2] = 0.5f;
		pos[2][0] = 0.5f, pos[2][1] = 0.0f, pos[2][2] = 0.0f;
		pos[3][0] = 0.0f, pos[3][1] = 0.0f, pos[3][2] = -0.5f;

	}

	void SetTranPos(int mulcount) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] *= mulcount;
			}
		}
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 4 * sizeof(int));

		cout << sizeof(*p) << endl << endl;

		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 0;
		p[7] = 1;
		p[8] = 3;

		p[9] = 1;
		p[10] = 2;
		p[11] = 3;

		return p;
	}

};




class GL_Pyramid : public Diagram{


public:
	GLfloat col[5][3];
	GLfloat pos[5][3];
	bool maked[5];
	bool spin[5];
	bool endspin[5];
	bool ccw[5];
	int start_index;
	int mulcount;
	
	GLPos center[5];
	GLPos Delta[5];
	GLPos radian[5];
	GLPos Stretch[5];
	GLPos StretchDelta[5];
	glm::vec3 axis[5];

	GL_Pyramid() : Diagram() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0;
				pos[i][j] = 0;
			}

			center[i] = { 0.0f, 0.0f, 0.0f };
			Delta[i] = { 0.0f, 0.0f, 0.0f };
			radian[i] = { 0.0f, 0.0f, 0.0f };
			Stretch[i] = { 1.0f, 1.0f, 1.0f };
			StretchDelta[i] = { -0.02f, -0.02f, -0.02f };
			axis[i] = glm::vec3(0.0f);

			maked[i] = false;
			spin[i] = true;
			endspin[i] = false;
			ccw[i] = false;
		}

		start_index = 0;
		mulcount = 1;
	}

	void Setcol(MyObjCol col[5]) {
		for (int i = 0; i < 5; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;

		}
	}


	void SetPos() {
		pos[0][0] = 0.0f, pos[0][1] = 0.5f, pos[0][2] = 0.0f;
		pos[1][0] = -0.5f, pos[1][1] = -0.5f, pos[1][2] = -0.5f;
		pos[2][0] = 0.5f, pos[2][1] = -0.5f, pos[2][2] = -0.5f;
		pos[3][0] = 0.5f, pos[3][1] = -0.5f, pos[3][2] = 0.5f;
		pos[4][0] = -0.5f, pos[4][1] = -0.5f, pos[4][2] = 0.5f;

		Delta[0] = { 0.0f, -0.5f, -0.5f };
		Delta[1] = { 0.5f, -0.5f, 0.0f };
		Delta[2] = { 0.0f, -0.5f, 0.5f };
		Delta[3] = { -0.5f, -0.5f, 0.0f };
		Delta[4] = { 0.0f, -0.5f, 0.0f };


	}

	void SetTranPos(int mulcount) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] *= mulcount;
			}

			if (i == 0 || i == 1) {
				ccw[i] = true;

			}
			else if(i < 4){
				ccw[i] = false;
			}

			Delta[i] = Delta[i] * mulcount;
		}
		this->mulcount = mulcount;
	}

	glm::mat4 GetWorldTransMatrix(glm::mat4 projection, glm::mat4 view, int index) {
		glm::mat4 result = glm::mat4(1.0f);

		result *= InitMoveProj(center[index] / mulcount);
		result *= InitRotateProj(radian[index], Delta[index] / mulcount);
		result *= ChangeScale(Stretch[index], Delta[index] / mulcount);

		return result;
	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 6 * sizeof(int));

		cout << sizeof(*p) << endl << endl;

		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 0;
		p[7] = 3;
		p[8] = 4;

		p[9] = 0;
		p[10] = 4;
		p[11] = 1;

		p[12] = 1;
		p[13] = 2; 
		p[14] = 3;

		p[15] = 1;
		p[16] = 3;
		p[17] = 4;

		return p;
	}

};





class GL_Sphere{

public:
	GLfloat radius;
	GLint slices;
	GLint stacks;


	GL_Sphere(){
		radius = 0.5;
		slices = 50;
		stacks = 50;


	}

};

class GL_Cylinder {
public:
	GLdouble baseRadius;
	GLdouble topRadius;
	GLdouble height;
	GLdouble slices;
	GLdouble stacks;

	GL_Cylinder() {
		baseRadius = 1.0;
		topRadius = 1.0;
		height = 2.0;
		slices = 20;
		stacks = 8;
	}
};