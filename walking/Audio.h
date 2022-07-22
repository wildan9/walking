/* by Wildan R. */

#pragma once

#include <vector>
#include "CoreLib.h"

const int8_t landStep{ 0 };
const int8_t waterStep{ 1 };
const int8_t gettingPunched{ 2 };

int8_t LoadSoundFile(const char* sound);

void InitAudio();
void ShutdownAudio();
void PlaySound(const int8_t& sound);
void UpdateAudio();

bool IsMuted();