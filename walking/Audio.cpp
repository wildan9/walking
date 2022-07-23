/* by Wildan R. */

#include "Audio.h"

float masterVolume{ 0.2f };

void SetVolume(float volume)
{
	SetMasterVolume(volume);
}

void UpdateAudioDevice()
{
	if (IsKeyPressed(KEY_L) && masterVolume < 0.5f)
	{
		masterVolume += 0.1f;
	}

	if (IsKeyPressed(KEY_K) && masterVolume > 0.0f)
	{
		masterVolume -= 0.1f;
	}

	if (masterVolume < 0.0f)
	{
		masterVolume = 0.0f;
	}

	SetVolume(masterVolume);

	if (IsKeyPressed(KEY_M))
	{
		masterVolume = (masterVolume == 0.0f) ? masterVolume = 0.2f : masterVolume = 0.0f;
	}
}

float GetMasterVolume()
{
	return masterVolume;
}

bool IsMuted()
{
	if (masterVolume == 0.0f) return 1;
	else return 0;
}