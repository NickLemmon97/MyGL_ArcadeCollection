#pragma once
#include <GamePCH.h>

class Pedestrian : public GameObject
{
public:
	void Init() override;
	void Update(float delta) override;
	void Reset() override;

	bool GetIsDead();

	void HandleBeginOverlap() override;

	void UpdateDirection();

private:
	glm::vec2 m_Movement = { 0.0f,0.0f };
	float m_Timer = 0.0f;
	float m_Direction = 0.0f;
	bool bIsDead = false;
};