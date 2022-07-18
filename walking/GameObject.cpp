/* by Wildan R. */

#include "GameObject.h"

void GameObject::PlayWalkSound()
{
    if (player.GetPosition().x < -15.0f || player.GetPosition().y < 0.0f ||
        player.GetPosition().x > ((float)map.GetDreamlandSize().width - 15.0f) * map.GetMapScale() &&
        player.GetPosition().x < (float)map.GetDreamlandSize().width + 1500.0f ||
        player.GetPosition().y > (float)map.GetDreamlandSize().height * map.GetMapScale())
    {
        player.OnWater();
    }
    else
    {
        player.OnLand();
    }
}

void GameObject::CheckCollision()
{
    if (CheckCollisionRecs(player.GetCollision(), animals.crocodile.GetCollision()) &&
        player.IsPunch() && OnTouch(&player, animals.crocodile.GetFacing(), animals.crocodile.GetPosition().x))
    {
        animals.crocodile.Hurt();
    }
    else
    {
        animals.crocodile.Walk();
    }

    for (auto& rhino : animals.rhinos)
    {
        if (CheckCollisionRecs(player.GetCollision(), rhino.GetCollision()) && player.GetSpeed() == 2.0f)
        {
            rhino.UpdatePosition(&player);
        }
        else if (CheckCollisionRecs(player.GetCollision(), rhino.GetCollision()) && player.GetSpeed() == 4.0f)
        {
            player.Stop();
        }
    }

    if (CheckCollisionRecs(player.GetCollision(), map.GetMapLine1()) ||
        CheckCollisionRecs(player.GetCollision(), map.GetMapLine2())) player.Stop();

    for (auto& invisibleFence : invisibleFences)
    {
        if (CheckCollisionRecs(player.GetCollision(),
            Rectangle{ invisibleFence.x, invisibleFence.y, invisibleFence.width, invisibleFence.height }))
        {
            player.Stop();
        }
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

void GameObject::Draw(float deltaTime)
{
    map.Draw();
    player.Draw();
    prop.Draw();
    animals.Draw(deltaTime);
}