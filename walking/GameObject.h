/* by Wildan R. */

#pragma once

#include "Player.h"
#include "Map.h"
#include "Animal.cpp"
#include "Prop.cpp"

struct GameObject
{
    Player player{};
    Map map;
    Prop prop;
    Animals animals;
    void PlayWalkSound();
    void CheckCollision();
    void Draw(float deltaTime);
};

inline void GameObject::PlayWalkSound()
{
    if (player.GetPosition().x < -15.0f || player.GetPosition().y < 0.0f ||
        player.GetPosition().x > ((float)map.GetDreamlandSize().width - 15.0f) * map.GetMapScale() &&
        player.GetPosition().x < (float)map.GetDreamlandSize().width + 1500.0f ||
        player.GetPosition().y > (float)map.GetDreamlandSize().height * map.GetMapScale()) player.OnWater();
    else player.OnLand();
}

inline void GameObject::CheckCollision()
{
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

    for (auto& invisibleFence : invisibleFences)
    {
        if (CheckCollisionRecs(player.GetCollision(), 
            Rectangle{ invisibleFence.x, invisibleFence.y, invisibleFence.width, invisibleFence.height })) player.Stop();
    }

    if (CheckCollisionRecs(player.GetCollision(), prop.naturalObj.GetBigStone1Coll())) player.SetPosition(Vector2D{ 3000.0f, 300.0f });

    if (CheckCollisionRecs(player.GetCollision(), prop.naturalObj.GetBigStone2Coll())) player.SetPosition(Vector2D{ 40.0f, 140.0f });
}

inline void GameObject::Draw(float deltaTime)
{
    map.Draw();
    player.Draw();
    prop.Draw();
    animals.Draw(deltaTime);
}