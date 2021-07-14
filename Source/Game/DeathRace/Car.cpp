#include "GamePCH.h"
#include "Car.h"

using namespace std;

Car::Car(Game* game)
{
	GameInputFunc input = bind(&Car::HandleKeyboardInput, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	game->RegisterForInputCallback(input);

	m_Speed = 185.0f;
}

Car::~Car()
{

}

void Car::Init()
{
	float farh = 7;
	float width = 5;
	float sizeModifier = 12;

	CreateCarMesh(width, farh, sizeModifier);

	m_Scale = { width * sizeModifier, farh * sizeModifier };

	m_Position = {
		App::Get().GetWindowWidth()  * 0.5,
		App::Get().GetWindowHeight() * 0.5
	};

	GameObject::Init();
}

void Car::Update(double delta)
{
	GameObject::Update(delta);

	if (bIsMoving > 0)
	{
		float speed = m_Speed* delta;
		switch (m_Direction)
		{
		case UP:
			m_Position.y += speed;
			KeepInScreenBounds();
			break;
		case DOWN:
			m_Position.y -= speed;
			KeepInScreenBounds();
			break;
		case LEFT:
			m_Position.x -= speed;
			KeepInScreenBounds();
			break;
		case RIGHT:
			m_Position.x += speed;
			KeepInScreenBounds();
			break;
		}
	}
}

void Car::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		bIsMoving++;

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

		default:
			bIsMoving--;
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
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
		
		bIsMoving--;
		if (bIsMoving < 0) bIsMoving = 0;
		}
	}
}

void Car::SetDirection(Direction d)
{
	m_Direction = d;

	switch (d)
	{
	case UP: 
		m_Rotation = 3.14f;
		m_Scale = { 5 * 12, 7 * 12 };
		break;
	case DOWN:
		m_Rotation = 0.0f;
		m_Scale = { 5 * 12, 7 * 12 };
		break;
	case LEFT:
		m_Rotation = 4.71f;
		m_Scale = { 7 * 12, 5 * 12};
		break;
	case RIGHT:
		m_Rotation = 1.57f;
		m_Scale = { 7 * 12, 5 * 12 };
		break;
	}
}

void Car::CreateCarMesh(int width, int farh, int sizeModifier)
{
	float axley = 5;
	float bodywidth = 2.5;

	std::vector<glm::vec2> points =
	{
		//front bumper
		{0.0f, -farh},{-width, -farh},{-width, -axley},{-bodywidth, -axley},
		//wheel
		{-bodywidth, -3},{-4, -3},{-4, -4},{-width, -4},{-width, -1},{-4, -1},{-4, -2},

		{-bodywidth, -2},
		{-bodywidth, 2},
		//wheel
		{-4, 2},{-4, 1},{-width, 1},{-width, 4},{-4, 4},{-4, 3},{-bodywidth, 3},
		//wheel
		{bodywidth, 3},	{4, 3},{4, 4},{width, 4},	{width, 1},{4, 1},	{4, 2},

		{bodywidth, 2},
		{bodywidth, -2},
		//wheel
		{4, -2},{4, -1},{width, -1},{width, -4},{4, -4},{4, -3},{bodywidth, -3},
		//bumper
		{bodywidth, -axley},{width, -axley},{width, -farh},
	};

	for (auto& v : points)
	{
		v.y += 1;
		v *= sizeModifier;
	}

	m_Mesh->Init(points, ColorList::WHITE, GL_LINE_LOOP);
}
