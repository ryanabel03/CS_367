#include <qapplication.h>
#include <qgl.h>
#include "GUI.h"

int main (int argc, char * argv[])
{
   QApplication a(argc, argv);
#if 0
   if ( ! QGLFormat::hasOpenGL()) {
       qWarning ("No OpenGL support");
       exit (-1);
   }
#endif
   GUI w;

   //w.resize (700, 650);
   a.setMainWidget (&w);
   w.show();
   return a.exec();
}
