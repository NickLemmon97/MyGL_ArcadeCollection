#pragma once
#include <GamePCH.h>

class DeathRaceAPI DeathRace : public Game
{
public:
	DeathRace();
	~DeathRace();

	void DisplayRules();

	void Init() override;
	void Update(double delta) override;
};
