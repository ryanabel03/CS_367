//
//  Arm.cpp
//  Animation
//
//  Created by Hans Dulimarta on 02/18/13.
//
//

#include "Arm.h"
const float LENGTH = 20.0;
Arm::Arm()
{

}

Arm::~Arm()
{
    gluDeleteQuadric(cyl_quad);
}

void Arm::newInstance()
{
    list_id = glGenLists(1);
    cyl_quad = gluNewQuadric();
    glNewList(list_id, GL_COMPILE);
    /* gluCylinder creates the cylinder along the Z-pos (Z=0 to Z=LENGTH). 
       We want to make the arm along the Z-neg. So 180 rotation is needed
     */
    glRotatef(180, 1, 0, 0);
    gluCylinder(cyl_quad, 0.2, 0.2, LENGTH, 20, 25);
    glEndList();
}

void Arm::draw()
{
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    Model::draw();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, +0.5, 0);
    Model::draw();
    glPopMatrix();
}

float Arm::length() const {
    return LENGTH;
}