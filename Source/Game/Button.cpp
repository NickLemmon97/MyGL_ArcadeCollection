#include "GamePCH.h"
#include "Button.h"

Button::Button(Game* game)
{
	GameMouseInputFunc mouse = std::bind(&Button::HandleMouseButton, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	game->RegisterForInputCallback(mouse);

	GameCursorPosFunc cursor = std::bind(&Button::HandleMouseCursor, this, std::placeholders::_1, std::placeholders::_2);
	game->RegisterForInputCallback(cursor);

	m_Scale.x = 200;
	m_Scale.y = 100;

	m_Position.x = 500;
	m_Position.y = 200;
}

void Button::HandleMouseCursor(double x, double y)
{
	bIsMouseInBounds = CheckMouseInBounds(x, y);

	if (bIsMouseInBounds)
	{
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
	else
	{
		DEBUG_LOG_MESSAGE(LogButton, LogVerbosity::Error, "Button Clicked with no callback set");
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
