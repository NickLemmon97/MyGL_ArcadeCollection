#include <GamePCH.h>
#include "SpaceInvaders.h"
#include "InvaderShip.h"

SpaceInvaders::SpaceInvaders()
{
	m_GameObjects.push_back(new InvaderShip(this));
}

SpaceInvaders::~SpaceInvaders()
{

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
}
