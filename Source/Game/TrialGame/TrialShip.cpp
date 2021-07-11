#include "GamePCH.h"
#include "TrialShip.h"

TrialShip::TrialShip(Game* game)
{
	GameCursorPosFunc cursor = std::bind(&TrialShip::HandleCursorPos, this, std::placeholders::_1, std::placeholders::_2);
	game->RegisterForInputCallback(cursor);
}

void TrialShip::HandleCursorPos(double x, double y)
{
	float nx = x;
	float ny = y;

	m_Position.x = nx;
	m_Position.y = ny;
}

void TrialShip::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{  0.0f,  50.0f},
		{ 30.0f, -50.0f},
		{  0.0f, -30.0f},
		{-30.0f, -50.0f},
	};

	m_Scale = { 30, 50 };
	GameObject::Init();

	m_Mesh->Init(vertices, ColorList::WHITE, GL_LINE_LOOP);
}

void TrialShip::Update(double delta)
{
}
