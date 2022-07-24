#include "Screen.h"

Screen* activeScreen = nullptr;

void SetActiveScreen(Screen* screen)
{
	activeScreen = screen;
}

void DrawScreen()
{
	if (activeScreen != nullptr)
	{
		activeScreen->Draw();
	}
}