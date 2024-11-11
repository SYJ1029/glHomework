#pragma once

#include "Head/LoadDiagram.h"

Camera* camera;
Projection* proj;

#define MAX_INDEX 12
#define MAX_INDEX13 2

#define ID_TRI 0
#define ID_RECT 1
#define ID_PENTA 2
#define ID_OCTA 3

#define PROJED true


GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid specialKeyboard(int key, int x, int y);




Diagram playground[3];


bool depthed = true;
bool gopersepective = true;
bool gospin[2] = { false, false };
bool direct = true;
bool goorbit = false;
bool endorbit = false;
bool checkPoint = false;
bool goStretch = false;
bool goSpiral = false;
bool spinSequence = false;


float base_axis[6][3] = {
	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f
};

float base_axis_col[6][3] = {
	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

int baseAxisIndex = 0;
int mulcount = 1;


GLvoid Setplayground() {

	for (int i = 0; i < 3; i++) {

		playground[i].center = {0.0f, 0.0f, 0.0f};

		playground[i].radian = {0.0f, 0.0f, 0.0f};

		playground[i].Stretch = {0.2f, 0.2f, 0.2f};

		playground[i].Orbit = {0.0f, 0.0f, 0.0f};

	}

	playground[0].postype = ID_TRI;

	playground[1].postype = ID_RECT;

	playground[2].postype = ID_TRI;

}


GLvoid SetCamera() {
	delete camera;

	camera = new Camera(glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

GLvoid SetProjection(int projtype) {
	delete proj;

	proj = new Projection();

	if (projtype == PROJ_ORTHO) {
		proj->InitOrtho(-5.0f, 5.0f, 5.0f, -5.0f, -30.0f, 15.0f);
	}
	else {
		proj->InitPerspective(glm::radians(160.0f), 1.0f, 0.1f, 100.0f);
	}

	IsobjsProjed(false);
}

void DepthCheck() {
	if (depthed)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Setindex() {
	int* p1 = tri->AddIndexList();
	int* p2 = rect->AddIndexList();

	cout << sizeof((p1));

	int present_bit = index_count;
	int cnt = 0;
	int begin = cnt;




	for (index_count; index_count < 3; index_count++) {
		index[index_count] = p1[index_count];

		cnt++;
	}

	tri->start_index = 0;
	//cnt += 36;

	present_bit = index_count;

	begin = cnt;

	rect->start_index = index_count;

	for (index_count; index_count < present_bit + 6; index_count++) {
		index[index_count] = 3 + p2[index_count - begin];

		cnt++;
	}

	//cnt += 12;

	present_bit = index_count;
	begin = cnt;

	//pyr->start_index = index_count;

	//for (index_count; index_count < present_bit + 18; index_count++) {
	//	index[index_count] = 12 + p3[index_count - begin];
	//}

	cnt += 15;


	//present_bit = index_count;
	//baseAxisIndex = index_count;

	//for (index_count; index_count < present_bit + 6; index_count++, index_array_count++) {
	//	index[index_count] = 12 + 5 + index_array_count;
	//}



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);

	free(p1);
	free(p2);
}

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}



GLvoid SetBuffer() {
	MyObjCol mycol[8];
	MyObjCol mycol2[4];
	MyObjCol mycol3[5];

	MyObjCol coltoken = SetRandObjCol();

	for (int i = 0; i < 3; i++) {
		mycol[i] = coltoken;
	}
	coltoken = SetRandObjCol();

	for (int i = 0; i < 4; i++) {
		mycol2[i] = coltoken;
	}
	coltoken = SetRandObjCol();

	for (int i = 0; i < 5; i++) {
		mycol3[i] = coltoken;
	}

	tri->Setcol(mycol);
	rect->Setcol(mycol2);
	//pyr->Setcol(mycol3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	tri->SetPos();
	rect->SetPos();
	//pyr->SetPos();

	//float* counter = new FLOAT();
	int* counter = new INT();
	(*counter) = 0;
	int type = 0;




	for (int i = 0; i < 3; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), tri->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}


	for (int i = 0; i < 4; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), rect->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	//for (int i = 0; i < 5; i++) {
	//	glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//		3 * sizeof(GLfloat), pyr->pos[i]);

	//	(*counter) += 3 * sizeof(GLfloat);
	//}



	//for (int i = 0; i < 6; i++) {
	//	glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//		3 * sizeof(GLfloat), base_axis[i]);

	//	(*counter) += 3 * sizeof(GLfloat);
	//}

	index_count = 0;
	index_array_count = 0;

	Setindex();



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);




	(*counter) = 0;


	for (int i = 0; i < 3; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), tri->col[i]);

		(*counter) += 3 * sizeof(GLfloat);

		//cout << "(" << cube.pos[i][0] << ", " << cube.pos[i][1] << ", " << cube.pos[i][2] << ')' << endl << endl;
	}

	for (int i = 0; i < 4; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), rect->col[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	//for (int i = 0; i < 5; i++) {
	//	glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//		3 * sizeof(GLfloat), pyr->col[i]);

	//	(*counter) += 3 * sizeof(GLfloat);
	//}




	//for (int i = 0; i < 6; i++) {
	//	glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//		3 * sizeof(GLfloat), base_axis_col[i]);

	//	(*counter) += 3 * sizeof(GLfloat);
	//}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}





void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	srand(time(NULL));

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(Screensize.x, Screensize.y); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Initialized\n";

	make_vertexShaders();
	make_fragmentShaders();
	make_shaderProgram();
	InitBuffer();


	glBindVertexArray(vao);
	SetBuffer();
	Setplayground();
	SetCamera();
	SetProjection(PROJ_PERSPECTIVE);
	tri->SetTranPos(20);
	rect->SetTranPos(20);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(Mouse);








	glutMainLoop(); // 이벤트 처리 시작


}



