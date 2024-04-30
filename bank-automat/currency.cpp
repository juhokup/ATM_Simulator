#include "currency.h"
#include "ui_currency.h"

int current_currency;

currency::currency(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::currency)
{
    ui->setupUi(this);
    //this->showFullScreen();

    //ui->label_euro->setPixmap(QPixmap(":/icons/flags/eu.png"));
    //ui->btn_eur->setIcon(QIcon(":/icons/flags/eu.png"));
    //ui->btn_usd->setIcon(QIcon(":/icons/flags/us.png"));
    //ui->btn_gbp->setIcon(QIcon(":/icons/flags/gb.png"));
    //ui->btn_sek->setIcon(QIcon(":/icons/flags/se.png"));
    //ui->btn_yen->setIcon(QIcon(":/icons/flags/jp.png"));
    /*
    connect(ui->btn_eur,SIGNAL(clicked(bool)),
            this,SLOT(on_btn_eur_clicked()));
    connect(ui->btn_usd,SIGNAL(clicked(bool)),
            this,SLOT(on_btn_usd_clicked()));
    connect(ui->btn_gbp,SIGNAL(clicked(bool)),
            this,SLOT(on_btn_gbp_clicked()));
    connect(ui->btn_sek,SIGNAL(clicked(bool)),
            this,SLOT(on_btn_sek_clicked()));
    connect(ui->btn_yen,SIGNAL(clicked(bool)),
            this,SLOT(on_btn_yen_clicked()));
    connect(ui->btn_exit,SIGNAL(clicked(bool)),
            this,SLOT(on_btn_exit_clicked()));
*/

}

currency::~currency()
{
    qDebug()<<"currency tuhottu";
    delete ui;
    //currency_wPtr->deleteLater();
}

void currency::on_btn_exit_clicked()
{
    soundObj.playSound(4);
    this->close();
    elapsed_time = 0;
}

void currency::on_btn_eur_clicked()
{
    QString temp = QString::number(currency_rate[0]);
    soundObj.playSound(6);
    elapsed_time = 0;
    qDebug()<<"EUROT VALITTU";
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                         "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                         "QLabel{ color: white}");
    msgBox.setText("Käytössä oleva valuutta : EURO \nNykyinen kurssi: "+temp);
    msgBox.exec();
    current_currency = 1;
}

void currency::on_btn_usd_clicked()
{
    QString temp = QString::number(currency_rate[1]);
    soundObj.playSound(7);
    elapsed_time = 0;
    qDebug()<<"DOLLARIT VALITTU";
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                         "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                         "QLabel{ color: white}");
    msgBox.setText("Käytössä oleva valuutta : USD \nNykyinen kurssi: "+temp);
    msgBox.exec();
    current_currency = 2;
}

void currency::on_btn_gbp_clicked()
{
    QString temp = QString::number(currency_rate[2]);
    soundObj.playSound(8);
    elapsed_time = 0;
    qDebug()<<"PUNNAT VALITTU";
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                         "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                         "QLabel{ color: white}");
    msgBox.setText("Käytössä oleva valuutta : PUNTA \nNykyinen kurssi: "+temp);
    msgBox.exec();
    current_currency = 3;

}

void currency::on_btn_sek_clicked()
{
    QString temp = QString::number(currency_rate[3]);
    soundObj.playSound(9);
    elapsed_time = 0;
    qDebug()<<"KRUUNUT VALITTU";
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                         "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                         "QLabel{ color: white}");
    msgBox.setText("Käytössä oleva valuutta : SEK \nNykyinen kurssi: "+temp);
    msgBox.exec();
    current_currency = 4;

}

void currency::on_btn_yen_clicked()
{
    QString temp = QString::number(currency_rate[4]);
    soundObj.playSound(10);
    elapsed_time = 0;
    qDebug()<<"JENIT VALITTU";
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox{ background-color: #1E0098;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;}"
                         "QPushButton{ background-color: #E2E2E2;font-family: Comic Sans MS; font-style: normal;  font-size: 15pt; color: #000000;border-width: 2px;border-radius: 5px;  }"
                         "QLabel{ color: white}");
    msgBox.setText("Käytössä oleva valuutta : JENI \nNykyinen kurssi: "+temp);

    msgBox.exec();
    current_currency = 5;
}

