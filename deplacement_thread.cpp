#include "deplacement_thread.h"

void Deplacement_thread::run()
{
    QThread::msleep(temps_attente_ms);
//    qDebug() << "hello from worker thread " << thread()->currentThreadId();
    emit fin_deplacement(entite, position_arriver_x, position_arriver_y);
}
