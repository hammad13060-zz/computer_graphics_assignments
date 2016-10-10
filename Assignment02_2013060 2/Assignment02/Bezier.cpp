//
// Created by Hammad Akhtar on 26/08/16.
//

#include "Bezier.h"
#include "pen.h"
#include "iostream"

Beizier::Beizier(std::vector<glm::vec3> positions, glm::vec3 color, bool drawTangent) : positions(positions), color(color), drawTangent(drawTangent) { }

glm::vec3 Beizier::beizier(std::vector<glm::vec3> positions, float t) {
    if (positions.size() == 1) return positions[0];
    else {
        std::vector<glm::vec3> newPositions;
        for (int i = 0; i < positions.size()-1; i++) {
            glm::vec3 pos1 = positions[i];
            glm::vec3 pos2 = positions[i+1];
            glm::vec3 newPos = glm::vec3((1.0f-t) * pos1.x + t * pos2.x, (1.0f-t) * pos1.y + t * pos2.y, pos1.z);
            newPositions.push_back(newPos);
        }
        return beizier(newPositions, t);
    }
}

void Beizier::draw() {
    std::vector<glm::vec3> points;
    float t = 0.0f;
    while (t <= 1.0f) {
        glm::vec3 point = this->beizier(this->positions, t);
        points.push_back(point);
        t += 0.01f;
    }
    //std::cout << "len of beizier: " << points.size() << std::endl;
    Pen curve(points, this->color);
    curve.draw();
    if (drawTangent) {
        Pen poly(this->positions, glm::vec3(1.0f, 0.0f, 0.0f)); //by default tangents are red
        poly.draw();
    }
}
