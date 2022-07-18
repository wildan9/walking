/*
                                                  !_
                                                  |*~=-.,
                                                  |_,-'`
                                                  |
                                                  |
                                                 /^\
                   !_                           /   \
                   |*`~-.,                     /,    \
                   |.-~^`                     /#"     \
                   |                        _/##_   _  \_
              _   _|  _   _   _            [ ]_[ ]_[ ]_[ ]
             [ ]_[ ]_[ ]_[ ]_[ ]            |_=_-=_ - =_|
           !_ |_=_ =-_-_  = =_|           !_ |=_= -    |
           |*`--,_- _        |            |*`~-.,= []  |
           |.-'|=     []     |   !_       |_.-"`_-     |
           |   |_=- -        |   |*`~-.,  |  |=_-      |
          /^\  |=_= -        |   |_,-~`  /^\ |_ - =[]  |
      _  /   \_|_=- _   _   _|  _|  _   /   \|=_-      |
     [ ]/,    \[ ]_[ ]_[ ]_[ ]_[ ]_[ ]_/,    \[ ]=-    |
      |/#"     \_=-___=__=__- =-_ -=_ /#"     \| _ []  |
     _/##_   _  \_-_ =  _____       _/##_   _  \_ -    |\
    [ ]_[ ]_[ ]_[ ]=_0~{_ _ _}~0   [ ]_[ ]_[ ]_[ ]=-   | \
    |_=__-_=-_  =_|-=_ |  ,  |     |_=-___-_ =-__|_    |  \
     | _- =-     |-_   | ((* |      |= _=       | -    |___\
     |= -_=      |=  _ |  `  |      |_-=_       |=_    |/+\|
     | =_  -     |_ = _ `-.-`       | =_ = =    |=_-   ||+||
     |-_=- _     |=_   =            |=_= -_     |  =   ||+||
     |=_- /+\    | -=               |_=- /+\    |=_    |^^^|
     |=_ |+|+|   |= -  -_,--,_      |_= |+|+|   |  -_  |=  |
     |  -|+|+|   |-_=  / |  | \     |=_ |+|+|   |-=_   |_-/
     |=_=|+|+|   | =_= | |  | |     |_- |+|+|   |_ =   |=/
     | _ ^^^^^   |= -  | |  <&>     |=_=^^^^^   |_=-   |/
     |=_ =       | =_-_| |  | |     |   =_      | -_   |
     |_=-_       |=_=  | |  | |     |=_=        |=-    |
^^^^^^^^^^`^`^^`^`^`^^^""""""""^`^^``^^`^^`^^`^`^``^`^``^``^^
*/

/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/

/* by Wildan R. */

#pragma once

#include <math.h>
#include <string>
#include <raylib.h>

namespace raylib
{
    struct Camera2D : public ::Camera2D
    {
        Camera2D() 
            : ::Camera2D{ offset = {}, target = {}, rotation = 0.0f, zoom = 1.0f }
        {}

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

using String = std::string;

namespace Math2D
{
    struct Vector2D : public Vector2
    {
        Vector2D(const Vector2 vec)
            : Vector2{ vec.x, vec.y }
        {}

        Vector2D(float x, float y)
            : Vector2{ x, y }
        {}

        Vector2D(float x)
            : Vector2{ x, 0.0f }
        {}

        Vector2D()
            : Vector2{ 0.0f, 0.0f }
        {}

        inline float Length() const
        {
            return float{ sqrtf((x * x) + (y * y)) };
        }

        inline float DotProduct(const Vector2D& vec) const
        {
            return float{ x * vec.x + y * vec.y };
        }

        inline Vector2D Add(const Vector2D& vec) const
        {
            return Vector2D{ x + vec.x, y + vec.y };
        }

        inline Vector2D Add(const Vector2 vec) const
        {
            return Vector2D{ x + vec.x, y + vec.y };
        }

        inline Vector2D Subtract(const Vector2D& vec) const
        {
            return Vector2D{ x - vec.x, y - vec.y };
        }

        inline Vector2D Subtract(const Vector2 vec) const
        {
            return Vector2D{ x - vec.x, y - vec.y };
        }

        inline Vector2D Scale(float scale) const
        {
            return Vector2D{ x * scale, y * scale };
        }

        inline Vector2D Normalize() const
        {
            Vector2D result{};

            float length{ sqrtf((x * x) + (y * y)) };

            if (length > 0)
            {
                float ilength = 1.0f / length;
                result.x = x * ilength;
                result.y = y * ilength;
            }

            return result;
        }

        inline Vector2D Rotate(float angle) const
        {
            Vector2D result{};

            float cosres{ cosf(angle) };
            float sinres{ sinf(angle) };

            result.x = x * cosres - y * sinres;
            result.y = x * sinres + y * cosres;

            return result;
        }

        inline String ToString() const
        {
            String str{};

            str.append("x: ")
                .append(std::to_string((int)x))
                .append("  y: ")
                .append(std::to_string((int)y));

            return str;
        }
    };
}

using namespace Math2D;