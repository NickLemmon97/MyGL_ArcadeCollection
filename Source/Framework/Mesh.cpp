#include <FrameworkPCH.h>

Mesh::Mesh()
	: m_Vbo(0)
	, m_Vao(0)
	, PrimitiveType(GL_LINE_STRIP)
{
}

Mesh::~Mesh()
{
}

void Mesh::SetVertices(GLfloat* vertices, size_t count)
{
	for (int i = 0; i < count; i++)
	{
		m_Vertices.push_back(vertices[i]);
	}

	SetupBuffers();
}

void Mesh::SetVertices(const std::vector<GLfloat>& verts)
{
	for (auto& v : verts)
	{
		m_Vertices.push_back(v);
	}

	SetupBuffers();
}

void Mesh::MakeTriangle()
{
	m_Vertices = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	SetupBuffers();
}

void Mesh::SetupBuffers()
{
	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * 9, m_Vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);
}
