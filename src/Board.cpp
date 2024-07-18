#include "Board.h"
#include "Presenter.h"
#include "InputManager.h"
#include "SoundManager.h"

Board::Board()
{

}

Board::~Board()
{

}

void Board::init()
{
	string configFile = "boardInit.txt";

	fstream stream;

	string backgorundImg, tmp;

	stream.open(CONFIG_FOLDER + configFile);

    stream >> tmp >> backgorundImg;

	stream.close();

	m_background = loadTexture(backgorundImg);
	m_player.texture = loadTexture("null.bmp");
	m_player.rect = { 250, 250, 60, 60 };
}

void Board::update()
{
	m_player.rect.x += InputManager::m_joystickCoor.x * 500.0f;
	m_player.rect.y += InputManager::m_joystickCoor.y * 500.0f;
	
	if (InputManager::isJoystickPressed())
	{
		if (num % 2 == 0)
		{
			m_player.texture = loadTexture("TitleScreen.bmp");
		}
		else 
		{
			m_player.texture = loadTexture("null.bmp");
		}
		num++;
	}
}

void Board::draw()
{
	drawObject(m_background);
	drawObject(m_player);
}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);
}