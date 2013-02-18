#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Translation.h"
#include "CoordFrame.h"

Translation::Translation (float tx, float ty, float tz)
{
    this->tx = tx;
    this->ty = ty;
    this->tz = tz;
}

void Translation::transform (CoordFrame* cf) {
    glm::mat4 m;
    m = glm::translate(cf->getMatrix(), tx, ty, tz);
    cf->setMatrix(m);
}
