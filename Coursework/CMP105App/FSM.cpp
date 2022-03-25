#include "FSM.h"

FSM::FSM(sf::RenderWindow* hwnd, GuardFSM* grdFSM, Player* plr)		//Constructor with passed references
{			
	window = hwnd;
	guardFSM = grdFSM;
	player = plr;
	srand(time(0));
}

FSM::~FSM()
{
}

void FSM::Init() //Initializations
{
	current_state = Still;		//First guard state is still
	wanderStates = p1;			//First point where the guard will go to

	wanderP1 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 12);		//First point to wander to
	wanderP2 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 2);		//Second point to wander to
	wanderToOrigin = guardFSM->getPosition();			//Once in second point, guard gets back to origin point

}

void FSM::Update(float dt)
{
	UpdateChecks();			//Checks that are always run, independently from fsm
	switch (current_state)		//Switch statement for fsm
	{
	case Still:
		StillFunc();
		break;
	case Wander:
		WanderFunc(dt);
		break;
	case Attack:
		AttackFunc(dt);
		break;
	case Die:
		DieFunc();
		break;
	case Suspicious:
		SuspiciousFunc(dt);
		break;
	default:
		break;
	}
}

void FSM::UpdateChecks()
{
//	std::cout << guardFSM->isAlive() << "\n";
	distanceToPlayer = player->getPosition() - guardFSM->getPosition();		//calculate distance from guard to player every frame
	directionTowardsPlayer = Vector::normalise(distanceToPlayer);		//Get direction to player
	if (distanceToPlayer.x < 0)			//Convert distance in case value is negative
		distanceToPlayer.x *= -1;
	if (distanceToPlayer.y < 0)
		distanceToPlayer.y *= -1;

	if ((distanceToPlayer.x < 200 && distanceToPlayer.y < 200)&& distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is close or if player is farther but making a noise (add noise boolean when player runs)
	{
		current_state = Attack;		
	}
	if ((distanceToPlayer.x < 70 && distanceToPlayer.y < 70) && distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is close or if player is farther but making a noise (add noise boolean when player runs)
	{
		player->pHealth -= 0.05;
	}
	if (current_state != Attack)		//If player is close and guard is not attacking
	{	
		if ((distanceToPlayer.x < 400 && distanceToPlayer.y < 400) && (distanceToPlayer.x > 200 || distanceToPlayer.y > 200) && player->noise == true)		//If player is runnning and guard is close enough, guard gets suspicious
		{
			current_state = Suspicious;
		}
	}
	if (guardFSM->health <= 0)		//Guard dies at 0 health
	{
		current_state = Die;
	}

}

void FSM::StillFunc()		//When guard is still, its speed is zero and  after three seconds, it starts wandering
{
	sf::Time time = clock.getElapsedTime();
	guardFSM->speed = 0;
	if (time.asSeconds() >= 3)
	{
		current_state = Wander;
		clock.restart();
	}
}

void FSM::WanderFunc(float dt)
{
	sf::Time time = clock.getElapsedTime();
	if (time.asSeconds() >= 4)		//Alternate wander and still, after 4 seconds in wandering, guard stands still
	{
		current_state = Still;
		clock.restart();
	}
	switch (wanderStates)		//Switch between patrolling three points
	{
	case p1:
		moveToPoint1(dt);
		break;
	case p2:
		moveToPoint2(dt);
		break;
	case orig:
		moveToOrigin(dt);
		break;
	}
}

void FSM::SuspiciousFunc(float dt)	//Suspicious function
{
	sf::Time time;		//Timer
	time = clock.getElapsedTime();

	guardFSM->speed = 40;		//While suspicious speed is 40
	guardFSM->setVelocity(directionTowardsPlayer * guardFSM->speed * dt);		//Guard moves towards player
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));
	guardRotation(player->getPosition());		//Guard rotates towards player
	if (time.asSeconds() >= 6)		//If guard has been suspicious for 6 seconds, then it casually choses a state between still and wander
	{
		clock.restart();
		int randomNumber = rand() % 101;		//Random number for random state 
		std::cout << randomNumber;
		if (randomNumber > 50)
			current_state = Still;
		else
			current_state = Wander;
	}


}

