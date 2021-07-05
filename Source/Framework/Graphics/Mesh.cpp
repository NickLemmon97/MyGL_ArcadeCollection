#include <FrameworkPCH.h>

Mesh::Mesh()
	: m_Vbo{ 0 }
	, m_Vao{ 0 }
	, m_PrimitiveType { GL_TRIANGLE_FAN }
	, m_NumVerts{0}
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteBuffers(1, &m_Vbo);
}

void Mesh::Init(VertexFormat* vertices, GLuint count, GLenum primitive)
{
	m_PrimitiveType = primitive;
	m_NumVerts = count;

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
}

void Mesh::Init(VertexFormat* vertices, GLuint count)
{
	Init(vertices, count, m_PrimitiveType);
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

void Mesh::SetPrimitiveType(GLenum primitive)
{
	m_PrimitiveType = primitive;
}
