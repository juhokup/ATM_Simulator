#ifndef CURRENCY_H
#define CURRENCY_H

#include "sounds.h"
#include <QDialog>
#include <QMessageBox>
#include <QDialog>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

extern float currency_rate[5];
extern int current_currency;

extern int elapsed_time;

namespace Ui {
class currency;
}

class currency : public QDialog
{
    Q_OBJECT

public:
    explicit currency(QWidget *parent = nullptr);
    ~currency();
    currency *currency_wPtr;

private:
    Ui::currency *ui;
    //int currency_eur = 1;
    //int currency_usd = 1;
    //int currency_gbp = 1;
    //int currency_sek = 11;
    //int currency_yen = 164;
    void currencyRateHandler(int);

    sounds soundObj;
private slots:
    void on_btn_exit_clicked();
    void on_btn_eur_clicked();
    void on_btn_usd_clicked();
    void on_btn_gbp_clicked();
    void on_btn_sek_clicked();
    void on_btn_yen_clicked();
};

#endif // CURRENCY_H
