#pragma once
#include "GameObject.h"

class Ship : public GameObject
{
public:
	Ship(Game* game);
	void Init();
	void Update(double delta);

protected:
	void HandleCursorPos(double x, double y);

	glm::vec2 m_Pos;
};
