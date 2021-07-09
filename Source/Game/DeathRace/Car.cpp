#include "GamePCH.h"
#include "Car.h"

using namespace std;

Car::Car(Game* game)
{
	GameInputFunc input = bind(&Car::HandleKeyboardInput, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	game->RegisterForInputCallback(input);

	m_Position = { 100.0f, 100.0f };
}

Car::~Car()
{

}

void Car::Init()
{
	//Should not hard code my game objects - it takes a while

	float farh = 7;
	float axley = 5;
	float width = 5;
	float bodywidth = 2.5;

	std::vector<glm::vec2> points =
	{
		//bumper
		{0.0f, -farh},
		{-width, -farh},
		{-width, -axley},
		{-bodywidth, -axley},
		//wheel
		{-bodywidth, -3},
		{-4, -3},
		{-4, -4},
		{-width, -4},
		{-width, -1},
		{-4, -1},
		{-4, -2},

		{-bodywidth, -2},

		{-bodywidth, 2},
		//wheel
		{-4, 2},
		{-4, 1},
		{-width, 1},
		{-width, 4},
		{-4, 4},
		{-4, 3},
		{-bodywidth, 3},
		//wheel
		{bodywidth, 3},
		{4, 3},
		{4, 4},
		{width, 4},
		{width, 1},
		{4, 1},
		{4, 2},


		{bodywidth, 2},

		{bodywidth, -2},
		//wheel
		{4, -2},
		{4, -1},
		{width, -1},
		{width, -4},
		{4, -4},
		{4, -3},
		{bodywidth, -3},
		//bumper
		{bodywidth, -axley},
		{width, -axley},
		{width, -farh},
	};

	//Modifiers to avoid rewriting the above code in anyway
	for (auto& v : points)
	{
		v.y += 1;
		v *= 4;
	}

	m_Mesh->Init(points, ColorList::WHITE, GL_LINE_LOOP);

	m_Scale = { 20,24 };
	GameObject::Init();
}

void Car::Update(double delta)
{

}

void Car::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	switch (key)
	{

	case GLFW_KEY_LEFT:
		[[fallthrough]];
	case GLFW_KEY_A:
		SetDirection(LEFT);
		break;

	case GLFW_KEY_RIGHT:
		[[fallthrough]];
	case GLFW_KEY_D:
		SetDirection(RIGHT);
		break;

	case GLFW_KEY_UP:
		[[fallthrough]];
	case GLFW_KEY_W:
		SetDirection(UP);
		break;

	case GLFW_KEY_DOWN:
		[[fallthrough]];
	case GLFW_KEY_S:
		SetDirection(DOWN);
		break;
	}

	switch (key)
	{
	case GLFW_KEY_LEFT: [[fallthrough]];
	case GLFW_KEY_A:	[[fallthrough]];
	case GLFW_KEY_RIGHT:[[fallthrough]];
	case GLFW_KEY_D:	[[fallthrough]];
	case GLFW_KEY_UP:   [[fallthrough]];
	case GLFW_KEY_W:    [[fallthrough]];
	case GLFW_KEY_DOWN: [[fallthrough]];
	case GLFW_KEY_S:

		if (action == GLFW_KEY_DOWN)
			bIsMoving++;
		if (action == GLFW_KEY_UP)
			bIsMoving--;

		break;
	}
}

void Car::SetDirection(Direction d)
{
	m_Direction = d;

	switch (d)
	{
	case UP:
	case DOWN:
	case LEFT:
	case RIGHT:
		break;
	}
}
