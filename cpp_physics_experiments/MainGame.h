#pragma once
#include <GL\glew.h>
#include <SDL3\SDL.h>

#include "Sprite.h"

#include "TestShader.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();


private:
	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Sprite _sprite;
	Sprite ground_sprite;

	TestShader shader;

	float location_tracker;
	float mouse_x;
	float mouse_y;
	float scale_mouse_x;
	float scale_mouse_y;
	const float float_fix = 0.0;
};

