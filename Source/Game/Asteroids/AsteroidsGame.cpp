#include <GamePCH.h>
#include "AsteroidsGame.h"
#include "Ship.h"
#include "Meteor.h"

AsteroidsGame::AsteroidsGame()
{
	m_GameObjects.push_back(std::make_shared<Ship>(this));

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
		<< "---------------------------\n"
		<< std::endl;
}

void AsteroidsGame::Init()
{
	Game::Init();

	App::Get().GetRenderer().SetBackgroundColor(ColorList::DARKGRAY);

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Trial Game Created!");	
}

void AsteroidsGame::Update(double delta)
{
	Game::Update(delta);

}
