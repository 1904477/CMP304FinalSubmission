#include "GuardFSM.h"

GuardFSM::GuardFSM(sf::RenderWindow* hwnd) : graphicsTools(hwnd)
{
	window = hwnd;
}

GuardFSM::~GuardFSM()
{
}

void GuardFSM::Init()
{
	setAlive(true);																//Guard is alive
	health = 100;																//Health is set
	setSize(sf::Vector2f(100, 100));											//Set size of guard
	setPosition(1000, 200);														//Set starting position of guard
	text.loadFromFile("gfx/skeleton.png");											//Load texture 
	setTexture(&text);																//Set texture
	setCollisionBox(sf::FloatRect(-20, -20, getSize().x / 2, getSize().y / 2));			//Set origin of guard
	setOrigin(getSize().x / 2, getSize().y / 2);										//Initialized graphics tools
	graphicsTools.Init();															//Guard starts rotated towards player
	setRotation(180);

}

void GuardFSM::Update(float dt,sf::Vector2f playerPos)
{
	graphicsTools.Update( sf::Vector2f (getPosition().x-getSize().x/2 , getPosition().y -getSize().y/2),health);		//Display health bar
}

void GuardFSM::Render()
{
	window->draw(*this);		 //Draw guard
	graphicsTools.Render();		 //Render health bar
}
