#ifndef DEPLACEMENT_THREAD_H
#define DEPLACEMENT_THREAD_H

#include <QThread>
#include <QtDebug>

#include "entite_simulation.h"

class Deplacement_thread : public QThread
{
    Q_OBJECT
public:
    void run();
    Entite_simulation* entite;
    int position_arriver_x;
    int position_arriver_y;
    int temps_attente_ms;

signals:
    void fin_deplacement(Entite_simulation* entite, int position_arriver_x, int position_arriver_y);
};

#endif // DEPLACEMENT_THREAD_H