void FSM::AttackFunc(float dt)		//When guard is attacking, it won't get back to the other states and attacks until it kills the player or dies.
{
	guardFSM->speed = 150;		//When attacking, guard speed is 150
	guardFSM->setVelocity(directionTowardsPlayer * guardFSM->speed * dt);		//Guard moves towards player
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));
	guardRotation(player->getPosition());			//Guard rotates towards player
}

void FSM::DieFunc()		//When guard is dead, remove it from the game
{
	guardFSM->setAlive(false);
}

void FSM::moveToPoint1(float dt)		//Guard moves to first point of wander
{
	guardFSM->speed = 80;		//When wandering, speed is 80
	sf::Vector2f distanceFromGuardToPoint1(wanderP1 - guardFSM->getPosition());		//Calculate distance between guard and first point of wander
	sf::Vector2f directionToPoint1 = Vector::normalise(distanceFromGuardToPoint1);	//calculate direction for rotation
	guardFSM->setVelocity(directionToPoint1 * guardFSM->speed * dt);				//Guard moves towards point
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));

	if (distanceFromGuardToPoint1.x < 0)			//If distance is negative, convert to positive
		distanceFromGuardToPoint1.x *= -1;
	if (distanceFromGuardToPoint1.y < 0)
		distanceFromGuardToPoint1.y *= -1;
	if (distanceFromGuardToPoint1.x < 50 && distanceFromGuardToPoint1.y < 50)		//If guard is close enough to the first point, change state and moves towards second point
		wanderStates = p2;
	guardRotation(wanderP1);		//Guard rotates towards first point
}

void FSM::moveToPoint2(float dt)		//Guard moves to second point of wander
{
	guardFSM->speed = 80;		//When wandering, speed is 80
	sf::Vector2f distanceFromGuardToPoint2(wanderP2 - guardFSM->getPosition());		//Calculate distance between guard and second point of wander
	sf::Vector2f directionToPoint2 = Vector::normalise(distanceFromGuardToPoint2);	//calculate direction for rotation
	guardFSM->setVelocity(directionToPoint2 * guardFSM->speed * dt);				//Guard moves towards point
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));

	if (distanceFromGuardToPoint2.x < 0)		//If distance is negative convert it to positive
		distanceFromGuardToPoint2.x *= -1;
	if (distanceFromGuardToPoint2.y < 0)
		distanceFromGuardToPoint2.y *= -1;

	if (distanceFromGuardToPoint2.x < 50 && distanceFromGuardToPoint2.y < 50)			//If guard is close enough, guard gets back to original position
	{
		wanderStates = orig;		//Change state of wander state machine
	}
	guardRotation(wanderP2);		//Rotate towards second point
}

void FSM::moveToOrigin(float dt)		//Guard moves towards first position
{
	guardFSM->speed = 80;				//Guard speed
	sf::Vector2f distanceFromGuardToOrig(wanderToOrigin - guardFSM->getPosition());		//Calculate distance between guard and original position
	sf::Vector2f directionToOrig = Vector::normalise(distanceFromGuardToOrig);			//calculate direction for rotation
	guardFSM->setVelocity(directionToOrig * guardFSM->speed * dt);						//Guard moves towards point
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));

	if (distanceFromGuardToOrig.x < 0)			//If distance is less than 0, makes it positive
		distanceFromGuardToOrig.x *= -1;
	if (distanceFromGuardToOrig.y < 0)
		distanceFromGuardToOrig.y *= -1;

	if (distanceFromGuardToOrig.x < 50 && distanceFromGuardToOrig.y < 50)		//If guard is close enough to second point, then change state and go towards to first point position 
	{
		wanderStates = p1;
	}
	guardRotation(wanderToOrigin);		//Rotate towards the origin point.
}

void FSM::guardRotation(sf::Vector2f pointPos)				//Guard rotation calculation
{
	sf::Vector2f curPos = guardFSM->getPosition();
	sf::Vector2f pPosition = pointPos;
	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.14159265;
	float dx = curPos.x - pPosition.x;
	float dy = curPos.y - pPosition.y;
	float rotation = (atan2(dy, dx)) * 180 / PI;
	guardFSM->setRotation(rotation + 180);
}
