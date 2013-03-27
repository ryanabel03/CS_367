#ifndef HANS_GUI
#define HANS_GUI
#include <qmainwindow.h>
#include <vector>
#include "myForm.h"
#include "GLTransform.h"

class GUI : public MyForm {
    Q_OBJECT
    public:
        GUI (QWidget* parent = 0, const char* name = 0, 
                WFlags f = WType_TopLevel);
    public slots:
        void add_transf_clicked();
        void del_transf_clicked();
        void trsfList_clicked( QListViewItem * );
        void upList_clicked();
        void downList_clicked();
        void run_clicked();
        void step_clicked();
        void reset_clicked();
    signals:
        void stepChanged (GLTransform *);

    private:
        void setTrans();
        std::vector<GLTransform*> myTr;
        GLTransform *curr_step;
};
#endif
