#include "Shader.h"
#include <iostream>
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    GLuint geometry;
    if (geometryPath) {
        std::string geomCode;
        std::ifstream gShaderFile;
        gShaderFile.open(geometryPath);
        std::stringstream gShaderStream;
        gShaderStream << gShaderFile.rdbuf();
        gShaderFile.close();
        geomCode = gShaderStream.str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        const GLchar* gShaderCode = geomCode.c_str();
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        glAttachShader(program, geometry);
    }
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath)
        glDeleteShader(geometry);
}

void Shader::Use()
{
    glUseProgram(program);
}

void Shader::setMat4(const char* value, glm::mat4 mat)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const char* value, glm::mat4 mat)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec4(const char* value, glm::vec4 vec)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setVec3(const char* value, glm::vec3 vec)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setVec2(const char* value, glm::vec2 vec)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniform2f(loc, vec.x, vec.y);
}

void Shader::setFloat(const char* value, float f)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniform1f(loc, f);
}
void Shader::setInt(const char* value, int f)
{
    Use();
    GLuint loc = glGetUniformLocation(program, value);
    glUniform1i(loc, f);
}

GLuint Shader::getUniformBlockIndex(const char* value)
{
    return glGetUniformBlockIndex(program, "Matrices");
}

void Shader::bindBlock(const char* blockName, int index)
{
    glUniformBlockBinding(program, getUniformBlockIndex(blockName), index);
}
