#pragma once

class IGameClass
{
public:
	virtual ~IGameClass() = default;

	virtual void Init() = 0;
	virtual void Update(double delta) = 0;
	virtual void Draw(const class Renderer& renderer) = 0;
	virtual void HandleInput(int key, int scancode, int action, int mode) = 0;
	virtual void HandleMousePosition(double x, double y) = 0;
	virtual void HandleMouseInput(int button, int action, int mods) = 0;

};
