#include "BrickBreakGame.h"
#include "BBPaddle.h"
#include "Ball.h"
#include "Brick.h"

BrickBreakGame::BrickBreakGame()
{
	m_GameObjects.push_back(new BBPaddle(this));
	m_GameObjects.push_back(new Ball());
	m_pBall = static_cast<Ball*>(m_GameObjects.back());

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

	if (!m_pBall->IsBouncing())
	{
		m_pBall->SetPosition({ m_GameObjects[0]->GetPosition().x, m_GameObjects[0]->GetPosition().y + 40.0f });

		return;
	}
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


