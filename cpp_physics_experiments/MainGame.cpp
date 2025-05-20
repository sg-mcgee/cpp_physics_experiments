#include "MainGame.h"

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
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
	}
}
void MainGame::processInput() {

}