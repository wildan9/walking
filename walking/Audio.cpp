/* by Wildan R. */

#include "Audio.h"

float masterVolume{ 0.2f };

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

	if (IsKeyPressed(KEY_M))
	{
		masterVolume = (masterVolume == 0.0f) ? masterVolume = 0.2f : masterVolume = 0.0f;
	}

	SetMasterVolume(masterVolume);
}

float GetMasterVolume()
{
	return masterVolume;
}