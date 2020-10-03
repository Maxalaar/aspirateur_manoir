#ifndef APPARITION_POUSSIERE_THREAD_H
#define APPARITION_POUSSIERE_THREAD_H

#include <QThread>

class Apparition_poussiere_thread : public QThread
{
    Q_OBJECT
public:
    void run();
    int temps_attente_ms;

signals:
    void fin_apparition_poussiere();
};

#endif // APPARITION_POUSSIERE_THREAD_H
