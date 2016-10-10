//
// Created by Hammad Akhtar on 08/08/16.
//

#include "Square.h"
#include "Line.h"
#include "Triangle.h"

Square::Square(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color, int mode) : pos1(pos1), pos2(pos2), color(color), mode(mode) { }


void Square::draw() {

    if (pos1.x == pos2.x || pos1.y == pos2.y) {
        Line line(pos1, pos2, this->color);
        line.draw();
        return;
    }

    glm::vec3 pos3((pos1.x + pos2.x + pos2.y - pos1.y) / 2, (pos1.y + pos2.y + pos1.x - pos2.x) / 2, (pos1.z + pos2.z) / 2 );
    glm::vec3 pos4((pos1.x + pos2.x + pos1.y - pos2.y) / 2, (pos1.y + pos2.y + pos2.x - pos1.x) / 2, (pos1.z + pos2.z) / 2 );

    if (mode == 0) {
        Line line1(pos1, pos3, this->color);
        Line line2(pos3, pos2, this->color);
        Line line3(pos2, pos4, this->color);
        Line line4(pos4, pos1, this->color);
        line1.draw();
        line2.draw();
        line3.draw();
        line4.draw();
    } else if (mode == 1) {
        Triangle triangle1(pos1, pos3, pos2, this->color, 1);
        Triangle triangle2(pos1, pos4, pos2, this->color, 1);
        triangle1.draw();
        triangle2.draw();
    }
}
