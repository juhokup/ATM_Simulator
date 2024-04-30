QT -= gui
QT += serialport
TEMPLATE = lib
DEFINES += DLL_RFID_LIBRARY

CONFIG += c++11

SOURCES += \
    dll_rfid.cpp \
    engine.cpp

HEADERS += \
    DLL_RFID_global.h \
    dll_rfid.h \
    engine.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
