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
	BTState(sf::RenderWindow*hwnd , GuardBT* grdBt, Player* pl);
	~BTState();

	void Init();
	void Update(float dt);
	void guardRotation(sf::Vector2f pointPos);
	void moveToPoint1();
	void moveToPoint2();
	void moveToOrigin();
	enum wanStates { p1, p2, orig };

	float deltaTime;


	BT::NodeStatus leafAttackFunction(BT::TreeNode* owner);
	BT::NodeStatus leafStandFunction(BT::TreeNode* owner);
	BT::NodeStatus leafWanderFunction(BT::TreeNode* owner);
	BT::NodeStatus leafSuspiciousFunction(BT::TreeNode* owner);

	sf::RenderWindow* window; 
	GuardBT* guardBt;
	Player* player;

	BT::FallbackSelector root;
	BT::FallbackSelector branch1;
	BT::SequenceSelector guardBranch;

	BT::LeafNode StandLeaf;
	BT::LeafNode WanderLeaf;
	BT::LeafNode SuspiciousLeaf;
	BT::LeafNode AttackLeaf;

	BT::Decorator StandTimer;
	BT::Decorator WanderTimer;
	BT::Decorator SuspiciousTimer;


	sf::Vector2f directionTowardsPlayer;
	sf::Vector2f distanceToPlayer;

	sf::Vector2f wanderP1, wanderP2, wanderToOrigin;
	wanStates wanderStates;
};

