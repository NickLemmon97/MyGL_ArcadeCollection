#include "GamePCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_Mesh = std::make_shared<Shape>();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Update(double delta)
{
}

void GameObject::Draw(const Renderer& renderer)
{
	renderer.Draw(*m_Mesh.get());
}
