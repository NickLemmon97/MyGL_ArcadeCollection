#include <GamePCH.h>
#include "SpaceInvaders.h"

SpaceInvaders::SpaceInvaders()
{
	
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
