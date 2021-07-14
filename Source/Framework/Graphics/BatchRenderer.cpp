#include <FrameworkPCH.h>
#include "BatchRenderer.h"

BatchRenderer::BatchRenderer()
{

}

BatchRenderer::~BatchRenderer()
{
	m_ActiveRenderer = nullptr;
}

void BatchRenderer::Init()
{
	m_UIRenderer = std::make_unique<UIRenderer>();
	m_ShapeRenderer = std::make_unique<ShapeRenderer>();
}

void BatchRenderer::BeginFrame()
{
	if (m_ActiveRenderer != nullptr)
	{
		m_ActiveRenderer->BeginDraw();
	}
}

void BatchRenderer::DrawShape(const Shape& shape, const glm::vec2& pos, float rotation)
{
	SwitchRenderers(RendererType::Shape);
	m_ShapeRenderer->DrawShape(shape, pos, rotation);
}

void BatchRenderer::DrawUI(const Shape& shape, const glm::vec2& pos, const glm::vec2& anchor, float rotation)
{
	SwitchRenderers(RendererType::Shape);
	m_UIRenderer->Draw(shape, pos, anchor, rotation);
}

void BatchRenderer::EndFrame()
{
	if (m_ActiveRenderer != nullptr)
	{
		m_ActiveRenderer->EndDraw();
	}
}

void BatchRenderer::SetBackgroundColor(glm::vec3 color)
{
	glClearColor(
		color.r,
		color.g,
		color.b,
		1.0f);
}

void BatchRenderer::SetProjection(float w, float h)
{
	m_ShapeRenderer->SetProjection(w, h);
	m_UIRenderer->SetProjection(w, h);
}

void BatchRenderer::SetCameraPosition(float x, float y)
{
	m_ShapeRenderer->SetCameraPosition(x, y);
	m_UIRenderer->SetCameraPosition(x, y);
}

void BatchRenderer::SwitchRenderers(RendererType type)
{
	if (m_ActiveRenderer != nullptr)
	{
		if (m_ActiveRenderer->GetType() == type) return;

		m_ActiveRenderer->EndDraw();
	}

	switch (type)
	{
	case RendererType::Shape:
		m_ActiveRenderer = m_ShapeRenderer.get();
		break;

	case RendererType::UI:
		m_ActiveRenderer = m_UIRenderer.get();
		break;

	default:
		DEBUG_LOG_MESSAGE(LogGraphics, LogVerbosity::Error, "Invalid Renderer chosen - Not set up for the batch renderer to switch to");
		break;
	}

	if (m_ActiveRenderer != nullptr)
	{
		m_ActiveRenderer->BeginDraw();
	}
}
ShapeRenderer::ShapeRenderer()
{
	m_Shader = std::make_unique<ShaderProgram>();
	if (!m_Shader->LoadShader("brshape"))
	{
		LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Unable to load shape renderer shader");
	}
}
ShapeRenderer::~ShapeRenderer()
{
}
RendererType ShapeRenderer::GetType()
{
	return RendererType::Shape;
}
void ShapeRenderer::BeginDraw()
{
	m_Shader->Use();
}
void ShapeRenderer::DrawShape(const Shape&, const glm::vec2& pos, float rotation)
{
}
void ShapeRenderer::EndDraw()
{
}
void ShapeRenderer::SetProjection(float w, float h)
{
	m_Shader->Use();
	m_Shader->SetUniform("u_ProjectionScale", glm::vec2{ 1 / w, 1 / h });
}
void ShapeRenderer::SetCameraPosition(float x, float y)
{
	m_Shader->Use();
	m_Shader->SetUniform("u_campos", glm::vec2(-x, -y));
}


UIRenderer::UIRenderer()
{
	m_Shader = std::make_unique<ShaderProgram>();
	m_Shader = std::make_unique<ShaderProgram>();
	if (!m_Shader->LoadShader("brUI.vert", "brshape.frag"))
	{
		LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Unable to load shape renderer shader");
	}
}
UIRenderer::~UIRenderer()
{
}
RendererType UIRenderer::GetType() 
{
	return RendererType::UI;
}
void UIRenderer::BeginDraw() 
{
	m_Shader->Use();
}

void UIRenderer::Draw(const Shape& shape, const glm::vec2& pos, const glm::vec2& anchor, float rotation)
{
}

void UIRenderer::EndDraw()
{
}

void UIRenderer::SetProjection(float w, float h)
{
	m_Shader->Use();
	m_Shader->SetUniform("u_ProjectionScale", glm::vec2{ 1 / w, 1 / h });
	m_Shader->SetUniform("u_ScreenSize", glm::vec2{ w, h });
}

void UIRenderer::SetCameraPosition(float x, float y)
{
	m_Shader->Use();
	m_Shader->SetUniform("u_campos", glm::vec2(-x, -y));
}
