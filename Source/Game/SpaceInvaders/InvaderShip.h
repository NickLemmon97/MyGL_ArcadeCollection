#pragma once
#include <GamePCH.h>

class InvaderShip : public GameObject
{
public:
	InvaderShip(class Game* game);
	void Init() override;
	void Update(float delta) override;

protected:
	void HandleKeyboardInput(int key, int scancode, int action, int mode);

private:

	class SpaceInvaders* m_pGame = nullptr;
	int m_Direction = 0;
};