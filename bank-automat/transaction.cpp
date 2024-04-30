#include "transaction.h"
#include "ui_transaction.h"
#include "login.h"

int numOfStrings=0; //seurataan alkioita jotka näytetään sivulla x
int page_number=1;  //self explaining
QString wtf;        //muutetaan page_number QStringiksi, jotta voidaan näyttää asiakkaalle tämän hetkinen sivunumero

QString AMOUNT, LOCATION, DATE;
std::string temp_amount, temp_location, temp_date;

transaction::transaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transaction)
{
    ui->setupUi(this);
    connect(ui->btn_next,SIGNAL(clicked(bool)),
            this,SLOT(NextClickHandler()));
    connect(ui->btn_prev,SIGNAL(clicked(bool)),
            this,SLOT(PreviousClickHandler()));
    connect(ui->ButtonExit,SIGNAL(clicked(bool)),
            this,SLOT(ExitClickHandler()));
    setTransactions();
}

transaction::~transaction() //destr
{
    delete ui;
}

void transaction::setTransactions() //asetetaan 5kpl tilitapahtumia näkymää sivulle page_number/20
{
    wtf = QString::number(page_number);
    ui->label_pageNUM->setText(wtf);
    temp_amount="",temp_location="",temp_date="";
    AMOUNT="",LOCATION="",DATE="";
    ui->txtEdit_balanceChange->setText("");
    ui->txtEdit_location->setText("");
    ui->txtEdit_date->setText("");
    qDebug()<<"page_number= "<<page_number;

    if (page_number==1)ui->btn_prev->setHidden(true);
    else if (page_number>1)ui->btn_prev->setHidden(false);

    if (page_number==20)ui->btn_next->setHidden(true);
    else if (page_number<20)ui->btn_next->setHidden(false);

        for (int x=0; x<5; x++){ //limit 5 käytännössä
        qDebug()<<"haetaan tiedot numOfStrings= "<<numOfStrings;
            temp_amount+=transactions_amount[numOfStrings]; //saman tyylinen yhdistely kuin mikä aikaisemmin tehtiin jo mainmenun puolella
            temp_location+=transactions_location[numOfStrings];
            temp_date+=transactions_date[numOfStrings];
            numOfStrings++;
        }
    AMOUNT = QString::fromStdString(temp_amount);
    LOCATION = QString::fromStdString(temp_location);
    DATE = QString::fromStdString(temp_date);
    ui->txtEdit_balanceChange->setText(AMOUNT);
    ui->txtEdit_location->setText(LOCATION);
    ui->txtEdit_date->setText(DATE);
}

void transaction::setTextTransaction(QString history) //nykynen
{
    ui->Transactions->setText(history);
}

void transaction::setTextTransactionPrevious(QString history) //previous
{
    ui->TransactionsPrevious->setText(history);
}

void transaction::setLabelSaldo(QString balance) //saldontulostus
{
    ui->label_saldo->setText(balance);
}

void transaction::setLabelCredit(QString creditLimit) //luottorajan tulostus
{
    ui->label_credit->setText(creditLimit);
}

void transaction::setLabelaccountnumber(QString accountnumber) //tilinumero tulostus
{
    ui->label_accountnumber->setText(accountnumber);
}

void transaction::setLabelusername(QString username) //nimen tulostus
{
    ui->label_username->setText(username);
}

void transaction::ExitClickHandler() //poistunappihandlings
{
    soundObj.playSound(4);
    temp_amount="",temp_location="",temp_date="";
    AMOUNT="",LOCATION="",DATE="";
    ui->txtEdit_balanceChange->setText("");
    ui->txtEdit_location->setText("");
    ui->txtEdit_date->setText("");
    page_number=1;
    numOfStrings=0;
    for (int x=0; x<TOTAL_AMOUNT; x++){
        transactions_date[x]="";
        transactions_amount[x]="";
        transactions_location[x]="";
    }
    TOTAL_AMOUNT=0;
    this->close();
    elapsed_time = 0;
}

void transaction::NextClickHandler() //seuraava sivu nappi handlings
{
    qDebug()<<"NextClick. numOfStrings= "<<numOfStrings;
    page_number++;
    soundObj.playSound(4);
    elapsed_time = 0;
    temp_amount="",temp_location="",temp_date="";
    AMOUNT="",LOCATION="",DATE="";
    ui->txtEdit_balanceChange->setText("");
    ui->txtEdit_location->setText("");
    ui->txtEdit_date->setText("");
    setTransactions();

    // QString get_next="http://localhost:3000/transaction/getNextById/"+id_acc;
    // QNetworkRequest request_getNext((get_next));
    // request_getNext.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // QByteArray myToken="Bearer " + webToken;
    // request_getNext.setRawHeader(QByteArray("Authorization"),(myToken));

    // historyManager = new QNetworkAccessManager(this);
    // connect(historyManager, SIGNAL(finished(QNetworkReply*)),
    //         this, SLOT(historySlot(QNetworkReply*)));
    // historyreply = historyManager->get(request_getNext);
    // this->close(); //PURKKARATKAISU, FIKSUMPIA IDEOITA SAA HEITELLÄ, jos joku keksii miten ton stackedwidgetin saa toimimaan niin ei tarvihe kikkailla xd

}

