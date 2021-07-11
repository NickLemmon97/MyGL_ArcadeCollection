#pragma once
#include "Core/GameObject.h"

class TrialShip : public GameObject
{
public:
	TrialShip(class Game* game);
	void Init();
	void Update(double delta);

protected:
	void HandleCursorPos(double x, double y);
};
