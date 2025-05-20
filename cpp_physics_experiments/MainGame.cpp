#include "MainGame.h"
#include <iostream>

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to exit..." << std::endl;
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();

	gameLoop();
}

void MainGame::initSystems() {
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	_window = SDL_CreateWindow("MainWindow", _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("STL Window failed to create");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew failed to init");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Two windows, for drawing and clearing then swap, prevents flicker

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //Set color (RGBA)
	


}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}

void MainGame::processInput() {
	SDL_Event user_event;

	while (SDL_PollEvent(&user_event)) {
		switch (user_event.type) {

			case SDL_EVENT_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				std::cout << user_event.motion.x << " " << user_event.motion.y << std::endl;
				break;

		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0); //Boilerplate
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears color buffer & depth buffer



	SDL_GL_SwapWindow(_window);

}