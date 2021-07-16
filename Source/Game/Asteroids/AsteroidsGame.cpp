#include <GamePCH.h>
#include "AsteroidsGame.h"
#include "Ship.h"
#include "Meteor.h"
#include "Projectile.h"

AsteroidsGame::AsteroidsGame()
{
	m_GameObjects.push_back(new Ship(this));
	m_pPlayer = static_cast<Ship*>( m_GameObjects.back() );

	for (int i = 0; i < 20; i++)
	{
		m_GameObjects.push_back(new Meteor());
	}

	ResetCountDownIcon = std::make_unique<Shape>();
}

AsteroidsGame::~AsteroidsGame()
{
	m_pPlayer = nullptr;

	for (auto& b : m_Projectiles)
	{
		delete b;
	}
	m_Projectiles.clear();
}

void AsteroidsGame::DisplayRules()
{
	std::cout
		<< "---------------------------\n"
		<< "A Classic game of asteroids\n"
		<< "Move with WASD/Arrows.\n"
		<< "Shoot with Space\n"
		<< "Destroy all Meteors to win!\n"
		<< "---------------------------\n"
		<< std::endl;
}

void AsteroidsGame::Init()
{
	Game::Init();

	App::Get().GetRenderer().SetBackgroundColor(ColorList::DARKGRAY);
	App::Get().SetWindowTitle("Asteroids");

	ResetCountDownIcon->MakeSqaure(10.0f, ColorList::WHITE, GL_TRIANGLE_FAN);

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Trial Game Created!");	
}

void AsteroidsGame::Update(float delta)
{
	Game::Update(delta);

	for (auto& b : m_Projectiles)
	{
		if (b->GetIsActive())
			b->Update(delta);
	}

	int RemainingAsteroids = 0;

	for (int i = 1; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetIsActive() == false) continue;

		RemainingAsteroids++;

		glm::vec2 pos = m_GameObjects[i]->GetPosition();
		glm::vec2 scale = m_GameObjects[i]->GetScale();

		if(m_pPlayer->IsOverlappingWithOther(pos, scale))
		{
			m_pPlayer->HandleBeginOverlap();

			m_GameObjects[i]->HandleBeginOverlap();
		}
		else
		{
			m_GameObjects[i]->HandleEndOverlap();
		}

		for (auto& b : m_Projectiles)
		{
			if (!b->GetIsActive()) continue;

			if (m_GameObjects[i]->IsOverlappingWithOther(b->GetPosition(), b->GetScale()))
			{
				m_GameObjects[i]->HandleBeginOverlap();
			}
		}
	}

	if (bStartReset)
	{
		ResetTimer -= delta;

		if (ResetTimer <= 0.0f)
		{
			bStartReset = false;
			Reset();
		}

		return;
	}


	if (RemainingAsteroids == 0)
	{
		//game has been won
		TriggerReset();
	}

}

void AsteroidsGame::Draw(const Renderer& renderer)
{
	Game::Draw(renderer);

	for (auto& b : m_Projectiles)
	{
		if (b->GetIsActive()) b->Draw(renderer);
	}


	if (bStartReset)
	{
		for (int i = 0; i < int(ResetTimer) + 1; i++)
		{
			glm::vec2 pos = { -10.0f + (i * 13), 0.0f };
			glm::vec2 anchor = { 0.0f,0.0f };
			renderer.DrawUI(*ResetCountDownIcon, pos, anchor, 0.0f);
		}
	}
}

void AsteroidsGame::ShootBullet(float rot, glm::vec2 pos)
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

	if(bullet == nullptr)
	{
		m_Projectiles.push_back(new Projectile());
		bullet = m_Projectiles.back();
		bullet->Init();
	}

	glm::vec2 dir = { sinf(-rot), cosf(rot) };

	bullet->Shoot(dir, pos);
}

void AsteroidsGame::TriggerReset()
{
	bStartReset = true;

	ResetTimer = 3.0f;
}
