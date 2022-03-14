#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Update(float dt)
{

	move(getVelocity() * dt);
}
