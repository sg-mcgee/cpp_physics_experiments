// cpp_physics_experiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <SDL3\SDL.h>
#include "MainGame.h"





int main() {
	MainGame mainGame;
	mainGame.run();

	std::cout << "Enter any key to exit...";
	int a;
	std::cin >> a;

	return 0;
}