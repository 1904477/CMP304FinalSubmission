#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Background.h"
#include "Player.h"
#include "GuardFSM.h"
#include "GuardBT.h"
#include "FSM.h"
#include "BTState.h"
#include "Goal.h"
class Manager		//Manager class, handle everything and is called in level
{
public:
	Manager(sf::RenderWindow* hwnd, Input* in);		//Constructor
	~Manager();			//Destructor

	void Init();		//Init function
	void Update(float dt);		//Update function
	void Render();		//Render function

private:		//Variables for manager class
	sf::RenderWindow* window;
	Input* input;
	Player player;
	Background background;
	GuardFSM guardFSM;
	GuardBT guardBT;
	FSM fsm;
	BTState btState;
	Goal goal;
};

