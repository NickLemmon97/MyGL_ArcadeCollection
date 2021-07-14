#pragma once
#include <GamePCH.h>

class PongGAPI PongGame : public Game
{
public:
	PongGame();
	virtual ~PongGame();

	void DisplayRules();

	void Init() override;
	void Update(double delta) override;

protected:
	
};
