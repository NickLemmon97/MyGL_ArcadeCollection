#pragma once
#include <GamePCH.h>

class TrialGame : public Game
{
public:
	TrialGame();
	~TrialGame();

	void Init() override;
	void Update(double delta) override;
};
