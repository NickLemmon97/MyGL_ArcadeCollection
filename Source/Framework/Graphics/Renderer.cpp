#include <FrameworkPCH.h>

void Renderer::Init()
{
	SetBackgroundColor(ColorList::CYAN);

	m_ShapeShader = std::make_unique<ShaderProgram>();
	if (m_ShapeShader->LoadShader("shape") == false)
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

void Renderer::Draw(const Shape& shape, const glm::vec2& pos) const
{
	glBindBuffer(GL_ARRAY_BUFFER, shape.m_Vbo);
	glBindVertexArray(shape.m_Vao);

	GLint loc_pos = 0;
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	m_ShapeShader->SetUniform("u_Col", shape.m_Color);
	m_ShapeShader->SetUniform("u_pos", pos);

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
	m_ShapeShader->SetUniform("u_campos", glm::vec2(-w/2, -h/2));
	m_ShapeShader->SetUniform("u_ProjectionScale", glm::vec2{ 1/(w/2), 1/(h/2) });
}
