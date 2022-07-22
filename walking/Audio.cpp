/* by Wildan R. */

#include "Audio.h"

bool muted{ 0 };

std::vector<Sound> sounds;

int8_t LoadSoundFile(const char* sound)
{
	sounds.push_back(LoadSound(sound));
	return int8_t(sounds.size() - 1);
}

void InitAudio()
{
	InitAudioDevice();

	LoadSoundFile("sounds/land_step.wav");
	LoadSoundFile("sounds/water_step.wav");
	LoadSoundFile("sounds/getting_punched.wav");
}

void ShutdownAudio()
{
	for (const auto& sound : sounds)
	{
		UnloadSound(sound);
	}

	sounds.clear();
	
	if (sounds.empty())
	{
		CloseAudioDevice();
	}
}

void PlaySound(const int8_t& sound)
{
	if (!muted)
	{
		PlaySound(sounds[sound]);
	}
}

void UpdateAudio()
{
	if (IsKeyPressed(KEY_M))
	{
		muted = !muted;
	}
}

bool IsMuted()
{
	return muted;
}