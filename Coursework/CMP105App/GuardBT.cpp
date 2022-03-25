#include "GuardBT.h"		
GuardBT::GuardBT(sf::RenderWindow* hwnd) : graphicsTools(hwnd)
{
	window = hwnd;
}

GuardBT::~GuardBT()
{
}

void GuardBT::Init()
{
	setAlive(true);								//Guard is alive
	health = 100;								//Health is set
	setSize(sf::Vector2f(100, 100));			//Set size of guard
	setPosition(1000, 500);						//Set starting position of guard
	text.loadFromFile("gfx/skeleton.png");			//Load texture 
	setTexture(&text);								//Set texture
	setOrigin(getSize().x / 2, getSize().y / 2);	//Set origin of guard
	graphicsTools.Init();								//Initialized graphics tools
	setRotation(180);								//Guard starts rotated towards player

}

void GuardBT::Update(float dt, sf::Vector2f playerPos)
{
	graphicsTools.Update(sf::Vector2f(getPosition().x - getSize().x / 2, getPosition().y - getSize().y / 2), health);		//Display health bar
}

void GuardBT::Render()
{
	window->draw(*this);		//Draw guard
	graphicsTools.Render();		//Render health bar
}
