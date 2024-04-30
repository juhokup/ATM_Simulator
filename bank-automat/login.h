#ifndef LOGIN_H
#define LOGIN_H

#include "sounds.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainmenu.h"
#include "cardtypeui.h"

#include "dll_rfid.h"

extern QString url_idcard_combi;



extern int elapsed_time;
extern short opened_window;

extern QByteArray webToken;

extern int temp_id_card;
extern int temp_id_acc;

extern QString id_card;
extern QString id_acc;

extern short msgbox_status;
extern bool cardLocked;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QJsonObject jsonObj_login;

    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *cardManager;
    QNetworkAccessManager *idcardManager;

    QNetworkReply *reply;
    QNetworkReply *reply_card;
    QNetworkReply *reply_idcard;
    QNetworkReply *reply_idcard_combi;


    QByteArray response_data;

    QString number;


public slots:
    void loginSlot(QNetworkReply *reply);
    void cardSlot(QNetworkReply *reply_card);
    void idcardSlot(QNetworkReply *reply_idcard);
    void idcardSlot_combi(QNetworkReply *reply_idcard_combi);

    void receiveCardNumber(QString data);

private slots:
    void on_btn_pin_clicked();
    void on_btn_rfid_clicked();

    void on_btn_n_1_clicked();
    void on_btn_n_2_clicked();
    void on_btn_n_3_clicked();
    void on_btn_n_4_clicked();
    void on_btn_n_5_clicked();
    void on_btn_n_6_clicked();
    void on_btn_n_7_clicked();
    void on_btn_n_8_clicked();
    void on_btn_n_9_clicked();
    void on_btn_n_0_clicked();

    void on_btn_erase_clicked();

signals:
    void sendPinNumToMain(QString); // ei vaadi cpp-toteutusta, toisin kuin slot
    void cardInsert(QString);
    void backToMainWindow();

private:
    Ui::Login *ui;

    int attemptsLeft; // tulevat tietokannasta
    int cardstatus;

    MainMenu *objMainMenu;
    cardtypeui *objCardTypeMenu;

    QString pinstring;
    QString prev_text;

    DLL_RFID *pDLLRFID;

    sounds soundObj;
};

#endif // LOGIN_H
