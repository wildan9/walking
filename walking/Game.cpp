/* by Wildan R. */

#include "Game.h"

Game::Game()
{
	InitWindow(_screenWidth, _screenHeight, "Walking");
	InitAudioDevice();
}

Game::~Game()
{
	CloseWindow();
	CloseAudioDevice();
}

void Game::Run()
{
	SetTargetFPS(60);

	Player player{};

	Animals animals;

	Map map;

	animals.SetBatFlyRadius(map.GetDreamlandSize().width * map.GetMapScale());

	Prop props;

	_camera.target = player.GetPosition();
	_camera.offset = Vector2{ _screenWidth / 2.0f,  _screenHeight / 2.0f };
	_camera.rotation = 0.0f;
	_camera.zoom = 1.0f;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		_camera.target = player.GetPosition();
		_camera.BeginMode();

		map.Draw();

		if (player.GetPosition().x < -15.0f || player.GetPosition().y < 0.0f ||
			player.GetPosition().x > ((float)map.GetDreamlandSize().width - 15.0f) * map.GetMapScale() &&
			player.GetPosition().x < (float)map.GetDreamlandSize().width + 1500.0f ||
			player.GetPosition().y > (float)map.GetDreamlandSize().height * map.GetMapScale()) player.OnWater();
		else player.OnLand();

		player.Draw();

		animals.Draw(GetFrameTime());

		props.Draw();

		if (CheckCollisionRecs(player.GetCollision(), animals.crocodile.GetCollision()) &&
			player.IsPunch() && (player.GetFacing() == 1.0f && animals.crocodile.GetFacing() >= -1.0f &&
			player.GetPosition().x < animals.crocodile.GetPosition().x)) animals.crocodile.Hurt();
		else if (CheckCollisionRecs(player.GetCollision(), animals.crocodile.GetCollision()) &&
			player.IsPunch() && (player.GetFacing() == -1.0f && animals.crocodile.GetFacing() >= -1.0f &&
			player.GetPosition().x > animals.crocodile.GetPosition().x)) animals.crocodile.Hurt();
		else animals.crocodile.Walk();

		for (auto& rhino : animals.rhinos) if (CheckCollisionRecs(player.GetCollision(), rhino.GetCollision())) player.Stop();

		if (CheckCollisionRecs(player.GetCollision(), map.GetMapLine1()) ||
			CheckCollisionRecs(player.GetCollision(), map.GetMapLine2())) player.Stop();

		for (const auto& invisibleFence : invisibleFences)
		{
			if (CheckCollisionRecs(player.GetCollision(),
				Rectangle{ invisibleFence.x, invisibleFence.y, invisibleFence.width, invisibleFence.height }))
			{
				player.Stop();
			}
		}

		if (CheckCollisionRecs(player.GetCollision(), props.naturalObj.GetBigStone1Coll())) player.SetPosition({ 3000.0f, 300.0f });

		if (CheckCollisionRecs(player.GetCollision(), props.naturalObj.GetBigStone2Coll())) player.SetPosition({ 40.0f, 140.0f });

		_camera.EndMode();
		EndDrawing();
	}
}