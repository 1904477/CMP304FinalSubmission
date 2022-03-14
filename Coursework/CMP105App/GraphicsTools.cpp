#include "GraphicsTools.h"

GraphicsTools::GraphicsTools(sf::RenderWindow* hwnd)
{
	window = hwnd;
}

GraphicsTools::~GraphicsTools()
{
}

void GraphicsTools::Init()
{
	setSize(sf::Vector2f(100, 20));
	setFillColor(sf::Color::Green);

}

void GraphicsTools::Update(sf::Vector2f pos, float health)
{
	setPosition(pos);
	setSize(sf::Vector2f(health, 20));
}

void GraphicsTools::Render()
{
	window->draw(*this);
}
