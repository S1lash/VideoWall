#include "dialog.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMessageBox>
#include <QString>
#include <QSharedMemory>
#include <QByteArray>
#include <QFile>
#include <sleeper.h>
#include <QVector>
#include <QMap>
#include <parser.h>
#include <player.h>
#include <QMediaPlaylist>
#include <QGridLayout>

using namespace std;

void Msg(QString text){
    QMessageBox msg;
    msg.setText(text);
    msg.addButton(QMessageBox::Button::Close);
    msg.addButton(QMessageBox::Button::Ok);
    int ret = msg.exec();
    if (ret == QMessageBox::Close){
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
QApplication a(argc, argv);

QDialog D;
QGridLayout *layout = new QGridLayout;
layout->setMargin(0);
layout->setSizeConstraint(QLayout::SetNoConstraint);
layout->setVerticalSpacing(1);
layout->setSpacing(1);
D.setLayout(layout);
D.setMinimumSize(70,70);
D.setWindowTitle("Player");

QSharedMemory mem("VideoWall.app");
bool isRuning;
if (!mem.create(10) && mem.error()==QSharedMemory::AlreadyExists){
    isRuning = true;
} else isRuning = false;

if (isRuning == false && argc != 1){
    Msg("Invalid start arguments!");
    return 0;
}
if (isRuning == true && (argc > 4 || argc < 2)){
    Msg("Invalid args (1..3)!");
    return 0;
}

QByteArray bar("");
if (argc != 1){
    for (int i = 1; i < argc; ++i) {
        bar.append("_!ARG!_");
        bar.append(argv[i]);
        bar.append("_!END!");
    }
}

if (!isRuning) {
    mem.create(10);
    mem.lock();
        char *data = (char*) mem.data();
        for (int i = 0; i < bar.size(); ++i) {
        data[i] = bar[i];
        }
    mem.unlock();
} else {
    if(mem.attach()){
            bool check = true;
            while (check){
                Sleeper::sleep(2);
                mem.lock();
                char *data = (char*) mem.data();
                QByteArray tempArr(data);
                if (tempArr.size() == 0){
                    check = false;
                } else mem.unlock();
            }
            char *data = (char*) mem.data();
            for (int i = 0; i < bar.size(); ++i) {
                data[i] = bar[i];
            }
        mem.unlock();
     } else Msg("No attach!");
    return 0;
}

QString quit("quit");
QString open("open");
QString close("close");
QMap<QString,Player*> playlist;
while (true){
        a.processEvents();
        Sleeper::sleep(1);
        mem.lock();
        char *data = (char*) mem.data();
        mem.unlock();
        QByteArray dBar(data);
        if (dBar.size() == 0){
           continue;
        } else {
            QString comand(dBar);
            Parser par(comand);

            if (par.args.size() == 1){
                if (par.args[0] == quit){
                    return 0;
                } else Msg("Incorrect arg");
            } else
            if (par.args.size() == 2){
                if (par.args[0] == close){
                    if (playlist.count(par.args[1]) > 0){

                        playlist.find(par.args[1]).value()->Close(playlist.size());
                        playlist.remove(par.args[1]);
                        if (playlist.size() == 0){
                            D.hide();
                        }
                        a.processEvents();

                    } else Msg ("This video does't exist");
                } else Msg ("Incorrect arg");
            } else
            if (par.args.size() == 3){
                if (par.args[0] == open){
                    QFile file(par.args[2]);
                    QRegExp format("*.mpg",Qt::CaseInsensitive, QRegExp::Wildcard);
                    if (par.args[2].contains(format) && file.exists()){
                        if (playlist.count(par.args[1]) == 0){

                            Player *player = new Player(par.args[2], par.args[1], layout, playlist.size()+1);
                            if (playlist.size() == 0){
                                D.show();
                            }
                            player->Play();
                            playlist.insert(par.args[1], player);
                            a.processEvents();

                        } else Msg("This video already exists");
                    } else Msg("Can't open file");
                } else Msg ("Incorrect arg");
            }




            QByteArray clean("");
            for (int i = 0; i < dBar.size(); ++i) {
                data[i] = clean[0];
             }
        }

}
return a.exec();
}


