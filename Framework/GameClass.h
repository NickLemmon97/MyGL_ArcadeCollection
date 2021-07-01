#pragma once
#include "../ProjectConfig.h"

class IGameClass
{
public:

	virtual void Update(double delta) = 0;
	virtual void Draw(const class Renderer& renderer) = 0;
	virtual void HandleInput(int key, int scancode, int action, int mode) = 0;
};
