#pragma once
#include <iostream>
#include <GL\glew.h>

class TestShader
{
public:
	void compile(const std::string& vertexPath, const std::string& fragmentPath);
	void use();
	GLuint getID() const { return _programID; }
private:
	GLuint _programID = 0;
	GLuint compileShader(const std::string& source, GLenum type);
};

