#include "Head/3DDiagram.h"

#define MAX_INDEX 12
#define MAX_INDEX13 2

GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyTimer(int index);


MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };
GL_Cube cube;
GL_Tetrahedron tri;

void Setindex() {
	int* p1 = cube.AddIndexList();
	int* p2 = tri.AddIndexList();

	cout << sizeof((p1));

	int present_bit = index_count;

	for (index_count; index_count < 36; index_count++) {
		index[index_count] = p1[index_count];
	}

	present_bit = index_count;

	for (index_count; index_count < present_bit + 12; index_count++) {
		index[index_count] = 8 + p2[index_count - 36];
	}

	
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


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	cube.SetPos();
	tri.SetPos();

	//float* counter = new FLOAT();
	int* counter = new INT();
	(*counter) = 0;
	int type = 0;

	

	for (int i = 0; i < 8; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube.pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}
	

	for (int i = 0; i < 4; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), tri.pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	/*index_count = 0;
	index_array_count = 0;*/

	Setindex();



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	


	(*counter) = 0;
	for (int i = 0; i < 8; i++) {
		

		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube.col[i]);

		(*counter) += 3 * sizeof(GLfloat);

		//cout << "(" << cube.pos[i][0] << ", " << cube.pos[i][1] << ", " << cube.pos[i][2] << ')' << endl << endl;
	}

	for (int i = 0; i < 4; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), tri.col[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

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


	MyObjCol mycol[8];
	MyObjCol mycol2[4];
	for (int i = 0; i < 8; i++) {
		mycol[i] = SetRandObjCol();
	}
	for (int i = 0; i < 4; i++) {
		mycol2[i] = SetRandObjCol();
	}
	cube.Setcol(mycol);
	tri.Setcol(mycol2);

	glBindVertexArray(vao);
	SetBuffer();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);


	glutMainLoop(); // 이벤트 처리 시작
	

}


void drawCube(float* counter, int index) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);


}

float radian = 10.0f;
int mycnt = 1;

void drawScene()
{
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//gluLookAt(0.0, 0.0, 100.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glUseProgram(shaderProgramID);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = model;
	glm::mat4 rm2 = model;

	/*model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f));*/




	rm = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rm2 = glm::rotate(model, glm::radians(radian), glm::vec3(0.0f, 1.0f, 0.0f));

	model = rm2 * rm;

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));


	glBindVertexArray(vao);




	int counter = 0;

	//(*counter) += 30 * sizeof(float);
	/*glDrawElements(GL_QUADS, 3, GL_UNSIGNED_INT, (void*)counter);*/
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)counter);

	for (int i = 0; i < 6; i++) {
		if (cube.maked[i]) {
			for (int j = 0; j < 2; j++) {

				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)counter);
				counter += 3 * sizeof(GLfloat);

			}
		}
		else {
			counter += 6 * sizeof(GLfloat);
		}


	}

	for (int i = 0; i < 4; i++) {
		if (tri.maked[i]) {
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)counter);
			counter += 3 * sizeof(GLfloat);
		}
		else {
			counter += 3 * sizeof(GLfloat);
		}
	}




	glEnable(GL_DEPTH_TEST);
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

	switch (key) {
	case '1': case '2': case '3': case '4': case '5': case '6':
		cube.maked[token] = !(cube.maked[token]);
		break;

	case '7':case '8': case '9': case '0':
		token -= 6;

		if (token < 0)
			token = 3;

		tri.maked[token] = !(tri.maked[token]);
		break;
	case 'c':
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				tri.maked[i] = false;
			}


			cube.maked[i] = false;
		}

		for (int i = 0; i < 2; i++) {
			randnum[i] = (float)((float)rand() / RAND_MAX) * 6;

			if (i > 0 && randnum[i] == randnum[i - 1]) {
				i--;
			}
		}


	

		cube.maked[randnum[0]] = true;
		cube.maked[randnum[1]] = true;



		break;
	case 't':
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				tri.maked[i] = false;
			}


			cube.maked[i] = false;
		}

		for (int i = 0; i < 2; i++) {
			randnum[i] = (float)((float)rand() / RAND_MAX) * 4;

			if (i > 0 && randnum[i] == randnum[i - 1]) {
				i--;
			}
		}

		tri.maked[randnum[0]] = true;
		tri.maked[randnum[1]] = true;

		break;
	default:
		break;
	}

	glutPostRedisplay();
}
GLvoid MyTimer(int index) {


	glutPostRedisplay();
}