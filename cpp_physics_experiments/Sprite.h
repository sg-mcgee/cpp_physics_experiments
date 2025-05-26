#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>


class Sprite
{
public:
	Sprite();
	~Sprite();

	void setPosition(float x, float y);

	void setScale(float w, float h);

	void draw(GLuint shaderID);

	void init(float width, float height, glm::vec4 color);

	void updateModel();


private:
	float _width;
	float _height;

	glm::vec4 _color;

	glm::vec2 _position = { 0.0f, 0.0f };
	glm::vec2 _scale = { 1.0f, 1.0f };
	glm::mat4 _model = glm::mat4(1.0f);

	GLuint _shaderID;
	GLuint _vboID;
	GLuint _vaoID;

};

