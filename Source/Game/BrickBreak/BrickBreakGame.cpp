#include "BrickBreakGame.h"
#include "BBPaddle.h"

BrickBreakGame::BrickBreakGame()
{
	m_GameObjects.push_back(new BBPaddle(this));
}

void BrickBreakGame::Init()
{
	Game::Init();
}

void BrickBreakGame::Update(double delta)
{
	Game::Update(delta);
}
