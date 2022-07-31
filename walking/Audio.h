/* by Wildan R. */

#pragma once

#include "CoreLib.h"

void  InitAudio();
void  UpdateAudio();
void  StartBGM(const char* musicFIle);
void  ShutdownAudio();
void  PlayBGM();
void  PauseBGM();
float GetMasterVolume();