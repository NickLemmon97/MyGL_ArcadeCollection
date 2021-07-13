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
	void Draw(const class Renderer& renderer) override;

private:
	int m_CarIdx;

	int m_RemainingCount = 0;
	class Shape* m_RemainingDisplay = nullptr;
};
