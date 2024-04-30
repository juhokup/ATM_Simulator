#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QList>

class engine : public QObject
{
    Q_OBJECT
public:
    engine(QObject * parent = nullptr);
    ~engine();
    void open(void);
signals:
    void sendSignalIO(QString);
public slots:
    void ReadCard();
private:
    QByteArray readData;
    QSerialPort * pQSerialPort;
    QSerialPortInfo *pQSerialPortInfo;
};

#endif // ENGINE_H
