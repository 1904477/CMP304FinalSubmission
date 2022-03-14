#include "Manager.h"

Manager::Manager(sf::RenderWindow* hwnd, Input* in) : player(hwnd, in, &guardFSM),      background(hwnd),        guardFSM(hwnd),       fsm(hwnd, &guardFSM, &player),       guardBT(hwnd),     btState(hwnd, &guardBT, &player)
{
	window = hwnd;
	input = in;
}

Manager::~Manager()
{
}

void Manager::Init()
{
	player.Init();
	background.Init();
	guardFSM.Init();
	guardBT.Init();
	fsm.Init();
}

void Manager::Update(float dt)
{
	player.Update(dt);
	if (guardFSM.isAlive() == true)
	{
		guardFSM.Update(dt, player.getPosition());
		fsm.Update(dt);
	}
	if (guardBT.isAlive() == true)
	{
		guardBT.Update(dt, player.getPosition());
		fsm.Update(dt);
	}
}

void Manager::Render()
{
	background.Render();
	player.Render();
	if (guardFSM.isAlive() == true)
	{
		guardFSM.Render();
	}

	if (guardBT.isAlive() == true)
	{
		guardBT.Render();
	}
}

