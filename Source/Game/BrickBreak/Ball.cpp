#include "Ball.h"

void Ball::Init()
{
	m_Mesh->MakeCircle(30, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Position = { 30.0f, 30.0f };

	m_Scale = { 15, 30 }; //Radius , Diameter I guess since I have it lol

	GameObject::Init();

	bIsBouncing = false;
}

void Ball::Update(float delta)
{
	if (!bIsBouncing) return;

	m_Position.y += 100 * delta;



}

void Ball::Bounce()
{
}

bool Ball::IsBouncing()
{
	return bIsBouncing;
}

void Ball::Shoot()
{
	bIsBouncing = true;
}
