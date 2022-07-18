/* by Wildan R. */

#pragma once

#include "Animation.h"

class Player : public BaseAnimation
{
public:
	Player();
	~Player();
	Vector2D GetPosition() const;
	Vector2D GetDirection() const;
	Rectangle GetCollision() const;
	bool IsTeleport() const; // don't need cinematic effect when teleporting
	bool IsPunch() const;
	float GetFacing() const;
	float GetSpeed() const;
	void SetPosition(const Vector2D& pos);
	void SetTeleportStatus(bool status); // don't need cinematic effect when teleporting
	void Stop();
	void OnLand();
	void OnWater();
	void Draw();

private:
	bool _isWalk{ 0 }, _isTeleport{ 0 };
	float _timer{}, _facing{ 1.0f };
	float Row() const;
	float Timer() const;
	const float _updateTime{ 0.0834f };
	Vector2D _texturePos{};
	Vector2D _textureLastPos{};
	Sound _landStep{ LoadSound("sounds/land_step.wav") };
	Sound _waterStep{ LoadSound("sounds/water_step.wav") };
	Texture2D _texture{ LoadTexture("textures/character/friendly_man_idle.png") };
	Texture2D _textureIdle{ LoadTexture("textures/character/friendly_man_idle.png") };
	Texture2D _texturePunch{ LoadTexture("textures/character/friendly_man_punch.png") };
	Texture2D _textureWalk{ LoadTexture("textures/character/friendly_man_walk.png") };
};