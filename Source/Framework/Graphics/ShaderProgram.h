#pragma once

class FrameworkAPI ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* shader);
	ShaderProgram(const char* vertex, const char* fragment);
	~ShaderProgram();

	bool LoadShader(const char* filename);
	bool LoadShader(const char* vertex, const char* fragment);

	bool ReloadShaderProgram();

	void CompileShader(GLuint& shader, const char* shaderstring);

	void Cleanup();

	GLuint GetProgram();

protected:

	char* m_FragmentShaderCode = nullptr;
	char* m_VertexShaderCode   = nullptr;

	GLuint m_VertexShader, m_FragmentShader, m_Program;

private:
};

