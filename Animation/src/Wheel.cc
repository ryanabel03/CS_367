#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include "Wheel.h"
#include "Cylinder.h"

Wheel::Wheel()
{
    radius = 3.5;
    tire_thickness = 0.4;
}

/*-------------------------------*
 * Make a wheel for the unicycle *
 *-------------------------------*/
void Wheel::newInstance ()
{
    const int NUM_SPOKES = 5;
    /* black rubber */
    Cylinder * spoke;

    spoke = new Cylinder (.5, .5, 1);
    spoke->setColor (0.75, 0.75, 0.75);
    spoke->newInstance();

    list_id = glGenLists(1);
    glNewList (list_id, GL_COMPILE);
    glPushMatrix();
    glRotatef (90, 1, 0, 0);

    glColor3ub (70,40, 40);
    glutSolidTorus (tire_thickness, radius, 10, 30);

    /* make the spokes */
    for (int k = 0; k < NUM_SPOKES; k++)
    {
        float angle = k * 360.0 / NUM_SPOKES;
        glPushMatrix();
        glRotatef (angle, 0, 0, 1);
        glRotatef (-90, 0, 1, 0);
        glScalef (0.75 * tire_thickness, 0.75 * tire_thickness,
                  radius - 0.2);
        spoke->draw();
        glPopMatrix();
    }
    /* make the hub */
    glPushMatrix();
    glTranslatef (0, 0, -tire_thickness/2);
    glScalef (0.3 * radius, 0.3 * radius, tire_thickness);
    spoke->draw();
    glPopMatrix();
    glPopMatrix();
    glEndList();
}

