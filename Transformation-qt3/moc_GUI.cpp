/****************************************************************************
** GUI meta object code from reading C++ file 'GUI.h'
**
** Created: Tue Jan 22 23:09:45 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "GUI.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GUI::className() const
{
    return "GUI";
}

QMetaObject *GUI::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GUI( "GUI", &GUI::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GUI::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GUI", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GUI::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GUI", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GUI::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = MyForm::staticMetaObject();
    static const QUMethod slot_0 = {"add_transf_clicked", 0, 0 };
    static const QUMethod slot_1 = {"del_transf_clicked", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_2 = {"trsfList_clicked", 1, param_slot_2 };
    static const QUMethod slot_3 = {"upList_clicked", 0, 0 };
    static const QUMethod slot_4 = {"downList_clicked", 0, 0 };
    static const QUMethod slot_5 = {"run_clicked", 0, 0 };
    static const QUMethod slot_6 = {"step_clicked", 0, 0 };
    static const QUMethod slot_7 = {"reset_clicked", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "add_transf_clicked()", &slot_0, QMetaData::Public },
	{ "del_transf_clicked()", &slot_1, QMetaData::Public },
	{ "trsfList_clicked(QListViewItem*)", &slot_2, QMetaData::Public },
	{ "upList_clicked()", &slot_3, QMetaData::Public },
	{ "downList_clicked()", &slot_4, QMetaData::Public },
	{ "run_clicked()", &slot_5, QMetaData::Public },
	{ "step_clicked()", &slot_6, QMetaData::Public },
	{ "reset_clicked()", &slot_7, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "GLTransform", QUParameter::In }
    };
    static const QUMethod signal_0 = {"stepChanged", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "stepChanged(GLTransform*)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GUI", parentObject,
	slot_tbl, 8,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GUI.setMetaObject( metaObj );
    return metaObj;
}

void* GUI::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GUI" ) )
	return this;
    return MyForm::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL stepChanged
void GUI::stepChanged( GLTransform* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

bool GUI::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: add_transf_clicked(); break;
    case 1: del_transf_clicked(); break;
    case 2: trsfList_clicked((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 3: upList_clicked(); break;
    case 4: downList_clicked(); break;
    case 5: run_clicked(); break;
    case 6: step_clicked(); break;
    case 7: reset_clicked(); break;
    default:
	return MyForm::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GUI::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: stepChanged((GLTransform*)static_QUType_ptr.get(_o+1)); break;
    default:
	return MyForm::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GUI::qt_property( int id, int f, QVariant* v)
{
    return MyForm::qt_property( id, f, v);
}

bool GUI::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