float radian = 10.0f;
int mycnt = 0;
glm::vec3 allAxis = glm::vec3(0.0f, 0.0f, 0.0f);

void drawScene()
{


	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//gluLookAt(0.0, 0.0, 100.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glUseProgram(shaderProgramID);
	glm::mat4 basemat = glm::mat4(1.0f);
	glm::mat4 rm = basemat;
	glm::mat4 rm2 = basemat;
	glm::mat4 model = basemat;
	glm::mat4 submodel = basemat;
	//glm::mat4 rm3 = glm::mat4(1.0f);

	/*model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f));*/
	int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");

	glBindVertexArray(vao);




	int counter = 0;



	for (int i = 0; i < 3; i++) {
		model = basemat;

		gluQuadricDrawStyle(qobj, playground[i].qset.drawstyle);
		gluQuadricNormals(qobj, playground[i].qset.normals);
		gluQuadricOrientation(qobj, playground[i].qset.orientation);



		glm::mat4 projection = glm::mat4(1.0);
		projection = proj->GetProjMatrix();
		unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


		glm::mat4 view = glm::mat4(1.0);
		view = camera->GetViewMatix();
		unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);



		model *= InitRotateProj(playground[i].Orbit, {0.0f, 0.0f, 0.0f});
		model *= InitRotateProj(playground[i].radian, playground[i].center);
		model *= InitMoveProj(playground[i].center);
		//model *= InitScaleProj(playground.Stretch);
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));








		switch (playground[i].postype) {
		case ID_TRI:
			counter = tri->start_index;
			submodel = model;

			submodel *= tri->GetWorldTransMatrix();
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
			counter += 3;
			break;
		case ID_RECT:
			counter = rect->start_index;
			submodel = model;

			submodel *= rect->GetWorldTransMatrix();
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
			counter += 6;
			break;
		case ID_PENTA:
			counter = rect->start_index;
			submodel = model;
			submodel *= rect->GetWorldTransMatrix();
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));

			break;
		case ID_OCTA:
			//gluSphere(qobj, sphere->radius, sphere->slices, sphere->stacks);
			break;

			model = basemat;
		}
	}







	//model = basemat;


	//model = rm2 * rm;

	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	//glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(baseAxisIndex * sizeof(GLfloat)));
	//counter += 6 * sizeof(GLint);




	glutSwapBuffers();

}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
	glViewport(0, 0, w, h);
}


