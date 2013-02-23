/**
 * Example of 3D object animation
 *
 * Hans Dulimarta
 * dulimar@cis.gvsu.edu
 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <sys/time.h>
#include <math.h>
#include <limits.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Arm.h"
#include "Cylinder.h"
#include "Wheel.h"

using namespace std;
void displayCallback();

/* define global variables here */
int glut_win;

Wheel *wheel;
Arm* swingarm;
Cylinder* spot;
glm::mat4 wheel_cf;
glm::mat4 swing_cf;
glm::mat4 camera_cf;
const float INIT_SWING_ANGLE = 35.0f;
const float GRAVITY = 9.8;   /* m/sec^2 */
bool is_idle_active = true;
GLfloat eye[] = {200, 150, 80};
/* light source setting */
GLfloat light0_pos[] = {0, 5, 10, 1};                /* position */
GLfloat light1_pos[] = {0, 10, -15, 1};                /* position */
GLfloat light1_dir[] = {0, -1, 0};
GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};   /* color */
GLfloat light1_color[] = {0.5, 1.0, 0.06, 1.0};   /* color */

/*--------------------------------*
 * GLUT Reshape callback function *
 *--------------------------------*/
void reshapeCallback (int w, int h)
{
    glViewport (0, 0, w, h);

    /* switch to Projection matrix mode */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    gluPerspective (60, (float) w / (float) h, 5.0, 100.0);

    /* switch back to Model View matrix mode */
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (25, 20, 0, 0, 0, 0, 0, 0, 1);
    glGetFloatv (GL_MODELVIEW_MATRIX, &camera_cf[0][0]);
}

/*================================================================*
 * Idle Callback function. This is the main engine for simulation *
 *================================================================*/
void idleCallback()
{
    static clock_t last_timestamp = 0;
    static float swing_time = 0;
    clock_t current;
    double delta;

    current = clock();
    /* convert CPU clock to milliseconds, this technique produces
     * the same animation speed regardless of the CPU clock speed
     */
    delta = 1000.0 * (current - last_timestamp)/CLOCKS_PER_SEC;
    if (delta < 25) return;
    /* do the following every 250 ms */

    /* rotate the wheel by 20 degrees */
    wheel_cf = glm::rotate(wheel_cf, 10.0f, 0.0f, 1.0f, 0.0f);

    /* use the pendulum equation to calculate its angle */
    float angle = INIT_SWING_ANGLE *
        cos (swing_time * sqrt(swingarm->length()/GRAVITY) * M_PI / 180.0);
    swing_time += 10;
    swing_cf = glm::rotate(angle, 0.0f, 1.0f, 0.0f);
    last_timestamp = current;


    /* make sure we refresh the main window, and these two functions must
     * be called prior to any other OpenGL call(s) that modify the
     * ModelView matrix */
    glutSetWindow (glut_win);
    /* Mark the main window for redisplay */
    glutPostRedisplay();
}

void myGLInit ()
{
    glClearColor (0.0, 0.0, 0.0, 1.0); /* black background */

    /* fill front-facing polygon */
    glPolygonMode (GL_FRONT, GL_FILL);
    /* draw outline of back-facing polygon */
    glPolygonMode (GL_BACK, GL_LINE);

    /* Enable depth test for hidden surface removal */
    glEnable (GL_DEPTH_TEST);

    /* enable back-face culling */
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);

    /* Enable shading */
    glEnable (GL_LIGHTING);
    glEnable (GL_NORMALIZE); /* Tell OpenGL to renormalize normal vector
                              after transformation */
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    /* initialize two light sources */
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light0_color);
    glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light1_color);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light1_color);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light1_color);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 40);
}

/*--------------------------------*
 * GLUT display callback function *
 *--------------------------------*/
void displayCallback ()
{
    /* clear the window */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadMatrixf(&camera_cf[0][0]);
    /* place the light source in the scene. */
    glLightfv (GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv (GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);

    glPushMatrix();
    glTranslatef (light0_pos[0], light0_pos[1], light0_pos[2]);
    glutSolidSphere(0.5, 20, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef (light1_pos[0], light1_pos[1], light1_pos[2]);
    glRotatef(90, 1, 0, 0);
    spot->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0, 0, 10);
    /* The following matrix multiplication technique is easy to do
     */
    glPushMatrix();
    glMultMatrixf(&swing_cf[0][0]);
    glMultMatrixf(&wheel_cf[0][0]);
    wheel->draw();
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf(&swing_cf[0][0]);
    swingarm->draw();
    glPopMatrix();

    glPopMatrix();
    /* to make smooth transition between frame */
    glutSwapBuffers ();
}

void myModelInit ()
{
    spot = new Cylinder(1 + tan(40.0*M_PI/180.0), 1, 2);
    spot->newInstance();
    spot->setColor(light1_color[0], light1_color[1], light1_color[2]);
    
    wheel = new Wheel();
    wheel->newInstance();
    wheel_cf = glm::translate(wheel_cf, 0.0f, 0.0f, -swingarm->length());

    swingarm = new Arm;
    swingarm->newInstance();
    swingarm->setColor(1.0, 0.65, 0.342);
    swing_cf = glm::rotate(swing_cf, INIT_SWING_ANGLE, 0.0f, 1.0f, 0.0f);
}

void fkeyCallback (int key, int x, int y)
{
    int mode = glutGetModifiers();
    if (mode == GLUT_ACTIVE_SHIFT) {
        switch (key) {
            case GLUT_KEY_UP: /* pull up closer */
                camera_cf = glm::translate(0.0f, 0.0f, +1.0f) * camera_cf;
                break;
            case GLUT_KEY_DOWN: /* move back farther */
                camera_cf = glm::translate(0.0f, 0.0f, -1.0f) * camera_cf;
                break;
            case GLUT_KEY_LEFT: /* pan left */
                camera_cf = glm::rotate(-10.0f, 0.0f, 1.0f, 0.0f) * camera_cf;
                break;
            case GLUT_KEY_RIGHT: /* pan right */
                camera_cf = glm::rotate(+10.0f, 0.0f, 1.0f, 0.0f) * camera_cf;
                break;

            default:
                break;
        }
        glutPostRedisplay();
    }
    else {

    }
}

void keyCallback (unsigned char key, int, int)
{
    switch (key)
    {
        case 0x1B:
            exit(0);
        case '0':
            if (glIsEnabled(GL_LIGHT0))
                glDisable(GL_LIGHT0);
            else
                glEnable(GL_LIGHT0);
            break;
        case '1':
            if (glIsEnabled(GL_LIGHT1))
                glDisable(GL_LIGHT1);
            else
                glEnable(GL_LIGHT1);
            break;

        case 'p': /* pause the animation */
            if (is_idle_active)
                glutIdleFunc(NULL);
            else
                glutIdleFunc(idleCallback);
            is_idle_active ^= true;
            break;
    }
    glutPostRedisplay();
}

int main (int argc, char **argv)
{

    /* Standard GLUT initialization */
    glutInit (&argc, argv);
    /* double buffer, RGB color mode, hidden surface removal */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize (800, 600); /* 500 x 500 pixel window */
    glutInitWindowPosition (0, 0); /* place window top left on display */

    glut_win = glutCreateWindow ("CS367 Computer Graphics");
    srand (getpid());
    
    myGLInit ();
    myModelInit ();
    
    /* setup display callback function */
    glutIdleFunc (idleCallback);
    glutDisplayFunc (displayCallback);
    glutReshapeFunc (reshapeCallback);
    glutKeyboardFunc (keyCallback);
    glutSpecialFunc(fkeyCallback);
    
    glutMainLoop ();
}
