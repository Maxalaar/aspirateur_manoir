#ifndef RAMASSAGE_THREAD_H
#define RAMASSAGE_THREAD_H

#include <QThread>
#include "entite_simulation.h"

class Ramassage_thread : public QThread
{
    Q_OBJECT
public:
    void run();
    Entite_simulation* entite;
    int temps_attente_ms;

signals:
    void fin_ramassage(Entite_simulation* entite);
};

#endif // RAMASSAGE_THREAD_H
