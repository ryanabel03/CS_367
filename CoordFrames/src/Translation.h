//
//  Translation.h
//
//  Created by Hans Dulimarta on 02/16/13.
//
//

#ifndef CoordFrames_Translate_h
#define CoordFrames_Translate_h

#include "Transformation.h"

class Translation : public Transformation {
public:
    Translation (float tx, float ty, float tz);

    void pre_transform (CoordFrame* cf);
    void post_transform (CoordFrame* cf);
private:
    float tx, ty, tz;
};


#endif
