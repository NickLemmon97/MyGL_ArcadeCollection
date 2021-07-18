#pragma once
#include <GamePCH.h>

class BBPaddle : public GameObject
{
public:
	BBPaddle(class Game* game);
	void Init() override;
	void Update(float delta) override;

	void SetBall(class Ball* ball);

protected:
	void HandleKeyboardInput(int key, int scancode, int action, int mode);
	bool IsOverlappingBall();

private:
	class Ball* m_pBall = nullptr;
	int m_Direction = 0;
};