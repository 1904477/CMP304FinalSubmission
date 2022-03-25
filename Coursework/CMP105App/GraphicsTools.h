#pragma once
#include "Framework\GameObject.h"
#include "SFML\Graphics.hpp"
class GraphicsTools: public GameObject		//Class to render in game element or texts
{
public: 
	GraphicsTools(sf::RenderWindow*hwnd);		//Constructor
	~GraphicsTools();							//Destructor

	void Init();			//Init function
	void Update(sf::Vector2f pos,float health);		//Update function
	void Render();		//render function

	sf::RenderWindow* window;
};

