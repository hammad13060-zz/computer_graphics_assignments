#include "iostream"
#include <string>

#include <GLUT/glut.h>
#include "OpenGL/gl3.h"
#include <GLUI/glui.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext.hpp"

#include <vector>

#include "Line.h"
#include "Triangle.h"
#include "Circle.h"
#include "Shader.h"
#include "Square.h"
#include "pen.h"
#include "Shape.h"


void key_callback(GLubyte key, GLint x, GLint y);
void mouseButtonCallback(GLint button, GLint state, GLint x, GLint y);
void cursorPosCallback(GLint xpos, GLint ypos);
void button_callback(int control);
void drawingMode_callback(int control);
void undo_redo_cb(int control);

//std::string workingDirectory = "/Users/hammad13060/Development/workspace/c++/CgPaint/";
std::string workingDirectory = "./";

const GLint WIDTH = 800, HEIGHT = 600;
GLint width, height;

int mode = 0;

std::vector<Shape*> shapes(0);
std::vector<Shape*> deletedShapes(0);
std::vector<glm::vec3> points;
Shape currentShape;


GLboolean firstMousePress = GL_FALSE;
glm::vec3 pos1;
glm::vec3 pos2;
GLfloat zvalue = -1.0f;

int red_value = 0;
int green_value = 0;
int blue_value = 0;
int sides = 6;


Shader shader;

GLint window;
int polygon = 1;
int solid = 1;

GLint shape_type = 1;

void myGlutIdle( void )
{
    /* According to the GLUT specification, the current window is
       undefined during an idle callback.  So we need to explicitly change
       it if necessary */
    if ( glutGetWindow() != window )
        glutSetWindow(window);

    glutPostRedisplay();
}

GLUI_Checkbox* polygonCheckBox;
GLUI_Checkbox* solidCheckBox;

void reshape(int w, int h)
{

    GLUI_Master.auto_set_viewport();

    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glLineWidth(0.5f);

    shader = Shader((workingDirectory + "vertexShader.glsl").c_str(), (workingDirectory + "fragmentShader.glsl").c_str());

    glutPostRedisplay();

}



void drawExistingShapes() {
    //std::cout << "vector size: " << shapes.size() << std::endl;
    for (int i = 0; i < shapes.size(); i++) shapes[i]->draw();
}

void display(void) {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::vec3 colorObject((GLfloat)red_value / 255.0f, (GLfloat)green_value / 255.0f, (GLfloat)blue_value / 255.0f);

    shader.Use();

    //GLint choosenColorLocation = glGetUniformLocation(shader.Program, "choosenColor");
    //glUniform3f(choosenColorLocation, colorObject.x, colorObject.y, colorObject.z);


    drawExistingShapes();

    //Shape* line =  new Triangle(glm::vec3(400.0f, 300.0f, -0.5f), glm::vec3(450.0f, 350.0f, -0.5f));
    //Line line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f));
    //line->draw();

    //std::cout << "first mouse press: " << firstMousePress << std::endl;

    if (firstMousePress) {
        //std::cout << "first mouse pressed" << std::endl;
        Shape *shape;
        if (shape_type == 1) shape = new Line(pos1, pos2, colorObject);
        else if (shape_type == 2) shape = new Triangle(pos1, pos2, colorObject, mode);
        else if (shape_type == 3) shape = new Circle(pos1, pos2, colorObject, 72, mode);
        else if (shape_type == 4) shape = new Square(pos1, pos2, colorObject, mode);
        else if (shape_type == 5) shape = new Circle(pos1, pos2, colorObject, sides, mode);
        else if (shape_type == 6) shape = new Pen(points, colorObject);
        shape->draw();
        delete shape;
    }

    glutSwapBuffers();
    glutPostRedisplay();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGB);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    window = glutCreateWindow("Paint");
    glutKeyboardFunc(key_callback);
    glutMouseFunc(mouseButtonCallback);
    glutMotionFunc(cursorPosCallback);
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);


    //GUI
    //GLUI_Master.create_glui("controls", GLUI_SUBWINDOW, 900, 0);
    //GLUI *control = GLUI_Master.create_glui_subwindow(window, GLUI_SUBWINDOW_RIGHT);

    GLUI *control = GLUI_Master.create_glui("controls");

    GLUI_Rollout* shapeRollout = control->add_rollout("Shapes", 1);

    GLUI_Button *line = control->add_button_to_panel(shapeRollout, "line", 1, button_callback);
    GLUI_Button *triangle = control->add_button_to_panel(shapeRollout,"triangle", 2, button_callback);
    GLUI_Button *circle = control->add_button_to_panel(shapeRollout,"circle", 3, button_callback);
    GLUI_Button *square = control->add_button_to_panel(shapeRollout,"square", 4, button_callback);
    GLUI_Button *polygon = control->add_button_to_panel(shapeRollout, "polygon", 5, button_callback);
    GLUI_Spinner *polygonSpinner = control->add_spinner_to_panel(shapeRollout, "sides of polygon", GLUI_SPINNER_INT, &sides);
    polygonSpinner->set_int_limits(5, 11);
    GLUI_Button *penTool = control->add_button_to_panel(shapeRollout, "pen tool", 6, button_callback);

    GLUI_Rollout* drawingModeRollout = control->add_rollout("Drawing mode", 2);

    polygonCheckBox = control->add_checkbox_to_panel(drawingModeRollout, "polygon", (int *)&polygon, 4, drawingMode_callback);
    solidCheckBox = control->add_checkbox_to_panel(drawingModeRollout, "solid`", (int *) &solid, 5, drawingMode_callback);

    polygonCheckBox->set_int_val(1);
    solidCheckBox->set_int_val(0);
    mode = 0;


    GLUI_Rollout *colorRollout = control->add_rollout("Color value", 3);
    GLUI_Spinner *red_spinner =
            control->add_spinner_to_panel(colorRollout ,"red:", GLUI_SPINNER_INT, &red_value );
    red_spinner->set_int_limits( 0, 255 );

    GLUI_Spinner *green_spinner =
            control->add_spinner_to_panel( colorRollout,"green:", GLUI_SPINNER_INT, &green_value );
    green_spinner->set_int_limits( 0, 255 );

    GLUI_Spinner *blue_spinner =
            control->add_spinner_to_panel( colorRollout,"blue:", GLUI_SPINNER_INT, &blue_value );
    blue_spinner->set_int_limits( 0, 255 );


    GLUI_Rollout *editRollout = control->add_rollout("Edit", 3);
    GLUI_Button *undo = control->add_button_to_panel(editRollout,"undo", 5, undo_redo_cb);
    GLUI_Button *redo = control->add_button_to_panel(editRollout,"redo", 6, undo_redo_cb);
    GLUI_Button *clear = control->add_button_to_panel(editRollout,"clear canvas", 7, undo_redo_cb);

    control->set_main_gfx_window( window );


    GLUI_Master.set_glutIdleFunc( myGlutIdle );
    GLUI_Master.set_glutReshapeFunc( reshape );
    //GLUI_Master.set_glutMouseFunc(mouseButtonCallback);

    glutMainLoop();

    return 0;
}

