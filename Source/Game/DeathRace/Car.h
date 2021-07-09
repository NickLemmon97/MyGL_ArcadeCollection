#pragma once
#include "GameObject.h"


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

public:
	Car(Game* game);
	~Car();

	void Init() override;
	void Update(double delta) override;

	void HandleKeyboardInput(int key, int scancode, int action, int mode);

private:
	void SetDirection(Direction d);

};
