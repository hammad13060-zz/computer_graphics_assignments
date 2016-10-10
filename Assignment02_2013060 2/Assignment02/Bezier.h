//
// Created by Hammad Akhtar on 26/08/16.
//

#ifndef CGPAINT_BEIZIER_H
#define CGPAINT_BEIZIER_H


#include <vector>
#include <glm/vec3.hpp>

class Beizier {
private:
    std::vector<glm::vec3> positions;
    glm::vec3 color;

    glm::vec3 beizier(std::vector<glm::vec3> positions, float t);

    bool drawTangent;

public:
    Beizier(std::vector<glm::vec3> positions, glm::vec3 color, bool drawTangent);
    virtual void draw();
};


#endif //CGPAINT_BEIZIER_H
