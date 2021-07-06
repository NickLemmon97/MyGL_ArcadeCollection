#pragma once
#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(Game* game);
	~Button() = default;

	void HandleMouseCursor(double x, double y);
	void HandleMouseButton(int button, int action, int mods);

	void HandleClicked();

	void Init() override;

	void SetHovered();
	void SetUnHovered();

	void SetOnClickCallback(std::function<void()> pressed);

protected:

	bool CheckMouseInBounds(double x, double y);

	std::function<void()> OnClickCallback;

	glm::vec2 m_Scale;

	bool bIsMouseInBounds = false;
	bool bHasBeenPressedBeforeRelease = false;
};

