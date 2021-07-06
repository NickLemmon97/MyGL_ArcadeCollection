#include <FrameworkPCH.h>

void Renderer::Init()
{
	//Initialize the clear color just once here
	glClearColor(
		ColorList::CYAN.r, 
		ColorList::CYAN.g, 
		ColorList::CYAN.b, 
		1.0f);

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

void Renderer::Draw(const Mesh& mesh) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Vbo);
	glBindVertexArray(mesh.m_Vao);

	GLint loc_pos = 0;
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, vertexPosition));

	GLint loc_col = 1;
	glEnableVertexAttribArray(loc_col);
	glVertexAttribPointer(loc_col, 3, GL_FLOAT, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, vertexColor));

	glDrawArrays(mesh.m_PrimitiveType, 0, mesh.m_NumVerts);

	glBindVertexArray(0);
}

void FrameworkAPI Renderer::Draw(const Shape& shape) const
{
	glBindBuffer(GL_ARRAY_BUFFER, shape.m_Vbo);
	glBindVertexArray(shape.m_Vao);

	GLint loc_pos = 0;
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	m_ShapeShader->SetUniform("u_Col", shape.m_Color);

	glDrawArrays(shape.m_PrimitiveType, 0, shape.m_NumVerts);

	glBindVertexArray(0);
}
