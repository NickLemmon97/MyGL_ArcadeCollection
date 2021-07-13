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

	m_RemainingDisplay = new Shape();
}

DeathRace::~DeathRace()
{
	delete m_RemainingDisplay;
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

	m_RemainingDisplay->MakeSqaure(10, ColorList::WHITE, GL_TRIANGLE_FAN);

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Death Race Created");
}

void DeathRace::Update(double delta)
{
	Game::Update(delta);

	m_RemainingCount = 0;

	for (int i = m_CarIdx + 1; i < m_CarIdx + 13; i++)
	{
		if (static_cast<Pedestrian*>(m_GameObjects[i])->GetIsDead()) continue;
		m_RemainingCount++;

		glm::vec2 pos, scale;
		pos = m_GameObjects[m_CarIdx]->GetPosition();
		scale = m_GameObjects[m_CarIdx]->GetScale();

		if (m_GameObjects[i]->IsOverlappingWithOther(pos, scale))
		{
			m_GameObjects[i]->HandleBeginOverlap();
		}
	}
}

void DeathRace::Draw(const Renderer& renderer)
{
	Game::Draw(renderer);

	for (int i = 0; i < m_RemainingCount; i++)
	{
		glm::vec2 anchor = { 0.0f,1.0f };
		glm::vec2 pos = { 
			-(i * 18),
			-20 };

		renderer.DrawUI(*m_RemainingDisplay, pos, anchor, 0);
	}
}
