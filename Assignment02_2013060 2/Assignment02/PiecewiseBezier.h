//
// Created by Hammad Akhtar on 01/09/16.
//

#ifndef LAB06_PIECEWISEBEZIER_H
#define LAB06_PIECEWISEBEZIER_H


#include <vector>
#include <glm/vec3.hpp>

class PiecewiseBezier {
private:
    std::vector<glm::vec3> controlPoints;
    glm::vec3 color;
    int bezierLevel;

    std::vector<glm::vec3> generatePhantomPoints(glm::vec3 pos1, glm::vec3 pos2, bool flipSign);

public:
    PiecewiseBezier(std::vector<glm::vec3> controlPoints, glm::vec3 color) : controlPoints(controlPoints), color(color){}
    void draw();
};


#endif //LAB06_PIECEWISEBEZIER_H
