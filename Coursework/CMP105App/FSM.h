#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "GuardFSM.h"
#include <time.h>
class FSM
{
public:
	FSM(sf::RenderWindow*hwnd, GuardFSM* grdFSM, Player *plr);
	~FSM();

	void Init();
	void Update(float dt);
	void UpdateChecks();
	void StillFunc();
	void WanderFunc(float dt);
	void SuspiciousFunc(float dt);
	void AttackFunc(float dt);
	void DieFunc();
	void TalkFunc();

	void moveToPoint1(float dt);
	void moveToPoint2(float dt);
	void moveToOrigin(float dt);
	void guardRotation(sf::Vector2f pointPos);
	enum States {Still=0 , Wander=1, Suspicious = 2, Attack = 3,Talk =4, Die = 5};
	enum wanStates {p1,p2,orig};


	States current_state;
	wanStates wanderStates;
	sf::RenderWindow* window;
	Player* player;
	GuardFSM* guardFSM;

	sf::Vector2f directionTowardsPlayer;
	sf::Vector2f distanceToPlayer;

	sf::Vector2f wanderP1, wanderP2, wanderToOrigin;

	sf::Clock clock;
};

