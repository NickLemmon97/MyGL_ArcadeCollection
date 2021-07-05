#include <FrameworkPCH.h>

DECLARE_LOG_CATEGORY(LogRenderer);

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
	//Initialize the clear color just once here
	glClearColor(0.23f, 0.56f, 0.89f, 1.0f);

	m_Shader = std::make_unique<ShaderProgram>();
	if (m_Shader->LoadShader("basic") == false)
	{
		DEBUG_LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Renderer Failed to load Shader");
	}
}

void Renderer::UseShader(std::string&& shaderName)
{
	m_Shader = std::make_unique<ShaderProgram>();
	if (m_Shader->LoadShader(shaderName) == false)
	{
		DEBUG_LOG_MESSAGE(LogRenderer, LogVerbosity::Error, "Renderer Failed to load Shader");
	}
}

void Renderer::BeginDraw() const
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_Shader->GetProgram());
}

void Renderer::EndDraw() const
{
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
