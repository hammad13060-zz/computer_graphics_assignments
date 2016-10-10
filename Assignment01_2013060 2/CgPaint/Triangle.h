//
// Created by Hammad Akhtar on 04/08/16.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

#include <GLUT/glut.h>
#include "OpenGL/gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext.hpp"
#include "Shape.h"
#include <vector>

class Triangle : public Shape {
private:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 pos3;
    glm::vec3 color;

    bool pos3Present = false;

    GLfloat disY;

    GLuint VAO, VBO;

    int mode;

public:
    Triangle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color, int mode);
    Triangle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 color, int mode);
    ~Triangle();

    void initBuffers(std::vector<glm::vec3> positions);

    std::vector<glm::vec3> calculatePositions();

    virtual void draw();
    void polyGonDraw(std::vector<glm::vec3> positions);
    void solidDraw();
};


#endif //CGPAINT_TRIANGLE_H
