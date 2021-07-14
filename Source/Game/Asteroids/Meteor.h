#pragma once
#include <GamePCH.h>
#include "Core/GameObject.h"

class Meteor : public GameObject
{
public:
	Meteor();
	void Init();
	void Update(double delta);

	void HandleBeginOverlap() override;
protected:

	glm::vec2 m_Velocity = { 0.0f, 0.0f };
	float m_RotationDirection = 0;

};
