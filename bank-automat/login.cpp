#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>

QString url_idcard_combi;   // = "http://localhost:3000/getAccountDebit/"+id_card;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    qDebug()<<"login luotu";
    pDLLRFID = new DLL_RFID;
    pDLLRFID->OpenRFID();
    connect(pDLLRFID, SIGNAL(sendSignal(QString)), this, SLOT(receiveCardNumber(QString)));
}

Login::~Login()
{
    qDebug()<<"login tuhottu";
    delete ui;
}

void Login::on_btn_rfid_clicked()
{
    //ui->lineEdit_rfid->setText(temp_text);

    qDebug()<<"rfid btn";
    //number = "06000626F2";
    //receiveCardNumber("06000626F2");

    //number = ui->lineEdit_rfid->text();
    //emit sendCardNumToMain(number);
}

void Login::receiveCardNumber(QString data)
{
    qDebug()<<"SLOT receive sign.";
    //data = "06000626F2";
    //temp_text = data;
    ui->lineEdit_rfid->setText(data);

    number = ui->lineEdit_rfid->text();
//    emit sendCardNumToMain(data);
//    qDebug()<<"send card num to main";
        emit cardInsert(data);
        //number = data;
        soundObj.playSound(11);

        qDebug()<<"data = "<<data<<" ja number = "<<number;
        cardLocked = false;
}


void Login::on_btn_pin_clicked()
{
    elapsed_time = 0;

    qDebug()<<"PIN btn click";

    jsonObj_login.insert("cardNumber", number);
    jsonObj_login.insert("pin", pinstring);


    // "sending request with postman"
    QString url = "http://localhost:3000/login";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(jsonObj_login).toJson());
}

void Login::loginSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    QMessageBox msgBox;

    // DB offline error handling:
    if (response_data == "" || response_data == "ECONNREFUSED"){
        soundObj.playSound(2);
        this->close(); // sulkee PIN syöttöikkunan
        msgbox_status = 1;
        logOut_clicked=1;
        //opened_window = 0;
        msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                              "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                             "QLabel{ color: white}");
        msgBox.setWindowTitle("ERROR");
        msgBox.setText("Tietokannan yhteysvirhe");
        msgBox.exec();
        qDebug()<<"Tietokannan yhteysvirhe";

    }

    else {
        if (response_data != "false") {
            // kirjautuminen OK tai väärä salasana
            int response_length = response_data.length();

            if(response_length > 91) {
                // salasana oikein
                objMainMenu = new MainMenu(this);
                objMainMenu->setWebToken(response_data);

                // Ensin card-taulun kautta idcard, sitten card-taulun idcard perusteella card_privileges-taulusta account_idaccount
                // muuttujaan id_acc
                QString url_card = "http://localhost:3000/card/"+number;
                QNetworkRequest request_card(url_card);
                request_card.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                //WEBTOKEN ALKU
                QByteArray myToken="Bearer "+webToken;
                request_card.setRawHeader(QByteArray("Authorization"), myToken);
                //WEBTOKEN LOPPU

                cardManager = new QNetworkAccessManager(this);
                connect(cardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cardSlot(QNetworkReply*)));
                reply_card = cardManager->get(request_card);
                this->close();

            }

            else {
                soundObj.playSound(2);
                // salasana väärä

                QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
                QJsonObject json_obj = json_doc.object();

                // ** pinAttempts ja cardStatus **
                cardstatus = json_obj["cardStatus"].toInt();
                attemptsLeft = json_obj["pinAttempts"].toInt();
                qDebug()<<"--cardstatus = "<<cardstatus;
                qDebug()<<"--attemptsLeft = "<<attemptsLeft;

                if(cardstatus == 0) {
                    msgbox_status = 1;
                    this->close();
                    cardLocked = true;
                }

                else {
                    // yritykset tulevat yksi jäljessä
                    if(attemptsLeft > 0){
                        if(attemptsLeft == 1) {
                            msgbox_status = 1;
                            this->close();
                            cardLocked = true;
                        }
                        else {
                            msgbox_status = 1;
                            soundObj.playSound(2);
                            msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                                                 "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                                                 "QLabel{ color: white}");
                            msgBox.setText("Kortti ja/tai PIN väärin\nYrityksiä jäljellä: "+QString::number(attemptsLeft-1));
                            msgBox.exec();
                        }
                    }
                }
            }
        }

        // kun response_data = false:
        else {
            soundObj.playSound(2);
            // väärät/puuttuvat tunnukset
            QMessageBox msgBox;
            msgbox_status = 1;
            logOut_clicked=1;
            this->close();

            msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                                 "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                                 "QLabel{ color: white}");
            msgBox.setText("Väärät tai puuttuvat tunnukset");
            msgBox.exec();
        }
    }
    ui->lineEdit_pin->setText("");
    pinstring = "";
    // ---

    reply->deleteLater();
    loginManager->deleteLater();

}

