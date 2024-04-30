QT       += core gui
QT += serialport
QT += network
QT += multimedia
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    currency.cpp \
    login.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    sounds.cpp \
    transaction.cpp \
    cardtypeui.cpp \
    withdraw_main.cpp

HEADERS += \
    currency.h \
    login.h \
    mainmenu.h \
    mainwindow.h \
    sounds.h \
    transaction.h \
    cardtypeui.h \
    withdraw_main.h

FORMS += \
    currency.ui \
    login.ui \
    mainmenu.ui \
    mainwindow.ui \
    transaction.ui \
    cardtypeui.ui \
    withdraw_main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# DLL käytössä:


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DLL_RFID/build/release/ -lDLL_RFID
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DLL_RFID/build/debug/ -lDLL_RFID

INCLUDEPATH += $$PWD/DLL_RFID
DEPENDPATH += $$PWD/DLL_RFID

RESOURCES += \
    resourcefile.qrc




