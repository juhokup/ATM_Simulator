#ifndef WITHDRAW_MAIN_H
#define WITHDRAW_MAIN_H

#include "sounds.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QTimer>
#include <QPixmap>

extern int elapsed_time;
extern QString id_acc;
extern int temp_id_acc;
extern QByteArray webToken;
extern float currency_rate[5];
extern int current_currency;
extern int num;

namespace Ui {
class withdraw_main;
}

class withdraw_main : public QDialog
{
    Q_OBJECT

public:
    explicit withdraw_main(QWidget *parent = nullptr);
    ~withdraw_main();

public slots:
    //void check
    void withdraw();    //suoritetaan nosto
    void timeout_func();
private slots:

    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn50_clicked();
    void on_btn100_clicked();
    void on_btn200_clicked();
    void on_btn500_clicked();

    void on_btnCustomAmount_clicked();
    void on_btnExit_clicked();


    void withdrawSlot(QNetworkReply *reply); //luodaan kenttä tietokannan transaction tauluun

    void getBalance();
    void getBalanceSlot (QNetworkReply *balanceReply);

    void on_btn_OK_clicked();

    void on_btn_erase_clicked();

    void on_btn_goBack_clicked();

    void digitPressed();

    void on_btn_confirmWithdraw_clicked();

    void on_btn_resetWithdraw_clicked();
signals:
    void connectToWithdraw();
private:
    Ui::withdraw_main *ui;
    sounds soundObj;
    int withdraw_amount;
    float account_Balance;
    int state = 0;
    QString amount, tempAmount;
    float withdrawAmount;
    QLineEdit *EditLine;
    QTimer *progressBarTimer;

    QJsonObject jsonObj;
    QNetworkAccessManager *withdrawManager;
    QNetworkReply *reply;
    QNetworkReply *balanceReply;
    QByteArray response_data;
    QNetworkAccessManager *saldoManager;

    void labelHandler(int);
    //--------------------------------
    int numOfInterrupts=0;
    float progBarValue = 0.00;
    int tempNum;
    //--------------------------------

    int temp[6]={20,40,50,100,200,500};
    float temp2[6];
    QString character[5]={"€","$","£","KR","¥"};
};

#endif // WITHDRAW_MAIN_H

