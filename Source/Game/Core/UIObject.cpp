#include "GamePCH.h"
#include "UIObject.h"

UIObject::UIObject()
{
	m_Mesh = std::make_shared<Shape>();
	m_Position = { 0.0f,0.0f };
	m_Scale = { 0.0f,0.0f };
	m_Anchor = { 0.0f,0.0f };
	m_Rotation = 0.0f;
}

//UI Element code below
void UIObject::Init()
{
#ifdef DEBUG
	m_DisplayArea = std::make_shared<Shape>();
	m_DisplayArea->MakeSqaure(10, ColorList::PURPLE, GL_TRIANGLE_FAN);
#endif
}

void UIObject::Draw(const Renderer& renderer)
{
	renderer.DrawUI(*m_Mesh.get(), m_Position, m_Anchor, m_Rotation);

#ifdef DEBUG
	float width  = (float)App::Get().GetWindowWidth();
	float height = (float)App::Get().GetWindowHeight();

	float xAnchorOffset = (width  - (width  * -m_Anchor.x));
	float yAnchorOffset = (height * m_Anchor.y);

	glm::vec2 posOffset = { xAnchorOffset + m_Position.x, yAnchorOffset + m_Position.y };

	renderer.Draw(*m_DisplayArea.get(), posOffset, m_Rotation);
#endif
}
