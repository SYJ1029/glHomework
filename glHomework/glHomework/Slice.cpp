#pragma once

#include "Head/CheckCollision.h"

Camera* camera;



GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid specialKeyboard(int key, int x, int y);
GLvoid MyThrow(int value);
GLvoid MyGen(int value);





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




GLPos WintoGL(int x, int y, int w, int h, Camera& camera) {
	GLPos newpos;


	newpos.x = ((float)x - (float)(w / 2));
	newpos.x /= ((float)w / 2);
	newpos.y = ((float)y - (float)(h / 2));
	newpos.y /= ((float)h / 2);

	newpos.y = newpos.y * -1;

	newpos.z = 0.0f;




	glm::vec3 token = GLPosToVec3(newpos);


	glm::mat4 model = glm::mat4(1.0f);
	glm::vec4 newtoken = glm::vec4(token, 1.0f);
	glm::mat4 newview = glm::inverse(camera.GetViewMatix());

	newview *= model;
	newtoken = newview * newtoken;
	newtoken /= newtoken.w;


	newpos = Vec3ToGLPos(newtoken);




	newpos.z = 0.0f;


	return newpos;
}


GLvoid SetCamera() {
	delete camera;

	camera = new Camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void DepthCheck() {
	if (depthed)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Setindex() {
	int** p1 = (int**)malloc(MAX_DIAGRAM * sizeof(int*));
	int** p2 = (int**)malloc(MAX_DIAGRAM * sizeof(int*));
	int** p3 = (int**)malloc(MAX_DIAGRAM * sizeof(int*));


	int present_bit = index_count;
	int cnt = 0;
	int begin = cnt;
	int indextoken = 0;


	for (int i = 0; i < MAX_DIAGRAM; i++) {

		switch (playground[i].postype) {
		case ID_TRI:
			playground[i].start_index = index_count;
			p1[i] = tri[i]->AddIndexList();

			for (index_count; index_count < present_bit + 3; index_count++) {
				index[index_count] = indextoken + p1[i][index_count - begin];

				cnt++;
			}


			present_bit = index_count;

			indextoken += 3;
			begin = cnt;

			break;
		case ID_RECT:
			playground[i].start_index = index_count;
			p2[i] = rect[i]->AddIndexList();
			for (index_count; index_count < present_bit + 6; index_count++) {
				index[index_count] = indextoken + p2[i][index_count - begin];

				cnt++;
			}
			indextoken += 4;

			present_bit = index_count;
			begin = cnt;
			break;
		case ID_PENTA:

			playground[i].start_index = index_count;
			p3[i] = pent[i]->AddIndexList();

			for (index_count; index_count < present_bit + 9; index_count++) {
				index[index_count] = indextoken + p3[i][index_count - begin];

				cnt++;
			}


			indextoken += 5;
			present_bit = index_count;
			begin = cnt;
			break;
		default:
			break;
		}
	}

	/*for (int i = 0; i < MAX_PERDIAGRAM; i++) {
		tri[i]->start_index = index_count;
		p1[i] = tri[i]->AddIndexList();

		for (index_count; index_count < present_bit + 3; index_count++) {
			index[index_count] = indextoken + p1[i][index_count - begin];

			cnt++;
		}


		present_bit = index_count;

		indextoken += 3;
		begin = cnt;


		rect[i]->start_index = index_count;
		p2[i] = rect[i]->AddIndexList();
		for (index_count; index_count < present_bit + 6; index_count++) {
			index[index_count] = indextoken + p2[i][index_count - begin];

			cnt++;
		}
		indextoken += 4;

		present_bit = index_count;
		begin = cnt;
	

		pent[i]->start_index = index_count;
		p3[i] = pent[i]->AddIndexList();

		for (index_count; index_count < present_bit + 9; index_count++) {
			index[index_count] = indextoken + p3[i][index_count - begin];

			cnt++;
		}


		indextoken += 5;
		present_bit = index_count;
		begin = cnt;
	}*/





	line->start_index = index_count;

	for (index_count; index_count < present_bit + 2; index_count++, index_array_count++) {
		index[index_count] = indextoken + index_array_count;

		cnt++;
	}

	indextoken += 2;

	present_bit = index_count;
	begin = cnt;


	int** sp1 = (int**)malloc(tri_slicedcnt * sizeof(int*));
	int** sp2 = (int**)malloc(rect_slicedcnt * sizeof(int*));
	int** sp3 = (int**)malloc(pent_slicedcnt * sizeof(int*));

	for (int i = 0; i < tri_slicedcnt; i++) {
		slicedtri[i]->start_index = index_count;
		sp1[i] = slicedtri[i]->AddIndexList();


		for (index_count; index_count < present_bit + 3; index_count++) {
			index[index_count] = indextoken + sp1[i][index_count - begin];

			cnt++;
		}


		present_bit = index_count;

		indextoken += 3;
		begin = cnt;
	}

	for (int i = 0; i < rect_slicedcnt; i++) {
		slicedrect[i]->start_index = index_count;
		sp2[i] = slicedrect[i]->AddIndexList();


		for (index_count; index_count < present_bit + 6; index_count++) {
			index[index_count] = indextoken + sp2[i][index_count - begin];

			cnt++;
		}


		present_bit = index_count;

		indextoken += 4;
		begin = cnt;
	}

	for (int i = 0; i < pent_slicedcnt; i++) {
		slicedpent[i]->start_index = index_count;
		sp3[i] = slicedpent[i]->AddIndexList();


		for (index_count; index_count < present_bit + 9; index_count++) {
			index[index_count] = indextoken + sp3[i][index_count - begin];

			cnt++;
		}


		present_bit = index_count;

		indextoken += 5;
		begin = cnt;
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);



	free(p1);
	free(p2);
	free(p3);
	free(sp1);
	free(sp2);
	free(sp3);

}

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}






GLvoid main_SetColor() {
	MyObjCol mycol[3];
	MyObjCol mycol2[4];
	MyObjCol mycol3[5];
	MyObjCol mycol4[2];

	MyObjCol coltoken = SetRandObjCol();


	for (int i = 0; i < 3; i++) {
		coltoken = SetRandObjCol();

		playground[i].Setcol(coltoken);
	}

	for (int j = 0; j < MAX_PERDIAGRAM; j++) {
		for (int i = 0; i < 3; i++) {
			mycol[i] = coltoken;
		}
		coltoken = SetRandObjCol();
		tri[j]->Setcol(mycol);



		for (int i = 0; i < 4; i++) {
			mycol2[i] = coltoken;
		}
		coltoken = SetRandObjCol();
		rect[j]->Setcol(mycol2);


		for (int i = 0; i < 5; i++) {
			mycol3[i] = coltoken;
		}
		pent[j]->Setcol(mycol3);

	}

	for (int i = 0; i < 2; i++) {
		mycol4[i].R = base_axis_col[i][0];
		mycol4[i].G = base_axis_col[i][1];
		mycol4[i].B = base_axis_col[i][2];
	}
	coltoken = SetRandObjCol();
	line->Setcol(mycol4);



	
}


GLvoid main_SetBuffer() {
	

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	//float* counter = new FLOAT();
	int* counter = new INT();
	(*counter) = 0;
	int type = 0;




	for (int j = 0; j < MAX_DIAGRAM; j++) {
		
		switch (playground[j].postype) {
		case ID_TRI:
			for (int i = 0; i < 3; i++) {
				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), tri[0]->pos[i]);

				(*counter) += 3 * sizeof(GLfloat);
			}
			break;
		case ID_RECT:
			for (int i = 0; i < 4; i++) {
				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), rect[0]->pos[i]);

				(*counter) += 3 * sizeof(GLfloat);
			}
			break;
		case ID_PENTA:
			for (int i = 0; i < 5; i++) {
				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), pent[0]->pos[i]);

				(*counter) += 3 * sizeof(GLfloat);
			}
			break;
		default:
			break;
		}




	


	}



	if (line->draw) {
		for (int i = 0; i < 2; i++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), line->pos[i]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}



	for (int i = 0; i < tri_slicedcnt; i++) {
		for (int j = 0; j < 3; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), slicedtri[i]->pos[j]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}

	for (int i = 0; i < rect_slicedcnt; i++) {
		for (int j = 0; j < 4; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), slicedrect[i]->pos[j]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}

	for (int i = 0; i < pent_slicedcnt; i++) {
		for (int j = 0; j < 5; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), slicedpent[i]->pos[j]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}
	index_count = 0;
	index_array_count = 0;

	Setindex();



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);




	(*counter) = 0;

	for (int i = 0; i < MAX_DIAGRAM; i++) {

		for (int j = 0; j < playground[i].postype; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), playground[i].col);

			(*counter) += 3 * sizeof(GLfloat);
		}

	}

	//for (int j = 0; j < MAX_PERDIAGRAM; j++) {

	//	for (int i = 0; i < 3; i++) {
	//		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//			3 * sizeof(GLfloat), playground[j].col);

	//		(*counter) += 3 * sizeof(GLfloat);

	//	}


	//	for (int i = 0; i < 4; i++) {
	//		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//			3 * sizeof(GLfloat), playground[j].col);

	//		(*counter) += 3 * sizeof(GLfloat);
	//	}

	//	for (int i = 0; i < 5; i++) {
	//		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
	//			3 * sizeof(GLfloat), playground[j].col);

	//		(*counter) += 3 * sizeof(GLfloat);
	//	}
	//}



	for (int i = 0; i < 2; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), line->col[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	for (int i = 0; i < tri_slicedcnt; i++) {
		for (int j = 0; j < 3; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), slicedtri[i]->col[j]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}

	for (int i = 0; i < rect_slicedcnt; i++) {
		for (int j = 0; j < 4; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), slicedrect[i]->col[j]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}

	for (int i = 0; i < pent_slicedcnt; i++) {
		for (int j = 0; j < 5; j++) {
			glBufferSubData(GL_ARRAY_BUFFER, (*counter),
				3 * sizeof(GLfloat), slicedpent[i]->col[j]);

			(*counter) += 3 * sizeof(GLfloat);
		}
	}

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
	InitDiagram();
	main_SetColor();
	main_SetBuffer();
	Setplayground();
	SetCamera();


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);

	//for (int i = 0; i < 3; i++) {
	//	glutTimerFunc(10, MyMove, i);
	//}
	glutTimerFunc(1000, MyGen, 0);






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

	main_SetBuffer();


	int counter = 0;
	int randnum = (int)((float)rand() / RAND_MAX + 0.5f);



	for (int i = 0; i < MAX_DIAGRAM; i++) {
		model = basemat;

		gluQuadricDrawStyle(qobj, playground[i].qset.drawstyle);
		gluQuadricNormals(qobj, playground[i].qset.normals);
		gluQuadricOrientation(qobj, playground[i].qset.orientation);





		glm::mat4 view = glm::mat4(1.0);
		view = camera->GetViewMatix();
		unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);



		model *= InitRotateProj(playground[i].radian, playground[i].center);
		model *= InitMoveProj(playground[i].center);
		//model *= InitScaleProj(playground.Stretch);
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));





		counter = playground[i].start_index;


		switch (playground[i].postype) {
		case ID_TRI:


			submodel = model;

			submodel *= tri[0]->GetWorldTransMatrix();
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));

			counter += 3;
			break;
		case ID_RECT:
			submodel = model;

			submodel *= rect[0]->GetWorldTransMatrix();
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
			counter += 6;
			break;
		case ID_PENTA:
			submodel = model;
			submodel *= pent[0]->GetWorldTransMatrix();
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));

			counter += 9;
			break;
		case ID_OCTA:
			//gluSphere(qobj, sphere->radius, sphere->slices, sphere->stacks);
			break;

			model = basemat;
		}
	}




	if (line->draw) {
		counter = line->start_index;
		submodel = glm::mat4(1.0f);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
	}




	model = glm::mat4(1.0f);

	for (int i = 0; i < tri_slicedcnt; i++) {
		counter = slicedtri[i]->start_index;
		submodel = model;

		submodel *= slicedtri[i]->GetWorldTransMatrix();
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
	}

	for (int i = 0; i < rect_slicedcnt; i++) {
		counter = slicedrect[i]->start_index;
		submodel = model;

		submodel *= slicedrect[i]->GetWorldTransMatrix();
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
	}

	for (int i = 0; i < pent_slicedcnt; i++) {
		counter = slicedpent[i]->start_index;
		submodel = model;
		submodel *= slicedpent[i]->GetWorldTransMatrix();
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
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
	GLPos newpos;
	bool mouseIn = false;
	MyObjCol coltoken[3] = { SetRandObjCol(), SetRandObjCol(), SetRandObjCol() };

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y, *camera);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			line->InitFirstPos(newpos);
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
		}

	}
	else {

		line->EndSetPos();

		CheckCollision();
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	GLPos newpos = WintoGL(x, y, Screensize.x, Screensize.y, *camera);

	line->UpdateEndPos(newpos);

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



GLvoid MyGen(int value) {

	if (value >= MAX_DIAGRAM)
		value %= MAX_DIAGRAM;

	SetNewplayground(value);

	glutTimerFunc(system_time, MyMove, value);
	glutTimerFunc(1000, MyGen, value + 1);
}

GLvoid MyThrow(int value) {


}