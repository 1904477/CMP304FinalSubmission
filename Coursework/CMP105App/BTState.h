#pragma once
#include <LeafNode.h>
#include <FallbackSelector.h>
#include <SequenceSelector.h>
#include <Decorator.h>
#include <Blackboard.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "GuardBT.h"
class BTState
{
public:
	BTState(sf::RenderWindow*hwnd , GuardBT* grdBt, Player* pl);		//Constructor
	~BTState();															//Destructor

	void Init();		//Initializer
	void Update(float dt);		//Update function
	void guardRotation(sf::Vector2f pointPos);		//Guard rotates
	void moveToPoint1();			//Guard moves to first point function
	void moveToPoint2();			//Guard moves to second point function
	void moveToOrigin();			//Guard moves to original point function
	enum wanStates { p1, p2, orig };		//States for wandering

	float deltaTime;		//Deltatime variable


	BT::NodeStatus leafAttackFunction(BT::TreeNode* owner);			//Attack function
	BT::NodeStatus leafStandFunction(BT::TreeNode* owner);			//Stand function
	BT::NodeStatus leafWanderFunction(BT::TreeNode* owner);			//Wander function
	BT::NodeStatus leafSuspiciousFunction(BT::TreeNode* owner);		//Suspicious function
	BT::NodeStatus Die(BT::TreeNode* owner);						//Die function

	sf::RenderWindow* window; 
	GuardBT* guardBt;
	Player* player;

	BT::FallbackSelector root;		//Root
	BT::FallbackSelector branch1;	//First branch
	BT::SequenceSelector guardBranch;		//Guard branch(wander and still

	BT::LeafNode DieLeaf;			//Leaves 
	BT::LeafNode StandLeaf;
	BT::LeafNode WanderLeaf;
	BT::LeafNode SuspiciousLeaf;
	BT::LeafNode AttackLeaf;

	BT::Decorator StandTimer;		//Timer to alternate different functions
	BT::Decorator WanderTimer;
	BT::Decorator SuspiciousTimer;


	sf::Vector2f directionTowardsPlayer;			//Vectors for positions
	sf::Vector2f distanceToPlayer;

	sf::Vector2f wanderP1, wanderP2, wanderToOrigin;
	wanStates wanderStates;		//Current wander state

	sf::Clock clock;

	bool inAttack;
	bool genRandomNumber = true;
	int randomNumber;
};

