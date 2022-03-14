#pragma once
#include "SFML\Graphics.hpp"
#include "Framework\GameObject.h"
class Background : public GameObject
{
public:
	Background(sf::RenderWindow*hwnd);
	~Background();

	void Init();
	void Render();
	
	sf::RenderWindow* window;
	sf::Texture text;


};

