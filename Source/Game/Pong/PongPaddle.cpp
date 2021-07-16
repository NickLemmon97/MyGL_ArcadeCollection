#include "PongPaddle.h"

PongPaddle::PongPaddle(Game* game)
{
	GameInputFunc input = std::bind(&PongPaddle::HandleKeyboardInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	game->RegisterForInputCallback(input);

	m_Position = { 30.0f, 180.0f };
}

void PongPaddle::Init()
{
	float w, h;
	h = 100.f;
	w = 35.0f;
	m_Mesh->MakeRectangle(w,h, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Scale = { w,h };

	GameObject::Init();
}

void PongPaddle::Update(float delta)
{
	m_Position.y -= m_Direction * delta * 140.0f;

	KeepInScreenBounds();
}

void PongPaddle::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W: [[fallthrough]];
		case GLFW_KEY_UP:
			m_Direction--;
			break;

		case GLFW_KEY_S: [[fallthrough]];
		case GLFW_KEY_DOWN:
			m_Direction++;
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W: [[fallthrough]];
		case GLFW_KEY_UP:
			m_Direction++;
				break;

		case GLFW_KEY_S: [[fallthrough]];
		case GLFW_KEY_DOWN:
			m_Direction--;
			break;
		}
	}
}
