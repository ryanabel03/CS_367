#include <iostream>
#include <qtabwidget.h>
#include <qspinbox.h>
#include <qlistview.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qlayout.h>
#include <sstream>
#include "GUI.h"
#include "GLTransform.h"
#include "GLPanel.h"

using namespace std;

GUI::GUI (QWidget * parent, const char *name, WFlags f)
:MyForm (parent, name, f)
{
   curr_step = NULL;
   trsfList->setSorting (-1);
   /*
   GLTransform *a;
   a = new RotateOp (trsfList, 30, 0, 0, 1);
   a = new TranslateOp (trsfList, a, 3, 0, 0);
   */

   //topGrid->setColStretch (0, 1);
   //topGrid->setColStretch (1, 0);

   connect (run, SIGNAL (clicked ()), glarea, SLOT (updateGL ()));
   connect (stepMode, SIGNAL (clicked (int)), glarea,
      SLOT (setStepMode (int)));
   connect (hScroll, SIGNAL (valueChanged (int)), glarea,
      SLOT (setFocusX (int)));
   connect (vScroll, SIGNAL (valueChanged (int)), glarea,
      SLOT (setFocusY (int)));
   connect (step, SIGNAL (clicked ()), glarea, SLOT (updateGL ()));
   connect (reset, SIGNAL (clicked ()), glarea, SLOT (updateGL ()));
   connect (this, SIGNAL (stepChanged (GLTransform *)),
      glarea, SLOT (showStep (GLTransform *)));
   glarea->setTransformation (&myTr);
}

void GUI::add_transf_clicked ()
{
   ostringstream cmd,
      parm;
   QListViewItem *newitem,
   *last = trsfList->lastItem ();
   switch (trans_tab->currentPageIndex ()) {
   case 0:
      if (last != NULL)
         newitem = new TranslateOp (trsfList, last,
            x_trans->value (), y_trans->value (), z_trans->value ());
      else
         newitem = new TranslateOp (trsfList,
            x_trans->value (), y_trans->value (), z_trans->value ());
      break;
   case 1:
      if (last != NULL)
         newitem = new ScaleOp (trsfList, last,
            x_scale->value (), y_scale->value (), z_scale->value ());
      else
         newitem = new ScaleOp (trsfList,
            x_scale->value (), y_scale->value (), z_scale->value ());
      break;
   case 2:
      if (last != NULL)
         newitem = new RotateOp (trsfList, last,
            rot_angle->value (),
            x_axis->isChecked (), y_axis->isChecked (),
            z_axis->isChecked ());
      else
         newitem = new RotateOp (trsfList,
            rot_angle->value (),
            x_axis->isChecked (), y_axis->isChecked (),
            z_axis->isChecked ());
   }
   curr_step = NULL;
}

void GUI::del_transf_clicked ()
{
   trsfList->takeItem (trsfList->selectedItem ());
   curr_step = NULL;
}

void GUI::upList_clicked ()
{
   QListViewItem *above,
   *curr;
   curr = trsfList->selectedItem ();
   above = curr->itemAbove ();
   if (above) {
      above->moveItem (curr);
      trsfList->setCurrentItem (curr);
   }
   curr_step = NULL;
}

void GUI::downList_clicked ()
{
   QListViewItem *curr,
   *next;
   curr = trsfList->selectedItem ();
   next = curr->itemBelow ();
   if (next) {
      curr->moveItem (next);
      trsfList->setCurrentItem (curr);
   }
   curr_step = NULL;
}

void GUI::trsfList_clicked (QListViewItem * cit)
{
   del_transf->setEnabled (cit);
   upList->setEnabled (cit);
   downList->setEnabled (cit);
   curr_step = NULL;
}

void GUI::run_clicked ()
{
   curr_step = NULL;
   setTrans ();
}

void GUI::reset_clicked()
{
   trsfList->clearSelection ();
   curr_step = NULL;
   myTr.clear ();
   emit stepChanged (NULL);
}

void GUI::setTrans ()
{
   QListViewItemIterator it (trsfList);
   QListViewItem *item;
   myTr.clear ();
   while ((item = it.current ()) != NULL) {
      myTr.push_back ((GLTransform *) item);
      ++it;
   }
}

void GUI::step_clicked ()
{
   GLTransform *n = NULL;
   switch (stepMode->selectedId ()) {
   case 1:                     /* local / forward */
      if (curr_step == NULL)
         n = (GLTransform *) trsfList->firstChild ();
      else
         n = (GLTransform *) curr_step->itemBelow ();
      break;
   case 2:                     /* global / backward */
      if (curr_step == NULL)
         n = (GLTransform *) trsfList->lastItem ();
      else
         n = (GLTransform *) curr_step->itemAbove ();
      break;
   }
   if (n != NULL) {
      curr_step = n;
      trsfList->setCurrentItem (curr_step);
      emit stepChanged (curr_step);
   }
   setTrans ();
}
