#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(double delta);
	virtual void Draw(const Renderer& renderer);

	bool IsOverlappingWithOther(const glm::vec2 pos, const glm::vec2 scale);

	virtual void HandleBeginOverlap();
	virtual void HandleEndOverlap();

	glm::vec2 GetPosition() { return m_Position; }
	glm::vec2 GetScale()    { return m_Scale; }

protected:
	std::shared_ptr<class Shape> m_Mesh;

	glm::vec2 m_Position;
	glm::vec2 m_Scale;
};
