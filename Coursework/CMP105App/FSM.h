#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "GuardFSM.h"
#include <time.h>
class FSM
{
public:
	FSM(sf::RenderWindow*hwnd, GuardFSM* grdFSM, Player *plr);		//Constructor
	~FSM();			//Destructor

	void Init();			//Initializer
	void Update(float dt);		//Update func
	void UpdateChecks();		//Update checks 
	void StillFunc();			//Guard sti
	void WanderFunc(float dt);		//Wander function
	void SuspiciousFunc(float dt);		//Suspicious function
	void AttackFunc(float dt);			//Attack function
	void DieFunc();			//Die function

	void moveToPoint1(float dt);		//Point 1 movement
	void moveToPoint2(float dt);		//Point 2 movement
	void moveToOrigin(float dt);		//Origin movement
	void guardRotation(sf::Vector2f pointPos);		//Guard rotation
	enum States {Still=0 , Wander=1, Suspicious = 2, Attack = 3, Die = 4};		//States for guard behaviour
	enum wanStates {p1,p2,orig};		//States for movement


	States current_state;		//Current state
	wanStates wanderStates;		//Current wander state
	sf::RenderWindow* window;
	Player* player;
	GuardFSM* guardFSM;

	sf::Vector2f directionTowardsPlayer;
	sf::Vector2f distanceToPlayer;						

	sf::Vector2f wanderP1, wanderP2, wanderToOrigin;	//Target position variables

	sf::Clock clock;
};