void transaction::PreviousClickHandler() //edellinen sivu nappi handlings
{
    qDebug()<<"PrevClick. numOfStrings alussa= "<<numOfStrings;
    page_number--;
    soundObj.playSound(4);
    elapsed_time = 0;
    numOfStrings-=10;
    qDebug()<<"PrevClick. numOfStrings lopussa= "<<numOfStrings;

    temp_amount="",temp_location="",temp_date="";
    AMOUNT="",LOCATION="",DATE="";
    ui->txtEdit_balanceChange->setText("");
    ui->txtEdit_location->setText("");
    ui->txtEdit_date->setText("");
    setTransactions();

    // QString get_previous="http://localhost:3000/transaction/getPreviousById/"+id_acc; //hakee getPrevious
    // QNetworkRequest request_getPrevious((get_previous));
    // request_getPrevious.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // QByteArray myToken="Bearer " + webToken;
    // request_getPrevious.setRawHeader(QByteArray("Authorization"),(myToken));

    // historyManager = new QNetworkAccessManager(this);
    // connect(historyManager, SIGNAL(finished(QNetworkReply*)),
    //         this, SLOT(historySlot(QNetworkReply*)));
    // historyreply = historyManager->get(request_getPrevious);
    // this->close(); //PURKKARATKAISU, FIKSUMPIA IDEOITA SAA HEITELLÄ, sulkee aukiolevan ikkunan nappia painettaessa
}


void transaction::historySlot(QNetworkReply *historyreply) //tilitapahtumaslotti
{
    response_data3=historyreply->readAll();
    qDebug()<<response_data3;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data3);
    QJsonArray json_array = json_doc.array();
    QString history;
    history="määrä | sijainti | pvm \r";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        history+=json_obj["balanceChange"].toString()+" | ";
        history+=json_obj["location"].toString()+" | ";
        history+=json_obj["date"].toString();
        history+="\r";
    }
    history_wPtr = new transaction(this);
    history_wPtr->setTextTransaction(history); //asettaa tiedot funktion kautta
    history_wPtr->setTextTransactionPrevious(history);

    QString url2 = "http://localhost:3000/account/"+id_acc; //ei toimi tässä, fixaa !!
    QNetworkRequest request2(url2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request2.setRawHeader(QByteArray("Authorization"), myToken);
    //WEBTOKEN LOPPU

    saldoManager2 = new QNetworkAccessManager(this);
    connect(saldoManager2, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot2(QNetworkReply*)));
    saldoreply = saldoManager2->get(request2);
    history_wPtr->show(); //PURKKARATKAISU, FIKSUMPIA IDEOITA SAA HEITELLÄ

}

void transaction::saldoSlot2(QNetworkReply *saldoreply) //testings
{
    response_data2 = saldoreply->readAll();

    if(response_data2 == "Forbidden") {
        soundObj.playSound(2);
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
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data2);
        QJsonObject json_obj = json_doc.object();

        QString balance = json_obj["balance"].toString();
        qDebug()<<balance;
         QString creditLimit = json_obj["creditLimit"].toString();
         qDebug()<<creditLimit;
         QString accountnumber = json_obj["accountNumber"].toString();
         qDebug()<<accountnumber;

       history_wPtr->setLabelSaldo(balance + "€");
       history_wPtr->setLabelCredit(creditLimit + "€"); //tietojen asettaminen
       history_wPtr->setLabelaccountnumber("FI" + accountnumber);

       QString url5 = "http://localhost:3000/customer/"+id_acc;
       QNetworkRequest request3(url5);
       request3.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

       //WEBTOKEN ALKU
       QByteArray myToken="Bearer "+webToken;
       request3.setRawHeader(QByteArray("Authorization"), myToken);
       //WEBTOKEN LOPPU

       customerManager2 = new QNetworkAccessManager(this);
       connect(customerManager2, SIGNAL(finished(QNetworkReply*)), this, SLOT(customerSlot2(QNetworkReply*)));
       customerreply2 = customerManager2->get(request3);

    }
}

void transaction::customerSlot2(QNetworkReply *customerreply2){

    response_data6 = customerreply2->readAll();

    if(response_data6 == "Forbidden") {
       soundObj.playSound(2);
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
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data6);
        QJsonObject json_obj = json_doc.object();
        QString username = json_obj["fname"].toString();
        qDebug()<<username;

       history_wPtr->setLabelusername("TERVETULOA " +username  + "!"); //tiedon asettaminen
    }
    customerreply2->deleteLater();
    customerManager2->deleteLater(); //poistellaan replyt ja managerit
    saldoreply->deleteLater();
    saldoManager2->deleteLater();
    historyreply->deleteLater();
    historyManager->deleteLater();
}

