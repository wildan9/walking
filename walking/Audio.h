/* by Wildan R. */

#pragma once

#include "CoreLib.h"

void  InitAudio();
void  UpdateAudio();
void  StartBGM(const char* musicFile);
void  ShutdownAudio();
void  PlayBGM();
void  PauseBGM();
float GetMasterVolume();