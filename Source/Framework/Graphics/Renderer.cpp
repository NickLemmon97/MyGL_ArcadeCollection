#include <FrameworkPCH.h>

void Renderer::Init()
{
	SetBackgroundColor(ColorList::CYAN);

	m_ShapeShader = std::make_unique<ShaderProgram>();
	if (m_ShapeShader->LoadShader("shape") == false)
	{
		DEBUG_LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Renderer Failed to load Shader");
	}

	m_UIShapeShader = std::make_unique<ShaderProgram>();
	if (m_UIShapeShader->LoadShader("ui.vert", "shape.frag") == false)
	{
		DEBUG_LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Renderer Failed to load Shader");
	}
}

void Renderer::UseShader(std::string&& shaderName)
{
	m_ShapeShader = std::make_unique<ShaderProgram>();
	if (m_ShapeShader->LoadShader(shaderName) == false)
	{
		DEBUG_LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Renderer Failed to load Shader");
	}
}

void Renderer::BeginDraw() const
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_ShapeShader->Use();
}

void Renderer::Draw(const Shape& shape, const glm::vec2& pos, float rotation) const
{
	m_ShapeShader->Use();

	glBindBuffer(GL_ARRAY_BUFFER, shape.m_Vbo);
	glBindVertexArray(shape.m_Vao);

	GLint loc_pos = 0;
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	m_ShapeShader->SetUniform("u_Col", shape.m_Color);
	m_ShapeShader->SetUniform("u_pos", pos);
	m_ShapeShader->SetUniform("u_rotation", rotation);

	glDrawArrays(shape.m_PrimitiveType, 0, shape.m_NumVerts);

	glBindVertexArray(0);
}

void FrameworkAPI Renderer::DrawUI(const Shape& shape, const glm::vec2& pos, glm::vec2& anchor, float rotation) const
{
	m_UIShapeShader->Use();

	glBindBuffer(GL_ARRAY_BUFFER, shape.m_Vbo);
	glBindVertexArray(shape.m_Vao);

	GLint loc_pos = 0;
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	m_UIShapeShader->SetUniform("u_Col", shape.m_Color);
	m_UIShapeShader->SetUniform("u_pos", pos);
	m_UIShapeShader->SetUniform("u_rotation", rotation);
	m_UIShapeShader->SetUniform("u_anchor", anchor);

	glDrawArrays(shape.m_PrimitiveType, 0, shape.m_NumVerts);

	glBindVertexArray(0);
}

void Renderer::SetBackgroundColor(glm::vec3 color)
{
	glClearColor(
		color.r,
		color.g,
		color.b,
		1.0f);
}

void Renderer::SetProjection(float w, float h)
{
	m_ShapeShader->Use();
	m_ShapeShader->SetUniform("u_ProjectionScale", glm::vec2{ 1/w, 1/h });

	m_UIShapeShader->Use();
	m_UIShapeShader->SetUniform("u_ProjectionScale", glm::vec2{ 1 / w, 1 / h });
	m_UIShapeShader->SetUniform("u_ScreenSize", glm::vec2{ w, h });
}

void Renderer::SetCameraPosition(float x, float y)
{
	m_ShapeShader->Use();
	m_ShapeShader->SetUniform("u_campos", glm::vec2(-x, -y));

	m_UIShapeShader->Use();
	m_UIShapeShader->SetUniform("u_campos", glm::vec2(-x, -y));
}
