#include "DeathGame.h"
#include "Car.h"

DeathRace::DeathRace()
{
	m_GameObjects.push_back(std::make_shared<Car>(this));
}

DeathRace::~DeathRace()
{
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

}
