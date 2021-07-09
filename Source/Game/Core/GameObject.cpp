#include "GamePCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_Mesh = std::make_shared<Shape>();
	m_Position = { 0.0f,0.0f };
	m_Scale = { 0.0f,0.0f };

#ifdef DEBUG
	m_DebugCollider = std::make_shared<Shape>();
#endif
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
#ifdef DEBUG
	m_DebugCollider->MakeRectangle(m_Scale.x, m_Scale.y, ColorList::PURPLE);
#endif
}

void GameObject::Update(double delta)
{
}

void GameObject::Draw(const Renderer& renderer)
{
	renderer.Draw(*m_Mesh.get(), m_Position);
#ifdef DEBUG
	renderer.Draw(*m_DebugCollider.get(), m_Position);
#endif
}

bool GameObject::IsOverlappingWithOther(const glm::vec2 pos, const glm::vec2 scale)
{
	return 
		(pos.x + scale.x) >= (m_Position.x - m_Scale.x) &&
		(pos.x - scale.x) <= (m_Position.x + m_Scale.x) &&
		(pos.y + scale.y) >= (m_Position.y - m_Scale.y) &&
		(pos.y - scale.y) <= (m_Position.y + m_Scale.y);
}

void GameObject::HandleBeginOverlap()
{
	m_Mesh->SetColor(ColorList::BLACK);
}

void GameObject::HandleEndOverlap()
{
	m_Mesh->SetColor(ColorList::WHITE);
}