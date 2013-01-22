/****************************************************************************
** GLPanel meta object code from reading C++ file 'GLPanel.h'
**
** Created: Tue Jan 22 08:13:34 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "GLPanel.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLPanel::className() const
{
    return "GLPanel";
}

QMetaObject *GLPanel::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLPanel( "GLPanel", &GLPanel::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GLPanel::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLPanel", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLPanel::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLPanel", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLPanel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setStepMode", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setFocusX", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setFocusY", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_ptr, "GLTransform", QUParameter::In }
    };
    static const QUMethod slot_3 = {"showStep", 1, param_slot_3 };
    static const QMetaData slot_tbl[] = {
	{ "setStepMode(int)", &slot_0, QMetaData::Public },
	{ "setFocusX(int)", &slot_1, QMetaData::Public },
	{ "setFocusY(int)", &slot_2, QMetaData::Public },
	{ "showStep(GLTransform*)", &slot_3, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GLPanel", parentObject,
	slot_tbl, 4,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLPanel.setMetaObject( metaObj );
    return metaObj;
}

void* GLPanel::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLPanel" ) )
	return this;
    return QGLWidget::qt_cast( clname );
}

bool GLPanel::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setStepMode((int)static_QUType_int.get(_o+1)); break;
    case 1: setFocusX((int)static_QUType_int.get(_o+1)); break;
    case 2: setFocusY((int)static_QUType_int.get(_o+1)); break;
    case 3: showStep((GLTransform*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QGLWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GLPanel::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool GLPanel::qt_property( int id, int f, QVariant* v)
{
    return QGLWidget::qt_property( id, f, v);
}

bool GLPanel::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
