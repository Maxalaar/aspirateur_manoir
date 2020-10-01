#include "deplacement_thread.h"

void Deplacement_thread::run()
{
    QThread::msleep(temps_attente_ms);
    emit fin_deplacement(entite, position_arriver_x, position_arriver_y);
}
