#include "sounds.h"
#include "QDebug"

sounds::sounds()
{
    player->setAudioOutput(audioOutput);
    //qDebug() << "sounds konstruktori";
}

sounds::~sounds()
{
    //qDebug() << "sounds destruktori";
    delete player;
    delete audioOutput;
}

void sounds::playSound(int sound)
{
    //0=start, 1=true, 2=false, 3=insert card, 4=click
    //5=printing, 6=EUR, 7=USD, 8=GBP, 9=SEK, 10=YEN
    //qDebug()<<"ääni toistetaan";
    QUrl url;
    if (sound==0){
        url = QUrl("qrc:///sound/flags/system_start.wav");
    }
    else if (sound==1){
        url = QUrl("qrc:///sound/flags/pin_correct.wav");
    }
    else if (sound==2){
        url = QUrl("qrc:///sound/flags/pin_wrong.wav");
    }
    else if (sound==3){
        url = QUrl("qrc:///sound/flags/insert_card.wav");
    }
    else if (sound==4){
        url = QUrl("qrc:///sound/flags/click.mp3");
    }
    else if (sound==5){
        url = QUrl("qrc:///sound/flags/printings.mp3");
    }
    else if (sound==6){
        url = QUrl("qrc:///sound/flags/EUR.mp3");
    }
    else if (sound==7){
        url = QUrl("qrc:///sound/flags/USD.mp3");
    }
    else if (sound==8){
        url = QUrl("qrc:///sound/flags/GBP.mp3");
    }
    else if (sound==9){
        url = QUrl("qrc:///sound/flags/SEK.mp3");
    }
    else if (sound==10){
        url = QUrl("qrc:///sound/flags/YEN.mp3");
    }
    else if (sound==11){
        url = QUrl("qrc:///sound/flags/scan_card.mp3");
    }
    player->setSource(url);
    player->play();
}
