#pragma once
#include "SFML\Graphics.hpp"
#include "Framework\GameObject.h"
#include "Framework\Vector.h"
#include "GraphicsTools.h"
#include <iostream>
class GuardFSM : public GameObject
{
public:
	GuardFSM(sf::RenderWindow*hwnd);
	~GuardFSM();


	void Init();
	void Update(float dt, sf::Vector2f playerPos);
	void Render();

	sf::RenderWindow* window;
	sf::Texture text;

	float speed;
	float health;
	GraphicsTools graphicsTools;

};

