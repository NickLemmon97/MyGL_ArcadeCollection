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
	if (IsOverlappingBall())
	{
		bIsActive = false;

		m_pBall->Bounce(m_Position);
	}
}

bool Brick::IsOverlappingBall()
{
	glm::vec2 ballPos = m_pBall->GetPosition();
	glm::vec2 checkPos = m_pBall->GetPosition();

	if (ballPos.x < m_Position.x - m_Scale.x)      checkPos.x = m_Position.x - m_Scale.x;
	else if (ballPos.x > m_Position.x + m_Scale.x) checkPos.x = m_Position.x + m_Scale.x;

	if (ballPos.y < m_Position.y - m_Scale.y)      checkPos.y = m_Position.y - m_Scale.y;
	else if (ballPos.y > m_Position.y + m_Scale.y) checkPos.y = m_Position.y + m_Scale.y;

	float distX = ballPos.x - checkPos.x;
	float distY = ballPos.y - checkPos.y;

	float distance = (distX * distX) + (distY * distY);

	return (distance <= (m_pBall->GetScale().x * m_pBall->GetScale().x));
}
