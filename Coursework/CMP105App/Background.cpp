#include "Background.h"

Background::Background(sf::RenderWindow* hwnd)
{
	window = hwnd;
}

Background::~Background()
{
}

void Background::Init()
{
	text.loadFromFile("gfx/grass.png");		//Load background texture
	setTexture(&text);		//Set background texture
	setPosition(0, 0);		//Position starts in top left (0,0)
}

void Background::Render()
{
	setSize(sf::Vector2f(window->getSize().x, window->getSize().y));		//Size equal to window size
	window->draw(*this);		//Draw background
}
