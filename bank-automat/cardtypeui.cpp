#include "cardtypeui.h"
#include "ui_cardtypeui.h"

cardtypeui::cardtypeui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cardtypeui)
{
    ui->setupUi(this);
    this->showFullScreen();
    soundObj.playSound(1);
}

cardtypeui::~cardtypeui()
{
    qDebug()<<"cardtype poistettu";
    delete ui;
}


void cardtypeui::on_btn_credit_clicked()
{
    soundObj.playSound(4);
    url_idcard_combi = "http://localhost:3000/card_privileges/getAccountCredit/"+id_card;
    this->close();
}

void cardtypeui::on_btn_debit_clicked()
{
    soundObj.playSound(4);
    url_idcard_combi = "http://localhost:3000/card_privileges/getAccountDebit/"+id_card;
    this->close();
}
