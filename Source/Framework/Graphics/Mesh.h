#pragma once

//FrameworkImpl template class FrameworkAPI std::vector<GLfloat>;

struct VertexFormat
{

};

class FrameworkAPI Mesh
{
	friend class Renderer;

public:
	Mesh();
	~Mesh();

	void SetVertices(GLfloat* vertices, size_t count);
	void SetVertices(const std::vector<GLfloat>& verts);

	void MakeTriangle();

protected:

	void SetupBuffers();

	GLenum PrimitiveType;

	GLuint m_Vbo;
	GLuint m_Vao;

	std::vector<GLfloat> m_Vertices;

private:

};
