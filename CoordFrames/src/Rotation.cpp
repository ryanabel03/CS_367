#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Rotation.h"
#include "CoordFrame.h"

Rotation::Rotation (float a, float ax, float ay, float az)
{
    this->angle = a;
    this->ax = ax;
    this->ay = ay;
    this->az = az;
}

void Rotation::transform (CoordFrame* cf) {
    glm::mat4 m;
    m = glm::rotate(cf->getMatrix(), angle, ax, ay, az);
    cf->setMatrix(m);
}
