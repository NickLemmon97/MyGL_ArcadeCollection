#include "GamePCH.h"
#include "Ship.h"

using namespace std;

Ship::Ship(Game* game)
{
	GameInputFunc input = bind(&Ship::HandleKeyboardInput, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	game->RegisterForInputCallback(input);
}

void Ship::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{  0.0f,  30.0f},
		{ 30.0f, -30.0f},
		{  0.0f, -25.0f},
		{-30.0f, -30.0f},
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
	ScreenWrapPosition();
}

void Ship::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		DEBUG_LOG_MESSAGE(LogShip, LogVerbosity::Log, "Key Down");

		switch (key)
		{
		case GLFW_KEY_LEFT:
			[[fallthrough]];
		case GLFW_KEY_A:
			break;

		case GLFW_KEY_RIGHT:
			[[fallthrough]];
		case GLFW_KEY_D:
			break;

		case GLFW_KEY_UP:
			[[fallthrough]];
		case GLFW_KEY_W:
			break;

		case GLFW_KEY_DOWN:
			[[fallthrough]];
		case GLFW_KEY_S:
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT: [[fallthrough]];
		case GLFW_KEY_A: [[fallthrough]];
		case GLFW_KEY_RIGHT: [[fallthrough]];
		case GLFW_KEY_D: [[fallthrough]];
		case GLFW_KEY_UP: [[fallthrough]];
		case GLFW_KEY_W: [[fallthrough]];
		case GLFW_KEY_DOWN: [[fallthrough]];
		case GLFW_KEY_S:
			DEBUG_LOG_MESSAGE(LogShip, LogVerbosity::Log, "Key Up");
		}
	}
}
