#include "FrameworkPCH.h"
#include "LineLoop.h"

LineLoop::LineLoop()
	: m_LineCol(0)
	, m_Vbo(0)
	, m_Vao(0)
	, m_NumVerts(0)
{
}

LineLoop::~LineLoop()
{
}

void LineLoop::Init(std::vector<glm::vec2>& points, MyColor& col)
{
	m_LineCol = col;
	m_NumVerts = points.size();

	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(VertexFormat) * m_NumVerts,
		points.data(),
		GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void LineLoop::Draw(ShaderProgram* shader)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBindVertexArray(m_Vao);

	GLint loc_pos = 0;
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	shader->SetUniform("u_Col", m_LineCol);

	glDrawArrays(GL_LINE_LOOP, 0, m_NumVerts);

	glBindVertexArray(0);
}
