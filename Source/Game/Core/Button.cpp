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
	bIsMouseInBounds = CheckMouseInBounds(x,y);

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
	UIObject::Init();
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
	float width  = (float)App::Get().GetWindowWidth();
	float height = (float)App::Get().GetWindowHeight();

	float xAnchorOffset = (width - (width * -m_Anchor.x));
	float yAnchorOffset = (height * m_Anchor.y);

	glm::vec2 posOffset = { xAnchorOffset + m_Position.x, yAnchorOffset + m_Position.y };

	return 
		((float)x >= (posOffset.x - m_Scale.x) &&
		 (float)x <= (posOffset.x + m_Scale.x) &&
		 (float)y >= (posOffset.y - m_Scale.y) &&
		 (float)y <= (posOffset.y + m_Scale.y) );
}


ExitButton::ExitButton(Game* game) : Button(game, { 35,20 }, {0,0})
{
	std::function<void()> exitButtonCallback = std::bind(&Game::Exit, game);
	SetOnClickCallback(exitButtonCallback);

	m_Position = { 35, -20 };
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

	m_Anchor = { -1.0f, 1.0f };
}

void ExitButton::Draw(const Renderer& renderer)
{
	UIObject::Draw(renderer);

	renderer.DrawUI(*m_X.get(), m_Position, m_Anchor, m_Rotation);
}
