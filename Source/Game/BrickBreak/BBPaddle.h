#pragma once
#include <GamePCH.h>

class BBPaddle : public GameObject
{
public:
	BBPaddle(class Game* game);
	void Init() override;
	void Update(double delta) override;

protected:
	void HandleKeyboardInput(int key, int scancode, int action, int mode);

private:

	int m_Direction = 0;
};