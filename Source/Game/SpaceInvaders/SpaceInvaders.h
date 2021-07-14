#pragma once
#include <GamePCH.h>

class SpaceInvadersAPI SpaceInvaders : public Game
{
public:
	SpaceInvaders();
	virtual ~SpaceInvaders();

	void DisplayRules();
	void Reset();

	void Init() override;
	void Update(double delta) override;
};
