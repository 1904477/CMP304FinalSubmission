#pragma once
#include "SFML\Graphics.hpp"
#include "Framework\GameObject.h"
class Background : public GameObject		//Class for background
{
public:
	Background(sf::RenderWindow*hwnd);		//Constructor
	~Background();							//Destructor

		void Init();			//Initializer
		void Render();			//Render Background
	
	sf::RenderWindow* window;
	sf::Texture text;


};

