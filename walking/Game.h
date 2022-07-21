/* by Wildan R. */

#pragma once

#include "CoreLib.h"
#include "Player.h"
#include "Map.h"
#include "Animal.cpp"
#include "Prop.cpp"

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	const int _screenWidth{ 512 };
	const int _screenHeight{ 512 };
	raylib::Camera2D _camera;
};