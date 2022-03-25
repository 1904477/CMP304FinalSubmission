#pragma once
#include "SFML\Graphics.hpp"
#include "Framework\GameObject.h"
#include "Framework\Vector.h"
#include "GraphicsTools.h"
#include <iostream>
class GuardBT : public GameObject		//Class for guard that uses behaviour tree
{
public:
	GuardBT(sf::RenderWindow* hwnd);		//Constructor
	~GuardBT();								//Destructor


	void Init();		//Init function
	void Update(float dt, sf::Vector2f playerPos);		//Update function
	void Render();		//Render function

	//Different variables for  guard class
	sf::RenderWindow* window;
	sf::Texture text;
	float speed;
	float health;
	GraphicsTools graphicsTools;
};

