#pragma once
#include <GamePCH.h>
#include "Core/GameObject.h"

class Meteor : public GameObject
{
public:
	Meteor();
	void Init() override;
	void Update(float delta) override;

	void Reset() override;

	void HandleBeginOverlap() override;
protected:

	glm::vec2 m_Velocity = { 0.0f, 0.0f };
	float m_RotationDirection = 0;

};
