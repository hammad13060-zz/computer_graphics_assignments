//
// Created by Hammad Akhtar on 08/08/16.
//

#ifndef CGPAINT_SQUARE_H
#define CGPAINT_SQUARE_H

#include "Shape.h"
#include "glm/glm.hpp"

class Square : public Shape {

private:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 color;
    int mode;

public:
    Square(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color, int mode);

    virtual void draw();

};


#endif //CGPAINT_SQUARE_H