void Login::cardSlot(QNetworkReply *reply_card)
{
    // suojattujen tietojen hakua card-taulusta varten; tarkastetaan aina onko token vielä voimassa
    // pin oltava oikein tässä kohdassa

    qDebug()<<"-------CARD SLOT------";
    response_data = reply_card->readAll(); // tulee kaikki card-taulun tiedot, joista valitaan tarvittavat

    if(response_data == "Forbidden") {
        soundObj.playSound(2);
        this->close();
        QMessageBox msgBox;
        msgbox_status = 1;
        logOut_clicked=1;
        msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                             "QLabel{ color: white}");
        msgBox.setText("Kirjautuminen vanhentunut! Jatkaaksesi kirjaudu sisään uudelleen.");
        msgBox.exec();
    }
    else {
        // Ensin haetaan card-taulun kautta idcard.
        // sitten card-taulun idcard perusteella card_privileges-taulusta haetaan account_idaccount muuttujaan id_acc
        // ennen sitä tarkistetaan, onko kortti 'kunnossa' jne.

        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        qDebug()<<"card SLOT response= "<<response_data;
        QJsonObject json_obj = json_doc.object();

        cardstatus = json_obj["cardStatus"].toInt();
        attemptsLeft = json_obj["pinAttempts"].toInt();

        if(cardstatus == 1 && attemptsLeft >= 1){
            int card_type = json_obj["type"].toInt();
            qDebug()<<"_cardtype:"<<card_type;

            temp_id_card = json_obj["idcard"].toInt();
            id_card = QString::number(temp_id_card);
            qDebug()<< "idcard:"<< id_card;

            idcardManager = new QNetworkAccessManager(this);

            if(card_type == 3){
                /* yhdistelmäkortti
                 *  debit tai credit
                 *  eli creditLimit = 0 tai > 0
                */

                // valinta cardtype-ui:sta
                objCardTypeMenu = new cardtypeui(this);
                objCardTypeMenu->exec(); // open ei toimi tässä?

                QNetworkRequest request_idcard_combi(url_idcard_combi);
                request_idcard_combi.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                //WEBTOKEN ALKU
                QByteArray myToken="Bearer "+webToken;
                request_idcard_combi.setRawHeader(QByteArray("Authorization"), myToken);
                //WEBTOKEN LOPPU

                connect(idcardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(idcardSlot_combi(QNetworkReply*)));
                reply_idcard_combi = idcardManager->get(request_idcard_combi);
            }
            else {
                // debit tai credit kortti (type = 1 tai 2) ('normaali tilanne')
                QString url_idcard = "http://localhost:3000/card_privileges/"+id_card;
                QNetworkRequest request_idcard(url_idcard);
                request_idcard.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                //WEBTOKEN ALKU
                QByteArray myToken="Bearer "+webToken;
                request_idcard.setRawHeader(QByteArray("Authorization"), myToken);
                //WEBTOKEN LOPPU

                connect(idcardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(idcardSlot(QNetworkReply*)));
                reply_idcard = idcardManager->get(request_idcard);
            }
        }

        else {
            //kortti lukittu, palataan mainWindow
            //cardStatus = 0 & attemptsLeft = 0
            cardLocked = true;
        }
    }
    reply_card->deleteLater();
    cardManager->deleteLater();
}


void Login::idcardSlot_combi(QNetworkReply *reply_idcard_combi)
{
    qDebug()<<"idCOMBINATION CARD SLOT";
    response_data = reply_idcard_combi->readAll();

    if(response_data == "Forbidden") {
        soundObj.playSound(2);
        this->close();
        msgbox_status=1;
        logOut_clicked=1;
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                             "QLabel{ color: white}");
        msgBox.setText("Kirjautuminen vanhentunut! Jatkaaksesi kirjaudu sisään uudelleen.");
        msgBox.exec();
    }

    else {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        qDebug()<<"response data combi= "<<response_data;
        QJsonObject json_obj = json_doc.object();

        temp_id_acc = json_obj["account_idaccount"].toInt(); // account_idaccount ei ole taulussa string-tyyppinen, joten toInt()
        id_acc = QString::number(temp_id_acc); // tieto korttiin liitetystä tilistä
        qDebug()<<"id_acc: "<<id_acc;

        soundObj.playSound(1);
        //objMainMenu->open(); // avataan päävalikko
        objMainMenu->showFullScreen();

        //currency_rate[0];
    }

    reply_idcard_combi->deleteLater();
    idcardManager->deleteLater();
}


void Login::idcardSlot(QNetworkReply *reply_idcard)
{
    qDebug()<<"IDcard SLOT";
    response_data = reply_idcard->readAll();

    if(response_data == "Forbidden") {
        soundObj.playSound(2);
        this->close();
        msgbox_status=1;
        logOut_clicked=1;

        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;}"
                             "QLabel{ color: white}");
        msgBox.setText("Kirjautuminen vanhentunut! Jatkaaksesi kirjaudu sisään uudelleen.");
        msgBox.exec();
    }
    else {
        //soundObj.playSound(1);
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        qDebug()<<"response_data = "<<response_data;
        QJsonObject json_obj = json_doc.object();

        temp_id_acc = json_obj["account_idaccount"].toInt(); // account_idaccount ei ole taulussa string-tyyppinen, joten toInt()
        id_acc = QString::number(temp_id_acc); // tieto korttiin liitetystä tilistä
        qDebug()<<"id_acc: "<<id_acc;

        soundObj.playSound(1);
        //objMainMenu->open();
        objMainMenu->showFullScreen();
    }

    reply_idcard->deleteLater();
    idcardManager->deleteLater();
}


// -----------------------------
// -- num buttons:

void Login::on_btn_n_1_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(1);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_2_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(2);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_3_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(3);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_4_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(4);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_5_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(5);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_6_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(6);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_7_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(7);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_8_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(8);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_9_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(9);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}

void Login::on_btn_n_0_clicked()
{
    elapsed_time = 0;
    prev_text = ui->lineEdit_pin->text();
    ui->lineEdit_pin->setText(prev_text+"*");

    pinstring += QString::number(0);
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}
// -- ----

void Login::on_btn_erase_clicked()
{
    elapsed_time = 0; // on every button click reset the time available
    ui->lineEdit_pin->setText("");
    pinstring = "";
    soundObj.playSound(4);

    qDebug()<<"pinstring on nyt = "<<pinstring<<"...";
}
