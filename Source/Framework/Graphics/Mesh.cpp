#include <FrameworkPCH.h>

Mesh::Mesh()
	: m_Vbo{ 0 }
	, m_Vao{ 0 }
	, PrimitiveType{ GL_LINE_LOOP }
	, m_NumVerts{0}
{
}

Mesh::~Mesh()
{
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
	VertexFormat{ 0.0f,  0.5f },
	VertexFormat{ 0.5f, -0.5f },
	VertexFormat{-0.5f, -0.5f }
	};
	
	Init(Vertices, 3, GL_LINE_LOOP);
}
