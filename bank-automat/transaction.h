#ifndef TRANSACTION_H
#define TRANSACTION_H
//#include "login.h"
#include "sounds.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonArray>

//#include "mainmenu.h"
//#include "login.h"

extern QByteArray webToken;
extern int temp_id_acc;
extern QString id_acc;

extern std::string transactions_balance[100];
extern std::string transactions_location[100];
extern std::string transactions_date[100];
extern int TOTAL_AMOUNT;

namespace Ui {
class transaction;
}

class transaction : public QDialog
{
    Q_OBJECT

public:
    explicit transaction(QWidget *parent = nullptr);
    ~transaction();
    transaction *history_wPtr;
    QNetworkAccessManager *saldoManager2;
    //transaction *history2_wPtr;
public slots:
    void setTransactions();
    void setTextTransaction(QString history);
    void setTextTransactionPrevious(QString history);
    void setLabelSaldo(QString balance);
    void setLabelaccountnumber(QString accountnumber);
    void setLabelCredit(QString creditLimit);
    void setLabelusername(QString username);
    void saldoSlot2(QNetworkReply *saldoreply);
    void customerSlot2(QNetworkReply *customerreply2);
    // void transactionSlot(QNetworkReply *transactionreply); //slot for tilitapahtumings
private slots:
    void ExitClickHandler(); //exit nappihandlings
    void NextClickHandler(); //next nappihandlings
    void PreviousClickHandler(); //prev nappihandlings
    void historySlot(QNetworkReply *historyreply);
    //void history2Slot(QNetworkReply *history2reply);

private:
    Ui::transaction *ui;
    QByteArray response_data;
    QByteArray response_data2;
    QByteArray response_data3;
    QByteArray response_data6;
    QNetworkReply *transactionreply;
    QNetworkAccessManager *transactionManager;
    QNetworkAccessManager *customerManager2;
    QNetworkReply *historyreply;
    QNetworkReply *saldoreply;
    QNetworkReply *customerreply2;
    //QString lastDate;
    //QString firstDate;
    // QNetworkReply *history2reply;
    QNetworkAccessManager *historyManager;
    //QNetworkAccessManager *history2Manager;
    sounds soundObj;

};

#endif // TRANSACTION_H
