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

	BT::NodeStatus leafAlarmFunction(BT::TreeNode* owner);
	BT::NodeStatus leafStandFunction(BT::TreeNode* owner);
	BT::NodeStatus leafPatrolFunction(BT::TreeNode* owner);
	BT::NodeStatus leafDisturbFunction(BT::TreeNode* owner);
	BT::NodeStatus leafExploreFunction(BT::TreeNode* owner);

	sf::RenderWindow* window; 
	GuardBT* guardBt;
	Player* player;


};

