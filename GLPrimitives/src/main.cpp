/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: dulimarh
 */

#include <GL/glut.h>
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
bool isDragging;
float bgColor[3];

void render(void)
{
//	cout << __PRETTY_FUNCTION__ << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	if (w <= h) {
		ratio = static_cast<GLfloat> (h) / w;
		gluOrtho2D(-4.0, 4.0, -4.0 * ratio, 4.0 * ratio);
	}
	else {
		ratio = static_cast<GLfloat> (w) / h;
		gluOrtho2D(-4.0 * ratio, 4.0 * ratio, -4.0, 4.0);
	}
	glGetDoublev(GL_PROJECTION_MATRIX, prMatrix);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
}

void mouseHandler(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON)
		return;
	/* only when the left mouse is down */
	if (state == GLUT_DOWN) {
		/* Use Shift-LeftMouse to add a vertex */
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			GLdouble wx, wy, wz;

			/* (x,y) is the position of the mouse on the SCREEN where
			 * y is positive towards the bottom of the screen.
			 *
			 * Use "unproject" to convert the screen coordinate to
			 * the world coordinate. Modify the y-input so it is zero
			 * at the bottom of the screen and positive at the top
			 * of the screen
			 */
			gluUnProject(x, viewport[3] - y - 1, 0.0, mvMatrix, prMatrix,
					viewport, &wx, &wy, &wz);

			/* store the vertex position (in the world coordinate) */
			vertices.push_back(std::make_pair(wx, wy));
			glutPostRedisplay(); /* request display refresh */
		}
	}
	isDragging = state == GLUT_DOWN;
}

void mouseMotionHandler (int x, int y)
{
	if (!isDragging) return;
	/* we can use the following for later ! */
	cout << __PRETTY_FUNCTION__ << " mouse drag " <<  x << " " << y << endl;
}

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

void initStates()
{
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



