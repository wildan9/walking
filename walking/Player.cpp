/* by Wildan R. */

#include "Player.h"

// ---------------- Public Functions ------------------------------------------

Player::Player()
	: _texturePos{ 40.0f, 140.0f }
{

}

Player::~Player()
{
	UnloadTexture(_texture);
	UnloadTexture(_textureIdle);
	UnloadTexture(_textureWalk);
	UnloadTexture(_texturePunch);
	UnloadSound(_landStep);
	UnloadSound(_waterStep);
}

Vector2D Player::GetPosition() const
{
	return _texturePos;
}

Vector2D Player::GetDirection() const
{
	Vector2D direction{};

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x -= 1.0f;
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direction.x += 1.0f;
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direction.y -= 1.0f;
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direction.y += 1.0f;

	return direction;
}

Rectangle Player::GetCollision() const
{
	return Rectangle{
		_texturePos.x, _texturePos.y,
		1.5f * (float)_texture.width / Row(),
		1.5f * (float)_texture.height
	};
}

float Player::GetFacing() const
{
	return _facing;
}

float Player::GetSpeed() const
{
	if (IsKeyDown(KEY_SPACE)) return 4.0f; // walk fast
	else return 2.0f; // walk slow
}

bool Player::IsPunch() const
{
	if (IsKeyDown(KEY_E) && !_isWalk) return 1;
	else return 0;
}

void Player::SetPosition(const Vector2D& pos)
{
	_texturePos = pos;
}

void Player::Stop()
{
	_texturePos = _textureLastPos;
}

void Player::OnLand()
{
	if (GetSpeed() == 2.0f) _timer += GetFrameTime() * 0.23f;
	else _timer += GetFrameTime() * 0.33f;

	if (_isWalk && _timer >= _updateTime)
	{
		_timer = 0.0f;
		PlaySound(_landStep);
	}
}

void Player::OnWater()
{
	if (GetSpeed() == 2.0f) _timer += GetFrameTime() * 0.11f;
	else _timer += GetFrameTime() * 0.13f;

	if (_isWalk && _timer >= _updateTime)
	{
		_timer = 0.0f;
		PlaySound(_waterStep);
	}
}

void Player::Draw()
{
	_textureLastPos = _texturePos;

	if (GetDirection().Length() != NULL)
	{
		_isWalk = 1;
		_texturePos = _texturePos.Subtract(GetDirection().Normalize().Scale(GetSpeed()));
		_texture = _textureWalk;
		if (GetDirection().x < 0.0f) _facing = 1.0f;
		if (GetDirection().x > 0.0f) _facing = -1.0f;
	}
	else
	{
		_isWalk = 0;
		_texture = _textureIdle;
	}

	if (IsPunch()) _texture = _texturePunch;

	Animate(_texturePos, _texture, GetFrameTime(), 1.5f, Row(), _facing, Timer());
}

// ---------------- Private Functions ------------------------------------------

float Player::Row() const
{
	if (IsPunch() && !_isWalk) return 3.0f;
	else if (!_isWalk) return 2.0f;
	else if (_isWalk) return 6.0f;
}

float Player::Timer() const
{
	if (_isWalk) return 0.0f;
	else if (IsPunch() && !_isWalk) return 0.02f;
	else return -0.2f;
}