#include "BBPaddle.h"
#include "Ball.h"

BBPaddle::BBPaddle(Game* game)
{
	GameInputFunc input = std::bind(&BBPaddle::HandleKeyboardInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	game->RegisterForInputCallback(input);

	m_Position = { HALF_WINDOW_WIDTH, 100.0f };
}

void BBPaddle::Init()
{
	float w, h;
	w = 100.f;
	h = 35.0f;
	m_Mesh->MakeRectangle(w,h, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Scale = { w,h };

	GameObject::Init();
}

void BBPaddle::Update(float delta)
{
	if (!m_pBall->IsBouncing())
	{
		m_pBall->SetPosition({GetPosition().x, GetPosition().y + 1140.0f });
	}

	if (IsOverlappingBall())
	{
		m_pBall->Bounce(GetPosition());
	}

	m_Position.x += m_Direction * delta * 160.0f;

	KeepInScreenBounds();
}

void BBPaddle::SetBall(Ball* ball)
{
	m_pBall = ball;
}

void BBPaddle::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_A: [[fallthrough]];
		case GLFW_KEY_LEFT:
			m_Direction--;
			break;

		case GLFW_KEY_D: [[fallthrough]];
		case GLFW_KEY_RIGHT:
			m_Direction++;
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_A: [[fallthrough]];
		case GLFW_KEY_LEFT:
			m_Direction++;
				break;

		case GLFW_KEY_D: [[fallthrough]];
		case GLFW_KEY_RIGHT:
			m_Direction--;
			break;
		}
	}
}

bool BBPaddle::IsOverlappingBall()
{
	glm::vec2 ballPos = m_pBall->GetPosition();
	glm::vec2 checkPos = m_pBall->GetPosition();

	if (ballPos.x < m_Position.x - m_Scale.x)      
		checkPos.x = m_Position.x - m_Scale.x;
	else if (ballPos.x > m_Position.x + m_Scale.x) 
		checkPos.x = m_Position.x + m_Scale.x;

	if (ballPos.y < m_Position.y - m_Scale.y)      
		checkPos.y = m_Position.y - m_Scale.y;
	else if (ballPos.y > m_Position.y + m_Scale.y) 
		checkPos.y = m_Position.y + m_Scale.y;

	float distX = ballPos.x - checkPos.x;
	float distY = ballPos.y - checkPos.y;

	float distance = (distX * distX) + (distY * distY);

	return (distance <= (m_pBall->GetScale().x * m_pBall->GetScale().x));
}
