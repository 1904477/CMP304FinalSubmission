#pragma once
#include "Bullet.h"
#include "Framework\GameObject.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Framework\Vector.h"
class BulletManager
{
	public:
	BulletManager(sf::RenderWindow*hwnd);
	~BulletManager();

	void Init();
	void Update(float dt);
	void Render();
	void DeathCheck();
	void Spawn(sf::Vector2f velocity, sf::Vector2f playerSize);

	sf::Vector2f spawnPosition;
	std::vector<Bullet>bullets;

private:

	sf::Texture texture;
	sf::RenderWindow* window;
	sf::Vector2f distanceToPlayer;
	float distanceToPlayerLenght;


};

