#pragma once
#include <GameObject.h>

class Car : public GameObject
{
	enum class Direction
	{
		DOWN  = 0,
		RIGHT,
		UP,
		LEFT,
	};

	Direction m_Direction = Direction::DOWN;

	int bIsMoving = 0;

	float m_Speed;

public:
	Car(Game* game);
	~Car();

	void Init() override;
	void Update(float delta) override;

	void HandleKeyboardInput(int key, int scancode, int action, int mode);

private:
	void SetDirection(Direction d);
	void CreateCarMesh(float width, float farh, float sizemodifier);
};
