/* by Wildan R. */

#pragma once

#include "raylib.h"

namespace raylib 
{
    struct Camera2D : public ::Camera2D
    {
        Camera2D() : ::Camera2D{ offset = {}, target = {}, rotation = 0.0f, zoom = 1.0f } {}

        inline Camera2D& BeginMode()
        {
            ::BeginMode2D(*this);
            return *this;
        }

        inline Camera2D& EndMode()
        {
            ::EndMode2D();
            return *this;
        }
    };
}