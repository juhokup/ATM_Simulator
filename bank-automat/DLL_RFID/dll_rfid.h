#ifndef DLL_RFID_H
#define DLL_RFID_H

#include "DLL_RFID_global.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include "engine.h"
#include <QDebug>
#include <QList>

class DLL_RFID_EXPORT DLL_RFID : public QObject
{
    Q_OBJECT
public:
    DLL_RFID(QObject * parent = nullptr);
    ~DLL_RFID();
    void OpenRFID(void);
signals:
    void sendSignal(QString);
public slots:
    void receiveCardNumber(QString data);
private:
    engine *pEngine;
};
#endif // DLL_RFID_H
