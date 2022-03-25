#include "BTState.h"
BTState::BTState(sf::RenderWindow* hwnd,GuardBT* grdBt, Player* pl)
	:
	root("rootNode"),		//Set all branches and leaves, assign them names and to decorators assign timer to switch function
	branch1("branch1"),
	guardBranch("Wander"),
	StandLeaf("Standing"),
	WanderLeaf("Patrolling"),
	SuspiciousLeaf("Disturbance"),
	AttackLeaf("Explore"),
	StandTimer("timerInsert",3000),
	SuspiciousTimer("timerInsert",9000),
	WanderTimer("timerInsert",15000),
	DieLeaf("Die")
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
	inAttack = false;		//Variable to track and decide if guard is attacking, starts as false
	wanderStates = p1;		//first point to travel to when wandering
	wanderP1 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 2);		//positions of points to travel to
	wanderP2 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 1.2);
	wanderToOrigin = guardBt->getPosition();

	StandLeaf.setRunFunction(std::bind(&BTState::leafStandFunction, this, std::placeholders::_1));		//Bind leaves to their respective functions, passing placeholders as required by the bind function
	WanderLeaf.setRunFunction(std::bind(&BTState::leafWanderFunction, this, std::placeholders::_1));
	SuspiciousLeaf.setRunFunction(std::bind(&BTState::leafSuspiciousFunction, this, std::placeholders::_1));
	AttackLeaf.setRunFunction(std::bind(&BTState::leafAttackFunction, this, std::placeholders::_1));
	DieLeaf.setRunFunction(std::bind(&BTState::Die, this, std::placeholders::_1));

	root.addChildNode(&guardBranch);		//Create structure of tree
	guardBranch.addChildNode(&StandTimer);
	guardBranch.addChildNode(&WanderTimer);
	WanderTimer.addChildNode(&WanderLeaf);
	StandTimer.addChildNode(&StandLeaf);
	root.addChildNode(&SuspiciousTimer);
	SuspiciousTimer.addChildNode(&SuspiciousLeaf);
	root.addChildNode(&AttackLeaf);
	root.addChildNode(&DieLeaf);
}

void BTState::Update(float dt)
{
	deltaTime = dt;		//deltaTime variable equal to the one passed through manager class to avoid passing deltaTime to many function
	distanceToPlayer = player->getPosition() - guardBt->getPosition();			//Calculate distance from guard to player
	directionTowardsPlayer = Vector::normalise(distanceToPlayer);				//Get direction from distance vector
	if (distanceToPlayer.x < 0)		//If distance is negative convert it to positive
		distanceToPlayer.x *= -1;
	if (distanceToPlayer.y < 0)
		distanceToPlayer.y *= -1;
	if (guardBt->health <= 0)		//If guard health is zero, jump to die function
	{
		BT::Blackboard::getInstance()->addNewValue("Noise", 1);
		BT::Blackboard::getInstance()->addNewValue("Attack", 1);
		BT::Blackboard::getInstance()->addNewValue("Die", 1);
	}
	if ((distanceToPlayer.x < 200 && distanceToPlayer.y < 200) && distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is very close to guard, attack
	{
		BT::Blackboard::getInstance()->addNewValue("Noise", 1);
		BT::Blackboard::getInstance()->addNewValue("Attack", 1);		//Add values to skip functions and execute the correct ones, noise and attack are added
	}
	if ((distanceToPlayer.x < 70 && distanceToPlayer.y < 70) && distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if guard is in contact with player, decrease player health
	{
		player->pHealth -= 0.05;
	}
	if (inAttack==false)		//If guard is not attacking
	{
		if ((distanceToPlayer.x < 400 && distanceToPlayer.y < 400) && (distanceToPlayer.x > 200 || distanceToPlayer.y > 200) && player->noise == true)//if player is close or if player is farther but making a noise (add noise boolean when player runs)
		{
			BT::Blackboard::getInstance()->addNewValue("Noise", 1);		//Guard get suspicious, add noise value
		}
	}

	BT::NodeStatus result = root.tick();			//Execute tree
	if (result == BT::NodeStatus::NODE_SUCCESS)		//Reset tree if node is succesfull
	{
		root.reset();
	}
	else if (result == BT::NodeStatus::NODE_FAILURE)		//Skip leaf if leaf returns failure 
	{
		return;
	}
}

void BTState::guardRotation(sf::Vector2f pointPos)			//Rotation based on direction
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

void BTState::moveToOrigin()		//Guard gets back to origin position
{
	guardBt->speed = 80;		//When wandering, guard speed is 80
	sf::Vector2f distanceFromGuardToOrig(wanderToOrigin - guardBt->getPosition());		//Calculate distance to origin point
	sf::Vector2f directionToOrig = Vector::normalise(distanceFromGuardToOrig);		//Get unit vector from distance vector for rotation
	guardBt->setVelocity(directionToOrig * guardBt->speed * deltaTime);				//Set velocity
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));

	if (distanceFromGuardToOrig.x < 0)			//If distance is negative, convert it to positive
		distanceFromGuardToOrig.x *= -1;
	if (distanceFromGuardToOrig.y < 0)
		distanceFromGuardToOrig.y *= -1;

	if (distanceFromGuardToOrig.x < 50 && distanceFromGuardToOrig.y < 50)		//If guard is close to origin point,head to first point
	{
		std::cout << "guard reached first wander point\n";
		wanderStates = p1;
	}
	guardRotation(wanderToOrigin);			//Calculate and apply rotation
}

