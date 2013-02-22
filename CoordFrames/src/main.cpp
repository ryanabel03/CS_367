/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: Hans Dulimarta <dulimarh@cis.gvsu.edu>
 */

// The following #define may be required to enable glWindowPos2i
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include "CoordFrame.h"
#include "Translation.h"
#include "Rotation.h"

using namespace std;

typedef pair<GLdouble, GLdouble> Pos2D;
void showHelp();
enum MenuEntries {
    MENU_CLEAR,
    MENU_EXIT};

GLint viewport[4];
GLdouble mvMatrix[16];
GLdouble prMatrix[16];

CoordFrame pot_cf;
deque<CoordFrame> cf_store;
vector<Pos2D> vertices;
map<MenuEntries,unsigned int> menuMap;
bool is_animating = false, in_help = false, has_moved = false;

int WIN_HEIGHT;
float bgColor[3];
int potlist, cf_list, arrow_list; /* teapot and coordinate frame */

void printMatrix(double[]);
void show_help();
void show_text(int, int, const string&);

/********************************************************************/
// Display callback
/********************************************************************/
void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    show_text (5, 5, "Esc: quit    h:show help");
    if (!is_animating)
        glCallList(cf_list);
    glPushMatrix();
    /* transform the teapot using its own frame */
    glMultMatrixf(pot_cf.getData());
    glCallList(potlist);
    glPopMatrix();

	glutSwapBuffers();
}

void printMatrix (double mat[])
{
    printf ("Coordinate Frame:\n");
    for (int k = 0; k < 4; k++)
    {
        for (int m = 0; m < 4; m++)
        {
            printf ("%2.3f ", mat[m*4+k]);
        }
        printf("\n");
    }
}

/********************************************************************/
// Resize callback
/********************************************************************/
void resize (int w, int h)
{
    WIN_HEIGHT = h;
	glViewport(0, 0, (GLint) w, (GLint) h);
	glGetIntegerv(GL_VIEWPORT, viewport);
	/* viewport[2] = width of the window
	 * viewport[3] = height of the window
	 */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

#if 0
	GLfloat ratio;
	if (w <= h) {
		ratio = static_cast<GLfloat> (h) / w;
		gluOrtho2D(-4.0, 4.0, -4.0 * ratio, 4.0 * ratio);
	}
	else {
		ratio = static_cast<GLfloat> (w) / h;
		gluOrtho2D(-4.0 * ratio, 4.0 * ratio, -4.0, 4.0);
	}
#else
    gluPerspective(60, (float)w/h, 0.5, 50);
#endif
    
	glGetDoublev(GL_PROJECTION_MATRIX, prMatrix);
    /* always switch back to MODEVLVIEW matrix mode !!!! */
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
    /* use the default camera placement: eye at origin, 
       the camera is pointed along the NEGATIVE z-axis, 
       and the camera Y-axis (its "up" axis) is parallel to the world Y-axis
     */
    gluLookAt(1, 2.0, 8.0,
              0, 0, 0,
              0, 1, 0);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
}

float alpha_interpol;
void timerHandler (int val)
{
    /* interpolate alpha in [0,1] */
    if (alpha_interpol < 1.0) {
        is_animating = true;
        const glm::mat4& teapot_m1 = cf_store.front().getMatrix();
        const glm::mat4& teapot_m2 = cf_store.back().getMatrix();
        /* get the fourth column of our coordinate frame matrix */
        const glm::vec4& teapot_t1 = glm::column(teapot_m1, 3);
        const glm::vec4& teapot_t2 = glm::column(teapot_m2, 3);
        const glm::quat& teapot_q1 = glm::toQuat(teapot_m1);
        const glm::quat& teapot_q2 = glm::toQuat(teapot_m2);
        glm::quat q_alpha;
        glm::mat4 teapot_m_alpha;
        switch(val) {
            case 'm':
                /* matrix linear interpolation */
                teapot_m_alpha = (1.0 - alpha_interpol) * teapot_m1 +
                    alpha_interpol * teapot_m2;
                break;
            case 'q':
                /* quaternion linear interpolation */
                q_alpha = glm::fastMix(teapot_q1, teapot_q2, alpha_interpol);
                /* convert quaternion to a rotation matrix */
                teapot_m_alpha = glm::toMat4(q_alpha);

                /* The quaternion takes only the Rotational component of our
                   coordinate frame matrix. We need to fill in the translational
                   component manually. */

                // te___[3] refers to the FOURTH column of the CF matrix
                teapot_m_alpha[3] = (1 - alpha_interpol) * teapot_t1 +
                    alpha_interpol * teapot_t2;
                break;
            case 's':
                /* quaternion spherical linear interpolation */
                q_alpha = glm::mix(teapot_q1, teapot_q2, alpha_interpol);
                /* convert quaternion to a rotation matrix */
                teapot_m_alpha = glm::toMat4(q_alpha);

                /* The quaternion takes only the Rotational component of our
                 coordinate frame matrix. We need to fill in the translational
                 component manually. */

                teapot_m_alpha[3] = (1 - alpha_interpol) * teapot_t1 +
                alpha_interpol * teapot_t2;
                break;
        }
        pot_cf.setMatrix(teapot_m_alpha);
        alpha_interpol += 0.05;
        glutTimerFunc(50, timerHandler, val);
    }
    else {
        is_animating = false;
        pot_cf = cf_store.back();
    }
    glutPostRedisplay();
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
            if (in_help) {
                in_help = false;
                glutDisplayFunc(render);
            }
            else
                exit (0);
            break;
        case 'h':
            if (! in_help) {
                in_help = true;
                glutDisplayFunc(showHelp);
            }

            break;
        case 'm': /* start animation by matrix interpolation */
        case 'q': /* start animation by quaternion interpolation */
        case 's': /* start animation by quaternion interpolation */
            if (cf_store.size() == 2) {
                alpha_interpol = 0.0f;
                /* begin matrix interpolation */
                glutTimerFunc(50, timerHandler, ch);
            }
            break;
        case 'r':  /* record current frame */
            if (has_moved) {
                has_moved = false;
                cf_store.push_back(pot_cf);
                /* keep the last two frames */
                if (cf_store.size() > 2)
                    cf_store.pop_front();
            }
            break;
        case 'z': /* rotate around the world Z-axis */
            /*
             *  F = Rot x F
             *
             *  [the effect is to rotate our coordinate frame around
             *   the WORLD axis]
             *  where F is our own coordinate frame and
             *  Rot is the openGL rotation
             */
            pot_cf.execute(new Rotation(-10.0f, 0, 0, 1), false);
            has_moved = true;
            break;
        case 'Z': /* rotate around the world Z-axis */
            pot_cf.execute(new Rotation(+10.0f, 0, 0, 1), false);
            has_moved = true;
            break;
    }
    glutPostRedisplay();
}

