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
	text.loadFromFile("gfx/grass.png");
	setTexture(&text);

	setPosition(0, 0);
}

void Background::Render()
{
	setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	window->draw(*this);
}
