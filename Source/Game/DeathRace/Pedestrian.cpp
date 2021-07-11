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

	GameObject::Init();
}

void Pedestrian::Update(double delta)
{
	if (bIsDead) return;
}

void Pedestrian::Draw(const Renderer& renderer)
{
	if (bIsDead) return;

	GameObject::Draw(renderer);
}

bool Pedestrian::GetIsDead()
{
	return bIsDead;
}

void Pedestrian::HandleBeginOverlap()
{
	//bIsDead = true;

	m_Mesh->SetColor(ColorList::RED);
}
