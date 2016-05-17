#include "player.h"
#include <QApplication>


int Player::down = 0;
int Player::right = 0;

Player::Player(QString PathToVideo, QString uniqKey, QGridLayout *layout, int size)
{
    mp = new QMediaPlayer;
    vw = new QVideoWidget;
    this->key = uniqKey;
    this->path = PathToVideo;
    this->layout = layout;
    this->size = size;
    if (size == 1){
        this->right = 0;
        this->down = 0;
    }
}

void Player::Play()
{
    mp->setVideoOutput(vw);
    mp->setMedia(QUrl::fromLocalFile(this->path));
    vw->show();

    int matrix = (right + 1) * (down + 1);
    if (size-1 < matrix) {
        int x;
        int y;
        if (size == matrix) {
            x= right;
            y = down;
        } else
        if (down == right){
            y = down;
            if (right == 0){
                x = 0;
            } else x = right - (matrix - size);
        } else {
            x = right;
            if (down == 0){
                y = 0;
            } else y = down - (matrix - size);
        }
        layout->addWidget(vw, y, x, 1, 1);
        mp->play();
        QApplication::processEvents();
    } else
        if (size - 1 == matrix){
            if (down == right){
                right += 1;
                this->Play();
            } else {
                down += 1;
                this->Play();
            }
        }
}


void Player::Close(int size)
{
    if (size == 1){
        mp->stop();
        vw->close();
        layout->removeWidget(vw);
    } else {
        int j = right;
        int i = down;
        while (j >= 0 && i >= 0 && layout->itemAtPosition(i,j) == 0){
            if (down == right){
                j-=1;
            } else {
                i -= 1;
            }
        }

            int row = 0;
            int column = 0;
            int rowSpan = 0;
            int columnSpan = 0;
            int idx = layout->indexOf(this->vw);
            layout->getItemPosition(idx, &row, &column, &rowSpan, &columnSpan);
            layout->addWidget(layout->itemAtPosition(i,j)->widget(), row, column, 1, 1);
            mp->stop();
            vw->close();
            if (down == right){
                if (down - ((right +1) * (down + 1) - size) == 0 && down > 0){
                    down-=1;
                }
            } else {
                if (right - ((right +1) * (down + 1) - size) == 0 && right > 0){
                    right-=1;
                }
            }

    }
    QApplication::processEvents();
}
