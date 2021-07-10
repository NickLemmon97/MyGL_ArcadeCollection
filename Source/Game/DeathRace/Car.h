#pragma once
#include "GameObject.h"
#include <stack>

class Car : public GameObject
{
	enum Direction
	{
		DOWN  = 0,
		RIGHT,
		UP,
		LEFT,
	};
	Direction m_Direction = DOWN;

	int bIsMoving = 0;

	float m_Speed;

public:
	Car(Game* game);
	~Car();

	void Init() override;
	void Update(double delta) override;

	void HandleKeyboardInput(int key, int scancode, int action, int mode);

private:
	void SetDirection(Direction d);

};
