#include "TitleScreen.h"
#include "World.h"

extern World world;

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::init()
{
	m_titleScreenLogo.rect = { 0, 0, 1920, 1080 };
	m_titleScreenLogo.texture = loadTexture("TitleScreen.bmp");
}

void TitleScreen::run()
{
	drawObject(m_titleScreenLogo);

	if (isAnyKeyPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::GAME);
		return;
	}
}

void TitleScreen::destroy()
{
	SDL_DestroyTexture(m_titleScreenLogo.texture);
}