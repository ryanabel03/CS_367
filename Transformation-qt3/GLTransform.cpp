#include <sstream>
#include <string>
#include "GLTransform.h"

using namespace std;

GLTransform::GLTransform (QListView *parent) : QListViewItem (parent) { }
GLTransform::GLTransform (QListView *parent, QListViewItem *after) 
   : QListViewItem (parent, after)
{
}

GLTransform::~GLTransform ()
{
}


TranslateOp::TranslateOp (QListView * parent,
   GLdouble a, GLdouble b, GLdouble c)
: GLTransform (parent)
{
   p1 = a;
   p2 = b;
   p3 = c;
}

TranslateOp::TranslateOp (QListView * parent, QListViewItem * after,
   GLdouble a, GLdouble b, GLdouble c)
: GLTransform (parent, after)
{
   p1 = a;
   p2 = b;
   p3 = c;
}

QString TranslateOp::text (int c) const
{
   string st;
   ostringstream stm;
   switch (c)
   {
      case 0: st = "glTranslate";
              break;
      case 1:
              stm << p1 << ", " << p2 << ", " << p3;
              st = stm.str();
              break;
   }
   return st;
}

void TranslateOp::run ()
{
   glTranslated (p1, p2, p3);
}

//--------------------------------------------------------------
ScaleOp::ScaleOp (QListView * parent,
   GLdouble a, GLdouble b, GLdouble c)
: GLTransform (parent)
{
   p1 = a;
   p2 = b;
   p3 = c;
}

ScaleOp::ScaleOp (QListView * parent, QListViewItem * after,
   GLdouble a, GLdouble b, GLdouble c)
: GLTransform (parent, after)
{
   p1 = a;
   p2 = b;
   p3 = c;
}

QString ScaleOp::text (int c) const
{
   string st;
   ostringstream stm;
   switch (c)
   {
      case 0: st = "glScale";
              break;
      case 1:
              stm << p1 << ", " << p2 << ", " << p3;
              st = stm.str();
   }
   return st;

}

void ScaleOp::run ()
{
   glScaled (p1, p2, p3);
}

//--------------------------------------------------------------
RotateOp::RotateOp (QListView * parent, QListViewItem * after,
   GLdouble a, GLdouble b, GLdouble c, GLdouble d)
: GLTransform (parent, after)
{
   p1 = a;
   p2 = b;
   p3 = c;
   p4 = d;
}

RotateOp::RotateOp (QListView * parent, 
   GLdouble a, GLdouble b, GLdouble c, GLdouble d)
: GLTransform (parent)
{
   p1 = a;
   p2 = b;
   p3 = c;
   p4 = d;
}

QString RotateOp::text (int c) const
{
   string st;
   ostringstream stm;
   switch (c)
   {
      case 0: st = "glRotate";
              break;
      case 1:
              stm << p1 << ", " << p2 << ", " << p3 << ", " << p4;
              st = stm.str();
   }
   return st;

}

void RotateOp::run ()
{
   glRotated (p1, p2, p3, p4);
}

