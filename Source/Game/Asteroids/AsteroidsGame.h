#pragma once
#include <GamePCH.h>

class AsteroidsGame : public Game
{
public:
	AsteroidsGame();
	~AsteroidsGame();

	void DisplayRules();

	void Init() override;
	void Update(double delta) override;
	void Draw(const class Renderer& renderer) override;

	void ShootBullet(float dir, glm::vec2 pos);

private:

	std::vector<class Projectile*> m_Projectiles;
	class GameObject* m_pPlayer = nullptr;
};
