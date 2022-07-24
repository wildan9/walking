/* by Wildan R. */

#pragma once

#include "Audio.h"
#include "CoreLib.h"
#include "GameObject.h"
#include "Screen.h"

struct Game
{
	void DrawGamePlayScreen(raylib::Camera2D* camera,	GameObject* gameObj);
	void DrawGamePlayHUD(Player* player);
	void UpdateCamera(raylib::Camera2D* camera,			Player* player);
	void Run();

	const int _screenWidth		= 512;
	const int _screenHeight		= 512;
	raylib::Camera2D _camera	= {};
};