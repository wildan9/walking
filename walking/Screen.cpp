/* by Wildan R. */

#include "Screen.h"

Screen* activeScreen = nullptr;

std::vector<Texture2D> textures;

uint8_t LoadTextureFile(const char* texture)
{
	textures.push_back(LoadTexture(texture));
	return uint8_t(textures.size() - 1);
}

void InitScreenTexture()
{
	LoadTextureFile("textures/screens_bg/helix_nebula.png");
	LoadTextureFile("textures/screens_bg/earth.png");
	LoadTextureFile("textures/screens_bg/galaxy.png");
}

void Screen::DrawHelixNebula()
{
	DrawTextureV(textures[0], {}, WHITE);
}

void Screen::DrawEarth()
{
	DrawTextureV(textures[1], {}, WHITE);
}

void Screen::DrawGalaxy()
{
	DrawTextureV(textures[2], {}, WHITE);
}

void UnloadScreenTexture()
{
	if (!textures.empty())
	{
		for (const auto& texture : textures)
		{
			UnloadTexture(texture);
		}

		textures.clear();
	}
}

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