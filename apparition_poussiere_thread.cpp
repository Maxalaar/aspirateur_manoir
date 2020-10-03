#include "apparition_poussiere_thread.h"

void Apparition_poussiere_thread::run()
{
    QThread::msleep(temps_attente_ms);
    emit fin_apparition_poussiere();
}
