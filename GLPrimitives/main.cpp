/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: dulimarh
 */

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
typedef pair<GLdouble, GLdouble> Pos2D;

GLint viewport[4];
GLdouble mvMatrix[16];
GLdouble prMatrix[16];
vector<Pos2D> vertices;

void render(void)
{
	cout << __PRETTY_FUNCTION__ << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(255, 255, 0);
	glBegin(GL_LINE_LOOP);
	std::vector<Pos2D>::const_iterator vit;
	for (vit = vertices.begin(); vit != vertices.end(); ++vit)
		glVertex2d(vit->first, vit->second);
	glEnd();
	glutSwapBuffers();
}

void resize (int w, int h)
{
	glViewport(0, 0, (GLint) w, (GLint) h);
	glGetIntegerv(GL_VIEWPORT, viewport);
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

void mouseHandler (int button, int state, int x, int y)
{
//	cout << __PRETTY_FUNCTION__ << endl;
	GLdouble wx, wy, wz;
	gluUnProject(x, viewport[3] - y - 1, 0.0, mvMatrix, prMatrix, viewport,
			&wx, &wy, &wz);
//	cout << x << "," << y << " => " << wx << ", " << wy << endl;
	vertices.push_back(std::make_pair(wx, wy));
	glutPostRedisplay();
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (400, 300);
	glutCreateWindow("Simple GLUT");

	/* initial setup */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3.0);
	glPointSize(4.0);
	glPolygonMode(GL_BACK, GL_LINE);
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseHandler);
	glutMainLoop();
}



