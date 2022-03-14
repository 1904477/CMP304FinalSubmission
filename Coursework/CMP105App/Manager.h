#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Background.h"
#include "Player.h"
#include "GuardFSM.h"
#include "GuardBT.h"
#include "FSM.h"
#include "BTState.h"
class Manager
{
public:
	Manager(sf::RenderWindow* hwnd, Input* in);
	~Manager();

	void Init();
	void Update(float dt);
	void Render();

private:
	sf::RenderWindow* window;
	Input* input;
	Player player;
	Background background;
	GuardFSM guardFSM;
	GuardBT guardBT;
	FSM fsm;
	BTState btState;
};

