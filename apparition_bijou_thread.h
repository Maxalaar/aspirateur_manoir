#ifndef APPARITION_BIJOU_THREAD_H
#define APPARITION_BIJOU_THREAD_H

#include <QThread>

class Apparition_bijou_thread : public QThread
{
     Q_OBJECT
public:
    void run();
    int temps_attente_ms;

signals:
    void fin_apparition_bijou();
};

#endif // APPARITION_BIJOU_THREAD_H
