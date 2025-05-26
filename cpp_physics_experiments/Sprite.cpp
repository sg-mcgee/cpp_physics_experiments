#include "Sprite.h"
#include <iostream>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite() {
	_vboID = 0;
	_vaoID = 0;
}

Sprite::~Sprite() {
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
	if (_vaoID != 0) {
		glDeleteVertexArrays(1, &_vaoID);
	}
}

void Sprite::init(float width, float height, glm::vec4 color) {
	_width = width;
	_height = height;
	_color = color;

	setScale(width, height);

	//float vertexData[12] = { //Two values for 6 points, square is made of 2 triangles
	//	width, height,
	//	0.0f,  height,
	//	0.0f,  0.0f,

	//	0.0f,  0.0f,
	//	width, 0.0f,
	//	width, height
	//};

	float vertexData[12] = {
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f
	};

	// Generate VAO
	if (_vaoID == 0) {
		glGenVertexArrays(1, &_vaoID);
	}
	glBindVertexArray(_vaoID);
	// Generate and bind VBO
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	//Set attribute pointers inside VAO bind
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	//Unbind to prevent accidental modification
	glBindVertexArray(0);  // Unbind VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Optional


}

void Sprite::setPosition(float x, float y) {
	_position = { x, y };
	updateModel();
}

void Sprite::setScale(float w, float h) {
	_scale = { w, h };
	updateModel();
}

void Sprite::updateModel() {
	_model = glm::mat4(1.0f);
	_model = glm::translate(_model, glm::vec3(_position.x, _position.y, 0.0f));
	_model = glm::scale(_model, glm::vec3(_scale, 1.0f));
}

void Sprite::draw(GLuint shaderProgramID) {
	glUseProgram(shaderProgramID);

	GLuint modelLoc = glGetUniformLocation(shaderProgramID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &_model[0][0]);

	GLuint colorLoc = glGetUniformLocation(shaderProgramID, "spriteColor");
	glUniform4f(colorLoc, _color.r, _color.g, _color.b, _color.a);
	//std::cout << "" << _color.r << std::endl;

	glBindVertexArray(_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}