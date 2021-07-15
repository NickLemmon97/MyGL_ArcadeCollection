#include "GamePCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_Mesh = std::make_shared<Shape>();
	m_Position = { 0.0f,0.0f };
	m_Scale = { 0.0f,0.0f };
	m_Rotation = 0.0f;

	bIsActive = true;

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
	renderer.Draw(*m_DebugCollider.get(), m_Position, 0);
#endif
}

void GameObject::Reset()
{

}

void GameObject::ScreenWrapPosition()
{

	if (m_Position.x < 0.0f)
		m_Position.x += INITIAL_WINDOW_WIDTH;
	if (m_Position.y < 0.0f)
		m_Position.y += INITIAL_WINDOW_HEIGHT;
	if (m_Position.x > INITIAL_WINDOW_WIDTH)
		m_Position.x -= INITIAL_WINDOW_WIDTH;
	if (m_Position.y > INITIAL_WINDOW_HEIGHT)
		m_Position.y -= INITIAL_WINDOW_HEIGHT;
}

void GameObject::KeepInScreenBounds()
{
	KeepInBounds({ 0,0 }, { INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT });
}

void GameObject::KeepInBounds(glm::vec2 lowerBounds, glm::vec2 upperBounds)
{

	glm::vec2 halfScale = { m_Scale.x * 0.5f, m_Scale.y * 0.5f };
	
	if (m_Position.x - halfScale.x < lowerBounds.x)
	{
		m_Position.x = halfScale.x;
	}

	if (m_Position.x + halfScale.x > upperBounds.x)
	{
		m_Position.x = upperBounds.x - halfScale.x;
	}

	if (m_Position.y - halfScale.y < lowerBounds.y)
	{
		m_Position.y = halfScale.y + lowerBounds.y;
	}

	if (m_Position.y + halfScale.y > upperBounds.y)
	{
		m_Position.y = upperBounds.y - halfScale.y;
	}
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
#ifndef RELEASE
	m_Mesh->SetColor(ColorList::RED);
#endif
}

void GameObject::HandleEndOverlap()
{
#ifndef RELEASE
	m_Mesh->SetColor(ColorList::WHITE);
#endif
}

glm::vec2 GameObject::GetPosition()
{
	return m_Position;
}

glm::vec2 GameObject::GetScale()
{
	return m_Scale;
}

void GameObject::SetPosition(glm::vec2&& pos)
{
	m_Position = pos;
}

bool GameObject::GetIsActive()
{
	return bIsActive;
}
