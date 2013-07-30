/****************************************************************************
** Meta object code from reading C++ file 'WeatherDataMgr.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/WeatherDataMgr.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WeatherDataMgr.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ebf__WeatherDataMgr[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       9,   69, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      42,   20,   20,   20, 0x05,
      70,   20,   20,   20, 0x05,
      99,   20,   20,   20, 0x05,
     117,   20,   20,   20, 0x05,
     140,   20,   20,   20, 0x05,
     159,   20,   20,   20, 0x05,
     175,   20,   20,   20, 0x05,
     194,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     209,   20,   20,   20, 0x08,

 // methods: signature, parameters, type, tag, flags
     234,  226,   20,   20, 0x02,

 // properties: name, type, flags
     270,  262, 0x0a495103,
     289,  262, 0x0a495103,
     301,  262, 0x0a495103,
     321,  262, 0x0a495103,
     330,  262, 0x0a495103,
     344,  262, 0x0a495103,
     359,  354, 0x01495103,
     366,  354, 0x01495103,
     376,  262, 0x0a495103,

 // properties: notify_signal_id
       1,
       0,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

static const char qt_meta_stringdata_ebf__WeatherDataMgr[] = {
    "ebf::WeatherDataMgr\0\0temperatureChanged()\0"
    "weatherDescriptionChanged()\0"
    "temperatureFeelLikeChanged()\0"
    "humidityChanged()\0windDirectionChanged()\0"
    "windSpeedChanged()\0activeChanged()\0"
    "succeededChanged()\0errorChanged()\0"
    "onNetworkReply()\0strCity\0"
    "requestWeatherData(QString)\0QString\0"
    "weatherDescription\0temperature\0"
    "temperatureFeelLike\0humidity\0windDirection\0"
    "windSpeed\0bool\0active\0succeeded\0error\0"
};

void ebf::WeatherDataMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WeatherDataMgr *_t = static_cast<WeatherDataMgr *>(_o);
        switch (_id) {
        case 0: _t->temperatureChanged(); break;
        case 1: _t->weatherDescriptionChanged(); break;
        case 2: _t->temperatureFeelLikeChanged(); break;
        case 3: _t->humidityChanged(); break;
        case 4: _t->windDirectionChanged(); break;
        case 5: _t->windSpeedChanged(); break;
        case 6: _t->activeChanged(); break;
        case 7: _t->succeededChanged(); break;
        case 8: _t->errorChanged(); break;
        case 9: _t->onNetworkReply(); break;
        case 10: _t->requestWeatherData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ebf::WeatherDataMgr::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ebf::WeatherDataMgr::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ebf__WeatherDataMgr,
      qt_meta_data_ebf__WeatherDataMgr, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ebf::WeatherDataMgr::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ebf::WeatherDataMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ebf::WeatherDataMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ebf__WeatherDataMgr))
        return static_cast<void*>(const_cast< WeatherDataMgr*>(this));
    return QObject::qt_metacast(_clname);
}

int ebf::WeatherDataMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = weatherDescription(); break;
        case 1: *reinterpret_cast< QString*>(_v) = temperature(); break;
        case 2: *reinterpret_cast< QString*>(_v) = temperatureFeelLike(); break;
        case 3: *reinterpret_cast< QString*>(_v) = humidity(); break;
        case 4: *reinterpret_cast< QString*>(_v) = windDirection(); break;
        case 5: *reinterpret_cast< QString*>(_v) = windSpeed(); break;
        case 6: *reinterpret_cast< bool*>(_v) = active(); break;
        case 7: *reinterpret_cast< bool*>(_v) = succeeded(); break;
        case 8: *reinterpret_cast< QString*>(_v) = error(); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setWeatherDescription(*reinterpret_cast< QString*>(_v)); break;
        case 1: setTemperature(*reinterpret_cast< QString*>(_v)); break;
        case 2: setTemperatureFeelLike(*reinterpret_cast< QString*>(_v)); break;
        case 3: setHumidity(*reinterpret_cast< QString*>(_v)); break;
        case 4: setWindDirection(*reinterpret_cast< QString*>(_v)); break;
        case 5: setWindSpeed(*reinterpret_cast< QString*>(_v)); break;
        case 6: setActive(*reinterpret_cast< bool*>(_v)); break;
        case 7: setSucceeded(*reinterpret_cast< bool*>(_v)); break;
        case 8: setError(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ebf::WeatherDataMgr::temperatureChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ebf::WeatherDataMgr::weatherDescriptionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ebf::WeatherDataMgr::temperatureFeelLikeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ebf::WeatherDataMgr::humidityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ebf::WeatherDataMgr::windDirectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ebf::WeatherDataMgr::windSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ebf::WeatherDataMgr::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ebf::WeatherDataMgr::succeededChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void ebf::WeatherDataMgr::errorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
