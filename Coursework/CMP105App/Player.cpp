#include "Player.h"

Player::Player(sf::RenderWindow* hwnd, Input* in, GuardFSM* grdFSM, GuardBT* grdBt) : bullet(hwnd),gTools(hwnd)
{
	window = hwnd;
	input = in;
	guardFSM = grdFSM;
	guardBT = grdBt;
}

Player::~Player()
{
}

void Player::Init()
{
	playerTex.loadFromFile("gfx/temp.png");		//Load texture 
	setTexture(&playerTex);		//Set texture
	setSize(sf::Vector2f(100, 100));	//Set size
	setPosition(sf::Vector2f(300, 100));	//Set starting position
	setOrigin(getSize().x / 2, getSize().y / 2);	//Set origin
	setCollisionBox(0,0, getSize().x/2, getSize().y/2);
	movSpeed = 100;		//Set movement speed
	pHealth = 100;		//Set player health
	bullet.Init();		//Init bullets and graphics tools
	gTools.Init();
}

void Player::Update(float dt)
{
	playerPos = getPosition();

	sf::Vector2f curPos = getPosition();
	sf::Vector2f position =sf::Vector2f( input->getMouseX(), input->getMouseY());
	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.14159265;
	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;
	float rotation = (atan2(dy, dx)) * 180 / PI;
	setRotation(rotation + 180 );

	HandleInput(dt);	//Handle input
	bullet.Update(dt);	//Update bullets
	CollisionCheck();	//Check for collisions

	gTools.Update(sf::Vector2f(getPosition().x - getSize().x / 2, getPosition().y - getSize().y / 2), pHealth);		//Update graphics tools
}

void Player::Render()
{
	bullet.Render();	//render bullets
	gTools.Render();	//render graphics tools
	window->draw(*this);	//draw player
}

void Player::HandleInput(float dt)
{
	Controls(dt);	//controls
}

void Player::Controls(float dt)
{
	if (input->isKeyDown(sf::Keyboard::A))		//Movement
	{
		setPosition(playerPos.x -= (movSpeed * dt), playerPos.y);
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		setPosition(playerPos.x += (movSpeed * dt), playerPos.y);
	}
	if (input->isKeyDown(sf::Keyboard::W))
	{
		setPosition(playerPos.x, playerPos.y -= (movSpeed * dt));
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		setPosition(playerPos.x, playerPos.y += (movSpeed * dt));
	}
	if (input->isKeyDown(sf::Keyboard::LShift))		//Player running, if player runs, he makes noise
	{
		movSpeed = 150;
		noise = true;
	}
	else     //Otherwise speed is 100 and player doesn't make noise
	{
		movSpeed = 100;
		noise = false;
	}
	if (input->isMouseLDown())		//Shooting on left mouse pressed
	{
		time = clock.getElapsedTime();
		if (time.asSeconds() > 0.2)		//cooldown of o.2 seconds
		{
			bulletDir.x = input->getMouseX();		//Get mouse position
			bulletDir.y = input->getMouseY();
			bulletDir = bulletDir - playerPos;		//Calculate distance to mouse
			bulletDir = Vector::normalise(bulletDir);	//Get distance unit vector from distance vector 
			bullet.spawnPosition = getPosition();	//Get spawn position
			bullet.Spawn(bulletDir, getSize());		//Spawn bullet
			clock.restart();
		}
	}
}

void Player::CollisionCheck()
{
	for (int i = 0; i < bullet.bullets.size(); i++)
	{
		if (bullet.bullets[i].isAlive())	//If bullets are alive
		{
			if (guardFSM->health > 0)		//If guard is alive
			{
				if (Collision::checkBoundingBox(&bullet.bullets[i], guardFSM))		//Check for bullet colliding with guard
				{
					bullet.bullets[i].setAlive(false);		//On hit, set bullets to dead
					std::cout << "bullet hit guard\n";
					guardFSM->health -= 10;		//Decrease guard health
				}
			}
			if (guardBT->health > 0)
			{
				if (Collision::checkBoundingBox(&bullet.bullets[i], guardBT))		//Check for bullet colliding with guard
				{
					bullet.bullets[i].setAlive(false);		//On hit, set bullets to dead
					std::cout << "bullet hit guard\n";
					guardBT->health -= 10;		//Decrease guard health
				}
			}
		}
	}
	if (pHealth <= 0)		//Health doesn't go below zero
		pHealth = 0;

}
