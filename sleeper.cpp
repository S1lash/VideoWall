#include "sleeper.h"

Sleeper::Sleeper()
{

}

void Sleeper::Sleep(unsigned long secs)
{
    QThread::sleep(secs);
}
