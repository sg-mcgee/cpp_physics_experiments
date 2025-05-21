#include "MainGame.h"
#include "TestShader.h"
#include "Sprite.h"

#include <iostream>

//Raise error in terminal and quiot
void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to exit..." << std::endl;
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

//Game information constructor
MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}

//Game destructor
MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();

	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

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

	shader.compile(
		"C:\\Users\\garto\\source\\shaders\\colorShading.vert.txt", 
		"C:\\Users\\garto\\source\\shaders\\colorShading.frag.txt"
	);
	
	//Test init of var
	float location_tracker = 0.0;
	int mouse_x = 0;
	int mouse_y = 0;

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
				mouse_x = user_event.motion.x;
				mouse_y = user_event.motion.y;
				float float_fix = 0.0f;
				scale_mouse_x = 2 * (mouse_x - _screenWidth + float_fix) / (_screenWidth)+1;
				scale_mouse_y = -(2 * (mouse_y - _screenHeight + float_fix) / (_screenHeight)+1);
				location_tracker += 0.1;
				std::cout << scale_mouse_x << " " << scale_mouse_y << std::endl;
				break;

		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0); //Boilerplate
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears color buffer & depth buffer

	shader.use();
	_sprite.init(0.0f + scale_mouse_x, 0.0f + scale_mouse_y, 1.0f, 1.0f);
	_sprite.draw();


	//Swap our buffer and draw everything to screen
	SDL_GL_SwapWindow(_window);

}