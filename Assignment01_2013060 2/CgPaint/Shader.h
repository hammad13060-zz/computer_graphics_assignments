
/*
 *  code taken from http://learnopengl.com/code_viewer.php?type=header&code=shader
 *  thanks to the author
 */

#ifndef SHADER_H
#define SHADER_H

#include <GLUT/glut.h>
#include "OpenGL/gl3.h"

class Shader
{
public:
    GLuint Program; // The program ID
    Shader() { }

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath); // Constructor reads and builds the shader
    void Use(); // Use the program
    void Delete();
};


#endif