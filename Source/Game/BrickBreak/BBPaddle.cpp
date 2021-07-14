#include "BBPaddle.h"

BBPaddle::BBPaddle(Game* game)
{
	GameInputFunc input = std::bind(&BBPaddle::HandleKeyboardInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	game->RegisterForInputCallback(input);

	m_Position = { HALF_WINDOW_WIDTH, 180.0f };
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

void BBPaddle::Update(double delta)
{
	m_Position.x += m_Direction * delta * 100.0f;

	KeepInScreenBounds();
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
