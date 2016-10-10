//
// Created by Hammad Akhtar on 19/08/16.
//

#include "pen.h"
#include "Line.h"
Pen::Pen(std::vector<glm::vec3> points, glm::vec3 color) : points(points), color(color) { }

void Pen::draw() {
    for (int i = 0; i < points.size()-1; i++) {
        Line *line = new Line(points[i], points[i+1], this->color);
        line->draw();
        delete line;
    }
}

Pen::~Pen() {
    points.clear();
}