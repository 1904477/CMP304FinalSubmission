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
	setSize(sf::Vector2f(100, 20));	//Set size
	setFillColor(sf::Color::Green);	//Set colour

}

void GraphicsTools::Update(sf::Vector2f pos, float health)
{
	setPosition(pos);		//Set position
	setSize(sf::Vector2f(health, 20));	//Set size ( to make health bar decrease
}

void GraphicsTools::Render()
{
	window->draw(*this);		//Draw 
}
