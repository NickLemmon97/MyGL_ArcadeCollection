#pragma once
#include <GamePCH.h>

class SpaceInvaders : public Game
{
public:
	SpaceInvaders();
	virtual ~SpaceInvaders();

	void DisplayRules();
	void Reset();

	void Init() override;
	void Update(float delta) override;
};
