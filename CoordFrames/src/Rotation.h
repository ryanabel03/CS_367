//
//  Rotation.h
//
//  Created by Hans Dulimarta on 02/16/13.
//
//

#ifndef CF_ROTATION_H
#define CF_ROTATION_H

#include "Transformation.h"

class Rotation : public Transformation {
public:
    Rotation (float angle, float ax, float ay, float az);

    void pre_transform (CoordFrame* cf);
    void post_transform (CoordFrame* cf);
private:
    float angle, ax, ay, az;
};


#endif
