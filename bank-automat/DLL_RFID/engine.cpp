#include "engine.h"

engine::engine(QObject *parent) : QObject(parent) //konstruktori
{
    pQSerialPort = new QSerialPort; //uusi Qserialport
    pQSerialPortInfo = new QSerialPortInfo; //uusi info
}

engine::~engine() //destruktori
{
    pQSerialPort->close();
    delete pQSerialPort;
    pQSerialPort = nullptr;
    delete pQSerialPortInfo;
    pQSerialPortInfo = nullptr; //poistetaan jäljet
}

void engine::ReadCard() //kortin luku
{
    readData.append(pQSerialPort->readAll()); // bytearrayna serialportin tuotos
    QString data = QString::fromUtf8(readData); // utf8-muodossa formatoituna
    if(readData.length() == 16)
    {
        qDebug()<<"dll:n saama data = "<<readData.length();
        qDebug()<<"vastaanotettu data = "<<data;
        data = data.mid(3, data.length() - 4).trimmed(); //trimmataan ylimääräiset merkit pois
        emit  sendSignalIO(data); //lähetetään trimmattu data
        return;
    }
}

void engine::open() //serial avaus ja debug
{
    QList<QSerialPortInfo> ports = pQSerialPortInfo->availablePorts(); //listataan vapaana olevat portit
    qDebug()<<"vapaat portit = "<<ports.count();
    QSerialPortInfo firstPort;
    if(ports.count() > 0)
    {
        qDebug()<<"luetaan eka portti ";
        firstPort = ports.first();
    }
    else {
        qDebug()<<"yhteysvirhe";
        return;
    }
    pQSerialPort->setPortName("COM4"); // laitehallinta, näytä piilotetut laitteet, portit -> com#, jos ei näy paina lukijan nappia pohjassa hetki.
    pQSerialPort->setBaudRate(9600);
    pQSerialPort->setDataBits(QSerialPort::Data8);
    if (!pQSerialPort->open(QIODevice::ReadWrite))
        {
            qDebug()<<"Serial portti ei auennut, kokeile painaa nappia"<< Qt::endl;
        }
    qDebug()<<"Serial portti avattu, paina nappia";
    connect(pQSerialPort,SIGNAL(readyRead()),
            this,SLOT(ReadCard()));
    readData.clear();
}

