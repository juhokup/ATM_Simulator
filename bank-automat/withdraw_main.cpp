#include "withdraw_main.h"
#include "ui_withdraw_main.h"
#include <QMessageBox>


#include "currency.h"
int currentWindow = 1;
int num=0;

withdraw_main::withdraw_main(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdraw_main)
{
    ui->setupUi(this);

    switch (current_currency){
    case 1:
        num=0;
        qDebug()<<"eurot valittu";
        labelHandler(num);
        ui->label_currentCurrency->setText("Nostettava valuutta: EUR"); //stackedWidget page 1
        ui->label_flag->setPixmap(QPixmap(":/icons/flags/eu.png"));
        ui->label_currentCurrency_2->setText("Nostettava valuutta: EUR"); //stackedWidget page 2
        ui->label_flag_2->setPixmap(QPixmap(":/icons/flags/eu.png"));
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case 2:
        num=1;
        qDebug()<<"dollarit valittu";
        labelHandler(num);
        ui->label_currentCurrency_2->setText("Nostettava valuutta: USD"); //stackedWidget page 2
        ui->label_flag_2->setPixmap(QPixmap(":/icons/flags/us.png"));
        withdraw_main::on_btnCustomAmount_clicked();
        break;
    case 3:
        num=2;
        qDebug()<<"punta valittu";
        labelHandler(num);
        ui->label_currentCurrency_2->setText("Nostettava valuutta: GBP"); //stackedWidget page 2
        ui->label_flag_2->setPixmap(QPixmap(":/icons/flags/gb.png"));
        withdraw_main::on_btnCustomAmount_clicked();
        break;
    case 4:
        num=3;
        qDebug()<<"ruotsin kruunu valittu";
        labelHandler(num);
        ui->label_currentCurrency_2->setText("Nostettava valuutta: SEK"); //stackedWidget page 2
        ui->label_flag_2->setPixmap(QPixmap(":/icons/flags/se.png"));
        withdraw_main::on_btnCustomAmount_clicked();
        break;
    case 5:
        num=4;
        qDebug()<<"jeni valittu";
        labelHandler(num);
        ui->label_currentCurrency_2->setText("Nostettava valuutta: YEN"); //stackedWidget page 2
        ui->label_flag_2->setPixmap(QPixmap(":/icons/flags/jp.png"));
        withdraw_main::on_btnCustomAmount_clicked();
        break;
    default:
        num=0;
        labelHandler(num);
        ui->label_currentCurrency->setText("Nostettava valuutta: EUR"); //stackedWidget page 1
        ui->label_flag->setPixmap(QPixmap(":/icons/flags/eu.png"));
        ui->label_currentCurrency_2->setText("Nostettava valuutta: EUR"); //stackedWidget page 2
        ui->label_flag_2->setPixmap(QPixmap(":/icons/flags/eu.png"));
        ui->stackedWidget->setCurrentIndex(0);
    }

    connect(ui->btn_num0, &QPushButton::clicked, this, &withdraw_main::digitPressed);   //yhdistellään stackedWidget page 2(muu summa)
    connect(ui->btn_num1, &QPushButton::clicked, this, &withdraw_main::digitPressed);   //numeronäppäimet digitPressed metodiin
    connect(ui->btn_num2, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num3, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num4, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num5, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num6, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num7, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num8, &QPushButton::clicked, this, &withdraw_main::digitPressed);
    connect(ui->btn_num9, &QPushButton::clicked, this, &withdraw_main::digitPressed);

    getBalance();
    qDebug()<<"withdraw konstruktori";
}

withdraw_main::~withdraw_main()
{
    qDebug()<<"withdraw destruktori";
    delete ui;
}

void withdraw_main::on_btnExit_clicked() //stackedWidget page 1
{
    elapsed_time = 0;
    if (current_currency>1) {
        ui->lbl_20_main->setText("");
        ui->lbl_40_main->setText("");
        ui->lbl_50_main->setText("");
        ui->lbl_100_main->setText("");
        ui->lbl_200_main->setText("");
        ui->lbl_500_main->setText("");
    }
    soundObj.playSound(4);
    this->close();
}

void withdraw_main::withdraw() //stackedWidget page 4
{
    qDebug()<<"withdraw metodi avattu";

    numOfInterrupts = 100;
    progBarValue = 0.00;
    ui->progressBar->setValue(progBarValue);
    soundObj.playSound(5);

    ui->stackedWidget->setCurrentIndex(3);
    progressBarTimer = new QTimer(this);
    connect(progressBarTimer, SIGNAL (timeout()), this, SLOT (timeout_func()));

    progressBarTimer->setInterval(100);
    progressBarTimer->start();
}

