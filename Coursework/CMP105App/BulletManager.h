#pragma once
#include "Bullet.h"
#include "Framework\GameObject.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Framework\Vector.h"
class BulletManager		//Class that manages all bullets
{
	public:
	BulletManager(sf::RenderWindow*hwnd);		//Constructor
	~BulletManager();							//Destructor
			
	void Init();			//Initialize function
	void Update(float dt);			//Update Function
	void Render();					//Render Function
	void DeathCheck();				//Checks if bullet need to die
	void Spawn(sf::Vector2f velocity, sf::Vector2f playerSize);		//Spawn Bullets

	sf::Vector2f spawnPosition;			//Variables and vectors
	std::vector<Bullet>bullets;
	
private:

	sf::Texture texture;
	sf::RenderWindow* window;
	sf::Vector2f distanceToPlayer;
	float distanceToPlayerLenght;


};

