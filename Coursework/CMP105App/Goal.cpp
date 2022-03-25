#include "Goal.h"

Goal::Goal(sf::RenderWindow* hwnd)
{
	window = hwnd;
}

Goal::~Goal()
{
}

void Goal::Init()
{
	win = false;		//Set all goal attributes
	setSize(sf::Vector2f(50, 50));
	setPosition(1100, 300);
	setFillColor(sf::Color::White);
	setOutlineColor(sf::Color::Red);
	setOutlineThickness(20);

	font.loadFromFile("font/arial.ttf");		//Set text for win
	winText.setPosition(window->getSize().x/2.5, window->getSize().y/4);
	winText.setString("YOU WON");
	winText.setCharacterSize(60);
	winText.setFillColor(sf::Color::White);
	winText.setFont(font);

	loseText.setPosition(window->getSize().x / 2.5, window->getSize().y / 4);		//Set text for lose
	loseText.setString("YOU LOST");
	loseText.setCharacterSize(60);
	loseText.setFillColor(sf::Color::Red);
	loseText.setFont(font);

	exitText.setPosition(window->getSize().x / 4, window->getSize().y / 1.6);		//Set text to exit program
	exitText.setString("Press Exit to close the program");
	exitText.setCharacterSize(40);
	exitText.setFillColor(sf::Color::White);
	exitText.setFont(font);
}

void Goal::Update(sf::Vector2f playerPos)
{
	sf::Vector2f distToPlayer = sf::Vector2f(playerPos - getPosition());		//Calculate distance to player
	if (distToPlayer.x < 0)		//If distance to player is negative, convert it to positive
		distToPlayer.x *= -1;
	if (distToPlayer.y < 0)
		distToPlayer.y *= -1;
	
	if (distToPlayer.x < 50 && distToPlayer.y < 50)			//If player is close enough to goal, player wins
		win = true;
}

void Goal::Render()
{
	window->draw(*this);		//render draw
}

void Goal::RenderWin()
{
	if (win == true)	//Render win text only if player wins
	{
		window->draw(winText);
		window->draw(exitText);
	}
}


void Goal::RenderLoss()
{		//If player loses draw lose text
	window->draw(loseText);
	window->draw(exitText);
}
