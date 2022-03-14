#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework\GameObject.h"
#include "SFML\Graphics\Texture.hpp"
#include <iostream>
#include "BulletManager.h"
#include "Framework\Vector.h"
#include "GuardFSM.h"
#include "Framework/Collision.h"
#include "GraphicsTools.h"
class Player : public GameObject
{
public:
	Player(sf::RenderWindow* hwnd, Input* in, GuardFSM* grdFSM);
	~Player();

	void Init();
	void Update(float dt);
	void Render();
	void HandleInput(float dt);
	void Controls(float dt);
	void CollisionCheck();

	float pHealth;
	bool noise;
private:


	sf::RenderWindow* window;
	Input* input;

	float movSpeed;
	
	sf::Vector2f playerPos;
	sf::Texture playerTex;
	sf::Window* window_;
	GuardFSM* guardFSM;

	BulletManager bullet;
	sf::Vector2f bulletDir;
	sf::Time time;
	sf::Clock clock;
	GraphicsTools gTools;

};

