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

enum MenuEntries {MENU_PRIMITIVE_POINTS, MENU_PRIMITIVE_LINES,
    MENU_PRIMITIVE_LINE_STRIP,
    MENU_PRIMITIVE_LOOP,
    MENU_PRIMITIVE_TRIANGLES,
    MENU_PRIMITIVE_TRIANGLE_STRIP,
    MENU_PRIMITIVE_FAN,
    MENU_PRIMITIVE_QUADS,
    MENU_PRIMITIVE_QUAD_STRIP,
    MENU_CLEAR,
    MENU_EXIT};

GLint viewport[4];
GLdouble mvMatrix[16];
GLdouble prMatrix[16];
MenuEntries current_primitive;
vector<Pos2D> vertices;
map<MenuEntries,unsigned int> menuMap;
int tri_list, c_list; /* declare the two list handles */
int ct_list;
bool isDragging;
float bgColor[3];

/********************************************************************/
// Display callback
/********************************************************************/
void render(void)
{
//	cout << __PRETTY_FUNCTION__ << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef (-0.5, 0, 0.0);
    glScalef(0.5, 1.0, 1);
    glCallList(ct_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0.5, 0, 0);
    glRotatef(30, 1, 0, 0);  /* rotate 30 around the x-axis */
    glCallList(ct_list);
    glPopMatrix();

	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3ub(255, 255, 0); /* render filled polygons in yellow */
	glBegin(menuMap[current_primitive]);
	std::vector<Pos2D>::const_iterator vit;
	for (vit = vertices.begin(); vit != vertices.end(); ++vit)
		glVertex2d(vit->first, vit->second);
	glEnd();

    
	if (current_primitive >= MENU_PRIMITIVE_TRIANGLES) {
		/* render the wireframe outline of the polygons in green */
		glPolygonMode(GL_FRONT, GL_LINE);
		glColor3ub(0, 255, 0);
		glBegin(menuMap[current_primitive]);
		std::vector<Pos2D>::const_iterator vit;
		for (vit = vertices.begin(); vit != vertices.end(); ++vit)
			glVertex2d(vit->first, vit->second);
		glEnd();
	}
	/* Label the points with numbers */
	for (int k = 0; k < vertices.size(); k++)
	{
		ostringstream ss;
		ss << k;
		string num = ss.str();
		glRasterPos2d(vertices[k].first, vertices[k].second);
		for (int m = 0; m < num.length(); m++)
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num[m]);
	}
	glutSwapBuffers();
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

	GLfloat ratio;
#if 0
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
#if 1
    gluLookAt(0, 0, 5.0, 0, 0, 0, 0, 1, 0);
#endif
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
}

#if 0
The "magic" behind gluUnProject:

Imagine your pupil (right or left) is the (0,0,0) of the camera
coordinate frame.
Now select a point on this screen and draw an infinite ray between
your pupil and the point and the screen. This ray will intersect
the view volume at the near plane (R) and far plane (S). Which intersection
returned depends on the third argument passed to gluUnproject (0.0) returns
the near intersection and 1.0 returns the far intersection.

gluUnproject calculates the coordinates of R and S with respect to the WORLD
coordinate frame.
#endif

/********************************************************************/
// Mouse callback
/********************************************************************/
void mouseHandler(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON)
		return;
	/* only when the left mouse is down */
	if (state == GLUT_DOWN) {
		/* Use Shift-LeftMouse to add a vertex */
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			GLdouble wx1, wy1, wz1;
            GLdouble wx0, wy0, wz0;

			/* (x,y) is the position of the mouse on the SCREEN where
			 * y is positive towards the bottom of the screen.
			 *
             * Modify the y-input so it is zero
			 * at the bottom of the screen and positive at the top
			 * of the screen
			 */
            /* determine the world coordinate of our eye projection on the
             * far plane */
			gluUnProject(x, viewport[3] - y - 1, 1.0, mvMatrix, prMatrix,
					viewport, &wx1, &wy1, &wz1);

            /* determine the world coordinate of our eye projection on the
             * near plane */
			gluUnProject(x, viewport[3] - y - 1, 0.0, mvMatrix, prMatrix,
                         viewport, &wx0, &wy0, &wz0);


            /* the parametric equation of the eye ray is
             *
             * [ x ]   [ wx0 ]          [ wx1 - wx0 ]
             * [ y ] = [ wy0 ]  + alpha [ wy1 - wy0 ]
             * [ z ]   [ wz0 ]          [ wz1 - wz0 ]
             *
             * to determine where the above line intersects the XY plane,
             * we set z to zero and solve for alpha. Then we can calculate
             *    x = wx0 + alpha (wx1 - wx0)
             *    y = wy0 + alpha (wy1 - wy0)
             */
            double alpha = wz0 /(wz0 - wz1);
			vertices.push_back(std::make_pair(wx0 + alpha * (wx1 - wx0),
                                              wy0 + alpha * (wy1 - wy0)));
			/* store the vertex position (in the world coordinate) */
			glutPostRedisplay(); /* request display refresh */
		}
	}
	isDragging = state == GLUT_DOWN;
}


void mouseMotionHandler (int x, int y)
{
    if (!isDragging) return;
    /* we can use the following for later ! */
    //cout << __PRETTY_FUNCTION__ << " mouse drag " <<  x << " " << y << endl;
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
    }

}

