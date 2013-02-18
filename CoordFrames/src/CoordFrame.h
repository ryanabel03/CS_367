//
//  CoordFrame.h
//  CoordFrames
//
//  Created by Hans Dulimarta on 02/16/13.
//
//

#ifndef __CoordFrames__CoordFrame__
#define __CoordFrames__CoordFrame__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transformation.h"

using namespace glm;
class CoordFrame {
public:
    /* Use the Strategy design pattern to handle various transformation
     * operations */
    void execute (Transformation*, bool);

    mat4 getMatrix() {
        return frame;
    }
    
    void setMatrix(const mat4& f) {
        frame = f;
    }
    mat4::value_type* getData() {
        return glm::value_ptr(frame);
    }
private:
    mat4 frame;
};
#endif /* defined(__CoordFrames__CoordFrame__) */
