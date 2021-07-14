#pragma once
#include <GamePCH.h>

class Ball : public GameObject
{
public:
	void Init() override;
	void Update(double delta) override;

	void Bounce();
};