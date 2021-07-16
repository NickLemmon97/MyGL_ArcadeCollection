#include "PongGame.h"
#include "PongPaddle.h"

PongGame::PongGame()
{
	m_GameObjects.push_back(new PongPaddle(this));
}

PongGame::~PongGame()
{

}

void PongGame::DisplayRules()
{
	std::cout 
		<< "------------------------------------\n"
		<< "Pong!\n"
		<< "Use W/S Up/Down to move up and down\n"
		<< "Hit the ball before it hits the wall"
		<< "------------------------------------\n"
		<< std::endl;
}

void PongGame::Init()
{
	
	Game::Init();
}

void PongGame::Update(float delta)
{
	Game::Update(delta);
}
