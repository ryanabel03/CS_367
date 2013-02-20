/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: Hans Dulimarta <dulimarh@cis.gvsu.edu>
 */

#define GL_GLEXT_PROTOTYPES
#include <cstdlib>
// The following #define may be required to enable glWindowPos2i
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <utility>
//#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_interpolation.hpp>

using namespace std;

typedef pair<GLdouble, GLdouble> Pos2D;

glm::vec4 lightpos (2, 1.4, 1.5, 1);
glm::mat4 camera_cf;

float material_ambi[] = {0.4, 0.4, 0.4, 1};
float material_diff[] = {.0, 0.4, 0, 1};
float material_spec[] = {0.8, 0.8, 0.0, 1};
float material_none[] = {0,0,0,1};
GLubyte teapot_color[] = {170, 195, 92, 1};

int WIN_HEIGHT;
float bgColor[3];
int potlist, cf_list, arrow_list; /* teapot and coordinate frame */
bool use_color_material;
void printMatrix(double[]);
void show_help();
void show_text(int, int, const string&);

/********************************************************************/
// Display callback
/********************************************************************/
void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    show_text (5, 5, "Esc: quit    x/X/y/Y/z/Z: move the light "
               "    m:enable/disable [color] material");
    glLightfv(GL_LIGHT0, GL_POSITION, &lightpos[0]);

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(lightpos[0], lightpos[1], lightpos[2]);
    glutSolidSphere(0.1, 20, 4);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glCallList(cf_list);
    glPushMatrix();
    if (use_color_material) {
        glMaterialfv (GL_FRONT, GL_AMBIENT, material_none);
        glMaterialfv (GL_FRONT, GL_DIFFUSE, material_none);
        glMaterialfv (GL_FRONT, GL_SPECULAR, material_none);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor4ubv(teapot_color);
    }
    else {
        glDisable(GL_COLOR_MATERIAL);
        glMaterialfv (GL_FRONT, GL_AMBIENT, material_ambi);
        glMaterialfv (GL_FRONT, GL_DIFFUSE, material_diff);
        glMaterialfv (GL_FRONT, GL_SPECULAR, material_spec);
        glMaterialf (GL_FRONT, GL_SHININESS, 127);  /* 0-127 */
    }
    glCallList(potlist);
    glPopMatrix();

	glutSwapBuffers();
}

/********************************************************************/
// Resize callback
/********************************************************************/
void resize (int w, int h)
{
    WIN_HEIGHT = h;
	glViewport(0, 0, (GLint) w, (GLint) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(60, (float)w/h, 0.5, 50);

    /* always switch back to MODEVLVIEW matrix mode !!!! */
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
    /* use the default camera placement: eye at origin, 
       the camera is pointed along the NEGATIVE z-axis, 
       and the camera Y-axis (its "up" axis) is parallel to the world Y-axis
     */
    gluLookAt(1, 2.0, 5.0,
              0, 0, 0,
              0, 1, 0);
}

/********************************************************************/
// Keyboard callback
/********************************************************************/
void keyHandler (unsigned char ch, int x, int y)
{
//    cout << glutGetModifiers() << endl;
    switch (ch)
    {
        case 0x1B: /* escape key */
            exit (0);
            break;

        case 'x':
            lightpos[0] -= 0.2;
            break;
        case 'X':
            lightpos[0] += 0.2;
            break;
        case 'y':
            lightpos[1] -= 0.2;
            break;
        case 'Y':
            lightpos[1] += 0.2;
            break;
        case 'z':
            lightpos[2] -= 0.2;
            break;
        case 'Z':
            lightpos[2] += 0.2;
            break;
        case 'm':
            use_color_material ^= true;
    }
    glutPostRedisplay();
}

/* Default Teapot orientation:
 * The spout is facing towards the positive-X
 * The axis of the teapot body is the Z-axis
 */
void fkeyHandler (int key, int x, int y)
{
    if (key == GLUT_KEY_F12)
        exit(0);
    int mod = glutGetModifiers();
    /* in the following code we use openGL matrix calls to
     * perform the following multiplication:
     *
     *  F = F x Mat
     *
     * where F is our own coordinate frame and
     * Mat is the openGL transformation operation
     *
     * [the effect is to transform our coordinate frame w.r.t to itself]
     */
    if (mod == GLUT_ACTIVE_SHIFT) {
        switch (key) {
            case GLUT_KEY_UP: /* pitch-up */
//                pot_cf.execute(RZneg20, true);
                break;
            case GLUT_KEY_DOWN: /* pitch-down */
//                pot_cf.execute(RZpos20, true);
                break;
            case GLUT_KEY_LEFT:
//                pot_cf.execute(RYpos20, true);
                break;
            case GLUT_KEY_RIGHT:
//                pot_cf.execute(RYneg20, true);
                break;
        }
    }
    else {
        switch (key) {
            case GLUT_KEY_UP: /* move forward */
                /* multiply the teapot frame with X-translate */
//                pot_cf.execute(Xpos5, true);
                break;
            case GLUT_KEY_DOWN: /* move backward */
//                pot_cf.execute(Xneg5, true);
                break;
            case GLUT_KEY_LEFT:   /* roll */
//                pot_cf.execute(RXneg20, true);
                break;
            case GLUT_KEY_RIGHT:  /* roll */
//                pot_cf.execute(RXpos20, true);
                break;
        }

    }
    glutPostRedisplay();
}

void show_text (int x, int y, const string& msg)
{
    /* color must be set BEFORE glWindowPos* !!!!! */
    glColor3f(1,1,1); /* white text */
    /* Use the window coordinates to place the text */
    glWindowPos2i(x, y);
    for (int k = 0; k < msg.length(); k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[k]);
}

/********************************************************************/
// Initialization routines
/********************************************************************/
void initStates()
{

    /* setup the axes */
    arrow_list = glGenLists(1);
    glNewList(arrow_list, GL_COMPILE);

    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScalef(2.0, .06, .06);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 2.0);
    glutSolidCone(.15, 0.4, 20, 2);
    glPopMatrix();
    glEndList();

    cf_list = glGenLists(1);
    glNewList(cf_list, GL_COMPILE);
    /* draw the x-axis in red */
    glColor3ub(255,0,0);
    glCallList(arrow_list);
    /* draw the y-axis in green */
    glColor3ub(0, 255, 0);
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glCallList(arrow_list);
    glPopMatrix();

    /* draw the z-axis in blue */
    glColor3ub(18, 168, 212);
    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glCallList(arrow_list);
    glPopMatrix();
    glEndList();

    /* Setup the teapot */
    potlist = glGenLists(1);
    glNewList(potlist, GL_COMPILE);
    glutSolidTeapot(1.0);
    glEndList();
    fill (bgColor, bgColor + 3, 0.0);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

    glLineWidth(2.0);
    glPointSize(3.0);

    /* render front polygons (CCW) as filled faces */
    glPolygonMode(GL_FRONT, GL_FILL);

    /* render back polygon (CW) as outline */
//    glPolygonMode(GL_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    use_color_material = true;
}
int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (800, 600);
    glutCreateWindow("Coordinate Frames");

    /* initial setup */
    initStates();

    /* setup callback functions */
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyHandler);
    glutSpecialFunc(fkeyHandler);
    glutMainLoop();
}



