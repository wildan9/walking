/* by Wildan R. */

#pragma once

#include "raylib.h"
#include "GameObject.h"

class Screen
{
public:
	virtual void Draw() = 0;

protected:
	// TODO: Update some variables/functions here
};

void SetActiveScreen(Screen* screen);
void DrawScreen();
