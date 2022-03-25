#pragma once
#include"SFML\Graphics.hpp"
#include "Framework\GameObject.h"
#include <iostream>
class Goal : public GameObject
{
public:			//Goal class
	Goal(sf::RenderWindow*hwnd);			//Constructor		
	~Goal();								//Destructor

	void Init();		//Init function
	void Update(sf::Vector2f playerPos);		//Update function
	void Render();			//Render function
	void RenderWin();		//Render win 
	void RenderLoss();		//Render loss

	sf::RenderWindow* window;		//Different variables
	sf::Font font;
	sf::Text exitText;
	sf::Text winText;
	sf::Text loseText;

	bool win;		//Check if player wins
};

