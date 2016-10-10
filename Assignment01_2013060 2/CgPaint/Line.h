//
// Created by Hammad Akhtar on 03/08/16.
//

#ifndef LINE_H
#define LINE_H


#include "Shape.h"


#include <string>
#include <GLUT/glut.h>
#include "OpenGL/gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Line: public Shape{
private:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 color;

    GLuint VAO, VBO;

    void createBuffers();

public:
    Line(const glm::vec3 pos1, const glm::vec3 pos2, const glm::vec3 color);
    ~Line();

    virtual void draw();
};


#endif
