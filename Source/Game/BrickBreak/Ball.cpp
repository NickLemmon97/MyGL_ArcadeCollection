#include "Ball.h"

void Ball::Init()
{
	m_Mesh->MakeCircle(30, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Position = { 30.0f, 30.0f };
}

void Ball::Update(float delta)
{
}

void Ball::Bounce()
{
}
