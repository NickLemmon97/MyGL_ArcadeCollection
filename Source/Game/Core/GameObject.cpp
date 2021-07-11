#include "GamePCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_Mesh = std::make_shared<Shape>();
	m_Position = { 0.0f,0.0f };
	m_Scale = { 0.0f,0.0f };
	m_Rotation = 0.0f;

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
	renderer.Draw(*m_Mesh.get(), m_Position, m_Rotation);
#ifdef DEBUG
	renderer.Draw(*m_DebugCollider.get(), m_Position, m_Rotation);
#endif
}

bool GameObject::IsOverlappingWithOther(const glm::vec2 pos, const glm::vec2 scale)
{
	return 
		(pos.x + scale.x*0.5) >= (m_Position.x - m_Scale.x*0.5) &&
		(pos.x - scale.x*0.5) <= (m_Position.x + m_Scale.x*0.5) &&
		(pos.y + scale.y*0.5) >= (m_Position.y - m_Scale.y*0.5) &&
		(pos.y - scale.y*0.5) <= (m_Position.y + m_Scale.y*0.5);
}

void GameObject::HandleBeginOverlap()
{
	m_Mesh->SetColor(ColorList::RED);
}

void GameObject::HandleEndOverlap()
{
	m_Mesh->SetColor(ColorList::WHITE);
}