//
//  CoordFrame.cpp
//  CoordFrames
//
//  Created by Hans Dulimarta on 02/16/13.
//
//

#include "CoordFrame.h"

void CoordFrame::execute (Transformation* t, bool isPostOperate) {
    if (isPostOperate)
        t->post_transform(this);
    else
        t->pre_transform(this);
}

