#include "mainmenu.h"
#include "ui_mainmenu.h"
//#include "iostream"
#include <algorithm>

QByteArray webToken;

int temp_id_card;
int temp_id_acc;

QString id_card;
QString id_acc;

float currency_rate[5]{1.00,1.00,1.00,1.00,1.00}; //vakio arvot, jotka korvaantuvat kun haetaan pilvestä
int TOTAL_AMOUNT=0;
std::string transactions_amount[100];
std::string transactions_location[100];
std::string transactions_date[100]; //erotellaan json muodossa saappuvat transaction tiedot toisistaan heti hakuvaiheessa

QString transaction_temp;

MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    //this->showFullScreen();

    qDebug()<<"MainMenu luotu";
    opened_window = 2;
}

MainMenu::~MainMenu()
{
    qDebug()<<"mainmenu tuhottu";
    delete ui;
}

void MainMenu::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

void MainMenu::on_btn_logout_clicked()
{
    soundObj.playSound(4);
    logOut_clicked = 1;
    qDebug()<<"logout btn";

    //elapsed_time=30000;
    this->close();
}


void MainMenu::on_btn_transactions_clicked() //haetaan tilitapahtumat

{
    soundObj.playSound(4);
    elapsed_time = 0;

    // avaa transaction ikkunan jos token OK ja hakee tiedot ikkunaan slotilla
    QString url = "http://localhost:3000/transaction/getById/"+id_acc; //+id_acc kun toimii
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"), myToken);
    //WEBTOKEN LOPPU

    transactionManager = new QNetworkAccessManager(this);
    connect(transactionManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transactionSlot(QNetworkReply*)));
    transactionreply = transactionManager->get(request);
}


void MainMenu::transactionSlot(QNetworkReply *transactionreply) //hakee tilitapahtumia
{
    response_data=transactionreply->readAll(); //muuttaa haetun tiedon tulostukseksi
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    //temp_transactions="määrä | sijainti | pvm \r";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();

        transaction_temp=json_obj["balanceChange"].toString()+" \r";
        transactions_amount[TOTAL_AMOUNT]=transaction_temp.toUtf8();

        transaction_temp=json_obj["location"].toString()+" \r";
        transactions_location[TOTAL_AMOUNT]=transaction_temp.toUtf8();

        transaction_temp=json_obj["date"].toString();
        //siivouspalvelu SOL
        std::replace(transaction_temp.begin(), transaction_temp.end(), 'T' , ' ');
        transaction_temp.chop(5);
        transaction_temp+=" \r";

        transactions_date[TOTAL_AMOUNT]=transaction_temp.toUtf8();
        TOTAL_AMOUNT++;
    }
    qDebug()<<"tietoja haettiin: "<<TOTAL_AMOUNT;

    transaction_wPtr = new transaction(this);

    QString url2 = "http://localhost:3000/account/"+id_acc;
    QNetworkRequest request2(url2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request2.setRawHeader(QByteArray("Authorization"), myToken);
    //WEBTOKEN LOPPU

    saldoManager = new QNetworkAccessManager(this);
    connect(saldoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));
    reply = saldoManager->get(request2);

    //transaction_wPtr->open();
    transaction_wPtr->showFullScreen();
    transactionreply->deleteLater();
    transactionManager->deleteLater();

}


void MainMenu::saldoSlot(QNetworkReply *reply) //hakee tilin tietoja
{
    response_data2 = reply->readAll();

    if(response_data2 == "Forbidden") {
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;}"
                             "QLabel{ color: white}");
        msgBox.setText("Kirjautuminen vanhentunut! Jatkaaksesi kirjaudu sisään uudelleen.");
        msgBox.exec();
    }
    else {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data2);
        QJsonObject json_obj = json_doc.object();

        QString balance = json_obj["balance"].toString();
        qDebug()<<balance;
         QString creditLimit = json_obj["creditLimit"].toString();
         qDebug()<<creditLimit;
         QString accountnumber = json_obj["accountNumber"].toString();
         qDebug()<<accountnumber;

       transaction_wPtr->setLabelSaldo(balance + "€");
       transaction_wPtr->setLabelCredit(creditLimit + "€");
       transaction_wPtr->setLabelaccountnumber("FI" + accountnumber);


       QString url3 = "http://localhost:3000/customer/"+id_acc; //ei toimi nyty
       QNetworkRequest request3(url3);
       request3.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

       //WEBTOKEN ALKU
       QByteArray myToken="Bearer "+webToken;
       request3.setRawHeader(QByteArray("Authorization"), myToken);
       //WEBTOKEN LOPPU

       customerManager = new QNetworkAccessManager(this);
       connect(customerManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(customerSlot(QNetworkReply*)));
       customerreply = customerManager->get(request3);
    }
}

void MainMenu::customerSlot(QNetworkReply *customerreply){ //hakee käyttäjän nimen

    response_data5 = customerreply->readAll();

    if(response_data5 == "Forbidden") {
       soundObj.playSound(2);
       QMessageBox msgBox;
       msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                            "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;}"
                            "QLabel{ color: white}");
        msgBox.setText("Kirjautuminen vanhentunut! Jatkaaksesi kirjaudu sisään uudelleen.");
        msgBox.exec();
    }
    else {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data5);
        QJsonObject json_obj = json_doc.object();

        QString username = json_obj["fname"].toString();
        qDebug()<<username;

       transaction_wPtr->setLabelusername("TERVETULOA "+username  + "!");
    }
    reply->deleteLater();
    saldoManager->deleteLater();
    customerreply->deleteLater();
    customerManager->deleteLater();
}


void MainMenu::on_btn_withdraw_clicked()
{
    soundObj.playSound(4);
    elapsed_time = 0;
    withdraw_wPtr = new withdraw_main(this);
    withdraw_wPtr->showFullScreen();
    //withdraw_wPtr->open();
}


void MainMenu::on_btn_currency_clicked()
{
    soundObj.playSound(4);
    elapsed_time = 0;

    // avaa currency ikkunan jos token OK ja hakee tiedot ikkunaan slotilla
    QString url = "https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/currencies/eur.json";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"), myToken);
    //WEBTOKEN LOPPU

    currencyManager = new QNetworkAccessManager(this);
    connect(currencyManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(currencySlot(QNetworkReply*)));
    replyCurrency = currencyManager->get(request);
}

void MainMenu::currencySlot(QNetworkReply *replyCurrency)
{
    //currencies="määrä | sijainti | pvm \r";

    response_data=replyCurrency->readAll(); //muuttaa haetun tiedon tulostukseksi
    //qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QJsonObject json_obj2 = json_obj["eur"].toObject();
    //qDebug()<<"\n";
    //qDebug()<<"___temp data :"<<json_obj2;

    currency_rate[1]=json_obj2["usd"].toDouble();
    currency_rate[2]=json_obj2["gbp"].toDouble();
    currency_rate[3]=json_obj2["sek"].toDouble();
    currency_rate[4]=json_obj2["jpy"].toDouble();

    currency_wPtr = new currency(this);
    //currency_wPtr->open();
    currency_wPtr->showFullScreen();
    replyCurrency->deleteLater();
    currencyManager->deleteLater();
}
