#include "FrameworkPCH.h"
#include "Shape.h"

Shape::Shape()
	: m_Color(0)
	, m_PrimitiveType (GL_LINE_LOOP)
	, m_Vbo(0)
	, m_Vao(0)
	, m_NumVerts(0)
{
}

Shape::~Shape()
{
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteBuffers(1, &m_Vbo);
}

void Shape::Init(std::vector<glm::vec2>& points)
{
	Init(points, glm::vec3(1.0f, 1.0f, 1.0f), GL_LINE_LOOP);
}

void Shape::Init(std::vector<glm::vec2>& points, GLenum primitive)
{
	Init(points, glm::vec3(1.0f, 1.0f, 1.0f), primitive);
}

void Shape::Init(std::vector<glm::vec2>& points, const glm::vec3& col)
{
	Init(points, col, GL_LINE_LOOP);
}

void Shape::Init(std::vector<glm::vec2>& points, const glm::vec3& col, GLenum primitive)
{
	m_Color = col;
	m_NumVerts = static_cast<int>(points.size());
	m_PrimitiveType = primitive;

	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec2) * m_NumVerts,
		points.data(),
		GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Shape::MakeCircle(float radius,const glm::vec3& col, GLenum primitive)
{
}

void Shape::MakeSqaure(float width,const glm::vec3& col, GLenum primitive)
{
	MakeRectangle(width, width, col, primitive);
}

void Shape::MakeRectangle(float width, float height, const glm::vec3& col, GLenum primitive)
{
	std::vector<glm::vec2> points =
	{
		{ width,  height},
		{ width, -height},
		{-width, -height},
		{-width,  height}
	};

	Init(points, col, primitive);
}

void Shape::SetColor(const glm::vec3& col)
{
	m_Color = col;
}

void Shape::SetPrimitive(GLenum primitive)
{
	m_PrimitiveType = primitive;
}
