//
// Created by Hammad Akhtar on 04/08/16.
//

#include "Circle.h"
#include "Triangle.h"

Circle::Circle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color, int sides, int mode) : pos1(pos1), pos2(pos2), color(color), sides(sides), mode(mode) { };

void Circle::draw() {
   pos2.y = pos1.y;

    float len = fabs(pos1.x - pos2.x);

    len = len / 2.0f;

    glm::vec3 prev;
    if (pos2.x >= pos1.x) prev = pos2;
    else prev = pos1;
    float angle = 0.0f;
    float angleIncr = 360.0f / (float)sides;

    while (angle <= 360.0f) {
        float x = len * glm::cos(glm::radians(angle));
        float y = len * glm::sin(glm::radians(angle));

        glm::vec3 newPoint((pos1.x + pos2.x) / 2.0f + x, (pos1.y + pos2.y) / 2.0f + y, pos1.z);
        if (true) {
            if (mode == 0) {
                Line line(prev, newPoint, this->color);
                line.draw();
            } else if (mode == 1) {
                Triangle triangle(prev, newPoint, glm::vec3((pos1.x + pos2.x) / 2.0, pos1.y, pos1.z), this->color, 1);
                triangle.draw();
            }
        }

        angle += angleIncr;
        prev = newPoint;
    }
}
