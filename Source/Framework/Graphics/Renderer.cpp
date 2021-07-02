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

	if (m_Shader->LoadShader("Shaders/triangle") == false)
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

void Renderer::DrawTriangle() const
{
	GLfloat Vertices[] =
	{
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint vbo;
	GLuint vao;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint loc = 0;
	glEnableVertexAttribArray(loc);

	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}


void Renderer::Draw(const Mesh& mesh) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Vbo);
	glBindVertexArray(mesh.m_Vao);

	GLint loc = 0;
	glEnableVertexAttribArray(loc);

	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(mesh.PrimitiveType, 0, mesh.m_NumVerts);

	glBindVertexArray(0);
}
