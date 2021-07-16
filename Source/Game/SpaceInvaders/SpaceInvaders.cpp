#include <GamePCH.h>
#include "SpaceInvaders.h"
#include "InvaderShip.h"
#include "Projectile.h"

SpaceInvaders::SpaceInvaders()
{
	m_GameObjects.push_back(new InvaderShip(this));
}

SpaceInvaders::~SpaceInvaders()
{
	for (auto& b : m_Projectiles)
	{
		delete b;
	}
	m_Projectiles.clear();
}

void SpaceInvaders::DisplayRules()
{
	std::cout 
		<< "----------------------------------\n"
		<< "NO RULES TO DISPLAY FOR THIS GAME!\n" 
		<< "----------------------------------\n"
		<< std::endl;
}

void SpaceInvaders::Reset()
{
	Game::Reset();
}

void SpaceInvaders::Init()
{
	Game::Init();
}

void SpaceInvaders::Update(float delta)
{
	Game::Update(delta);

	for (auto& b : m_Projectiles)
	{
		if (b->GetIsActive())
			b->Update(delta);
	}
}

void SpaceInvaders::Draw(const Renderer& renderer)
{
	Game::Draw(renderer);

	for (auto& b : m_Projectiles)
	{
		if (b->GetIsActive()) b->Draw(renderer);
	}
}

void SpaceInvaders::ShootBullet(float rot, glm::vec2 pos)
{
	Projectile* bullet = nullptr;

	for (auto& b : m_Projectiles)
	{
		if (!b->GetIsActive())
		{
			bullet = b;
			break;
		}
	}

	if (bullet == nullptr)
	{
		m_Projectiles.push_back(new Projectile());
		bullet = m_Projectiles.back();
		bullet->Init();
	}

	glm::vec2 dir = { sinf(-rot), cosf(rot) };

	bullet->Shoot(dir, pos);
}
