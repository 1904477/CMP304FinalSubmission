#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in) : manager(hwnd,in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	manager.Init();
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

}

// Update game objects
void Level::update(float dt)
{
	manager.Update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	manager.Render();
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}