#pragma once
#include <SFML/Graphics.hpp>
#include "Framework\GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void Init();
	void Update(float dt);


};

