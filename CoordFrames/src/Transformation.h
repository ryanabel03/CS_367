//
//  Transformation.h
//  CoordFrames
//
//  Created by Hans Dulimarta on 02/16/13.
//
//

#ifndef __CoordFrames__Transformation__
#define __CoordFrames__Transformation__
#include <glm/glm.hpp>

class CoordFrame;
class Transformation {
public:
    virtual ~Transformation() {}
    virtual void pre_transform(CoordFrame*) = 0;
    virtual void post_transform(CoordFrame*) = 0;
};
#endif /* defined(__CoordFrames__Transformation__) */
