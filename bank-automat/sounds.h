#ifndef SOUNDS_H
#define SOUNDS_H
#include "QMediaPlayer"
#include "QAudioOutput"

class sounds
{
public:
    sounds();
    ~sounds();

public slots:
    void playSound(int);

private:
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    QString filePath;
};

#endif // SOUNDS_H
