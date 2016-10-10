/*
 *  code taken from http://learnopengl.com/code_viewer.php?type=header&code=shader
 *  thanks to the author
 */

#include "Shader.h"

//#include "GL/glew.h"
#include "OpenGL/gl3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
 // Include glew to get all the required OpenGL headers

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;

    try
    {
        std::ifstream vShaderFile(vertexPath);
        std::ifstream fShaderFile(fragmentPath);
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::badbit);
        //vShaderFile.op
        // Convert stream into string
        vertexCode = "";
        fragmentCode = "";

        if(vShaderFile.is_open()) {
            std::string line = "";

            while(std::getline(vShaderFile, line)) {
                vertexCode += "\n" + line;
                //std::cout << line << std::endl;
            }

            vShaderFile.close();
        }

        if(fShaderFile.is_open()) {
            std::string line = "";

            while(std::getline(fShaderFile, line)) {
                fragmentCode += "\n" + line;
            }

            fShaderFile.close();
        }

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    //std::cout << "vertex code: "  << vertexCode << std::endl;
    //std::cout << "fragent code: "  << fragmentCode << std::endl;

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar * fShaderCode = fragmentCode.c_str();
    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::Use() { glUseProgram(this->Program); }

void Shader::Delete() { glDeleteProgram(this->Program); }