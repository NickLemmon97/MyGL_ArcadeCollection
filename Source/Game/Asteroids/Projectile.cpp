#include "Projectile.h"

Projectile::Projectile()
{
	m_Rotation = 0.0f;
	m_Position = { 0.0f,0.0f };
	m_Direction = { 0.0f, 0.0f };
}

void Projectile::Init()
{
	if (bWasInitialized) return;

	bWasInitialized = true;

	m_Mesh->MakeSqaure(8.0f, ColorList::RED, GL_TRIANGLE_FAN);

	m_Scale = { 8.0f,8.0f };

	GameObject::Init();
}

void Projectile::Update(float delta)
{
	if (bIsActive)
	{
		m_Position.x += m_Direction.x * delta * 250.0f;
		m_Position.y += m_Direction.y * delta * 250.0f;
		
		ScreenWrapPosition();

		m_ActiveTimer -= delta;

		if (m_ActiveTimer < 0.0f)
		{
  			bIsActive = false;
		}
	}
}

void Projectile::Shoot(glm::vec2 dir, glm::vec2 pos)
{
	bIsActive = true;

	m_ActiveTimer = 2.0f;

	m_Direction = dir;

	m_Position = pos;
}
