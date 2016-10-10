//
// Created by Hammad Akhtar on 19/08/16.
//

#ifndef CGPAINT_PEN_H
#define CGPAINT_PEN_H

#include <vector>
#include <glm/vec3.hpp>
#include "Shape.h"

class Pen : public Shape{
private:
    std::vector<glm::vec3> points;
    glm::vec3 color;
public:
    Pen(std::vector<glm::vec3> points, glm::vec3 color);
    ~Pen();
    virtual void draw();
};


#endif //CGPAINT_PEN_H
