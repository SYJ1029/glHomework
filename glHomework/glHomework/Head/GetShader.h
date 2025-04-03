#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "3DDiagram.h"
#include <fstream>
#include <sstream>


void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
//--- �ʿ��Ѻ�������
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷��̸�
GLuint vertexShader;
GLuint fragmentShader; //--- �����׸�Ʈ ���̴���ü

//--- ���̴��ڵ������ҹ��ڿ�
//--- ���ؽ����̴��о������ϰ��������ϱ�
//--- filetobuf: ����������Լ����ؽ�Ʈ���о���ڿ��������ϴ��Լ�

GLint result;
GLchar errorLog[512];
GLuint vao, vbo[2], EBO;
GLchar* vertexSource;
GLchar* fragmentSource;

int index[1000];


GLfloat triShape[3][3] = {
 { -0.5, -0.5, 0.0 }, { 0.0, -0.5, 0.0 }, { -0.25, 0.5, 0.0} };

float triShape2[] = {
	0.5f,  0.5f, 0.0f,  // ���� ���
	0.5f, -0.5f, 0.0f,  
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f   // ���� ���
};

GLfloat triShape3[3][3] = {
 { 0.5, -0.5, 0.0 }, { 1.0, -0.5, 0.0 }, { 0.75, 0.5, 0.0} };

GLfloat alltriShape[6][3] = {
{ -0.5, -0.5, 0.0 }, { 0.0, -0.5, 0.0 }, { -0.25, 0.5, 0.0},
{ 0.0, -0.5, 0.0 }, { 0.5, -0.5, 0.0 }, { 0.25, 0.5, 0.0}

};


const GLfloat colors[3][3] = {
   {  1.0,  0.0,  0.0  }, {  0.0,  1.0,  0.0  }, {  0.0,  0.0,  1.0  } };


GLchar* filetobuf(const char* vertexSource) {
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(vertexSource, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}


void make_vertexShaders() {

	vertexSource = filetobuf("Shader/vertex.txt");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**) & vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}

	
}

void make_fragmentShaders() 
{
	fragmentSource = filetobuf("Shader/fragment.txt");    // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_shaderProgram()
{

	/*make_vertexShaders();
	make_fragmentShaders();*/

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgramID);

}





GLvoid InitBuffer() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	/*glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);*/
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), 9 * sizeof(GLfloat), colors);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

}



GLvoid UpdateBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(GLfloat), alltriShape);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), 9 * sizeof(GLfloat), triShape2);
	//glDrawArrays(GL_TRIANGLES, 3, 3);


	glEnableVertexAttribArray(0);
}