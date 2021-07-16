#pragma once
#include <GamePCH.h>

class Projectile : public GameObject
{
public:
	Projectile();
	void Init() override;
	void Update(float delta) override;

	void Shoot(glm::vec2 dir, glm::vec2 pos);

protected:

	float m_ActiveTimer = 0.0f;
	glm::vec2 m_Direction;

	bool bWasInitialized = false;

};
