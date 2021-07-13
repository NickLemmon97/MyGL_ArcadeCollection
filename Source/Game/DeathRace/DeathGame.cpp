#include <GamePCH.h>
#include "DeathGame.h"
#include "Car.h"
#include "Pedestrian.h"

DeathRace::DeathRace()
{
	m_GameObjects.push_back(new Car(this));
	m_CarIdx = m_GameObjects.size() - 1;

	for (int i = 0; i < 12; i++)
	{
		m_GameObjects.push_back(new Pedestrian());
	}
}

DeathRace::~DeathRace()
{
}

void DeathRace::DisplayRules()
{
	std::cout
		<< "-----------------------------------------------\n"
		<< "RULES:\n"
		<< "Move the player car around with WASD/Arrow Keys\n"
		<< "Hit all the other objects on screen\n"
		<< "-----------------------------------------------"
		<< std::endl;
}

void DeathRace::Init()
{
	Game::Init();

	App::Get().GetRenderer().SetBackgroundColor(ColorList::DARKGRAY);
	App::Get().SetWindowTitle("Death Race");

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Death Race Created");
}

void DeathRace::Update(double delta)
{
	Game::Update(delta);

	for (int i = m_CarIdx + 1; i < m_CarIdx + 13; i++)
	{
		glm::vec2 pos, scale;
		pos = m_GameObjects[m_CarIdx]->GetPosition();
		scale = m_GameObjects[m_CarIdx]->GetScale();

		if (m_GameObjects[i]->IsOverlappingWithOther(pos, scale))
		{
			m_GameObjects[i]->HandleBeginOverlap();
		}
	}
}
