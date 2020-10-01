#include "aspiration_thread.h"

void Aspiration_thread::run()
{
    QThread::msleep(temps_attente_ms);
    emit fin_aspiration(entite);
}