void withdraw_main::timeout_func() //stackedWidget page 4
{
    if(numOfInterrupts > 0){
        elapsed_time = 0;
        numOfInterrupts--;

        progBarValue += 1.00;
        ui->progressBar->setValue(progBarValue);
    }else if (numOfInterrupts == 0){
        progressBarTimer->stop();
        progressBarTimer->disconnect();
        delete progressBarTimer;
        progressBarTimer = nullptr;
        this->close();
    }
}

void withdraw_main::on_btnCustomAmount_clicked() //stackedWidget page 1
{
    elapsed_time = 0, withdraw_amount = 0, currentWindow = 2;
    EditLine = ui->lineEdit_customAmount;
    EditLine->setText("");
    amount = EditLine->text();
    qDebug()<<"Amount on nyt = "<<amount<<"...";
    if (num==0) soundObj.playSound(4);
    ui->stackedWidget->setCurrentIndex(1);
}

void withdraw_main::digitPressed() { //stackedWidget page 2
    elapsed_time = 0;
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString btnNum = button->text();
    tempNum = btnNum.toInt();
    if (tempNum == 0 && state == 0){
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                             "QLabel{ color: white}");
        msgBox.setText("Nollaa ei voi syöttää ensimmäiseksi");
        msgBox.exec();
    } else {
        state = 1;
        soundObj.playSound(4);
        amount = EditLine->text() + btnNum;
        EditLine->setText(EditLine->text() + btnNum);
        qDebug() << "Amount on nyt " << amount; //tulostaa debug tietoa
    }
}

void withdraw_main::on_btn_OK_clicked() //stackedWidget page 2
{
    elapsed_time = 0;
    withdrawAmount=amount.toFloat();
    if ((withdrawAmount/currency_rate[num])< 20 ){
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                             "QLabel{ color: white}");
        msgBox.setText("Nostettava summa on liian pieni");
        msgBox.exec();
    } else if ((withdrawAmount/currency_rate[num]) > 1000 ){
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                             "QLabel{ color: white}");
        msgBox.setText("Nostettava summa on liian suuri");
        msgBox.exec();
    } else if ((withdrawAmount/currency_rate[num]) > account_Balance ){
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                             "QLabel{ color: white}");
        msgBox.setText("Tilin kate ei riitä");
        msgBox.exec();
    } else {

    ui->label_confirmWithdraw->setText(amount+character[num]);
    withdrawAmount = amount.toFloat();
    if (currentWindow == 1){amount="";}
    else if (currentWindow == 2){EditLine->setText(""), amount = EditLine->text();}
    soundObj.playSound(4);
    ui->stackedWidget->setCurrentIndex(2);
    }
}


void withdraw_main::on_btn_resetWithdraw_clicked() //stackedWidget page 3
{
    withdraw_main::on_btn_goBack_clicked();
}

void withdraw_main::on_btn_confirmWithdraw_clicked() //stackedWidget page 3
{
    elapsed_time = 0;
    soundObj.playSound(4);
    qDebug()<<"OK btn click";
    qDebug()<<"temp_id="<<temp_id_acc;
    qDebug()<<"amount"<<amount;
    qDebug()<<"withdrawAmount="<<withdrawAmount;

    jsonObj.insert("currency_rate", currency_rate[num]);
    jsonObj.insert("account_idaccount", temp_id_acc);
    jsonObj.insert("amount", withdrawAmount);

    // "sending request with postman"
    QString url = "http://localhost:3000/stored_proc";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray myToken="Bearer " + webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));
    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}

void withdraw_main::withdrawSlot(QNetworkReply *reply)
{
    qDebug()<<" withdrawSlot";
    response_data=reply->readAll();
    qDebug()<<response_data;

    if(response_data == "\"ER_SIGNAL_EXCEPTION\"" ||response_data == "\"ER_WARN_DATA_OUT_OF_RANGE\"") {
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px; }"
                             "QLabel{ color: white}");
        msgBox.setText("Nostoa ei voitu suorittaa");
        msgBox.exec();
    } else {
        ui->progressBar->setValue(100);
        this->withdraw();
    }

    reply->deleteLater();
    withdrawManager->deleteLater();
}

void withdraw_main::getBalance()
{
    QString url = "http://localhost:3000/account/"+id_acc;
    QNetworkRequest request2(url);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request2.setRawHeader(QByteArray("Authorization"), myToken);
    //WEBTOKEN LOPPU

    saldoManager = new QNetworkAccessManager(this);
    connect(saldoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));
    balanceReply = saldoManager->get(request2);
}

