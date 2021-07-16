#include "InvaderShip.h"
#include "SpaceInvaders.h"

InvaderShip::InvaderShip(Game* game)
{
	GameInputFunc input = std::bind(&InvaderShip::HandleKeyboardInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	game->RegisterForInputCallback(input);

	m_pGame = static_cast<SpaceInvaders*>(game);

	m_Position = { HALF_WINDOW_WIDTH, 50.0f };
}

void InvaderShip::Init()
{
	float w, h;
	w = 60.f;
	h = 18.0f;

	std::vector<glm::vec2> verts =
	{
		{w, h},
		{w,-h},
		{-w,-h},
		{-w,h},
		{0.0f, h + 15.0f},
	};

	m_Mesh->Init(verts, ColorList::WHITE, GL_TRIANGLE_FAN);

	m_Scale = { w,h };

	GameObject::Init();
}

void InvaderShip::Update(float delta)
{
	m_Position.x += m_Direction * delta * 100.0f;

	KeepInScreenBounds();
}

void InvaderShip::HandleKeyboardInput(int key, int scancode, int action, int mode)
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

		case GLFW_KEY_SPACE:
			m_pGame->ShootBullet(m_Rotation, { m_Position.x, m_Position.y + 18.0f });
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
