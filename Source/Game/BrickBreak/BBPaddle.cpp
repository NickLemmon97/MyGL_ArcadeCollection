#include "BBPaddle.h"

BBPaddle::BBPaddle(Game* game)
{
	GameInputFunc input = std::bind(&BBPaddle::HandleKeyboardInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	game->RegisterForInputCallback(input);

	m_Position = { HALF_WINDOW_WIDTH, HALF_WINDOW_HEIGHT - 200.0f };
}

void BBPaddle::Init()
{
	m_Mesh->MakeRectangle(30.0f, 10.0f, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Scale = { 30.0f, 10.0f };

	GameObject::Init();
}

void BBPaddle::Update(double delta)
{
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