void withdraw_main::getBalanceSlot(QNetworkReply *balanceReply)
{
    response_data = balanceReply->readAll();

    if(response_data == "Forbidden") {
        soundObj.playSound(2);
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;}"
                             "QLabel{ color: white}");
        msgBox.setText("Kirjautuminen vanhentunut! Jatkaaksesi kirjaudu sisään uudelleen.");
        msgBox.exec();
    }
    else {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();

        QString balance = json_obj["balance"].toString();
        qDebug()<<balance;
        QString creditLimit = json_obj["creditLimit"].toString();
        qDebug()<<creditLimit;
        account_Balance=balance.toFloat()+creditLimit.toFloat();
    }
    qDebug()<<"account_Balance ois: "<<account_Balance;
    balanceReply->deleteLater();
}


void withdraw_main::on_btn_erase_clicked() //stackedWidget page 2
{
    elapsed_time = 0, tempNum = 0, currentWindow = 2;   
    EditLine->setText("");
    amount = EditLine->text();
    soundObj.playSound(4);
    qDebug()<<"Amount on nyt = "<<amount<<"...";
}


void withdraw_main::on_btn_goBack_clicked() //stackedWidget page 2
{
    elapsed_time = 0;
    if (currentWindow == 1){amount="";}
    else if (currentWindow == 2){EditLine->setText(""), amount = EditLine->text();}
    qDebug()<<"Amount on nyt = "<<amount<<"...";
    if (num>0){
        currentWindow = 1;
        soundObj.playSound(4);
        on_btnExit_clicked();
    } else {
    currentWindow = 1;
    soundObj.playSound(4);
    ui->stackedWidget->setCurrentIndex(0);
    }
}

void withdraw_main::on_btn20_clicked()
{
    //amount = 20€*currency_rate->temp2
    amount = QString::number(temp2[0]);
    elapsed_time = 0, currentWindow = 1;
    withdraw_main::on_btn_OK_clicked();
}


void withdraw_main::on_btn40_clicked()
{
    //amount = 40€*currency_rate->temp2
    amount = QString::number(temp2[1]);
    elapsed_time = 0, currentWindow = 1;
    withdraw_main::on_btn_OK_clicked();
}


void withdraw_main::on_btn50_clicked()
{
    //amount = 50*currency_rate->temp2
    amount = QString::number(temp2[2]);
    elapsed_time = 0, currentWindow = 1;
    withdraw_main::on_btn_OK_clicked();
}


void withdraw_main::on_btn100_clicked()
{
    //amount = 100*currency_rate->temp2
    amount = QString::number(temp2[3]);
    elapsed_time = 0, currentWindow = 1;
    withdraw_main::on_btn_OK_clicked();
}


void withdraw_main::on_btn200_clicked()
{
    //amount = 200*currency_rate->temp2
    amount = QString::number(temp2[4]);
    elapsed_time = 0, currentWindow = 1;
    withdraw_main::on_btn_OK_clicked();
}


void withdraw_main::on_btn500_clicked()
{
    //amount = 500*currency_rate->temp2
    amount = QString::number(temp2[5]);
    elapsed_time = 0, currentWindow = 1;
    withdraw_main::on_btn_OK_clicked();
}

void withdraw_main::labelHandler(int number)
{
    for (int x=0; x<6; x++){
        temp2[x]=temp[x]*currency_rate[number];
    }

    //alla olevaa logiikkaa ei enää tarvita, koska silloin kun joku muu kuin euro on valittu siirrytään heti "Muu -summa" näkymään
    if (number == 0){
        ui->lbl_20_main->setText("");
        ui->lbl_40_main->setText("");
        ui->lbl_50_main->setText("");
        ui->lbl_100_main->setText("");
        ui->lbl_200_main->setText("");
        ui->lbl_500_main->setText("");

    } else { //QString character[5]={"€","$","£","KR","¥"};

        ui->lbl_20_main->setText(QString::number(temp2[0]) + character[number]);
        ui->lbl_40_main->setText(QString::number(temp2[1]) + character[number]);
        ui->lbl_50_main->setText(QString::number(temp2[2]) + character[number]);
        ui->lbl_100_main->setText(QString::number(temp2[3]) + character[number]);
        ui->lbl_200_main->setText(QString::number(temp2[4]) + character[number]);
        ui->lbl_500_main->setText(QString::number(temp2[5]) + character[number]);
    }
}
