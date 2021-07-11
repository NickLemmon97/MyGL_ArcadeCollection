#pragma once
#include "Core/GameObject.h"

class Ship : public GameObject
{
public:
	Ship(class Game* game);
	void Init();
	void Update(double delta);

protected:
	void HandleKeyboardInput(int key, int scancode, int action, int mode);
};
