#include "BulletManager.h"


BulletManager::BulletManager(sf::RenderWindow*hwnd)
{
	window = hwnd;

}

BulletManager::~BulletManager()
{
}

void BulletManager::Init()
{
	texture.loadFromFile("gfx/bullet.png");
	for (int i = 0; i < 1000; i++)
	{
		bullets.push_back(Bullet());
		bullets[i].setAlive(false);
		bullets[i].setTexture(&texture);
		bullets[i].setFillColor(sf::Color::Red);
		bullets[i].setSize(sf::Vector2f(120, 120));
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, 30, 30));
	}
}

void BulletManager::Update(float dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].Update(dt);
		}
	}
	DeathCheck();
}

void BulletManager::Render()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);
		}
	}
}

void BulletManager::DeathCheck()
{

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			distanceToPlayer = bullets[i].getPosition() - spawnPosition;
			distanceToPlayerLenght = Vector::magnitude(distanceToPlayer);

			if (bullets[i].getPosition().x <0)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().x > window->getSize().x)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < 0)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > window->getSize().y)
			{
				bullets[i].setAlive(false);
			}
			if (distanceToPlayerLenght > 400)
			{
				bullets[i].setAlive(false);
			}

		}
	}
}

void BulletManager::Spawn(sf::Vector2f velocity,sf::Vector2f playerSize)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].isAlive())
		{
			velocity = sf::Vector2f(velocity.x * 1400, velocity.y * 1400);
			bullets[i].setAlive(true);
			bullets[i].setPosition(spawnPosition.x-playerSize.x/2,spawnPosition.y-playerSize.y/2);
			bullets[i].setVelocity(velocity);
			return;
		}
	}
}
