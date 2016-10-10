//
// Created by Hammad Akhtar on 01/09/16.
//

#include <OpenGL/OpenGL.h>
#include "PiecewiseBezier.h"
#include "cmath"
#include "glm/glm.hpp"
#include "Bezier.h"
#include <iostream>
#include "Line.h"

/*std::vector<glm::vec3> PiecewiseBezier::generatePhantomPoints(glm::vec3 pos1, glm::vec3 pos2, bool flipSign) {

    if (pos1.x > pos2.x) {
        glm::vec3 tmp = pos2;
        pos2 = pos1;
        pos1 = tmp;
    }

    std::vector<glm::vec3> result;

    glm::vec3 mid = (pos1 + pos2) / 2.0f;

    GLfloat xx = mid.x - pos1.x;
    GLfloat yy = mid.y - pos1.y;

    xx *= xx;
    yy *= yy;

    float sum = (float)(xx + yy);

    GLfloat radius = (GLfloat)sqrt(sum);


    glm::vec3 position_vec = pos2 - mid;
    GLfloat offset = glm::acos(position_vec.x / sqrt(position_vec.x*position_vec.x+
                                                    position_vec.y*position_vec.y+
                                                    position_vec.z*position_vec.z
    ));

    float incr = 180.0f / (float)(bezierLevel);
    if (!flipSign) incr *= -1.0f;

    float angle = 0.0f;

    //result.push_back(pos1);

    while(fabs(angle) <= 180.0f) {
        GLfloat x = radius * (GLfloat)glm::cos(glm::radians(angle) + offset);
        GLfloat y = radius * (GLfloat)glm::sin(glm::radians(angle) + offset);

        glm::vec3 pos = glm::vec3(mid.x + x, mid.y + y, mid.z);

        result.push_back(pos);

        angle += incr;
    }

    //result.push_back(pos2);

    result[0] = pos2;
    result[result.size()-1] = pos1;

    return result;

}*/

/*void PiecewiseBezier::draw() {
    bool flipSign = true;
    for(int i = 0; i < controlPoints.size()-1; i++) {

        if (controlPoints[i].y > controlPoints[i+1].y) flipSign = !flipSign;

        std::vector<glm::vec3> phantomPoints = generatePhantomPoints(controlPoints[i], controlPoints[i+1], flipSign);
        Beizier beizier(phantomPoints, this->color);
        beizier.draw();

        Line line(
                glm::vec3(controlPoints[i].x, controlPoints[i].y, controlPoints[i].z + 0.5f),
                glm::vec3(controlPoints[i+1].x, controlPoints[i+1].y, controlPoints[i+1].z + 0.5f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                false
        );
        line.draw();

        flipSign = !flipSign;
    }

}*/

void PiecewiseBezier::draw() {

    if (controlPoints.size() > 0) {
        //Line line1(controlPoints[0], controlPoints[0], glm::vec3(1.0f, 0.0f, 0.0f), false);
        //line1.draw();

        std::vector<glm::vec3> controlPoints;
        controlPoints.push_back(this->controlPoints[0]);

        int i;
        for (i = 0; i < this->controlPoints.size(); i++)
            controlPoints.push_back(this->controlPoints[i]);

        controlPoints.push_back(this->controlPoints[i-1]);

        for (int i = 1; i < controlPoints.size() - 1; i++) {
            std::vector<glm::vec3> points;
            points.clear();
            glm::vec3 mid1 = (controlPoints[i] + controlPoints[i - 1]) / 2.0f;
            glm::vec3 mid2 = (controlPoints[i] + controlPoints[i + 1]) / 2.0f;
            points.push_back(mid1);
            points.push_back(controlPoints[i]);
            points.push_back(mid2);
            Beizier beizier(points, this->color, true);
            beizier.draw();


            Line line1(mid1, mid1, glm::vec3(0.0f, 1.0f, 0.0f), false);
            line1.draw();

            /*Line line2(mid2, mid2, glm::vec3(0.0f, 1.0f, 0.0f), false);
            line2.draw();*/


            Line line3(controlPoints[i], controlPoints[i], glm::vec3(1.0f, 0.0f, 0.0f), false);
            line3.draw();
        }

        //Line line2(controlPoints[controlPoints.size() - 1], controlPoints[controlPoints.size() - 1],
          //          glm::vec3(1.0f, 0.0f, 0.0f), false);
        //line2.draw();
    }
}


