#ifndef SLEEPER_H
#define SLEEPER_H
#include <QThread>

class Sleeper: public QThread
{
public:
    Sleeper();
    static void Sleep (unsigned long secs);
};

#endif // SLEEPER_H
