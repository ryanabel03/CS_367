//
//  CoordFrame.cpp
//  CoordFrames
//
//  Created by Hans Dulimarta on 02/16/13.
//
//

#include "CoordFrame.h"

void CoordFrame::execute (Transformation* t) {
    t->transform(this);
}

