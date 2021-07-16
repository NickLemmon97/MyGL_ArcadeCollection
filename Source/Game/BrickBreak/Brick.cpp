#include "Brick.h"
#include "Ball.h"

Brick::Brick(Ball* ball, int idx)
{
	m_pBall = ball;

	m_Col = Colors[idx];
}

void Brick::Init()
{
	m_Scale = { 35,30 };
	GameObject::Init();

	m_Mesh->MakeRectangle(35.0f, 30.0f, m_Col, GL_TRIANGLE_FAN);
}

void Brick::Update(float delta)
{
	if (IsOverlappingWithOther(m_pBall->GetPosition(), m_pBall->GetScale()))
	{
		bIsActive = false;

		//Spawn Upgrade?
	}
}
