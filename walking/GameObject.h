/* by Wildan R. */

#pragma once

#include "Map.h"
#include "Player.h"
#include "Prop.cpp"
#include "Animal.cpp"

class GameObject
{
public:
    Map map{};
    Prop prop{};
    Player player{};
    Animals animals{};
    void PlayWalkSound();
    void CheckCollision();
    void Draw(float deltaTime);

private:
    inline bool GameObject::on_touch(Player* player, const float targetFacing, const float targetPosX)
    {
        if (player->GetFacing() == 1.0f && targetFacing >= -1.0f && player->GetPosition().x < targetPosX) return 1;
        else if (player->GetFacing() == -1.0f && targetFacing >= -1.0f && player->GetPosition().x > targetPosX) return 1;
        else return 0;
    }
};