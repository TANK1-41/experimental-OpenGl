//
// Created by TANK1_41 on 3/29/2022.
//

#include "shader.h"

shader::shader(const char *vertexPath, const char *fragmentPath) {
    //1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream f_vertexShader;
    std::ifstream f_fragmentShader;
    //ensure ifstream objects can throw exceptions
    f_vertexShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_fragmentShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        //open files
        f_vertexShader.open(vertexPath);
        f_fragmentShader.open(fragmentPath);
        std::stringstream s_vertexStream, s_fragmentStream;
        //read file's buffer contents into streams
        s_vertexStream << f_vertexShader.rdbuf();
        s_fragmentStream << f_fragmentShader.rdbuf();
        //close files handlers
        f_vertexShader.close();
        f_fragmentShader.close();
        //convert into string
        vertexCode = s_vertexStream.str();
        fragmentCode = s_fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char *c_vertexCode = vertexCode.c_str();
    const char *c_fragmentCode = fragmentCode.c_str();
    //2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &c_vertexCode, nullptr);
    glCompileShader(vertex);
    //print errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
    }
    //similar for fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &c_fragmentCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
    }
    //shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    //print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void shader::use() const {
    glUseProgram(ID);
}

void shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setVec4(const std::string &name, float v1, float v2, float v3, float v4) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
}

shader::~shader() {
    glDeleteProgram(ID);
}

unsigned int shader::getID() const {
    return ID;
}
