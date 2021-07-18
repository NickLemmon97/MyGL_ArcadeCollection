#include "Ball.h"

void Ball::Init()
{
	m_Mesh->MakeCircle(30, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Position = { 30.0f, 30.0f };

	m_Scale = { 15, 30 }; //Radius , Diameter I guess since I have it lol

	GameObject::Init();

	bIsBouncing = false;

	Velocity = { 0, -100 };
}

void Ball::Update(float delta)
{
	if (!bIsBouncing) return;

	m_Position += Velocity * delta;
}

void Ball::Bounce(glm::vec2 otherPos)
{
	int checkX, checkY;

	if (otherPos.x > m_Position.x) checkX = 1;
	else checkX = -1;

	if (otherPos.y > m_Position.y) checkY = -1;
	else checkY = 1;

	Velocity.x *= checkX;
	Velocity.y *= checkY;
}

bool Ball::IsBouncing()
{
	return bIsBouncing;
}

void Ball::Shoot()
{
	bIsBouncing = true;
}
