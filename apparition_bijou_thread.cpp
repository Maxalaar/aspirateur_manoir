#include "apparition_bijou_thread.h"

void Apparition_bijou_thread::run()
{
    QThread::msleep(temps_attente_ms);
    emit fin_apparition_bijou();
}
