#include <FrameworkPCH.h>

Mesh::Mesh()
	: m_Vbo{ 0 }
	, m_Vao{ 0 }
	, PrimitiveType{ GL_TRIANGLE_FAN }
	, m_NumVerts{0}
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteBuffers(1, &m_Vbo);
}

void Mesh::Init(VertexFormat* vertices, GLuint count, GLenum primitive /*= GL_LINE_LOOP*/)
{
	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(VertexFormat) * count,
				 vertices,
				 GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	PrimitiveType = primitive;
	m_NumVerts = count;
}

void Mesh::MakeTriangle()
{
	VertexFormat Vertices[] = {
	VertexFormat{ { 0.0f,  0.5f}, {1.0f, 1.0f, 1.0f} },
	VertexFormat{ { 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f} },
	VertexFormat{ {-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f} }
	};
	
	Init(Vertices, 3, GL_TRIANGLES);
}

void Mesh::Draw(const Renderer& renderer)
{
	Draw();
}

void Mesh::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBindVertexArray(m_Vao);

	GLint loc_pos = 0;
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(loc_pos);

	GLint loc_col = 1;
	glVertexAttribPointer(loc_col, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)8);
	glEnableVertexAttribArray(loc_col);

	glDrawArrays(PrimitiveType, 0, m_NumVerts);

	glBindVertexArray(0);
}
