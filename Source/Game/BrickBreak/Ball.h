#pragma once
#include <GamePCH.h>

class Ball : public GameObject
{
public:
	void Init() override;
	void Update(float delta) override;

	void Bounce(glm::vec2 otherPos);

	bool IsBouncing();

	void Shoot();

private:
	bool bIsBouncing;

	glm::vec2 Velocity;

};