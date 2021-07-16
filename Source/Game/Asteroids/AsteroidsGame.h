#pragma once
#include <GamePCH.h>

class AsteroidsGame : public Game
{
public:
	AsteroidsGame();
	~AsteroidsGame();

	void DisplayRules();

	void Init() override;
	void Update(float delta) override;
	void Draw(const class Renderer& renderer) override;

	void ShootBullet(float dir, glm::vec2 pos);

	void TriggerReset();

private:

	std::vector<class Projectile*> m_Projectiles;
	class Ship* m_pPlayer = nullptr;

	std::unique_ptr<class Shape> ResetCountDownIcon;
	float ResetTimer = 0.0f;
	bool bStartReset = false;
};
