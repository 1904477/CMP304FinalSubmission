#pragma once
#include "Framework\GameObject.h"
#include "SFML\Graphics.hpp"
class GraphicsTools: public GameObject
{
public: 
	GraphicsTools(sf::RenderWindow*hwnd);
	~GraphicsTools();

	void Init();
	void Update(sf::Vector2f pos,float health);
	void Render();

	sf::RenderWindow* window;
};

