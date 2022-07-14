/* by Wildan R. */

#pragma once

#include "Player.h"
#include "Map.h"
#include "Animal.cpp"
#include "Prop.cpp"

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
        player.IsPunch() && on_touch(&player, animals.crocodile.GetFacing(), animals.crocodile.GetPosition().x))
    {
        animals.crocodile.Hurt();
    }
    else
    {
        animals.crocodile.Walk();
    }

    for (auto& rhino : animals.rhinos) if (CheckCollisionRecs(player.GetCollision(), rhino.GetCollision())) player.Stop();

    if (CheckCollisionRecs(player.GetCollision(), map.GetMapLine1()) ||
        CheckCollisionRecs(player.GetCollision(), map.GetMapLine2())) player.Stop();

    for (auto& invisibleFence : invisibleFences)
    {
        if (CheckCollisionRecs(player.GetCollision(),
            Rectangle{ invisibleFence.x, invisibleFence.y, invisibleFence.width, invisibleFence.height })) player.Stop();
    }

    if (CheckCollisionRecs(player.GetCollision(), prop.naturalObj.GetBigStone1Coll()))
    {
        player.SetPosition({ 3400.0f - 80.0f, 600.0f });
        player.SetTeleportStatus(1);
    }

    if (CheckCollisionRecs(player.GetCollision(), prop.naturalObj.GetBigStone2Coll()))
    {
        player.SetPosition({ 1600.0f - 80.0f, 700.0f });
        player.SetTeleportStatus(1);
    }
}

inline void GameObject::Draw(float deltaTime)
{
    map.Draw();
    player.Draw();
    prop.Draw();
    animals.Draw(deltaTime);
}