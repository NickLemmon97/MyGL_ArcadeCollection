#include <GamePCH.h>
#include "TrialGame.h"
#include "MyGameObject.h"
#include "TrialShip.h"

TrialGame::TrialGame()
{
	m_GameObjects.push_back(new TrialShip(this));
	m_GameObjects.push_back(new MyGameObject());
}

TrialGame::~TrialGame()
{
}

void TrialGame::Init()
{
	Game::Init();

	App::Get().GetRenderer().SetBackgroundColor(ColorList::DARKGRAY);

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Trial Game Created!");	
}

void TrialGame::Update(float delta)
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
