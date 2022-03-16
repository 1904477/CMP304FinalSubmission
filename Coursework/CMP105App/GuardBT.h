#pragma once
#include "SFML\Graphics.hpp"
#include "Framework\GameObject.h"
#include "Framework\Vector.h"
#include "GraphicsTools.h"
#include <iostream>
class GuardBT : public GameObject
{
public:
	GuardBT(sf::RenderWindow* hwnd);
	~GuardBT();


	void Init();
	void Update(float dt, sf::Vector2f playerPos);
	void Render();

	sf::RenderWindow* window;
	sf::Texture text;

	float speed;
	float health;
	GraphicsTools graphicsTools;



};

