#include <GamePCH.h>
#include "AsteroidsGame.h"
#include "Ship.h"
#include "Meteor.h"

AsteroidsGame::AsteroidsGame()
{
	m_GameObjects.push_back(std::make_shared<Ship>(this));
	m_pPlayer = m_GameObjects.back().get();

	for (int i = 0; i < 20; i++)
	{
		m_GameObjects.push_back(std::make_shared<Meteor>());
	}
}

AsteroidsGame::~AsteroidsGame()
{
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

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Trial Game Created!");	
}

void AsteroidsGame::Update(double delta)
{
	Game::Update(delta);

	for (int i = 2; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetIsActive() == false) continue;

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
	}
}
