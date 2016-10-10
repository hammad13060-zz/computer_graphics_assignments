//
// Created by Hammad Akhtar on 04/09/16.
//

#ifndef ASSIGNMENT02_INTERPOLATIONCURVE_H
#define ASSIGNMENT02_INTERPOLATIONCURVE_H


#include <vector>
#include "Tangent.cpp"
class InterpolationCurve {
private:
    std::vector<Tangent> controlPoints;
    glm::vec3 color;

public:
    InterpolationCurve(std::vector<Tangent> controlPoints, glm::vec3 color) : controlPoints(controlPoints), color(color){}
    void draw();
    void drawTangent(Tangent tangent);

};


#endif //ASSIGNMENT02_INTERPOLATIONCURVE_H
