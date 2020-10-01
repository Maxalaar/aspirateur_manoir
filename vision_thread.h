#ifndef VISION_THREAD_H
#define VISION_THREAD_H

#include <QThread>
#include "entite_simulation.h"

class Vision_thread : public QThread
{
    Q_OBJECT
public:
    void run();
    Entite_simulation* entite;
    int temps_attente_ms;

signals:
    void fin_vision(Entite_simulation* entite);
};

#endif // VISION_THREAD_H
