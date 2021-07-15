#include "BrickBreakGame.h"
#include "BBPaddle.h"
#include "Ball.h"
#include "Brick.h"

BrickBreakGame::BrickBreakGame()
{
	m_GameObjects.push_back(new BBPaddle(this));
	m_GameObjects.push_back(new Ball());
	m_pBall = static_cast<Ball*>(m_GameObjects.back());

	for (int i = 0; i < 80; i++)
	{
		float xOffset = i % 10 * 40.0f;
		int yIdx = i / 6;
		float yOffset = yIdx * 35.0f;

		Brick* b = new Brick(m_pBall, yIdx);
		b->SetPosition({xOffset + HALF_WINDOW_WIDTH, yOffset + HALF_WINDOW_HEIGHT});

		m_GameObjects.push_back(b);
	}

}

void BrickBreakGame::Init()
{
	Game::Init();
}

void BrickBreakGame::Update(double delta)
{
	Game::Update(delta);
}
