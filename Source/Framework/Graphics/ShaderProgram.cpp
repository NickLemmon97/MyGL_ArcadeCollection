#include <FrameworkPCH.h>
#include "ShaderProgram.h"

DECLARE_LOG_CATEGORY(LogShader);

ShaderProgram::ShaderProgram()
    :m_VertexShader    { 0 }
    , m_FragmentShader { 0 }
    , m_Program        { 0 }
{
}

ShaderProgram::ShaderProgram(const char* shader)
    : m_VertexShader{ 0 }
    , m_FragmentShader{ 0 }
    , m_Program{ 0 }
{
    LoadShader(shader);
}

ShaderProgram::ShaderProgram(const char* vertex, const char* fragment)
    : m_VertexShader{ 0 }
    , m_FragmentShader{ 0 }
    , m_Program{0 }
{
    LoadShader(vertex, fragment);
}

ShaderProgram::~ShaderProgram()
{
    Cleanup();
}

void ShaderProgram::LoadShader(const char* filename)
{
    std::string vertex{ filename };
    vertex.append(".vert");

    std::string fragment{ filename };
    fragment.append(".frag");

    LoadShader(vertex.c_str(), fragment.c_str());
}

void ShaderProgram::LoadShader(const char* vertex, const char* fragment)
{
    m_VertexShaderCode = Utilities::LoadCompleteFileFromData(vertex);
    m_FragmentShaderCode = Utilities::LoadCompleteFileFromData(fragment);

    if (m_VertexShaderCode == nullptr)
    {
        LOG_MESSAGE(LogShader, LogVerbosity::Error, "Failed to load Vertex Shader");
    }

    if (m_FragmentShaderCode == nullptr)
    {
        LOG_MESSAGE(LogShader, LogVerbosity::Error, "Failed to load Fragment Shader");
    }
}

void ShaderProgram::Cleanup()
{
    if (m_VertexShaderCode != nullptr)
    {
        delete m_VertexShaderCode;
    }
    m_VertexShaderCode = nullptr;

    if (m_FragmentShaderCode != nullptr)
    {
        delete m_FragmentShaderCode;
    }
    m_FragmentShaderCode = nullptr;
}

GLuint ShaderProgram::GetProgram()
{
    return GLuint();
}
