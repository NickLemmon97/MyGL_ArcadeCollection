#include "DeathGame.h"
#include "Car.h"

DeathRace::DeathRace()
{
	m_GameObjects.push_back(std::make_shared<Car>(this));
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

}
