//
// Created by Hammad Akhtar on 04/09/16.
//

#include "InterpolationCurve.h"
#include "Bezier.h"
#include "Line.h"

void InterpolationCurve::draw() {
    if (controlPoints.size() > 0) {
        drawTangent(controlPoints[0]);
        for (int i = 0; i < controlPoints.size() - 1; i++) {
            std::vector<glm::vec3> points;
            points.push_back(controlPoints[i].pos);
            points.push_back(controlPoints[i].pos1);
            points.push_back(controlPoints[i + 1].pos2);
            points.push_back(controlPoints[i + 1].pos);

            Beizier beizier(points, this->color, false);
            beizier.draw();

            drawTangent(controlPoints[i]);
            drawTangent(controlPoints[i+1]);
        }
    }
}

void InterpolationCurve::drawTangent(Tangent tangent) {
    Line line(tangent.pos1, tangent.pos2, glm::vec3(1.0f, 0.0f, 0.0f), true);
    line.draw();

    Line point1(tangent.pos1, tangent.pos1, glm::vec3(0.0f, 1.0f, 0.0f), false);
    point1.draw();

    Line point2(tangent.pos2, tangent.pos2, glm::vec3(0.0f, 1.0f, 0.0f), false);
    point2.draw();

    Line point3(tangent.pos, tangent.pos, glm::vec3(1.0f, 0.0f, 0.0f), false);
    point3.draw();
}
