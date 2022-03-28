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
	texture.loadFromFile("gfx/bullet.png");		//load texture for bullet
	for (int i = 0; i < 1000; i++)		//Handle 1000 bullets
	{
		bullets.push_back(Bullet());		//Bullet pushed back to the vector
		bullets[i].setAlive(false);			//Start as dead
		bullets[i].setTexture(&texture);	//Sets texture of bullet
		bullets[i].setFillColor(sf::Color::Red);	//Bullets colour
		bullets[i].setSize(sf::Vector2f(120, 120));		//Bullets size
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, 30, 30));		//Set collision box of bullets
	}
}

void BulletManager::Update(float dt)		
{
	for (int i = 0; i < bullets.size(); i++)		//Update bullets only if they are alive
	{
		if (bullets[i].isAlive())
		{
			bullets[i].Update(dt);
		}
	}
	DeathCheck();		//Check if bullets are dead
}

void BulletManager::Render()
{
	for (int i = 0; i < bullets.size(); i++)		//Render bullets only if they are alive
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
		if (bullets[i].isAlive())		//Different checks to set bullets dead
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
			if (distanceToPlayerLenght > 150)
			{
				bullets[i].setAlive(false);
			}

		}
	}
}

void BulletManager::Spawn(sf::Vector2f velocity,sf::Vector2f playerSize)		
{
	for (int i = 0; i < bullets.size(); i++)		//Spawn bullets if they are alive
	{
		if (!bullets[i].isAlive())
		{
			velocity = sf::Vector2f(velocity.x * 700, velocity.y * 700);		//Velocity is set
			bullets[i].setAlive(true);		//Bullets once spawned are alive
			bullets[i].setPosition(spawnPosition.x-playerSize.x/2,spawnPosition.y-playerSize.y/2);		//Spawn position based on player position and size
			bullets[i].setVelocity(velocity);		//Set velocity of bullet
			return;
		}
	}
}
