#pragma once

#include <map>

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

	void Use();

	void SetUniform(const GLchar* name, const glm::vec2& value);
	void SetUniform(const GLchar* name, const glm::vec3& value);
	void SetUniform(const GLchar* name, const glm::vec4& value);

protected:

	GLint GetUniformLocation(const GLchar* name);

	char* m_FragmentShaderCode = nullptr;
	char* m_VertexShaderCode   = nullptr;

	GLuint m_VertexShader, m_FragmentShader, m_Program;

	std::map<std::string, GLint> m_UniformLocations;

private:
};

