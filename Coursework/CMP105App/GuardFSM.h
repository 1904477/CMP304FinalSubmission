#pragma once
#include "SFML\Graphics.hpp"
#include "Framework\GameObject.h"
#include "Framework\Vector.h"
#include "GraphicsTools.h"
#include <iostream>
class GuardFSM : public GameObject		//Class for guard that uses FSM
{
public:
	GuardFSM(sf::RenderWindow*hwnd);	//Constructor
	~GuardFSM();						//Destructor


	void Init();		//Init function
	void Update(float dt, sf::Vector2f playerPos);		//Update function
	void Render();		//Render function

	//Variables for guard class
	sf::RenderWindow* window;
	sf::Texture text;
	float speed;
	float health;
	GraphicsTools graphicsTools;

};

