#pragma once

class GameAPI GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(double delta);
	virtual void Draw(const Renderer& renderer);

	void ScreenWrapPosition();
	
	bool IsOverlappingWithOther(const glm::vec2 pos, const glm::vec2 scale);

	virtual void HandleBeginOverlap();
	virtual void HandleEndOverlap();

	glm::vec2 GetPosition();
	glm::vec2 GetScale();
							
	bool GetIsActive();

protected:
	std::shared_ptr<class Shape> m_Mesh;

	glm::vec2 m_Position;
	glm::vec2 m_Scale;
	float m_Rotation;

	bool bIsActive;

#ifdef DEBUG
	std::shared_ptr<class Shape> m_DebugCollider;
#endif
};