GLvoid Mouse(int button, int state, int x, int y) {


	glutPostRedisplay();
}




GLvoid Keyboard(unsigned char key, int x, int y) {

	int token = (int)key - (int)'1';
	int randnum[2];
	randnum[0] = -1, randnum[1] = -1;
	GLPos firsttoken = { 0.0f, 0.8f, 0.0f };

	switch (key) {
	case 'w': case 'W':
		if ((int)key - (int)'a' < 0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			for (int i = 0; i < 2; i++) {
				playground[i].qset.drawstyle = GLU_FILL;
			}

		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			for (int i = 0; i < 2; i++) {
				playground[i].qset.drawstyle = GLU_LINE;
			}
		}

		break;

	
	
	case 'm':
		goorbit = false;
		gospin[0] = false;
		gospin[1] = false;
		goStretch = false;
		goSpiral = false;
		Setplayground();
		break;



	case 'q':
		delete rect;
		delete tri;
		//delete pyr;

		glutLeaveMainLoop();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		playground[0].center -= {10.0f, 0.0f, 0.0f};
		break;
	case GLUT_KEY_RIGHT:
		playground[0].center += {10.0f, 0.0f, 0.0f};
		break;
	case GLUT_KEY_UP:
		playground[0].center += {0.0f, 10.0f, 0.0f};
		break;
	case GLUT_KEY_DOWN:
		playground[0].center -= {0.0f, 10.0f, 0.0f};
		break;
	}

	glutPostRedisplay();
}



GLvoid MyCcw(int value) {

	playground[value].radian.x += (playground[value].axis.x * 5);

	playground[value].radian.y += (playground[value].axis.y * 5);

	playground[value].radian.z += (playground[value].axis.z * 5);




	if (gospin[value] && direct) {
		glutTimerFunc(10, MyCcw, value);
	}
	else if (gospin[1 - value] && direct) {
		glutTimerFunc(10, MyCcw, 1 - value);
	}
	glutPostRedisplay();
}

GLvoid MyCw(int value) {

	playground[value].radian.x -= (playground[value].axis.x * 5);

	playground[value].radian.y -= (playground[value].axis.y * 5);

	playground[value].radian.z -= (playground[value].axis.z * 5);

	if (playground[value].radian.x <= -180)
		cout << "pause" << endl << endl;


	if (gospin[value] && direct == false) {
		glutTimerFunc(10, MyCw, value);
	}

	else if (gospin[1 - value] && direct == false) {
		glutTimerFunc(10, MyCw, 1 - value);
	}

	glutPostRedisplay();
}


GLvoid OrbitCcw(int value) {

	playground[value].Orbit += Vec3ToGLPos(playground[value].OrbitAxis) * 5;

	if (goorbit && playground[value].orbitccw) {
		glutTimerFunc(30, OrbitCcw, value);
	}
	glutPostRedisplay();
}





GLvoid OrbitCw(int value) {
	playground[value].Orbit -= Vec3ToGLPos(playground[value].OrbitAxis) * 5;


	if (goorbit && playground[value].orbitccw == false) {

		if (endorbit && playground[value].Orbit.y <= -180) {
			playground[value].center = playground[value].target;
			playground[value].Orbit = 0.0f;

			//glm::mat4 result = glm::mat4(1.0);

			//result *= InitRotateProj(playground[value].Orbit, { 0.0f, 0.0f, 0.0f });
			//result *= InitMoveProj(playground[value].center);
			//result *= InitScaleProj(playground[value].Stretch);

			//playground[value].center = GetProjedPos(playground[value].center, result);
			//playground[value].Orbit = 0.0f;
		}
		else
			glutTimerFunc(30, OrbitCw, value);
	}
	glutPostRedisplay();
}



