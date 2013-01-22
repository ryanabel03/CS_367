
/**
 * This class is designed as the parent class for both WorldView and
 * CameraView. The only important function in this class is
 * initializeGL().
 */
#include <GL/glut.h>
#include <iostream>
#include <utility>
#include <qgl.h>
//#include <boost/numeric/ublas/vector.hpp>
#include "GLPanel.h"
#include <algorithm>

using namespace std;

//using namespace boost::numeric::ublas;

GLPanel::GLPanel (QWidget * parent, const char *name):QGLWidget (parent,
   name),
eye (3),
focus (3)
{
   eye[0] = eye[1] = 0;
   eye[2] = 2;
   focus[0] = focus[1] = focus[2] = 0;

   /* trsf is a pointer an STL vector. Each element of the vector is a
    * pointer to a GLTransform object */
   trsf = 0;
   stepMode = 1;                /* step mode is initialize to "local/forward" */
   current_step = 0;
}

void GLPanel::setStepMode (int x)
{
   stepMode = x;
}

void GLPanel::setTransformation (std::vector < GLTransform * >*t)
{
   /* trsf is a pointer to an STL vector */

   trsf = t;
}

void GLPanel::setFocusX (int d)
{
   focus[0] = (GLdouble) d / 10;
   updateGL ();
}

void GLPanel::setFocusY (int d)
{
   focus[1] = (GLdouble) d / -10;
   updateGL ();
}

void GLPanel::initializeGL ()
{
   static bool done = false;
   if (done)
      return;
   done = true;

   glEnable (GL_DEPTH_TEST);
   glClearColor (0.0, 0.0, 0.0, 1.0); /* black background */
   glLineWidth (2.0);
   //glPointSize (2.0);
   //glCullFace (GL_BACK);
   //glEnable (GL_CULL_FACE);

   /* always show back face of polygons as outline */
   glPolygonMode (GL_BACK, GL_LINE);
   glPolygonMode (GL_FRONT, GL_FILL);

   /* the following trick is needed to allow us to use GLUT functions */
   int c = 0;
   glutInit (&c, NULL);

   /* define the points for the letter 'D' */
   std::vector < std::pair < GLdouble, GLdouble > >outer, inner;
   outer.push_back (std::make_pair (0.0, 0.0));
   outer.push_back (std::make_pair (0.8, 0.0));
   outer.push_back (std::make_pair (1.0, 0.2));
   outer.push_back (std::make_pair (1.0, 0.8));
   outer.push_back (std::make_pair (0.8, 1.0));
   outer.push_back (std::make_pair (0.0, 1.0));
   outer.push_back (std::make_pair (0.0, 0.0));

   inner.push_back (std::make_pair (0.2, 0.2));
   inner.push_back (std::make_pair (0.7, 0.2));
   inner.push_back (std::make_pair (0.8, 0.3));
   inner.push_back (std::make_pair (0.8, 0.7));
   inner.push_back (std::make_pair (0.7, 0.8));
   inner.push_back (std::make_pair (0.2, 0.8));
   inner.push_back (std::make_pair (0.2, 0.2));

   /* create and populate the list of letter 'D' */
   D_list = glGenLists (1);
   glNewList (D_list, GL_COMPILE);
   glBegin (GL_QUAD_STRIP);
   for (unsigned int k = 0; k < outer.size (); ++k) {
      glVertex2d (inner[k].first, inner[k].second);
      glVertex2d (outer[k].first, outer[k].second);
   }
   glEnd ();
   glBegin (GL_QUAD_STRIP);
   for (unsigned int k = 0; k < outer.size (); ++k) {
      glColor4ub (189, 189, 49, 127);
      glVertex3d (inner[k].first, inner[k].second, -0.5);
      glColor4ub (131, 87, 25, 127);
      glVertex3d (inner[k].first, inner[k].second, 0);
   }
   glEnd ();
   glBegin (GL_QUAD_STRIP);
   for (unsigned int k = 0; k < outer.size (); ++k) {
      glColor4ub (189, 189, 49, 127);
      glVertex3d (outer[k].first, outer[k].second, 0);
      glColor4ub (131, 87, 25, 127);
      glVertex3d (outer[k].first, outer[k].second, -0.5);
   }
   glEnd ();
   glEndList ();

   /* create and populate the list of coordinate frame arrows */
   const double LEN = 1.5;
   const double ARR = .25;
   CF_list = glGenLists (1);
   glNewList (CF_list, GL_COMPILE);
   glColor4ub (255, 0, 0, 127);
   glBegin (GL_LINE_STRIP);
   glVertex3f (0.0, 0.0, 0.0);
   glVertex3f (LEN, 0.0, 0.0);
   glVertex3f (LEN - ARR, ARR, 0.0);
   glVertex3f (LEN - ARR, -ARR, 0.0);
   glVertex3f (LEN, 0.0, 0.0);
   glVertex3f (LEN - ARR, 0.0, ARR);
   glVertex3f (LEN - ARR, 0.0, -ARR);
   glVertex3f (LEN, 0.0, 0.0);
   glEnd ();

   glColor4ub (51, 204, 255, 127);
   glBegin (GL_LINE_STRIP);
   glVertex3f (0.0, 0.0, 0.0);
   glVertex3f (0.0, LEN, 0.0);
   glVertex3f (0.0, LEN - ARR, ARR);
   glVertex3f (0.0, LEN - ARR, -ARR);
   glVertex3f (0.0, LEN, 0.0);
   glVertex3f (ARR, LEN - ARR, 0.0);
   glVertex3f (-ARR, LEN - ARR, 0.0);
   glVertex3f (0.0, LEN, 0.0);
   glEnd ();

   glColor4ub (0, 255, 0, 127);
   glBegin (GL_LINE_STRIP);
   glVertex3f (0.0, 0.0, 0.0);
   glVertex3f (0.0, 0.0, LEN);
   glVertex3f (ARR, 0.0, LEN - ARR);
   glVertex3f (-ARR, 0.0, LEN - ARR);
   glVertex3f (0.0, 0.0, LEN);
   glVertex3f (0.0, ARR, LEN - ARR);
   glVertex3f (0.0, -ARR, LEN - ARR);
   glVertex3f (0.0, 0.0, LEN);
   glEnd ();
   glColor4ub (255, 255, 0, 127);
   glRasterPos3f (1.1, 0.0, 0.0);
   glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, 'x');
   glRasterPos3f (0.0, 1.1, 0.0);
   glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, 'y');
   glRasterPos3f (0.0, 0.0, 1.1);
   glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, 'z');
   glEndList ();
}

