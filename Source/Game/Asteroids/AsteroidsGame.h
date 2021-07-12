#pragma once
#include <GamePCH.h>

class AsteroidsAPI AsteroidsGame : public Game
{
public:
	AsteroidsGame();
	~AsteroidsGame();

	void DisplayRules();

	void Init() override;
	void Update(double delta) override;

private:

	class GameObject* m_pPlayer = nullptr;

};
