#include "BrickBreakGame.h"
#include "BBPaddle.h"
#include "Ball.h"
#include "Brick.h"

BrickBreakGame::BrickBreakGame()
{
	m_GameObjects.push_back(new BBPaddle(this));
	BBPaddle* paddle = static_cast<BBPaddle*>(m_GameObjects.back());
	m_GameObjects.push_back(new Ball());
	m_pBall = static_cast<Ball*>(m_GameObjects.back());

	paddle->SetBall(m_pBall);

	for (int i = 0; i < 126; i++)
	{
		float xOffset = i % 18 * 40.0f;
		int yIdx = i / 18;
		float yOffset = yIdx * 35.0f;

		Brick* b = new Brick(m_pBall, yIdx);
		b->SetPosition({xOffset + HALF_WINDOW_WIDTH - (9 * 40), yOffset + HALF_WINDOW_HEIGHT - (1 * 35)});

		m_GameObjects.push_back(b);
	}
}

void BrickBreakGame::Init()
{
	Game::Init();
}

void BrickBreakGame::Update(float delta)
{
	Game::Update(delta);

}

void BrickBreakGame::HandleInput(int key, int scancode, int action, int mode)
{
	Game::HandleInput(key, scancode, action, mode);

	if (!m_pBall->IsBouncing())
	{
		if (key == GLFW_KEY_SPACE)
		{
			m_pBall->Shoot();
		}
	}

}


