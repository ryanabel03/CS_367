//
//  Arm.h
//  Animation
//
//  Created by Hans Dulimarta on 02/18/13.
//
//

#ifndef __Animation__Arm__
#define __Animation__Arm__

#include <iostream>
#include "Model.h"
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
class Arm : public Model {
public:
    Arm();
    ~Arm();
    void newInstance();
    void draw();
    float length() const;
private:
    GLUquadric* cyl_quad;
};
#endif /* defined(__Animation__Arm__) */
