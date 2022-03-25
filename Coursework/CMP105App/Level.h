#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include <string>
#include <iostream>
#include "Manager.h"

class Level{		//Main level class
public:
	Level(sf::RenderWindow* hwnd, Input* in);		//Constructor
	~Level();			//destructor

	void handleInput(float dt);			//Handle input function
	void update(float dt);				//Update function	
	void render();		//render function

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
	Manager manager;
};