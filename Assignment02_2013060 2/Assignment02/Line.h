//
// Created by Hammad Akhtar on 03/08/16.
//

#ifndef LINE_H
#define LINE_H


#include <string>
#include <GLUT/glut.h>
#include "OpenGL/gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Line{
private:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 color;

    GLuint VAO, VBO;

    bool lineMode;

    void createBuffers();

public:
    Line(const glm::vec3 pos1, const glm::vec3 pos2, const glm::vec3 color, bool mode);
    ~Line();
    void draw();
};


#endif
