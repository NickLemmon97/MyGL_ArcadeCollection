#include "GamePCH.h"
#include "Button.h"

Button::Button(Game* game) : Button(game, { 60.0f,40.0f }, { 80.0f, INITIAL_WINDOW_HEIGHT - 40.0f })
{
}

Button::Button(Game* game, glm::vec2 scale, glm::vec2 position)
{
	GameMouseInputFunc mouse = std::bind(&Button::HandleMouseButton, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	game->RegisterForInputCallback(mouse);

	GameCursorPosFunc cursor = std::bind(&Button::HandleMouseCursor, this, std::placeholders::_1, std::placeholders::_2);
	game->RegisterForInputCallback(cursor);

	m_Scale = scale;
	m_Position = position;
}

void Button::HandleMouseCursor(double x, double y)
{
	bIsMouseInBounds = IsOverlappingWithOther({ x, y }, { 0,0 });

	if (bIsMouseInBounds)
	{
		if(!bHasBeenPressedBeforeRelease)
			SetHovered();
	}
	else
	{
		SetUnHovered();
		bHasBeenPressedBeforeRelease = false;
	}
}

void Button::HandleMouseButton(int button, int action, int mods)
{
	if (bIsMouseInBounds)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			bHasBeenPressedBeforeRelease = true;
			SetPressed();
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && bHasBeenPressedBeforeRelease)
		{
			bHasBeenPressedBeforeRelease = false;

			HandleClicked();
		}
	}
}

void Button::HandleClicked()
{
	if (OnClickCallback)
	{
		DEBUG_LOG_MESSAGE(LogButton, LogVerbosity::Success, "Button Clicked!");
		OnClickCallback();
	}
}

void Button::Init()
{
	m_Mesh->MakeRectangle(m_Scale.x, m_Scale.y, ColorList::RED, GL_TRIANGLE_FAN);
}

void Button::SetHovered()
{
	m_Mesh->SetPrimitive(GL_LINE_LOOP);
}

void Button::SetUnHovered()
{
	m_Mesh->SetPrimitive(GL_TRIANGLE_FAN);
	m_Mesh->SetColor(ColorList::RED);
}

void Button::SetPressed()
{
	m_Mesh->SetColor(ColorList::GREEN);
}

void Button::SetOnClickCallback(std::function<void()> pressed)
{
	OnClickCallback = pressed;
}

bool Button::CheckMouseInBounds(double x, double y)
{
	return 
		(x >= m_Position.x - m_Scale.x &&
		 x <= m_Position.x + m_Scale.x &&
		 y >= m_Position.y - m_Scale.y &&
		 y <= m_Position.y + m_Scale.y);
}


ExitButton::ExitButton(Game* game) : Button(game, { 35,20 }, {45, INITIAL_WINDOW_HEIGHT - 35})
{
	std::function<void()> exitButtonCallback = std::bind(&Game::Exit, game);
	SetOnClickCallback(exitButtonCallback);
}

void ExitButton::Init()
{
	Button::Init();

	m_X = std::make_shared<Shape>();
	std::vector<glm::vec2> points
	{
		{0.0f,0.0f},
		{12.0f,20.0f},
		{20.0f,12.0f},
		{0.0f,0.0f},
		{20.0f,-12.0f},
		{12.0f,-20.0f},
		{0.0f,0.0f},
		{-12.0f,-20.0f},
		{-20.0f,-12.0f},
		{0.0f,0.0f},
		{-20.0f,12.0f},
		{-12.0f,20.0f},
	};

	m_X->Init(points, ColorList::WHITE, GL_TRIANGLES);
}

void ExitButton::Draw(const Renderer& renderer)
{
	GameObject::Draw(renderer);

	renderer.Draw(*m_X.get(), m_Position);
}
