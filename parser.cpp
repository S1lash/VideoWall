#include "parser.h"
#include <QDebug>
#include <QMessageBox>

Parser::Parser(QString string)
{
    QVector<QString> args;
    QRegExp regStart("_!ARG!_");
    QRegExp regEnd("_!END!");
    int start = 0 , end = 0;
    while (string.indexOf(regStart,0) >=0){
        start = string.indexOf(regStart,0);
        end = string.indexOf(regEnd,0);
        end += 5;
        QString temp = string.mid(start, end-start+1);
        QRegExp tempReg (temp);
        string.remove(start, end-start+1);
        temp.remove(regStart);
        temp.remove(regEnd);
        this->args.append(temp);
        start = 0;
        end = 0;
    }
}

