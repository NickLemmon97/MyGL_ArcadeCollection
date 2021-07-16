#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(float delta);
	virtual void Draw(const Renderer& renderer);

	virtual void Reset();

	void ScreenWrapPosition();
	void KeepInScreenBounds();
	void KeepInBounds(glm::vec2 lowerBounds, glm::vec2 upperBounds);
	
	bool IsOverlappingWithOther(const glm::vec2 pos, const glm::vec2 scale);

	virtual void HandleBeginOverlap();
	virtual void HandleEndOverlap();

	glm::vec2 GetPosition();
	glm::vec2 GetScale();

	void SetPosition(glm::vec2&& pos);
							
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
