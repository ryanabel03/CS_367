#include <cstdlib>
#include <cmath>
#include "Cylinder.h"
#include <glm/glm.hpp>
const int Cylinder::NSIDE = 20;

Cylinder::Cylinder (GLfloat _trad, GLfloat _brad, GLfloat _ht)
{
    top_rad = _trad;
    base_rad = _brad;
    height = _ht;
}

/*---------------------------------------------------*
 * Make a unit one (a cone that fits in a unit cube) *
 *---------------------------------------------------*/
void Cylinder::newInstance ()
{
    int k;
    glm::vec3 v1, v2, v3, v4, normal;
    float angle;
    list_id = glGenLists(1);

    /* the base of the cone is on the XY-plane, the apex on the
     * positive-Z axis */
    glNewList (list_id, GL_COMPILE);

    /* build the top cover */
    glNormal3f (0, 0, 1); /* normal of the top cover is +Z axis */
    glBegin (GL_POLYGON);
    for (k = 0; k < NSIDE; k++) {
        angle = k * 2 * M_PI / NSIDE;
        glVertex3f (top_rad * cos(angle), top_rad * sin(angle), height);
    }
    glEnd();
    /* first make the base of the cylinder */
    glNormal3f (0, 0, -1);
    glBegin (GL_POLYGON);
    for (k = 0; k < NSIDE; k++) {
        angle = k * 2 * M_PI / NSIDE;
        glVertex3f (base_rad * cos(angle), base_rad * sin(-angle), 0);
    }
    glEnd();

    glBegin (GL_QUAD_STRIP);
    v1 = glm::vec3(top_rad, 0, height);
    v2 = glm::vec3 (base_rad, 0, 0);
    for (k = 1; k <= NSIDE; k++) {
        angle = k * 2 * M_PI / NSIDE;
        v3 = glm::vec3 (top_rad * cos(angle), top_rad * sin(angle), height);
        v4 = glm::vec3 (base_rad * cos(angle), base_rad * sin(angle), 0);

        /* Use Algebra3.h */
        normal = glm::normalize(glm::cross(v1 - v2, v2 - v4));

        glNormal3f (normal[0], normal[1], normal[2]);
        glVertex3f (v1[0], v1[1], v1[2]);
        glVertex3f (v2[0], v2[1], v2[2]);
        v1 = v3;
        v2 = v4;
    }
    glVertex3f (v1[0], v1[1], v1[2]);
    glVertex3f (v2[0], v2[1], v2[2]);
    glEnd();
    glEndList();
}
