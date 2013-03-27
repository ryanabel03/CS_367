/****************************************************************************
** Form interface generated from reading ui file 'myForm.ui'
**
** Created: Tue Jan 22 23:09:40 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MYFORM_H
#define MYFORM_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class GLPanel;
class QScrollBar;
class QButtonGroup;
class QRadioButton;
class QPushButton;
class QListView;
class QListViewItem;
class QTabWidget;
class QWidget;
class QLabel;
class QSpinBox;

class MyForm : public QMainWindow
{
    Q_OBJECT

public:
    MyForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~MyForm();

    QScrollBar* vScroll;
    GLPanel* glarea;
    QScrollBar* hScroll;
    QButtonGroup* stepMode;
    QRadioButton* localCF;
    QRadioButton* globalCF;
    QPushButton* add_transf;
    QPushButton* del_transf;
    QListView* trsfList;
    QPushButton* upList;
    QPushButton* downList;
    QPushButton* run;
    QPushButton* step;
    QPushButton* reset;
    QTabWidget* trans_tab;
    QWidget* tab;
    QLabel* textLabel3;
    QSpinBox* y_trans;
    QLabel* textLabel2;
    QSpinBox* x_trans;
    QLabel* textLabel1;
    QSpinBox* z_trans;
    QWidget* tab_2;
    QLabel* textLabel3_2;
    QSpinBox* y_scale;
    QLabel* textLabel2_2;
    QSpinBox* x_scale;
    QLabel* textLabel1_2;
    QSpinBox* z_scale;
    QWidget* TabPage;
    QLabel* textLabel1_3;
    QSpinBox* rot_angle;
    QButtonGroup* buttonGroup1;
    QRadioButton* x_axis;
    QRadioButton* z_axis;
    QRadioButton* y_axis;
    QMenuBar *MenuBar;
    QPopupMenu *fileMenu;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileSaveAsAction;
    QAction* filePrintAction;
    QAction* fileExitAction;

public slots:
    virtual void addTransformation();
    virtual void removeTransformation();
    virtual void upList_clicked();
    virtual void downList_clicked();
    virtual void trsfList_currentChanged( QListViewItem * );
    virtual void trsfList_selectionChanged( QListViewItem * );
    virtual void trsfList_clicked( QListViewItem * );
    virtual void run_clicked();
    virtual void step_clicked();
    virtual void vScroll_valueChanged( int );
    virtual void hScroll_valueChanged( int );
    virtual void add_transf_clicked();
    virtual void del_transf_clicked();
    virtual void stepMode_clicked( int );
    virtual void reset_clicked();

protected:
    QHBoxLayout* layout13;
    QGridLayout* layout12;
    QGridLayout* layout11;
    QHBoxLayout* layout34;
    QHBoxLayout* layout10;
    QVBoxLayout* layout9;
    QGridLayout* layout2;
    QGridLayout* layout2_2;
    QHBoxLayout* layout7;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;

};

#endif // MYFORM_H