BT::NodeStatus BTState::Die(BT::TreeNode* owner)		//Guard died
{
	guardBt->setAlive(false);		//Set guard to dead
	return BT::NodeStatus::NODE_RUNNING;	
}

void BTState::moveToPoint1()			//Guard moves to first point
{
	guardBt->speed = 80;
	sf::Vector2f distanceFromGuardToPoint1(wanderP1 - guardBt->getPosition());	   //Calculate distance to origin point
	sf::Vector2f directionToPoint1 = Vector::normalise(distanceFromGuardToPoint1);  //Get unit vector from distance vector for rotationt1);
	guardBt->setVelocity(directionToPoint1 * guardBt->speed * deltaTime);			 //Set velocity
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));
	if (distanceFromGuardToPoint1.x < 0)	//If distance is negative, convert it to positive
		distanceFromGuardToPoint1.x *= -1;
	if (distanceFromGuardToPoint1.y < 0)
		distanceFromGuardToPoint1.y *= -1;

	if (distanceFromGuardToPoint1.x < 50 && distanceFromGuardToPoint1.y < 50)		//If guard is close to first point,head to second point
		wanderStates = p2;

	guardRotation(wanderP1);		//Calculate and apply rotation
}

void BTState::moveToPoint2()		//Guard moves to second point
{
	guardBt->speed = 80;
	sf::Vector2f distanceFromGuardToPoint2(wanderP2 - guardBt->getPosition());			 //Calculate distance to origin point
	sf::Vector2f directionToPoint2 = Vector::normalise(distanceFromGuardToPoint2);		  //Get unit vector from distance vector for rotationt1);
	guardBt->setVelocity(directionToPoint2 * guardBt->speed * deltaTime);				 //Set velocity
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));

	if (distanceFromGuardToPoint2.x < 0)		//If distance is negative, convert it to positive
		distanceFromGuardToPoint2.x *= -1;
	if (distanceFromGuardToPoint2.y < 0)
		distanceFromGuardToPoint2.y *= -1;

	if (distanceFromGuardToPoint2.x < 50 && distanceFromGuardToPoint2.y < 50)		//If guard is close to second point,head to origin point
	{
		std::cout << "guard reached first wander point\n";
		wanderStates = orig;
	}

	guardRotation(wanderP2);		//Calculate and apply rotation
}

BT::NodeStatus BTState::leafAttackFunction(BT::TreeNode* owner)		//Attack function 
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Die"))		//If guard is not dead (doesn't have the dead value)
	{
		return BT::NodeStatus::NODE_FAILURE;		//Skip function if dead
	}
	inAttack = true;		//guard is attacking
	guardBt->speed = 150;		//Speed is 150
	guardBt->setVelocity(directionTowardsPlayer * guardBt->speed * deltaTime);		//Update velocity
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));		//Set position

	guardRotation(player->getPosition());		//Rotate towards player

	if (player->pHealth == 0)		
	{
		return BT::NodeStatus::NODE_FAILURE;
	}
	else
		return BT::NodeStatus::NODE_RUNNING;
}


BT::NodeStatus BTState::leafStandFunction(BT::TreeNode* owner)			//Function for stand leaf
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Noise")|| BT::Blackboard::getInstance()->getAndDeleteValue("Attack") || BT::Blackboard::getInstance()->getAndDeleteValue("Die"))		//If guard is suspicious, attacking or dead
	{																																															//Skip this function
		return BT::NodeStatus::NODE_FAILURE;
	}
	guardBt->speed = 0;		//When standing, speed is 0
	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus BTState::leafWanderFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Noise") || BT::Blackboard::getInstance()->getAndDeleteValue("Attack") || BT::Blackboard::getInstance()->getAndDeleteValue("Die"))		//If guard is suspicious, attacking or dead
		return BT::NodeStatus::NODE_FAILURE;																																					//Skip this function

	switch (wanderStates)		//Wander state machine
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

	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus BTState::leafSuspiciousFunction(BT::TreeNode* owner)			////Function for suspicious leaf
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("Attack") || BT::Blackboard::getInstance()->getAndDeleteValue("Die"))		//If guard is attacking or is dead, skip this function
	{
		return BT::NodeStatus::NODE_FAILURE;
	}
	sf::Time time2 = clock.getElapsedTime();		//Get time

	guardBt->speed = 40;		//speed of guard while suspicious is 40
	guardBt->setVelocity(directionTowardsPlayer * guardBt->speed * deltaTime);		//Velocity set 
	guardBt->setPosition(sf::Vector2f(guardBt->getPosition().x + guardBt->getVelocity().x, guardBt->getPosition().y + guardBt->getVelocity().y));		//Position set
	guardRotation(player->getPosition());		//Set guard rotation
	if (time2.asSeconds() >= 6)		//If timer reaches 6 seconds
	{
		BT::Blackboard::getInstance()->getAndDeleteValue("Noise");
		BT::Blackboard::getInstance()->getAndDeleteValue("Attack");
		root.reset();		//Restart tree and get back to wander
		clock.restart();
		return BT::NodeStatus::NODE_FAILURE;
	}
	return BT::NodeStatus::NODE_RUNNING;
}


