#include "FSM.h"

FSM::FSM(sf::RenderWindow* hwnd, GuardFSM* grdFSM, Player* plr)
{
	window = hwnd;
	guardFSM = grdFSM;
	player = plr;
	srand(time(0));
}

FSM::~FSM()
{
}

void FSM::Init()
{
	current_state = Still;
	wanderStates = p1;

	wanderP1 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 12);
	wanderP2 = sf::Vector2f(window->getSize().x / 1.5, window->getSize().y / 2);
	wanderToOrigin = guardFSM->getPosition();

}

void FSM::Update(float dt)
{
	UpdateChecks();
	switch (current_state)
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
	case Talk:
		TalkFunc();
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
	distanceToPlayer = player->getPosition() - guardFSM->getPosition();
	directionTowardsPlayer = Vector::normalise(distanceToPlayer);
	if (distanceToPlayer.x < 0)
		distanceToPlayer.x *= -1;
	if (distanceToPlayer.y < 0)
		distanceToPlayer.y *= -1;


	if ((distanceToPlayer.x < 200 && distanceToPlayer.y < 200)&& distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is close or if player is farther but making a noise (add noise boolean when player runs)
	{
		current_state = Attack;
	}
	if ((distanceToPlayer.x < 70 && distanceToPlayer.y < 70) && distanceToPlayer.x > 0 && distanceToPlayer.y > 0) //if player is close or if player is farther but making a noise (add noise boolean when player runs)
	{
		player->pHealth -= 0.01;
	}
	if (current_state != Attack)
	{
		if ((distanceToPlayer.x < 400 && distanceToPlayer.y < 400) && (distanceToPlayer.x > 200 || distanceToPlayer.y > 200) && player->noise == true)
		{
			current_state = Suspicious;
		}
	}


}

void FSM::StillFunc()
{
	sf::Time time = clock.getElapsedTime();
	std::cout << "Guard stopped\n";
	guardFSM->speed = 0;
	if (time.asSeconds() >= 3)
	{
		int randomNumber = rand() % 101;
		std::cout << randomNumber;
		if (randomNumber > 50)
			current_state = Wander;
		else
			current_state = Talk;
		clock.restart();
	}
}

void FSM::WanderFunc(float dt)
{
	std::cout << "Guard is wandering\n";
	sf::Time time = clock.getElapsedTime();
	if (time.asSeconds() >= 4)
	{
		int randomNumber = rand() % 101;
		std::cout << randomNumber;
		if (randomNumber > 50)
			current_state = Still;
		else
			current_state = Talk;
		clock.restart();
	}
	switch (wanderStates)
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

void FSM::SuspiciousFunc(float dt)
{
	sf::Time time;
	time = clock.getElapsedTime();
	std::cout << "Guard is suspicious\n";

	guardFSM->speed = 40;
	guardFSM->setVelocity(directionTowardsPlayer * guardFSM->speed * dt);
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));
	guardRotation(player->getPosition());
	if (time.asSeconds() >= 6)
	{
		clock.restart();
		current_state = Wander;
	}


}

void FSM::AttackFunc(float dt)
{
	std::cout << "Guard is attacking\n";
	if (distanceToPlayer.x > 10 && distanceToPlayer.y > 10)
	{
		guardFSM->speed = 150;
	}
	else
		guardFSM->speed = 0;

	guardFSM->setVelocity(directionTowardsPlayer * guardFSM->speed * dt);
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));
	guardRotation(player->getPosition());
}

void FSM::DieFunc()
{
	guardFSM->setAlive(false);
}

void FSM::TalkFunc()
{
	std::cout << "Guard is talking to the other guard. \n";
	guardFSM->speed = 0;
	sf::Time time = clock.getElapsedTime();
	if (time.asSeconds() >= 4)
	{
		current_state = Wander;
		clock.restart();
	}
}

void FSM::moveToPoint1(float dt)
{
	guardFSM->speed = 80;
	sf::Vector2f distanceFromGuardToPoint1(wanderP1 - guardFSM->getPosition());
	sf::Vector2f directionToPoint1 = Vector::normalise(distanceFromGuardToPoint1);
	guardFSM->setVelocity(directionToPoint1 * guardFSM->speed * dt);
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));

	if (distanceFromGuardToPoint1.x < 0)
		distanceFromGuardToPoint1.x *= -1;
	if (distanceFromGuardToPoint1.y < 0)
		distanceFromGuardToPoint1.y *= -1;
	if (distanceFromGuardToPoint1.x < 50 && distanceFromGuardToPoint1.y < 50)
		wanderStates = p2;
	guardRotation(wanderP1);
}

void FSM::moveToPoint2(float dt)
{
	guardFSM->speed = 80;
	sf::Vector2f distanceFromGuardToPoint2(wanderP2 - guardFSM->getPosition());
	sf::Vector2f directionToPoint2 = Vector::normalise(distanceFromGuardToPoint2);
	guardFSM->setVelocity(directionToPoint2 * guardFSM->speed * dt);
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));

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

void FSM::moveToOrigin(float dt)
{
	guardFSM->speed = 80;
	sf::Vector2f distanceFromGuardToOrig(wanderToOrigin - guardFSM->getPosition());
	sf::Vector2f directionToOrig = Vector::normalise(distanceFromGuardToOrig);
	guardFSM->setVelocity(directionToOrig * guardFSM->speed * dt);
	guardFSM->setPosition(sf::Vector2f(guardFSM->getPosition().x + guardFSM->getVelocity().x, guardFSM->getPosition().y + guardFSM->getVelocity().y));

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

void FSM::guardRotation(sf::Vector2f pointPos)
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
