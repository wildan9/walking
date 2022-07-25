/* by Wildan R. */

#pragma once

#include <vector>
#include "CoreLib.h"

class Screen
{
public:
	virtual void Draw() = 0;

protected:
	void DrawHelixNebula();
	void DrawEarth();
	void DrawGalaxy();
};

void SetActiveScreen(Screen* screen);
void DrawScreen();

void InitScreenTexture();
void UnloadScreenTexture();