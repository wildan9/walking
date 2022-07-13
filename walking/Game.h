/* by Wildan R. */

#pragma once

#include "CoreLib.h"
#include "Camera2D.h"
#include "GameObject.h"

class GameScreen
{
protected:
	const int _screenWidth{ 512 };
	const int _screenHeight{ 512 };
	enum class Screen{ LOGO = 0, TITLE, GAMEPLAY };
};

class Game : public GameScreen
{
public:
	Game();
	~Game();
	void Run();

private:
	raylib::Camera2D _camera{};
	void UpdateCamera(Camera2D* camera, Player* player);
};