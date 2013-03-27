#ifndef HANS_WHEEL_H
#define HANS_WHEEL_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "Model.h"

/* Wheel : torus  + spokes */
class Wheel : public Model {
   public:
      /* default size is unit box */
      Wheel();
      void newInstance();
      GLfloat getRadius() const { return radius; }
      GLfloat getThickness() const { return tire_thickness; }
   private:
      GLfloat radius;
      GLfloat tire_thickness;
};
#endif
