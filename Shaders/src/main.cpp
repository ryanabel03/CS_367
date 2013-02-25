/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: Hans Dulimarta <dulimarh@cis.gvsu.edu>
 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include "Shader.h"
using namespace std;

Shader vertex;
Shader fragment;
int prog;

/********************************************************************/
// Display callback
/********************************************************************/
void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(1.0);
	glutSwapBuffers();
}

/********************************************************************/
// Resize callback
/********************************************************************/
void resize (int w, int h)
{
	glViewport(0, 0, (GLint) w, (GLint) h);
	/* viewport[2] = width of the window
	 * viewport[3] = height of the window
	 */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(60, (float)w/h, 1, 10);

    /* always switch back to MODELVIEW matrix mode !!!! */
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
    /* glLoadIdentity(): use the default camera placement: eye at origin,
       the camera is viewing along the NEGATIVE z-axis, 
       and the camera Y-axis (its "up" axis) is parallel to the world Y-axis
     */
    /* gluLookAt: move the eye to (0, 0, 5) */
    gluLookAt(0, 3, 5.0, 0, 0, 0, 0, 1, 0);
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
        case 'w':
            glPolygonMode(GL_FRONT, GL_LINE);
            break;
        case 'W':
            glPolygonMode(GL_FRONT, GL_FILL);
            break;
    }
    glutPostRedisplay();
    
}

/********************************************************************/
// Initialization routines
/********************************************************************/
void initStates()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);


    /* render front polygons (CCW) as filled faces */
    glPolygonMode(GL_FRONT, GL_FILL);

    /* render back polygon (CW) as outline */
    glPolygonMode(GL_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /* Enable use of vertex pointer */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

}

void initShaders()
{
    vertex.load ("../../src/vshader.vs", GL_VERTEX_SHADER);
    fragment.load ("../../src/fshader.fs", GL_FRAGMENT_SHADER);
    prog = glCreateProgram();
    glAttachShader(prog, vertex.id());
    glAttachShader(prog, fragment.id());
    glLinkProgram(prog);

    GLint status;
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status)
        glUseProgram(prog);
    else {
        int len;
        char *log;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        log = new char[len];
        glGetProgramInfoLog(prog, len, &len, log);
        cout << "Link log: " << log << endl;
        delete [] log;
    }
}

void on_exit()
{
    cout << "Cleaning up ..." << endl;
    glDetachShader(prog, vertex.id());
    glDetachShader(prog, fragment.id());
    glDeleteProgram(prog);
}

int main (int argc, char** argv)
{
    atexit(on_exit);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (600, 450);
    glutCreateWindow("Simple GLUT");
    cout << "Your OpenGL version is " << glGetString(GL_VERSION) << endl;

    /* initial setup */
    initStates();
    initShaders();

    /* setup callback functions */
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyHandler);
//    glutIdleFunc(idleHandler);
    glutMainLoop();
}



