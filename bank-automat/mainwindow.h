#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// custom parameters:
#define TIME_LIMIT_PIN 10000 // 10 sec (10000 ms)
#define TIME_LIMIT_LOGGEDIN 30000 // 30 sec
// ---

#include "sounds.h"
#include <QMainWindow>
#include "login.h"

//#include "dll_rfid.h"

extern int elapsed_time;
extern short opened_window;
extern short logOut_clicked;
extern short msgbox_status;
extern bool cardLocked;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void waitCardInsert();

public slots:
    void backTo_waitCardInsert();


private slots:
    void handleInsertCardClick(QString);
    void updateTime();

    //void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    short card_was_inserted = 0;

    QString pinNumber;
    QString cardNumber;

    Login *pinPtr;
    QTimer *pQTimer;

    //short opened_window;

    sounds soundObj;


    // deprecated:
    QString correctCardNumber = "1234567891234567";
    QString correctPinNumber = "1122";

    //void handleCardNumberRead();
    //void handlePinNumberRead(QString);

    // -------------

signals:
    void timeout();
    void closeMainMenu();
};
#endif // MAINWINDOW_H
