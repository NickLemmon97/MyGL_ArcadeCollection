#include <FrameworkPCH.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw() const
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * 9, &Vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint loc = 0;
	glEnableVertexAttribArray(loc);

	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}
