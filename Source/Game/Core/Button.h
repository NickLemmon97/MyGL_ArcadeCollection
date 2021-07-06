#pragma once
#include "GameObject.h"

class Button : public GameObject
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

	void SetOnClickCallback(std::function<void()> pressed);

protected:

	bool CheckMouseInBounds(double x, double y);

	std::function<void()> OnClickCallback;

	glm::vec2 m_Scale;

	bool bIsMouseInBounds = false;
	bool bHasBeenPressedBeforeRelease = false;
};


class ButtonWithX : public Button
{
public:
	ButtonWithX(class Game* game);
	void Init() override;
	void Draw(const class Renderer& renderer) override;

protected:

	std::shared_ptr<class Shape> m_X;
};
