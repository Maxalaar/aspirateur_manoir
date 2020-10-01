#ifndef ASPIRATION_THREAD_H
#define ASPIRATION_THREAD_H

#include <QThread>
#include "entite_simulation.h"

class Aspiration_thread : public QThread
{
    Q_OBJECT
public:
    void run();
    Entite_simulation* entite;
    int temps_attente_ms;

signals:
    void fin_aspiration(Entite_simulation* entite);
};

#endif // ASPIRATION_THREAD_H
