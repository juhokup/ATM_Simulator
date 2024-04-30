#ifndef CARDTYPEUI_H
#define CARDTYPEUI_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>
#include <QMessageBox>
#include "sounds.h"

extern QString url_idcard_combi;
extern QString id_card;

namespace Ui {
class cardtypeui;
}

class cardtypeui : public QDialog
{
    Q_OBJECT

public:
    explicit cardtypeui(QWidget *parent = nullptr);
    ~cardtypeui();

private:
    Ui::cardtypeui *ui;
    sounds soundObj;

private slots:
    void on_btn_credit_clicked();
    void on_btn_debit_clicked();

};

#endif // CARDTYPEUI_H
