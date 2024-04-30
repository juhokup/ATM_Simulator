#include "dll_rfid.h"

DLL_RFID::DLL_RFID(QObject *parent): QObject(parent)
{
   qDebug()<<"DLL luotu";
   pEngine = new engine(this);
   connect(pEngine,SIGNAL(sendSignalIO(QString)),
           this,SLOT(receiveCardNumber(QString)));
}

DLL_RFID::~DLL_RFID()
{
    qDebug()<<"DLL tuhottu";
    disconnect(pEngine,SIGNAL(sendSignalIO(QString)),
            this,SLOT(receiveCardNumber(QString)));
    delete pEngine;
    pEngine = nullptr;
}

void DLL_RFID::OpenRFID()
{
    pEngine->open();
}

void DLL_RFID::receiveCardNumber(QString data) //vastaanotto ja eteenpäin lähetys
{
    emit sendSignal(data);
    DLL_RFID::~DLL_RFID();
}






