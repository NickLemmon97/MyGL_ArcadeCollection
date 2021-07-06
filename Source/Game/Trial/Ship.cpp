#include "GamePCH.h"
#include "Ship.h"

Ship::Ship(Game* game)
{
	GameCursorPosFunc cursor = std::bind(&Ship::HandleCursorPos, this, std::placeholders::_1, std::placeholders::_2);
	game->RegisterForInputCallback(cursor);
}

void Ship::HandleCursorPos(double x, double y)
{
	DEBUG_LOG_MESSAGE(LogShip, LogVerbosity::Log, "Handling cursor position");
}

void Ship::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{ 0.0f,  0.5f},
		{ 0.3f, -0.8f},
		{ 0.0f, -0.3f},
		{-0.3f,  -0.8f},
	};

	m_Mesh->Init(vertices, ColorList::WHITE);
}

void Ship::Update(double delta)
{

}
