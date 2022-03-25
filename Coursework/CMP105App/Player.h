#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework\GameObject.h"
#include "SFML\Graphics\Texture.hpp"
#include <iostream>
#include "BulletManager.h"
#include "Framework\Vector.h"
#include "GuardFSM.h"
#include "GuardBT.h"
#include "Framework/Collision.h"
#include "GraphicsTools.h"
class Player : public GameObject		//Player class
{
public:
	Player(sf::RenderWindow* hwnd, Input* in, GuardFSM* grdFSM, GuardBT* grtBt);		//Constructor, communicates with manager class to get pointer to the different guard classes
	~Player();

	void Init();		//Init function
	void Update(float dt);		//Update function
	void Render();		//Render function
	void HandleInput(float dt);		//Handle input function
	void Controls(float dt);		//Controls, called in handle input
	void CollisionCheck();		//Collision function

	float pHealth;		//Variables for player class
	bool noise;
private:


	sf::RenderWindow* window;
	Input* input;

	float movSpeed;
	
	sf::Vector2f playerPos;
	sf::Texture playerTex;
	sf::Window* window_;
	GuardFSM* guardFSM;
	GuardBT* guardBT;

	BulletManager bullet;
	sf::Vector2f bulletDir;
	sf::Time time;
	sf::Clock clock;
	GraphicsTools gTools;

};