void fkeyHandler (int key, int x, int y)
{
    if (key == GLUT_KEY_F12)
        exit (0);
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

void primitiveSelector (int select)
{
    current_primitive = (MenuEntries)select;
    glutPostRedisplay(); /* request display refresh */
}

/********************************************************************/
// Initialization routines
/********************************************************************/
void initStates()
{
    /* create two separate display lists */
    tri_list = glGenLists(1);
    c_list = glGenLists(1);

    /* populate each list here, compile only do not execute the list */
    glNewList(tri_list, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.4, 1.0);
    glVertex2f(-0.4, 1.0);
    glVertex2f(0.0, -1.0);
    glEnd();
    glEndList();

    /* populate each list here */
    glNewList(c_list, GL_COMPILE);
    /* letter C (crooked!) */
    glBegin(GL_QUAD_STRIP);
    glColor3f (1.0, .4, .25);
    glVertex2f(0.5, 0.5);
    glColor3f (0.8, .4, .75);
    glVertex2f(0.6, 0.6);
    glColor3f (1.0, .5, .25);
    glVertex2f(0.1, 0.5);
    glColor3f (0.7, .4, .75);
    glVertex2f(0.05, 0.8);
    glColor3f (1.0, .6, .25);
    glVertex2f(-0.2, 0.3);
    glColor3f (0.6, .4, .75);
    glVertex2f(-0.5, 0.6);
    glColor3f (1.0, .7, .25);
    glVertex2f(-0.3, 0);
    glColor3f (0.5, .4, .75);
    glVertex2f(-0.75, 0);
    glColor3f (1.0, .8, .25);
    glVertex2f(-0.3, -0.3);
    glColor3f (0.4, .4, .75);
    glVertex2f(-0.5, -0.7);
    glColor3f (1.0, .9, .25);
    glVertex2f(0.2, -0.45);
    glColor3f (0.3, .4, .75);
    glVertex2f(0.2, -0.8);
    glEnd();
    glEndList();


    ct_list = glGenLists(1);
    glNewList(ct_list, GL_COMPILE);
    glCallList(tri_list);   /* render the triangle in the list */
    glPushMatrix();
    glTranslatef(-0.4, 1.0, 0.1);
    glRotatef(-60, 0, 0, 1);
    glCallList(c_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, 1.0, 0);
    glRotatef(-120, 0, 0, 1);
    glCallList(c_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -1.0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(0.4, 0.4, 1.0);
    glCallList(c_list);
    glPopMatrix();

    glEndList();

    current_primitive = MENU_PRIMITIVE_POINTS;
    isDragging = false;
    fill (bgColor, bgColor + 3, 0.0);

    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

    glLineWidth(2.0);
    glPointSize(3.0);

    /* render front polygons (CCW) as filled faces */
    glPolygonMode(GL_FRONT, GL_FILL);

    /* render back polygon (CW) as outline */
    glPolygonMode(GL_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

}

void initMenus()
{
    int primMenu;
    primMenu = glutCreateMenu(primitiveSelector);
    glutAddMenuEntry("Points", MENU_PRIMITIVE_POINTS);
    glutAddMenuEntry("Lines", MENU_PRIMITIVE_LINES);
    glutAddMenuEntry("Line Loop", MENU_PRIMITIVE_LOOP);
    glutAddMenuEntry("Line Strip", MENU_PRIMITIVE_LINE_STRIP);
    glutAddMenuEntry("Triangles", MENU_PRIMITIVE_TRIANGLES);
    glutAddMenuEntry("Triangle Strip", MENU_PRIMITIVE_TRIANGLE_STRIP);
    glutAddMenuEntry("Quads", MENU_PRIMITIVE_QUADS);
    glutAddMenuEntry("Quad Strip", MENU_PRIMITIVE_QUAD_STRIP);
    glutAddMenuEntry("Triangle Fan", MENU_PRIMITIVE_FAN);

    menuMap[MENU_PRIMITIVE_POINTS] = GL_POINTS;
    menuMap[MENU_PRIMITIVE_LINES] = GL_LINES;
    menuMap[MENU_PRIMITIVE_LOOP] = GL_LINE_LOOP;
    menuMap[MENU_PRIMITIVE_LINE_STRIP] = GL_LINE_STRIP;
    menuMap[MENU_PRIMITIVE_TRIANGLES] = GL_TRIANGLES;
    menuMap[MENU_PRIMITIVE_TRIANGLE_STRIP] = GL_TRIANGLE_STRIP;
    menuMap[MENU_PRIMITIVE_FAN] = GL_TRIANGLE_FAN;
    menuMap[MENU_PRIMITIVE_QUADS] = GL_QUADS;
    menuMap[MENU_PRIMITIVE_QUAD_STRIP] = GL_QUAD_STRIP;

    glutCreateMenu(topMenuHandler);
    glutAddSubMenu("Primitives", primMenu);
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
    glutCreateWindow("Simple GLUT");

    /* initial setup */
    initStates();
    initMenus();

    /* setup callback functions */
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyHandler);
    glutSpecialFunc(fkeyHandler);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(mouseMotionHandler);
    glutMainLoop();
}



