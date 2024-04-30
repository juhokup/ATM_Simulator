#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>

// opened window = 2 kun menu aukeaa

int elapsed_time = 0; // kaikkialla sama aika, voidaan resetoida muista ikkunoista asettamalla nollaksi ilman että timer pysähtyy.
short opened_window = 0;
short logOut_clicked = 0;
short msgbox_status = 0;
bool cardLocked = false;

// Riittää, kun elapsed_time asetetaan aina nollaksi, kun jotain tehdään (nappia painetaan, ikkuna aukeaa/sulkeutuu).
// Pysäyttämisen ja ikkunan sulkemisen hoitaa updateTime() alempana.


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    soundObj.playSound(0);
    this->showFullScreen();
    MainWindow::waitCardInsert();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::waitCardInsert()
{
    elapsed_time=0;
    qDebug()<<"wait card insert";
    pinPtr = new Login(this);
    connect(pinPtr, SIGNAL(backToMainWindow()), this, SLOT(backTo_waitCardInsert()));
    connect(pinPtr, SIGNAL(cardInsert(QString)), this, SLOT(handleInsertCardClick(QString)));
}

void MainWindow::backTo_waitCardInsert()
{
    qDebug()<<"back to wait card insert";
    // voidaan poistaa, kun varoitusikkunoita ei ole auki
    if (msgbox_status == 0) delete pinPtr;
    pQTimer->stop();
    disconnect(pQTimer);
    delete pQTimer;
    waitCardInsert();
    this->showFullScreen();
}

void MainWindow::handleInsertCardClick(QString s)
{
    qDebug()<<"handle insert card";
    cardNumber = s;

    msgbox_status = 0;
    card_was_inserted = 1;
    elapsed_time = 0;
    opened_window = 1;

    pinPtr->showFullScreen();
    //pinPtr->open();

    // ajanotto alkaa
    pQTimer = new QTimer(this);
    connect(pQTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    pQTimer->start(1000);
}


void MainWindow::updateTime()
{
    elapsed_time += 1000; // +1 sec to elapsed count
    if(logOut_clicked == 1) logOut_clicked = 0, opened_window = 0, backTo_waitCardInsert();

    if (cardLocked == true){
        soundObj.playSound(2);
        QMessageBox msgBox;

        msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                             "QLabel{ color: white}");
        msgBox.setText("Kortti lukittu tai ei käytössä. Ota yhteys pankkiin.");
        msgBox.exec();
        opened_window = 0;
        pinPtr->close();
        MainWindow::backTo_waitCardInsert();
    }
    if (elapsed_time >= TIME_LIMIT_PIN && opened_window == 1){
        // PIN syöttöikkunan ollessa auki aikaa 10s ennen kuin palataan kirjautumisnäkymään ('syötä kortti')
        soundObj.playSound(2);
        QMessageBox msgBox;
        pinPtr->close();
        MainWindow::backTo_waitCardInsert();
        opened_window=0;
        msgBox.setWindowTitle("ERROR");
        msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                             "QLabel{ color: white}");
        msgBox.setText("Yhteys aikakatkaistu!");
        msgBox.exec();
    }
    else if (elapsed_time >= TIME_LIMIT_LOGGEDIN && opened_window == 2){
        // sisäänkirjautuneena 30s aikaa ennen kuin palataan alkunäkymään; jos jotain tehdään aika resetoituu
        soundObj.playSound(2);
        QMessageBox msgBox;
        pinPtr->close();
        MainWindow::backTo_waitCardInsert();
        opened_window=0;
        msgBox.setWindowTitle("ERROR");
        msgBox.setStyleSheet("QMessageBox{ background-color: #5C45C1;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                             "QPushButton{ background-color: #6D54EA; color: #FFCB91;}"
                             "QLabel{ color: white}");
        msgBox.setText("Yhteys aikakatkaistu!");
        msgBox.exec();
    }
    qDebug()<<elapsed_time;
}


//  Tätä käytettiin työn helpottamiseksi, kun RFID-lukijaa ei löytynyt kaikilta ryhmän jäseniltä
// void MainWindow::on_pushButton_clicked() //ettei tarvinnut aina kortinlukijaa
// {
//     //cardNumber = "06000626F2";
//     //handleInsertCardClick("06000626F2");
// }