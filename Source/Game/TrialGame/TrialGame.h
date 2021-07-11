#pragma once
#include <GamePCH.h>

class TrialGameAPI TrialGame : public Game
{
public:
	TrialGame();
	~TrialGame();

	void Init() override;
	void Update(double delta) override;
};
