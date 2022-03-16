#include "Shader.h"

#include <GL/glew.h>
#include<sstream>
#include<fstream>
#include <iostream>
#include "Renderer.h"



Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath) , m_RendererID(0)
{
    shaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);
	//you must bind the shader after this
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
    GLCall(glDeleteProgram(m_RendererID));
}



shaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class shaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    //search through string and find the beginning of each shader and store it in
    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                //sets mode to vertex
                type = shaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                //sets mode to vertex
                type = shaderType::FRAGMENT;
            }
        }
        else {
            //adds the line to the correct array for example if type was 1 it would add to fragment bc enum
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    //Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        //allocates on the stack
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "failed to compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
 unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& framentShader) {
    unsigned int program = glCreateProgram();
    //vertex shader
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    //fragment shader
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, framentShader);

    //link the shaders
    GLCall(glAttachObjectARB(program, vs));
    GLCall(glAttachObjectARB(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    //delete shaders after link
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
    GLCall(glUniform1f(GetUniformLocation(name), v0));

}

void Shader::SetUniform4i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1,GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    //makes it so we don't have to get the unformlocation again if we already have it
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform does not insist" << name << std::endl;

	m_UniformLocationCache[name] = location;
    return location;
}
