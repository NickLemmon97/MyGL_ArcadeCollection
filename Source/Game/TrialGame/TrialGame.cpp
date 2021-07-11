#include <GamePCH.h>
#include "TrialGame.h"
#include "MyGameObject.h"
#include "Ship.h"

TrialGame::TrialGame()
{
	m_GameObjects.push_back(std::make_shared<Ship>(this));
	m_GameObjects.push_back(std::make_shared<MyGameObject>());
}

TrialGame::~TrialGame()
{
}

void TrialGame::Init()
{
	Game::Init();

	App::Get().GetRenderer().SetBackgroundColor(ColorList::GREEN);

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Trrial Game Created!");	
}

void TrialGame::Update(double delta)
{
	Game::Update(delta);
	if (m_GameObjects[1]->IsOverlappingWithOther(m_GameObjects[0]->GetPosition(), m_GameObjects[0]->GetScale()))
	{
		m_GameObjects[1]->HandleBeginOverlap();
	}
	else
	{
		m_GameObjects[1]->HandleEndOverlap();
	}
}