void GLPanel::resizeGL (int w, int h)
{
   glViewport (0, 0, (GLint) w, (GLint) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective (60.0, (GLdouble) w / h, 1.0, 20.0);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (3, 4, 5, focus[0], focus[1], 0, 0, 1, 0);
}

/* the boolean parameter controls whether the object is drawn using
 * "solid" surface or wireframe
 */
void GLPanel::drawModel (bool wire)
{
   glPushMatrix ();

   if (wire)
      glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
   else {
      glPolygonMode (GL_FRONT, GL_FILL);
      glPolygonMode (GL_BACK, GL_LINE);
   }
   glCallList (CF_list);        /* always draw the object coordinate frame */
   if (wire)
      glColor4ub (189, 189, 49, 127);
   else
      glColor4ub (195, 129, 37, 127);
   glCallList (D_list);         /* then draw the object */
   glPopMatrix ();
}

void GLPanel::paintGL ()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity ();
   gluLookAt (3, 4, 5, focus[0], focus[1], 0, 0, 1, 0);
   if (trsf && trsf->size () > 0) {
      glEnable (GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      /* draw the world coordinate frame */
      glCallList (CF_list);

      /* draw the object */
      drawModel (true);

      /*
       * In the following switch statement, trsf is a pointer to an STL
       * vector.
       * To access the vector, the C/C++ indirection operator is used:
       *         (*trsf)
       * To access one element of the vector the [] operator is used:
       *         (*trsf)[k]  
       * The element is a pointer to a GLTransform object. To invoke its
       * run() function, the arrow "->" operator is used:
       *         (*trsf)[k] -> run()
       */
      std::vector < GLTransform * >::iterator it, curr, it_beg, it_end;
      glPushMatrix ();
      switch (stepMode) {
      case 1:                  /* step forward using local coordinate frame */
         it_beg = trsf->begin();
         /* during step mode, the concatenation of transformations must
          * end at the current step. Otherwise, the concatenation
          * include ALL transformations in the list */
         if (current_step != NULL)
            /*it_end =*/ std::find (trsf->begin (), trsf->end (), const_cast<GLTransform*>(current_step));
         else
            it_end = trsf->end() - 1;
         for (it = it_beg; it != it_end; ++it) {
            (*it)->run ();
            glCallList (CF_list);
            drawModel (true);
         }
         glDisable (GL_BLEND);
         (*it)->run ();    /* run the last transformation */
         glCallList (CF_list);
         drawModel (false);
         break;

      case 2:                  /* step backward using global coordinate frame */
         std::vector < GLTransform * >::reverse_iterator rit, rit_beg, rit_end;
         rit_beg = trsf->rbegin();
         /** during step mode, the concatenation of transformations must
          * begin at the current step and end to the end of the list
          */
         if (current_step != NULL)
            rit_end = std::find (trsf->rbegin (), trsf->rend (), 
                  current_step) + 1;
         else
            rit_end = trsf->rend();
         for (rit = rit_beg; rit != rit_end; ++rit) {
            glPushMatrix ();
            for (it = (rit+1).base(); it != trsf->end(); ++it)
               (*it)->run ();
            glCallList (CF_list);
            /* disable blending for the last instance */
            if (rit == rit_end - 1)
               glDisable (GL_BLEND);

            /* draw solid for the last instance, wireframe for the
             * remaining instances */
            drawModel (rit != rit_end - 1);
            glPopMatrix ();
         }
         break;
      }
      glPopMatrix ();
   }
   else {
      /* no transformation is defined, just show the world coordinate
       * frame */
      glCallList (CF_list);

      /* and show the object */
      drawModel (false);
   }
}

void GLPanel::showStep (GLTransform * c)
{
   current_step = c;
   updateGL ();
}
