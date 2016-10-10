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

#include "Shader.h"

#include "pen.h"
#include "Bezier.h"
#include "PiecewiseBezier.h"
//#include "Tangent.cpp"
#include "InterpolationCurve.h"


void key_callback(GLubyte key, GLint x, GLint y);
void mouseButtonCallback(GLint button, GLint state, GLint x, GLint y);
void button_callback(int control);
double distance(glm::vec3 pos1, glm::vec3 pos2);
void cursorPosCallback(GLint xpos, GLint ypos);
void undo_redo_cb(int control);

//std::string workingDirectory = "/Users/hammad13060/Development/workspace/c++/LAB06/";
std::string workingDirectory = "./";

const GLint WIDTH = 800, HEIGHT = 600;
GLint width, height;

std::vector<glm::vec3> points(0);
std::vector<glm::vec3> deletedPoints(0);
std::vector<Tangent> interpolationPoints(0);



GLboolean firstMousePress = GL_FALSE;
glm::vec3 pos1;
glm::vec3 pos2;
GLfloat zvalue = -1.0f;

int red_value = 0;
int green_value = 0;
int blue_value = 0;
int bezierLevel = 2;


Shader shader;

GLint window;
int polygon = 1;
int solid = 1;

GLint shape_type = 1;

int mode = 1;
int ind;

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



void display(void) {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::vec3 colorObject((GLfloat)red_value / 255.0f, (GLfloat)green_value / 255.0f, (GLfloat)blue_value / 255.0f);

    shader.Use();

        PiecewiseBezier curve(points, colorObject);
        curve.draw();


        InterpolationCurve interpolationCurve(interpolationPoints, colorObject);
        interpolationCurve.draw();

    glutSwapBuffers();
    glutPostRedisplay();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGB);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    window = glutCreateWindow("Bezier tool");
    glutKeyboardFunc(key_callback);
    glutMouseFunc(mouseButtonCallback);
    glutMotionFunc(cursorPosCallback);
    glutDisplayFunc(display);

    GLUI *control = GLUI_Master.create_glui("controls");

    GLUI_Rollout* shapeRollout = control->add_rollout("curves", 1);

    GLUI_Button *curve = control->add_button_to_panel(shapeRollout, "Approximation Curve", 1, button_callback);
    GLUI_Button *edit = control->add_button_to_panel(shapeRollout, "manipulate approx curve", 2, button_callback);
    GLUI_Button *interpolationCurve = control->add_button_to_panel(shapeRollout, "interpolation curve", 3, button_callback);



    GLUI_Rollout *colorRollout = control->add_rollout("Color value", 2);
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
    GLUI_Button *clear = control->add_button_to_panel(editRollout,"clear canvas", 7, undo_redo_cb);

    control->set_main_gfx_window( window );


    GLUI_Master.set_glutIdleFunc( myGlutIdle );
    GLUI_Master.set_glutReshapeFunc( reshape );

    glutMainLoop();

    return 0;
}

void key_callback(GLubyte key, GLint x, GLint y) {
    if (key == 27)
        glutDestroyWindow(window);
}

void mouseButtonCallback(GLint button, GLint state, GLint x, GLint y) {
    glm::vec3 pos((GLfloat) x, (GLfloat) (600.0f - (GLfloat) y), 0.0f);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        firstMousePress = GL_TRUE;
        if (mode == 1) {
            points.push_back(pos);
        } else if (mode == 2) {
            for (int i = 0; i < points.size(); i++) {
                if (distance(points[i], pos) <= 5.0f) {
                //if (points[i].x == pos.x && points[i].y == pos.y) {
                    ind = i;
                    break;
                }
            }
        } else if (mode == 3) {
            Tangent tangent;
            tangent.pos = pos;
            tangent.pos1 = pos;
            tangent.pos2 = pos;
            interpolationPoints.push_back(tangent);
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        firstMousePress = GL_FALSE;
    }
}



void cursorPosCallback(GLint xpos, GLint ypos) {
    glm::vec3 pos((GLfloat) xpos, (GLfloat) (600.0f - (GLfloat) ypos), 0.0f);
    if (firstMousePress == GL_TRUE) {
        if (mode == 2) {
            points[ind].x = pos.x;
            points[ind].y = pos.y;
        } else if (mode == 3) {
            if (interpolationPoints.size() > 0) {
                Tangent &tangent = interpolationPoints[interpolationPoints.size() - 1];
                tangent.pos1 = pos;
                tangent.pos2 = (tangent.pos - (tangent.pos1 - tangent.pos));
            }
        }
    }
}

void button_callback(int control) {
    mode = control;
}

void undo_redo_cb(int control) {
    if (control == 7) {
        points.clear();
        deletedPoints.clear();
        interpolationPoints.clear();
    }
}

double distance(glm::vec3 pos1, glm::vec3 pos2) {
    glm::vec3 pos = pos1 - pos2;
    pos *= pos;

    return sqrt(pos.x + pos.y);
}
