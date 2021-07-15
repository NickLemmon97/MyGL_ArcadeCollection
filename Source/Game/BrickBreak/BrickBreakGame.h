#pragma once
#include <GamePCH.h>

class BrickBreakAPI BrickBreakGame : public Game
{
public:
	BrickBreakGame();

	void Init() override;
	void Update(double delta) override;

private:
	class Ball* m_pBall = nullptr;
};