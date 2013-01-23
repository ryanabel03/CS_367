/****************************************************************************
** MyForm meta object code from reading C++ file 'myForm.h'
**
** Created: Tue Jan 22 23:09:46 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "myForm.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyForm::className() const
{
    return "MyForm";
}

QMetaObject *MyForm::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyForm( "MyForm", &MyForm::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyForm::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyForm", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyForm::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyForm", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyForm::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"addTransformation", 0, 0 };
    static const QUMethod slot_1 = {"removeTransformation", 0, 0 };
    static const QUMethod slot_2 = {"upList_clicked", 0, 0 };
    static const QUMethod slot_3 = {"downList_clicked", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_4 = {"trsfList_currentChanged", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_5 = {"trsfList_selectionChanged", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_6 = {"trsfList_clicked", 1, param_slot_6 };
    static const QUMethod slot_7 = {"run_clicked", 0, 0 };
    static const QUMethod slot_8 = {"step_clicked", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"vScroll_valueChanged", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"hScroll_valueChanged", 1, param_slot_10 };
    static const QUMethod slot_11 = {"add_transf_clicked", 0, 0 };
    static const QUMethod slot_12 = {"del_transf_clicked", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"stepMode_clicked", 1, param_slot_13 };
    static const QUMethod slot_14 = {"reset_clicked", 0, 0 };
    static const QUMethod slot_15 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "addTransformation()", &slot_0, QMetaData::Public },
	{ "removeTransformation()", &slot_1, QMetaData::Public },
	{ "upList_clicked()", &slot_2, QMetaData::Public },
	{ "downList_clicked()", &slot_3, QMetaData::Public },
	{ "trsfList_currentChanged(QListViewItem*)", &slot_4, QMetaData::Public },
	{ "trsfList_selectionChanged(QListViewItem*)", &slot_5, QMetaData::Public },
	{ "trsfList_clicked(QListViewItem*)", &slot_6, QMetaData::Public },
	{ "run_clicked()", &slot_7, QMetaData::Public },
	{ "step_clicked()", &slot_8, QMetaData::Public },
	{ "vScroll_valueChanged(int)", &slot_9, QMetaData::Public },
	{ "hScroll_valueChanged(int)", &slot_10, QMetaData::Public },
	{ "add_transf_clicked()", &slot_11, QMetaData::Public },
	{ "del_transf_clicked()", &slot_12, QMetaData::Public },
	{ "stepMode_clicked(int)", &slot_13, QMetaData::Public },
	{ "reset_clicked()", &slot_14, QMetaData::Public },
	{ "languageChange()", &slot_15, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyForm", parentObject,
	slot_tbl, 16,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyForm.setMetaObject( metaObj );
    return metaObj;
}

void* MyForm::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyForm" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool MyForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: addTransformation(); break;
    case 1: removeTransformation(); break;
    case 2: upList_clicked(); break;
    case 3: downList_clicked(); break;
    case 4: trsfList_currentChanged((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 5: trsfList_selectionChanged((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 6: trsfList_clicked((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 7: run_clicked(); break;
    case 8: step_clicked(); break;
    case 9: vScroll_valueChanged((int)static_QUType_int.get(_o+1)); break;
    case 10: hScroll_valueChanged((int)static_QUType_int.get(_o+1)); break;
    case 11: add_transf_clicked(); break;
    case 12: del_transf_clicked(); break;
    case 13: stepMode_clicked((int)static_QUType_int.get(_o+1)); break;
    case 14: reset_clicked(); break;
    case 15: languageChange(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MyForm::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MyForm::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool MyForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
