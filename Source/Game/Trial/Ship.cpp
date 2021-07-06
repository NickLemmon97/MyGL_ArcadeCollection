#include "GamePCH.h"
#include "Ship.h"

Ship::Ship(Game* game)
{
	GameCursorPosFunc cursor = std::bind(&Ship::HandleCursorPos, this, std::placeholders::_1, std::placeholders::_2);
	game->RegisterForInputCallback(cursor);
}

void Ship::HandleCursorPos(double x, double y)
{
	float nx = x;
	float ny = y;

	m_Position.x = nx;
	m_Position.y = ny;
}

void Ship::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{   0.0f,  500.0f},
		{ 300.0f, -500.0f},
		{   0.0f, -300.0f},
		{-300.0f, -500.0f},
	};

	m_Mesh->Init(vertices, ColorList::WHITE, GL_LINE_LOOP);
}

void Ship::Update(double delta)
{

}
