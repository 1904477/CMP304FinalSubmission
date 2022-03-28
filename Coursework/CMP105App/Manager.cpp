#include "Manager.h"

Manager::Manager(sf::RenderWindow* hwnd, Input* in) :		//Pass variables where they need to be passed
	player(hwnd, in, &guardFSM, &guardBT),
	background(hwnd),        
	guardFSM(hwnd),
	fsm(hwnd, &guardFSM, &player), 
	guardBT(hwnd), 
	btState(hwnd, &guardBT, &player),
	goal(hwnd)
{
	window = hwnd;
	input = in;
}

Manager::~Manager()
{
}

void Manager::Init()		//Initialize the different objects
{
	player.Init();
	background.Init();
	guardFSM.Init();
	guardBT.Init();
	fsm.Init();
	btState.Init();
	goal.Init();
	numOfTicks = 0;
}

void Manager::Update(float dt)
{
	if (goal.win == false && player.pHealth >= 0)		//If player hasn't won and is alive
	{
		player.Update(dt);		//Update player
		if (guardFSM.isAlive() == true)		//Update guard and its fsm only if guard is alive
		{
			guardFSM.Update(dt, player.getPosition());
			
		//	if (runTest == true)
		//	{
			//	start = the_clock::now();			// Start timing 
			//	for (int i = 0; i < 100000; i++)
			//	{
					fsm.Update(dt);
			//	}
			//	end = the_clock::now();			// Stop timing 
			//	auto time_taken = duration_cast<milliseconds>(end - start).count();
			//	std::cout <<"FSM  "<< (float)time_taken << "\n";
			//	// Compute the difference between the two times in milliseconds
			//	runTest = false;
			//}

		}
		if (guardBT.isAlive() == true)			//Update guard and its bt only if guard is alive
		{
			guardBT.Update(dt, player.getPosition());
		//	if (runTest2 == true)
		//	{
			//	start = the_clock::now();			// Start timing 
			//	for (int i = 0; i < 100000; i++)
			//	{
					btState.Update(dt);
				//}
				//end = the_clock::now();			// Stop timing 
				//auto time_taken = duration_cast<milliseconds>(end - start).count();
				//std::cout <<"BT  "<< (float)time_taken << "\n";
				//// Compute the difference between the two times in milliseconds
				//runTest2 = false;
		//	}

		}
		goal.Update(player.getPosition());		//Update goal
	}
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();		//On escape press, exit program
	}
}

void Manager::Render()
{
	background.Render();		//Render background
	if (goal.win == false && player.pHealth >= 0)		//If player hasn't won and is alive
	{
		goal.Render();		//Render goal
		player.Render();	//Render player
		if (guardFSM.isAlive() == true)		//Render guard only if alive
			guardFSM.Render();
		if (guardBT.isAlive() == true)		//Render guard only if alive
			guardBT.Render();
	}
	if(goal.win==true)		//If player win, render win text
		goal.RenderWin();
	if (player.pHealth<=0)		//If player loses, render loss
		goal.RenderLoss();
}

