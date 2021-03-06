/* by Wildan R. */

#include "Game.h"

enum class ApplicationStates
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    PAUSE
};
ApplicationStates applicationState{ ApplicationStates::LOGO };

class LogoScreen : public Screen
{
public:
    void Draw() override
    {
        DrawHelixNebula();
    }
};
LogoScreen logoScreen;

class TitleScreen : public Screen
{
public:
    void Draw() override
    {
        DrawEarth();
        DrawText("Walking", 15, 20, 40, GREEN);
        DrawText("PRESS ENTER or TAP to Walking!", 80, 220, 20, GREEN);
    }
};
TitleScreen titleScreen;

class PauseScreen : public Screen
{
public:
    void Draw() override
    {
        DrawGalaxy();
        DrawText("Paused", 145, 220, 60, BLUE);
    }
};
PauseScreen pauseScreen;

void Game::DrawGamePlayScreen(raylib::Camera2D* camera, GameObject* gameObj)
{
    camera->BeginMode();
    gameObj->CheckCollision();
    gameObj->PlayWalkSound();
    gameObj->Draw(GetFrameTime());
    camera->EndMode();
}

void StartTimer(Timer* timer, float lifeTime)
{
    if (timer != NULL)
    {
        timer->_lifeTime = lifeTime;
    }
}

void UpdateTimer(Timer* timer)
{
    if (timer != NULL && timer->_lifeTime > 0)
    {
        timer->_lifeTime -= GetFrameTime();
    }
}

bool TimerDone(Timer* timer)
{
    if (timer != NULL)
    {
        return timer->_lifeTime <= 0;
    }

    return 0;
}

void Game::DrawGamePlayHUD(Player* player, Timer* timer)
{
    std::string strFPS{ "FPS: " };
    std::string strStatus{};

    const char* strVolume[7]{ "Muted", "Volume: #", "Volume: # #", "Volume: # # #", "Volume: # # # #", "Volume: # # # # #", "NULL" };

    if (player->GetDirection().Length() == NULL) strStatus = "Status: IDLE";
    else strStatus = (player->GetSpeed() == 4.0f) ? "Status: Walk Fast" : "Status: Walk Slow";

    if (GetMasterVolume() == NULL || !TimerDone(timer))
    {
        DrawText(strVolume[(int8_t)(GetMasterVolume() * 10)], 10, 10, 24, RED);
    }

    DrawText(player->GetPosition().ToString().c_str(), 10, _screenHeight - 50, 24, BLACK);
    DrawText(strFPS.append(std::to_string(GetFPS())).c_str(), _screenWidth - 80, 10, 18, RED);
    DrawText(strStatus.c_str(), _screenWidth - 165, _screenHeight - 40, 19, RED);
}

void Game::UpdateCamera(raylib::Camera2D* camera, Player* player)
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
    InitWindow(_screenWidth, _screenHeight, "Walking");
    
    InitAudio();

    InitScreenTexture();

    SetTargetFPS(60);

    SetActiveScreen(&logoScreen);

    GameObject gameObj;

    gameObj.animals.SetBatFlyRadius(gameObj.map.GetDreamlandSize().width * gameObj.map.GetMapScale());

    int framesCounter{ 0 };

    Timer hudTimer{ 0 };

    while (!WindowShouldClose())
    {
        UpdateAudio();

        switch (applicationState)
        {
        case ApplicationStates::LOGO:
        {
            framesCounter++;

            if (framesCounter > 180)
            {
                SetActiveScreen(&titleScreen);

                applicationState = ApplicationStates::TITLE;
            }

        } break;
        case ApplicationStates::TITLE:
        {
            PlayBGM();
            
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                SetActiveScreen(nullptr);

                applicationState = ApplicationStates::GAMEPLAY;
                
                PauseBGM();
            }

        } break;
        case ApplicationStates::GAMEPLAY:
        {   
            if (IsKeyPressed(KEY_P))
            {
                SetActiveScreen(&pauseScreen);

                applicationState = ApplicationStates::PAUSE;

                PlayBGM();
            }

        } break;
        case ApplicationStates::PAUSE:
        {
            if (IsKeyPressed(KEY_P))
            {
                SetActiveScreen(nullptr);

                applicationState = ApplicationStates::GAMEPLAY;

                PauseBGM();
            }

        } break;
        default: break;
        }

        BeginDrawing();

        ClearBackground(SKYBLUE);

        if (applicationState == ApplicationStates::GAMEPLAY)
        {
            if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_L) || IsKeyPressed(KEY_K))
            {
                StartTimer(&hudTimer, 4.0f);
            }

            UpdateTimer(&hudTimer);

            UpdateCamera(&_camera, &gameObj.player);

            DrawGamePlayScreen(&_camera, &gameObj);

            DrawGamePlayHUD(&gameObj.player, &hudTimer);
        }

        DrawScreen();

        EndDrawing();
    }

    UnloadScreenTexture();

    CloseWindow();

    ShutdownAudio();
}