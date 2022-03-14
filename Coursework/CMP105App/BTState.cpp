#include "BTState.h"
BTState::BTState(sf::RenderWindow* hwnd,GuardBT* grdBt, Player* pl)
{
	window = hwnd;
	player = pl;
	guardBt = grdBt;

}

BTState::~BTState()
{
}

void BTState::Init()
{

}

void BTState::Update(float dt)
{
}

BT::NodeStatus BTState::leafAlarmFunction(BT::TreeNode* owner)
{
	return BT::NodeStatus();
}

BT::NodeStatus BTState::leafStandFunction(BT::TreeNode* owner)
{
	return BT::NodeStatus();
}

BT::NodeStatus BTState::leafPatrolFunction(BT::TreeNode* owner)
{
	return BT::NodeStatus();
}

BT::NodeStatus BTState::leafDisturbFunction(BT::TreeNode* owner)
{
	return BT::NodeStatus();
}

BT::NodeStatus BTState::leafExploreFunction(BT::TreeNode* owner)
{
	return BT::NodeStatus();
}
