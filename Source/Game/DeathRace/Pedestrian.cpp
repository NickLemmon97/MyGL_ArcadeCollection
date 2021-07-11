#include "GamePCH.h"
#include "Pedestrian.h"

void Pedestrian::Init()
{
	float width = 12.0f;
	float height = 25.0f;

	m_Mesh->MakeRectangle(width, height, ColorList::WHITE, GL_LINE_LOOP);

	m_Scale = { width + 1, height + 1 };

	m_Position.x = Random::RandomFloat(30.0f, INITIAL_WINDOW_WIDTH - 30.0f);
	m_Position.y = Random::RandomFloat(30.0f, INITIAL_WINDOW_HEIGHT - 30.0f);

	bIsDead = false;
	
	UpdateDirection();

	GameObject::Init();
}

void Pedestrian::Update(double delta)
{
	if (bIsDead) return;

	m_Position.x += m_Movement.x * delta * 100;
	m_Position.y += m_Movement.y * delta * 100;

	if (m_Position.x < 0)
		m_Position.x += INITIAL_WINDOW_WIDTH;
	if (m_Position.y < 0)
		m_Position.y += INITIAL_WINDOW_HEIGHT;
	if (m_Position.x > INITIAL_WINDOW_WIDTH)
		m_Position.x -= INITIAL_WINDOW_WIDTH;
	if (m_Position.y > INITIAL_WINDOW_HEIGHT)
		m_Position.y -= INITIAL_WINDOW_HEIGHT;

	m_Timer -= delta;

	if (m_Timer < 0)
		UpdateDirection();

}

void Pedestrian::Draw(const Renderer& renderer)
{
	//if (bIsDead) return;

	GameObject::Draw(renderer);
}

bool Pedestrian::GetIsDead()
{
	return bIsDead;
}

void Pedestrian::HandleBeginOverlap()
{
	m_Mesh->SetColor(ColorList::RED);
	bIsDead = true;
}

void Pedestrian::UpdateDirection()
{
	m_Direction = Random::RandomFloat(0, 6.28);

	m_Movement.x = sinf(m_Direction);
	m_Movement.y = cosf(m_Direction);

	m_Timer = Random::RandomFloat(0.5f, 2.5f);
}
