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
	setAlive(true);
	health = 100;
	setSize(sf::Vector2f(100, 100));
	setPosition(1000, 500);
	text.loadFromFile("gfx/skeleton.png");
	setTexture(&text);
	setCollisionBox(sf::FloatRect(-20, -20, getSize().x / 2, getSize().y / 2));
	setOrigin(getSize().x / 2, getSize().y / 2);
	graphicsTools.Init();
	setRotation(180);

}

void GuardBT::Update(float dt, sf::Vector2f playerPos)
{
	graphicsTools.Update(sf::Vector2f(getPosition().x - getSize().x / 2, getPosition().y - getSize().y / 2), health);
	if (health <= 0)
		setAlive(false);
}

void GuardBT::Render()
{
	window->draw(*this);
	graphicsTools.Render();
}
