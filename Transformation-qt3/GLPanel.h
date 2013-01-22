#ifndef HANS_GL_PANEL
#define HANS_GL_PANEL
#include <qgl.h>
#include <qlistview.h>
#include "GLTransform.h"
#include <vector>


//#include <boost/numeric/ublas/vector.hpp>

//using namespace boost::numeric::ublas;
using namespace std;

class GLPanel: public QGLWidget {

    Q_OBJECT
    public:
        GLPanel (QWidget *parent, const char *name);
        void drawModel(bool);
        vector<GLdouble> getEye() const { return eye; }
        vector<GLdouble> getFocus() const { return focus; }
        void setTransformation (std::vector<GLTransform*> *);

    public slots:
       void setStepMode (int);
       void setFocusX (int);
       void setFocusY (int);
       void showStep (GLTransform *);

    protected:
        /* draw a coordinate frame */
        void initializeGL ();            /* display callback */
        void resizeGL (int, int);
        void paintGL();
        /* in the following declaration of ublas::vector, we cannot
         * specify the actual size to initialize eye, focus, and up.
         * The actual size must be in the member initialization list
         */
        vector<GLdouble> eye;
        vector<GLdouble> focus;
    private:
        std::vector<GLTransform*> *trsf;
        GLTransform* current_step;
        int stepMode;
        int D_list, /* display list id for the letter 'D' object */
            CF_list; /* display list id for the coordinate frame */
};
#endif
