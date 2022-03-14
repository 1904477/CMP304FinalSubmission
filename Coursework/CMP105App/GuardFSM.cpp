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
	setAlive(true);
	health = 100;
	setSize(sf::Vector2f(100, 100));
	setPosition(1000, 200);
	text.loadFromFile("gfx/skeleton.png");
	setTexture(&text);
	setCollisionBox(sf::FloatRect(-20, -20, getSize().x/2, getSize().y/2));
	setOrigin(getSize().x / 2, getSize().y / 2);
	graphicsTools.Init();
	setRotation(180);

}

void GuardFSM::Update(float dt,sf::Vector2f playerPos)
{
	graphicsTools.Update( sf::Vector2f (getPosition().x-getSize().x/2 , getPosition().y -getSize().y/2),health);
	if (health <= 0)
		setAlive(false);
}

void GuardFSM::Render()
{
	window->draw(*this);
	graphicsTools.Render();
}
