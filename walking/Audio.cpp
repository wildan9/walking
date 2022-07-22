/* by Wildan R. */

#include "Audio.h"

bool muted{ 0 };

std::vector<Sound> sounds;

int LoadSoundFile(const char* sound)
{
	sounds.push_back(LoadSound(sound));
	return int(sounds.size() - 1);
}

void InitAudio()
{
	InitAudioDevice();

	LoadSoundFile("sounds/land_step.wav");
	LoadSoundFile("sounds/water_step.wav");
}

void ShutdownAudio()
{
	CloseAudioDevice();

	for (auto& sound : sounds)
	{
		UnloadSound(sound);
	}

	sounds.clear();
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