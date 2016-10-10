//
// Created by Hammad Akhtar on 03/08/16.
//

#include "Line.h"
#include "iostream"

Line::Line(glm::vec3 pos1, glm::vec3 pos2, const glm::vec3 color, bool mode) : pos1(pos1), pos2(pos2), color(color), lineMode(mode) {
    this->createBuffers();
}

void Line::createBuffers() {
    GLfloat vertices[12];

    vertices[0] = ((GLfloat)pos1.x - 400.0f) / 400.0f;
    vertices[1] = ((GLfloat)pos1.y - 300.0f) / 300.0f;
    vertices[2] = (GLfloat)pos1.z;

    vertices[3] = ((GLfloat)pos2.x - 400.0f) / 400.0f;
    vertices[4] = ((GLfloat)pos2.y - 300.0f) / 300.0f;
    vertices[5] = (GLfloat)pos2.z;

    vertices[6] = color.x; //red
    vertices[7] = color.y; //blue
    vertices[8] = color.z; //green

    vertices[9] = color.x; //red
    vertices[10] = color.y; //blue
    vertices[11] = color.z; //green

    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Line::draw() {
    glBindVertexArray(this->VAO);
    //glDrawArrays(GL_LINES, 0, 2);
    //glDrawArrays(GL_LINES, 0, 2);
    if (lineMode) {
        glPointSize(1.0f);
        glDrawArrays(GL_LINES, 0, 2);
    }
    else {
        glPointSize(5.0f);
        glDrawArrays(GL_POINTS, 0, 2);
    }
    glBindVertexArray(0);
}

Line::~Line() {
    glDeleteBuffers(1, &(this->VBO));
    glDeleteVertexArrays(1, &(this->VAO));
}
