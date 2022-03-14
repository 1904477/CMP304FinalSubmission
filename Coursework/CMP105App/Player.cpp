#include "Player.h"

Player::Player(sf::RenderWindow* hwnd, Input* in, GuardFSM* grdFSM) : bullet(hwnd),gTools(hwnd)
{
	window = hwnd;
	input = in;
	guardFSM = grdFSM;
}

Player::~Player()
{
}

void Player::Init()
{
	playerTex.loadFromFile("gfx/temp.png");
	setTexture(&playerTex);
	setSize(sf::Vector2f(100, 100));
	setPosition(sf::Vector2f(300, 100));
	setOrigin(getSize().x / 2, getSize().y / 2);
	setCollisionBox(0,0, getSize().x/2, getSize().y/2);
	movSpeed = 100;
	pHealth = 100;

	bullet.Init();
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
	HandleInput(dt);
	bullet.Update(dt);
	CollisionCheck();

	gTools.Update(sf::Vector2f(getPosition().x - getSize().x / 2, getPosition().y - getSize().y / 2), pHealth);
}

void Player::Render()
{
	bullet.Render();
	gTools.Render();
	window->draw(*this);
}

void Player::HandleInput(float dt)
{
	Controls(dt);
}

void Player::Controls(float dt)
{
	if (input->isKeyDown(sf::Keyboard::A))
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
	if (input->isKeyDown(sf::Keyboard::LShift))
	{
		movSpeed = 150;
		noise = true;
	}
	else
	{
		movSpeed = 100;
		noise = false;
	}
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}
	if (input->isMouseLDown())
	{
		time = clock.getElapsedTime();
		if (time.asSeconds() > 0.2)
		{
			bulletDir.x = input->getMouseX();
			bulletDir.y = input->getMouseY();
			bulletDir = bulletDir - playerPos;
			bulletDir = Vector::normalise(bulletDir);
			bullet.spawnPosition = getPosition();
			bullet.Spawn(bulletDir, getSize());
			clock.restart();
		}
	}
}

void Player::CollisionCheck()
{
	for (int i = 0; i < bullet.bullets.size(); i++)
	{
		if (bullet.bullets[i].isAlive())	//COLLISION BETWEEN PLAYER BULLETS AND BOSS
		{
			if (guardFSM->health > 0)
			{
				if (Collision::checkBoundingBox(&bullet.bullets[i], guardFSM))
				{
					bullet.bullets[i].setAlive(false);
					std::cout << "bullet hit guard\n";
					guardFSM->health -= 10;
				}
			}
		}
	}
	if (pHealth <= 0)
		pHealth = 0;

}
