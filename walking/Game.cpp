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

void Game::UpdateCamera(Camera2D* camera, Player* player)
{
    Vector2D diff{ player->GetPosition().Subtract(camera->target) };

    float speed{ player->GetSpeed() };

    speed = (speed == 2.0f) ? fmaxf(0.8f * diff.Length(), 70.0f) : fmaxf(0.8f * diff.Length(), 240.0f);

    if (player->IsTeleport()) // don't need cinematic effect when teleporting
    {
        camera->target = player->GetPosition();
        player->SetTeleportStatus(0);
    }

    if (diff.Length() > 10.0f)
    {
        camera->offset = Vector2D{ _screenWidth / 2.0f,  _screenHeight / 2.0f };
        camera->target = Vector2D{ camera->target }.Add(diff.Scale(speed * GetFrameTime() / diff.Length()));
    }
}

void Game::Run()
{
    SetTargetFPS(60);

    Screen currentScreen{ Screen::LOGO };

    int framesCounter{ 0 };

    GameObject gameObj;

    gameObj.animals.SetBatFlyRadius(gameObj.map.GetDreamlandSize().width * gameObj.map.GetMapScale());

    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
        case Screen::LOGO:
        {
            framesCounter++;

            if (framesCounter > 180) currentScreen = Screen::TITLE;
            
        } break;
        case Screen::TITLE:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = Screen::GAMEPLAY;

        } break;
        default: break;
        }

        BeginDrawing();

        ClearBackground(SKYBLUE);

        switch (currentScreen)
        {
        case Screen::LOGO:
        {
            DrawText("Walking", 120, 220, 80, BLACK);

        } break;
        case Screen::TITLE:
        {
            DrawText("Walking", 15, 20, 40, BLACK);
            DrawText("PRESS ENTER or TAP to Walking!", 80, 220, 20, BLACK);

        } break;
        case Screen::GAMEPLAY:
        {
            UpdateCamera(&_camera, &gameObj.player);
            _camera.BeginMode();
            gameObj.CheckCollision();
            gameObj.PlayWalkSound();
            gameObj.Draw(GetFrameTime());
            _camera.EndMode();

            DrawText(gameObj.player.GetPosition().ToString().c_str(), 10, _screenHeight - 35, 30, BLACK);
            DrawFPS(_screenWidth - 30, 10);

        } break;
        default: break;
        }

        EndDrawing();
    }
}