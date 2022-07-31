/* by Wildan R. */

#include "Audio.h"

float masterVolume{ 0.2f };

Music bgm{};

void InitAudio()
{
	InitAudioDevice();

	StartBGM("sounds/epic_cinematic_trailer_elite.ogg");
}

void UpdateAudio()
{
	if (bgm.frameCount > 0)
	{
		UpdateMusicStream(bgm);
	}

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

void StartBGM(const char* musicFIle)
{
	bgm = LoadMusicStream(musicFIle);
	bgm.looping = 1;
}

void PlayBGM()
{
	PlayMusicStream(bgm);
}

void PauseBGM()
{
	PauseMusicStream(bgm);
}

void StopBGM()
{
	if (bgm.frameCount > 0)
	{
		StopMusicStream(bgm);

		bgm.frameCount = 0;

		UnloadMusicStream(bgm);
	}
}

void ShutdownAudio()
{
	StopBGM();

	CloseAudioDevice();
}

float GetMasterVolume()
{
	return masterVolume;
}