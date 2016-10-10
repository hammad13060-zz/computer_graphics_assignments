//
// Created by Hammad Akhtar on 04/08/16.
//

#include "Triangle.h"
#include "Line.h"
#include "glm/ext.hpp"
#include "iostream"

Triangle::Triangle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color, int mode) : pos1(pos1), pos2(pos2), mode(mode), color(color), pos3Present(false) {}

Triangle::Triangle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 color, int mode) : pos1(pos1), pos2(pos2), pos3(pos3), mode(mode), color(color), pos3Present(true){}

void Triangle::draw() {

    std::vector<glm::vec3> positions;
    if (!pos3Present) positions = calculatePositions();
    else {
        positions.push_back(pos1);
        positions.push_back(pos2);
        positions.push_back(pos3);
    }

    if (mode == 0) {
        polyGonDraw(positions);
    } else if (mode == 1) {
        initBuffers(positions);
        solidDraw();
    }

}

std::vector<glm::vec3> Triangle::calculatePositions() {

    glm::vec3 pos1(this->pos1);
    glm::vec3 pos2(this->pos2);
    glm::vec3 pos3;

    disY = pos2.y - pos1.y;

    pos2.y = pos1.y;

    pos3 = glm::vec3();
    pos3.x = ( pos2.x + pos1.x ) / 2.0f;
    pos3.y = pos1.y + disY;
    pos3.z = pos1.z;

    std::vector<glm::vec3> positions(3);
    positions[0] = pos1;
    positions[1] = pos2;
    positions[2] = pos3;
    return positions;

}

void Triangle::initBuffers(std::vector<glm::vec3> positions) {
    GLfloat vertices[18];

    vertices[0] = ((GLfloat)positions[0].x - 400.0f) / 400.0f;
    vertices[1] = ((GLfloat)positions[0].y - 300.0f) / 300.0f;
    vertices[2] = (GLfloat)positions[0].z;

    vertices[3] = ((GLfloat)positions[1].x - 400.0f) / 400.0f;
    vertices[4] = ((GLfloat)positions[1].y - 300.0f) / 300.0f;
    vertices[5] = (GLfloat)positions[1].z;

    vertices[6] = ((GLfloat)positions[2].x - 400.0f) / 400.0f;
    vertices[7] = ((GLfloat)positions[2].y - 300.0f) / 300.0f;
    vertices[8] = (GLfloat)positions[2].z;

    vertices[9] = color.x; //red
    vertices[10] = color.y; //blue
    vertices[11] = color.z; //green

    vertices[12] = color.x; //red
    vertices[13] = color.y; //blue
    vertices[14] = color.z; //green

    vertices[15] = color.x; //red
    vertices[16] = color.y; //blue
    vertices[17] = color.z; //green



    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Triangle::solidDraw() {
    glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::polyGonDraw(std::vector<glm::vec3> positions) {
    //std::cout << "draw called" << std::endl;


    Line line1(positions[0], positions[1], this->color);
    Line line2(positions[1], positions[2], this->color);
    Line line3(positions[2], positions[0], this->color);

    line1.draw();
    line2.draw();
    line3.draw();
}

Triangle::~Triangle() {
    glDeleteBuffers(1, &(this->VBO));
    glDeleteVertexArrays(1, &(this->VAO));
}

