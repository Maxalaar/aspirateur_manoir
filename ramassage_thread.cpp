#include "ramassage_thread.h"

void Ramassage_thread::run()
{
    QThread::msleep(temps_attente_ms);
    emit fin_ramassage(entite);
}
