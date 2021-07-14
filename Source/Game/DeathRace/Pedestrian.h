#pragma once
#include <GamePCH.h>

class Pedestrian : public GameObject
{
public:
	void Init() override;
	void Update(double delta) override;
	void Reset() override;

	bool GetIsDead();

	void HandleBeginOverlap() override;

	void UpdateDirection();

private:
	glm::vec2 m_Movement;
	float m_Timer;
	float m_Direction;
	bool bIsDead;
};