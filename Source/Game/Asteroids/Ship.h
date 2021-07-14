#pragma once
#include "Core/GameObject.h"

class Ship : public GameObject
{
public:
	Ship(class AsteroidsGame* game);
	void Init();
	void Update(double delta);

protected:
	void HandleKeyboardInput(int key, int scancode, int action, int mode);

	class AsteroidsGame* m_pGame = nullptr;

	glm::vec2 m_Velocity = { 0.0f, 0.0f };
	float m_Speed = 0.0f;
	int m_RotationDirection = 0;
	
	bool bDoThrust = false;
};
