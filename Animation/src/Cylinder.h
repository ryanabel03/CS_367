#ifndef HANS_CYLINDER_H
#define HANS_CYLINDER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "Model.h"

/* Cylinder with different top and base radius */
class Cylinder : public Model {
   public:
      /* default size is unit box */
      Cylinder(GLfloat _toprad = 1, GLfloat _baserad = 1, 
            GLfloat _ht = 1.0);
      void newInstance();

   private:
      static const int NSIDE;
      GLfloat height, top_rad, base_rad;
};
#endif
