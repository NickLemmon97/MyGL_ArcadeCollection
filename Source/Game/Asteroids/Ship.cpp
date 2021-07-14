#include "GamePCH.h"
#include "Ship.h"
#include "Projectile.h"
#include "AsteroidsGame.h"

using namespace std;

Ship::Ship(AsteroidsGame* game)
{
	m_pGame = game;

	GameInputFunc input = bind(&Ship::HandleKeyboardInput, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	game->RegisterForInputCallback(input);
}

void Ship::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{  0.0f,  40.0f},
		{ 40.0f, -40.0f},
		{  0.0f, -25.0f},
		{-40.0f, -40.0f},
	};

	m_Scale = { 30, 30 };

	m_Position = {
		App::Get().GetWindowWidth() * 0.5,
		App::Get().GetWindowHeight() * 0.5
	};

	GameObject::Init();

	m_Mesh->Init(vertices, ColorList::WHITE, GL_LINE_LOOP);
}

void Ship::Update(double delta)
{
	m_Rotation += m_RotationDirection * delta * (m_Speed * 0.01);

	if (bDoThrust)
	{
		m_Speed += delta * 50;
		if (m_Speed > 150.0f) m_Speed = 150.0f;

		m_Velocity.y = cosf(-m_Rotation);
		m_Velocity.x = sinf(-m_Rotation);
	}
	else
	{
		m_Speed -= m_Speed * 0.5f * delta;
	}

	m_Position.x += m_Velocity.x * float(delta) * m_Speed;
	m_Position.y += m_Velocity.y * float(delta) * m_Speed;

	ScreenWrapPosition();
}

void Ship::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT:
			[[fallthrough]];
		case GLFW_KEY_A:
			m_RotationDirection += 1;
			break;

		case GLFW_KEY_RIGHT:
			[[fallthrough]];
		case GLFW_KEY_D:
			m_RotationDirection += -1;
			break;

		case GLFW_KEY_UP:
			[[fallthrough]];
		case GLFW_KEY_W:
			bDoThrust = true;
			break;

		case GLFW_KEY_DOWN:
			[[fallthrough]];
		case GLFW_KEY_S:
			break;

		case GLFW_KEY_SPACE:
			m_pGame->ShootBullet(m_Rotation, m_Position);
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT: [[fallthrough]];
		case GLFW_KEY_A:
			m_RotationDirection += -1;
			break;
		case GLFW_KEY_RIGHT: [[fallthrough]];
		case GLFW_KEY_D: 
			m_RotationDirection += 1;
			break;
		case GLFW_KEY_UP: [[fallthrough]];
		case GLFW_KEY_W: 
			bDoThrust = false;
			break;
		case GLFW_KEY_DOWN: [[fallthrough]];
		case GLFW_KEY_S:
			break;
		}
	}
}
