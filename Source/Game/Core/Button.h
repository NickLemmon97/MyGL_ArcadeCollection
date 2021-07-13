#pragma once
#include "UIObject.h"

class Button : public UIObject
{
public:
	Button(class Game* game);
	Button(class Game* game, glm::vec2 scale, glm::vec2 position);
	~Button() = default;

	void HandleMouseCursor(double x, double y);
	void HandleMouseButton(int button, int action, int mods);

	void HandleClicked();

	void Init() override;

	void SetHovered();
	void SetUnHovered();
	void SetPressed();

	void SetOnClickCallback(std::function<void()> pressed);

protected:

	bool CheckMouseInBounds(double x, double y);

	std::function<void()> OnClickCallback;

	bool bIsMouseInBounds = false;
	bool bHasBeenPressedBeforeRelease = false;
};


class ExitButton : public Button
{
public:
	ExitButton(class Game* game);
	void Init() override;
	void Draw(const class Renderer& renderer) override;

protected:

	std::shared_ptr<class Shape> m_X;
};
