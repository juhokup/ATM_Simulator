#ifndef MAINMENU_H
#define MAINMENU_H

#include "sounds.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

#include "transaction.h"
#include "withdraw_main.h"
#include "currency.h"


#include <QMessageBox>

extern QByteArray webToken;

extern int temp_id_card;
extern int temp_id_acc;

extern QString id_card;
extern QString id_acc;

extern short opened_window;
extern short logOut_clicked;
extern float currency_rate[5];

extern std::string transactions_amount[100];
extern std::string transactions_location[100];
extern std::string transactions_date[100];
extern int TOTAL_AMOUNT;


namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void setWebToken(const QByteArray &newWebToken);
    QNetworkAccessManager *saldoManager;
    transaction *transaction_wPtr;
    withdraw_main *withdraw_wPtr;
    currency *currency_wPtr;

private slots:
    void on_btn_logout_clicked();
    void saldoSlot(QNetworkReply*);
    void on_btn_transactions_clicked();
    void transactionSlot(QNetworkReply *transactionreply);
    void on_btn_withdraw_clicked();
    void on_btn_currency_clicked();
    void customerSlot(QNetworkReply *customerreply);
    void currencySlot(QNetworkReply *replyCurrency);


private:
    Ui::MainMenu *ui;
    QNetworkReply *reply;
    QNetworkReply *replyCurrency;
    QNetworkAccessManager *currencyManager;
    QByteArray response_data;
    QByteArray response_data2;
    QByteArray response_data3;
    QNetworkReply *transactionreply;
    QNetworkAccessManager *transactionManager;
    QByteArray response_data5;
    QNetworkReply *customerreply;
    QNetworkAccessManager *customerManager;

    sounds soundObj;
};

#endif // MAINMENU_H
