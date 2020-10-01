#include "vision_thread.h"

void Vision_thread::run()
{
    QThread::msleep(temps_attente_ms);
    emit fin_vision(entite);
}
