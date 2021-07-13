#pragma once

class UIObject
{
protected:
	std::shared_ptr<class Shape> m_Mesh;
#ifdef DEBUG
	std::shared_ptr<class Shape> m_DisplayArea;
#endif
	glm::vec2 m_Position;
	glm::vec2 m_Scale;
	glm::vec2 m_Anchor;
	float m_Rotation;

public:

	UIObject();
	virtual ~UIObject() = default;
	virtual void Init();
	virtual void Draw(const class Renderer& renderer);

};
