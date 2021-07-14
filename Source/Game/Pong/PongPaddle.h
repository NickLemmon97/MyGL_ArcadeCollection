#pragma once
#include <GamePCH.h>

class PongPaddle : public GameObject
{
public:
	PongPaddle(class Game* game);
	void Init() override;
	void Update(double delta) override;

protected:
	void HandleKeyboardInput(int key, int scancode, int action, int mode);

private:

	int m_Direction = 0;
};