#ifndef PARSER_H
#define PARSER_H
#include <QVector>
#include <QString>
#include <QRegExp>
using namespace std;

class Parser
{
public:
    Parser(QString string);
    QVector<QString> args;
};

#endif // PARSER_H