void key_callback(GLubyte key, GLint x, GLint y) {
    if (key == 27)
        glutDestroyWindow(window);
}

void mouseButtonCallback(GLint button, GLint state, GLint x, GLint y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        firstMousePress = GL_TRUE;
        //std::cout << "mouse pressed" << std::endl;
        pos2.x = pos1.x = (GLfloat)x;
        pos2.y = pos1.y = (GLfloat)(600.0f - (GLfloat)y);
        pos2.z = pos1.z = (GLfloat)zvalue;
        points.clear();
        points.push_back(pos2);
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        //std::cout << "mouse released" << std::endl;
        Shape *shape;

        glm::vec3 colorObject((GLfloat)red_value / 255.0f, (GLfloat)green_value / 255.0f, (GLfloat)blue_value / 255.0f);
        if (shape_type == 1) shape = new Line(pos1, pos2, colorObject);
        else if (shape_type == 2) shape = new Triangle(pos1, pos2, colorObject, mode);
        else if (shape_type == 3) shape = new Circle(pos1, pos2, colorObject, 72, mode);
        else if (shape_type == 4) shape = new Square(pos1, pos2, colorObject, mode);
        else if (shape_type == 5) shape = new Circle(pos1, pos2, colorObject, sides, mode);
        else if (shape_type == 6) shape = new Pen(points, colorObject);
        shapes.push_back(shape);
        deletedShapes.clear();
        firstMousePress = GL_FALSE;
        zvalue += 0.001f;
    }
}

void cursorPosCallback(GLint xpos, GLint ypos) {
    if (firstMousePress == GL_FALSE) {
        pos1.x = (GLfloat)xpos;
        pos1.y = (GLfloat)(600.0f - (GLfloat)ypos);
        pos1.z = (GLfloat)zvalue;
    } else if (firstMousePress == GL_TRUE) {
        //std::cout << "hello" << std::endl;
        pos2.x = (GLfloat) xpos;
        pos2.y = (GLfloat) (600.0f - (GLfloat) ypos);
        points.push_back(pos2);
    }
    //glutPostRedisplay();
    //std::cout << xpos << ", " << 600 - ypos << std::endl;
    //std::cout << "pos1 " << glm::to_string(pos1) << std::endl;
    //std::cout << "pos2 " << glm::to_string(pos2) << std::endl;
    //std::cout << "xpos: " << xpos << " ypos: " << (600.0f - ypos) << std::endl;
}

void button_callback(int control) {
    shape_type = (GLint)control;
}

void drawingMode_callback(int control) {
    if (control == 4) {
        std::cout << "polygon" << std::endl;
        if (polygon == 0) {
            solidCheckBox->set_int_val(1);
            mode = 1;
        }
        else if (polygon == 1) {
            solidCheckBox->set_int_val(0);
            mode = 0;
        }
    } else if (control == 5) {
        std::cout << "solid" << std::endl;
        if (solid == 0) {
            polygonCheckBox->set_int_val(1);
            mode = 0;
        }
        else if (solid == 1) {
            polygonCheckBox->set_int_val(0);
            mode = 1;
        }
    }
}

void undo_redo_cb(int control) {
    if (control == 5) {
        //undo
        if (shapes.size() > 0) {
            Shape* shape = shapes[shapes.size()-1];
            shapes.pop_back();
            deletedShapes.push_back(shape);
        }
    } else if (control == 6) {
        //redo
        if (deletedShapes.size() > 0) {
            Shape* shape = deletedShapes[deletedShapes.size()-1];
            deletedShapes.pop_back();
            shapes.push_back(shape);
        }
    } else if (control == 7) {
        shapes.clear();
    }
}