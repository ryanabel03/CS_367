#ifndef HANS_GLTRANSFORM
#define HANS_GLTRANSFORM

#include <qlistview.h>
#include <qgl.h>

class GLTransform : public QListViewItem {
   public:
      GLTransform (QListView *);
      GLTransform (QListView *, QListViewItem *);
      virtual ~GLTransform() = 0;
      virtual void run() = 0;

   protected:
      GLdouble p1, p2, p3;
};

class TranslateOp : public GLTransform {
   public:
      TranslateOp (QListView *parent, GLdouble, GLdouble, GLdouble);
      TranslateOp (QListView *parent, QListViewItem *after,
            GLdouble, GLdouble, GLdouble);
      void run();
      QString text (int) const;
};

class ScaleOp : public GLTransform {
   public:
      ScaleOp (QListView *parent, GLdouble, GLdouble, GLdouble);
      ScaleOp (QListView *parent, QListViewItem *after,
            GLdouble, GLdouble, GLdouble);
      void run();
      QString text (int) const;
};

class RotateOp : public GLTransform {
   public:
      RotateOp (QListView *parent, GLdouble, GLdouble, GLdouble, GLdouble);
      RotateOp (QListView *parent, QListViewItem *after,
            GLdouble, GLdouble, GLdouble, GLdouble);
      void run();
      QString text (int) const;

   private:
      GLdouble p4;
};
#endif
