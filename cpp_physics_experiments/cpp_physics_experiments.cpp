// cpp_physics_experiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <GL\glew.h>
#include <SDL3\SDL.h>
#include <SDL3\SDL_opengl.h>
#include "MainGame.h"





int main() {
	MainGame mainGame;
	mainGame.run();
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;

	return 0;
}