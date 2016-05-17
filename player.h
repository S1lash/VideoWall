#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGridLayout>

class Player
{
private:
    QGridLayout *layout;
    static int right;
    static int down;
    int size;
public:
    Player(QString pathToVideo, QString uniqKey, QGridLayout *layout, int size);
    void Play();
    void Close(int size);
    void Change();
    QString key;
    QString path;

    QMediaPlayer *mp;
    QVideoWidget *vw;

};

#endif // PLAYER_H
