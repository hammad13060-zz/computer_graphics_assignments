//
// Created by Hammad Akhtar on 04/08/16.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#define GLEW_STATIC

#include <GLUT/glut.h>
#include "OpenGL/gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext.hpp"

#include "Line.h"
#include "Shape.h"


class Circle : public Shape {
private:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 color;
    int sides;
    int mode;
public:
    Circle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color, int sides, int mode);

    virtual void draw();
};


#endif //CGPAINT_CIRCLE_H
