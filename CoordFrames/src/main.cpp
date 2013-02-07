/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: Hans Dulimarta <dulimarh@cis.gvsu.edu>
 */

#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;
typedef pair<GLdouble, GLdouble> Pos2D;
void showHelp();
enum MenuEntries {
    MENU_CLEAR,
    MENU_EXIT};

GLint viewport[4];
GLdouble mvMatrix[16];
GLdouble prMatrix[16];
GLdouble potCoordFrame[16];  /* teapot coordinate frame */
vector<Pos2D> vertices;
map<MenuEntries,unsigned int> menuMap;

float bgColor[3];
int potlist, cf_list, arrow_list; /* teapot and coordinate frame */

void printMatrix(double[]);
/********************************************************************/
// Display callback
/********************************************************************/
void render(void)
{
//	cout << __PRETTY_FUNCTION__ << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    showHelp();

    glCallList(cf_list);
    glPushMatrix();
    /* transform the teapot using its own frame */
    
    // glLoadMatrixd(potCoordinateFrame); <== WRONG function used in class
    glMultMatrixd(potCoordFrame);
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
    gluPerspective(60, (float)w/h, 1, 10);
#endif
    
	glGetDoublev(GL_PROJECTION_MATRIX, prMatrix);
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
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
}

/********************************************************************/
// Keyboard callback
/********************************************************************/
void keyHandler (unsigned char ch, int x, int y)
{
    cout << glutGetModifiers() << endl;
    switch (ch)
    {
        case 0x1B: /* escape key */
            exit (0);
            break;
        case 'z': /* rotate around the world Z-axis */
            /* in the following code we use openGL matrix calls to
             * perform the following multiplication:
             *
             *  F = Rot x F
             *
             *  [the effect is to rotate our coordinate frame around
             *   the WORLD axis]
             *  where F is our own coordinate frame and
             *  Rot is the openGL rotation
             */

            glPushMatrix();
            glLoadIdentity();
            glRotatef (10, 0, 0, 1);
            glMultMatrixd(potCoordFrame);
            glGetDoublev(GL_MODELVIEW_MATRIX, potCoordFrame);
            glPopMatrix();
            break;
        case 'Z': /* rotate around the world Z-axis */
            glPushMatrix();
            glLoadIdentity();
            glRotatef (-10, 0, 0, 1);
            glMultMatrixd(potCoordFrame);
            glGetDoublev(GL_MODELVIEW_MATRIX, potCoordFrame);
            glPopMatrix();
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
    glPushMatrix();
    glLoadMatrixd(potCoordFrame);    /* C = potCF              */
    if (mod == GLUT_ACTIVE_SHIFT) {
        switch (key) {
            case GLUT_KEY_UP: /* pitch-up */
                glRotatef(-20, 0, 0, 1);
                break;
            case GLUT_KEY_DOWN: /* pitch-down */
                glRotatef(20, 0, 0, 1);
                break;
            case GLUT_KEY_LEFT:
                glRotatef(20, 0, 1, 0); /* yaw */
                break;
            case GLUT_KEY_RIGHT:
                glRotatef(-20, 0, 1, 0); /* yaw */
                break;
        }
    }
    else {
        switch (key) {
            case GLUT_KEY_UP: /* move forward */
                /* multiply the teapot frame with X-translate */
                glTranslated(0.5, 0, 0);       /* C = pot_CF * Translate */
                break;
            case GLUT_KEY_DOWN: /* move backward */
                glTranslated(-0.5, 0, 0);      /* C = pot_CF * Translate */
                break;
            case GLUT_KEY_LEFT:   /* roll */
                glRotatef(-20, 1, 0, 0);       /* C = pot_CF * rot-x */
                break;
            case GLUT_KEY_RIGHT:  /* roll */
                glRotatef(+20, 1, 0, 0);       /* C = pot_CF * rot-x */
                break;
        }

    }
    glGetDoublev(GL_MODELVIEW_MATRIX, potCoordFrame); /* potCF = C */
    glPopMatrix();
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

void showText (int x, int y, string msg)
{
    /* color must be set BEFORE glWindowPos* !!!!! */
    glColor3f(1,1,1); /* white text */
    /* Use the window coordinates to place the text */
    glWindowPos2i(x, y);
    for (int k = 0; k < msg.length(); k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[k]);
}

void showHelp()
{
    showText(5, 5, "Welcome...");
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
    glCallList(cf_list);

    glColor3ub(170, 195, 92);
    glutSolidTeapot(1.0);
    glEndList();
    fill (bgColor, bgColor + 3, 0.0);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

    glLineWidth(2.0);
    glPointSize(3.0);

    /* use glLoadIdentity to initialize my teapot CF */
    glPushMatrix();
    glLoadIdentity();                                   /* C = I     */
    glGetDoublev(GL_MODELVIEW_MATRIX, potCoordFrame);   /* potCF = C */
    glPopMatrix();

    
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
    glutInitWindowSize (600, 450);
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



