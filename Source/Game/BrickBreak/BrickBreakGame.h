#pragma once
#include <GamePCH.h>

class BrickBreakGame : public Game
{
public:
	BrickBreakGame();

	void Init() override;
	void Update(float delta) override;

	void HandleInput(int key, int scancode, int action, int mode) override;

private:
	class Ball* m_pBall = nullptr;
};