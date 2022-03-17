#include "BTState.h"
BTState::BTState(sf::RenderWindow* hwnd,GuardBT* grdBt, Player* pl)
	:
	root("rootNode"),
	branch1("branch1"),
	guardBranch("Wander"),
	StandLeaf("Standing"),
	WanderLeaf("Patrolling"),
	SuspiciousLeaf("Disturbance"),
	AttackLeaf("Explore"),

	StandTimer("timerInsert",3),
	WanderTimer("timerInsert",5),
	SuspiciousTimer("timerInsert",6)
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
	inAttack = false;
	wanderStates = p1;
	wanderP1 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 1.2);
	wanderP2 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 0.4);
	wanderToOrigin = guardBt->getPosition();


	//StandLeaf.setRunFunction(leafStandFunction);
//	WanderLeaf.setRunFunction(leafWanderFunction);


	root.addChildNode(&branch1);
	branch1.addChildNode(&guardBranch);

	guardBranch.addChildNode(&StandTimer);
	guardBranch.addChildNode(&WanderTimer);
	StandTimer.addChildNode(&StandLeaf);
	WanderTimer.addChildNode(&WanderLeaf);

}

void BTState::Update(float dt)
{
	deltaTime = dt;
	distanceToPlayer = player->getPosition() - guardBt->getPosition();
	directionTowardsPlayer = Vector::normalise(distanceToPlayer);

	if (distanceToPlayer.x < 0)
		distanceToPlayer.x *= -1;
	if (distanceToPlayer.y < 0)
		distanceToPlayer.y *= -1;

	if ((distanceToPlayer.x < 200 && distanceToPlayer.y < 200) && distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is close or if player is farther but making a noise (add noise boolean when player runs)
	{
		BT::Blackboard::getInstance()->addNewValue("Noise", 1);
		BT::Blackboard::getInstance()->addNewValue("Attack", 1);
	}
	if ((distanceToPlayer.x < 70 && distanceToPlayer.y < 70) && distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is close or if player is farther but making a noise (add noise boolean when player runs)
	{
		player->pHealth -= 0.01;
	}
	if (inAttack==false)
	{
		if ((distanceToPlayer.x < 400 && distanceToPlayer.y < 400) && (distanceToPlayer.x > 200 || distanceToPlayer.y > 200) && player->noise == true)
		{
			BT::Blackboard::getInstance()->addNewValue("Noise", 1);
		}
	}

	BT::NodeStatus result = root.tick();
	if (result == BT::NodeStatus::NODE_SUCCESS)
	{
		root.reset();
	}
	else if (result == BT::NodeStatus::NODE_FAILURE)
	{
		window->close();
	}
}

void BTState::guardRotation(sf::Vector2f pointPos)
{
	sf::Vector2f curPos = guardBt->getPosition();
	sf::Vector2f pPosition = pointPos;
	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.14159265;
	float dx = curPos.x - pPosition.x;
	float dy = curPos.y - pPosition.y;
	float rotation = (atan2(dy, dx)) * 180 / PI;
	guardBt->setRotation(rotation + 180);
}

void BTState::moveToOrigin()
{
	guardBt->speed = 80;
	sf::Vector2f distanceFromGuardToOrig(wanderToOrigin - guardBt->getPosition());
	sf::Vector2f directionToOrig = Vector::normalise(distanceFromGuardToOrig);
	guardBt->setVelocity(directionToOrig * guardBt->speed * deltaTime);
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));

	if (distanceFromGuardToOrig.x < 0)
		distanceFromGuardToOrig.x *= -1;
	if (distanceFromGuardToOrig.y < 0)
		distanceFromGuardToOrig.y *= -1;

	if (distanceFromGuardToOrig.x < 50 && distanceFromGuardToOrig.y < 50)
	{
		std::cout << "guard reached first wander point\n";
		wanderStates = p1;
	}
	guardRotation(wanderToOrigin);
}

void BTState::moveToPoint1()
{
	guardBt->speed = 80;
	sf::Vector2f distanceFromGuardToPoint1(wanderP1 - guardBt->getPosition());
	sf::Vector2f directionToPoint1 = Vector::normalise(distanceFromGuardToPoint1);
	guardBt->setVelocity(directionToPoint1 * guardBt->speed * deltaTime);
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));

	if (distanceFromGuardToPoint1.x < 0)
		distanceFromGuardToPoint1.x *= -1;
	if (distanceFromGuardToPoint1.y < 0)
		distanceFromGuardToPoint1.y *= -1;
	if (distanceFromGuardToPoint1.x < 50 && distanceFromGuardToPoint1.y < 50)
		
	guardRotation(wanderP1);
}

void BTState::moveToPoint2()
{
	guardBt->speed = 80;
	sf::Vector2f distanceFromGuardToPoint2(wanderP2 - guardBt->getPosition());
	sf::Vector2f directionToPoint2 = Vector::normalise(distanceFromGuardToPoint2);
	guardBt->setVelocity(directionToPoint2 * guardBt->speed * deltaTime);
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));

	if (distanceFromGuardToPoint2.x < 0)
		distanceFromGuardToPoint2.x *= -1;
	if (distanceFromGuardToPoint2.y < 0)
		distanceFromGuardToPoint2.y *= -1;

	if (distanceFromGuardToPoint2.x < 50 && distanceFromGuardToPoint2.y < 50)
	{
		std::cout << "guard reached first wander point\n";
		wanderStates = orig;
	}

	guardRotation(wanderP2);
}

BT::NodeStatus BTState::leafAttackFunction(BT::TreeNode* owner)
{
	inAttack = true;

	std::cout << "Guard is attacking\n";
	if (distanceToPlayer.x > 10 && distanceToPlayer.y > 10)
		guardBt->speed = 150;
	else
		guardBt->speed = 0;

	guardBt->setVelocity(directionTowardsPlayer * guardBt->speed * deltaTime);
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));

	guardRotation(player->getPosition());

	if (player->pHealth == 0)		//Last function, if player is dead end program
	{
		return BT::NodeStatus::NODE_FAILURE;
	}
	else
		return BT::NodeStatus::NODE_RUNNING;
}


BT::NodeStatus BTState::leafStandFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Noise"))
	{
		return BT::NodeStatus::NODE_FAILURE;
	}


	std::cout << "Guard stopped\n";
	guardBt->speed = 0;


	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus BTState::leafWanderFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Noise"))
	{
		return BT::NodeStatus::NODE_FAILURE;
	}

	std::cout << "Guard is wandering\n";
	switch (wanderStates)
	{
	case p1:
		moveToPoint1();
		break;
	case p2:
		moveToPoint2();
		break;
	case orig:
		moveToOrigin();
		break;
	}
	std::cout << "Guard stopped\n";
	guardBt->speed = 0;

	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus BTState::leafSuspiciousFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Noise"))
	{
		return BT::NodeStatus::NODE_FAILURE;
	}
	guardBt->speed = 40;
	guardBt->setVelocity(directionTowardsPlayer * guardBt->speed * deltaTime);
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));
	guardRotation(player->getPosition());

	return BT::NodeStatus::NODE_RUNNING;
}