/* Default Teapot orientation:
 * The spout is facing towards the positive-X
 * The axis of the teapot body is the Z-axis
 */
void fkeyHandler (int key, int x, int y)
{
    static Translation * Xpos5 = new Translation (0.5f, 0.0f, 0.0f);
    static Translation * Xneg5 = new Translation (-0.5f, 0.0f, 0.0f);
    static Rotation* RZneg20 = new Rotation (-20, 0, 0, 1);
    static Rotation* RZpos20 = new Rotation (+20, 0, 0, 1);
    static Rotation* RYneg20 = new Rotation (-20, 0, 1, 0);
    static Rotation* RYpos20 = new Rotation (+20, 0, 1, 0);
    static Rotation* RXneg20 = new Rotation (-20, 1, 0, 0);
    static Rotation* RXpos20 = new Rotation (+20, 1, 0, 0);

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
                pot_cf.execute(RZneg20, true);
                has_moved = true;
                break;
            case GLUT_KEY_DOWN: /* pitch-down */
                pot_cf.execute(RZpos20, true);
                has_moved = true;
                break;
            case GLUT_KEY_LEFT:
                pot_cf.execute(RYpos20, true);
                has_moved = true;
                break;
            case GLUT_KEY_RIGHT:
                pot_cf.execute(RYneg20, true);
                has_moved = true;
                break;
        }
    }
    else {
        switch (key) {
            case GLUT_KEY_UP: /* move forward */
                /* multiply the teapot frame with X-translate */
                pot_cf.execute(Xpos5, true);
                has_moved = true;
                break;
            case GLUT_KEY_DOWN: /* move backward */
                pot_cf.execute(Xneg5, true);
                has_moved = true;
                break;
            case GLUT_KEY_LEFT:   /* roll */
                pot_cf.execute(RXneg20, true);
                has_moved = true;
                break;
            case GLUT_KEY_RIGHT:  /* roll */
                pot_cf.execute(RXpos20, true);
                has_moved = true;
                break;
        }

    }
    glutPostRedisplay();
}

/********************************************************************/
// Menu handlers
/********************************************************************/
void topMenuHandler (int select)
{
    switch (select)
    {
    case MENU_EXIT:
        exit (0);
    case MENU_CLEAR:
        vertices.clear();
        break;
    }

    glutPostRedisplay(); /* request display refresh */
}

void show_text (int x, int y, const string& msg)
{
    /* color must be set BEFORE glWindowPos* !!!!! */
    glColor3f(1,1,1); /* white text */
    /* Use the window coordinates to place the text */
#ifdef GL_VERSION_1_5
    glWindowPos2i(x, y);
    for (int k = 0; k < msg.length(); k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[k]);
#endif
}

void showHelp()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    show_text (5, 5, "Esc: quit");

    string help_text[] = {
        "[Shift]+arrow keys to manipulate the teapot around its own coordinate frame",
        "z/Z  : rotate the teapot around the WORLD z-axis",
        "",
        "r    : record the current coordinate frame to the queue",
        "m/q/s: animate between the last two frames in the queue",
        "    m => use matrix linear interpolation",
        "    q => linear quaternion interpolation",
        "    s => spherical linear quaternion interpolation",
        "",
        "To see the visual defect in matrix linear interpolation, ",
        "    choose two coordinate frames that require 180 rotation "
        , "NOMORE" /* WATCH OUT for the COMMA!!!! */
    };
    for (int k = 0; help_text[k] != "NOMORE"; k++)
        show_text (5, WIN_HEIGHT - 20*k - 20, help_text[k]);
	glutSwapBuffers();
}

/********************************************************************/
// Initialization routines
/********************************************************************/
void initStates()
{
    static float lightpos[] = {1, 4, 0, 1};



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
//    glCallList(cf_list);

    glColor3ub(170, 195, 92);
    glutSolidTeapot(1.0);
    glEndList();
    fill (bgColor, bgColor + 3, 0.0);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

    glLineWidth(2.0);
    glPointSize(3.0);

    cf_store.push_back(pot_cf);
    
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
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void initMenus()
{
    glutCreateMenu(topMenuHandler);
    glutAddMenuEntry ("Clear", MENU_CLEAR);
    glutAddMenuEntry ("Exit (F12)", MENU_EXIT);

    /* Activate the menu from the right-button */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (800, 600);
    glutCreateWindow("Coordinate Frames");

    /* initial setup */
    initStates();
    initMenus();

    /* setup callback functions */
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyHandler);
    glutSpecialFunc(fkeyHandler);
    glutMainLoop();
}



