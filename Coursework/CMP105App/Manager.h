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
#include <chrono>
#include <fstream>
using std::chrono::duration_cast;
using std::ofstream;
using std::chrono::milliseconds;
typedef std::chrono::steady_clock the_clock;
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
	ofstream ReportFile;			//creation of excel file, found in folder
	int numOfTicks;
	the_clock::time_point start;
	the_clock::time_point end;

	bool runTest = true;
	bool runTest2 = true;
};

