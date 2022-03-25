#pragma once
#include <SFML/Graphics.hpp>
#include "Framework\GameObject.h"
class Bullet : public GameObject		//Bullet class
{
public:
	Bullet();		//Constructor	
	~Bullet();		//Destructor

	void Init();		//Initialiser 
	void Update(float dt);		//Update function


};

