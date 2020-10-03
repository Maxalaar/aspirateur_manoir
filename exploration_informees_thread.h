#ifndef EXPLORATION_INFORMEES_THREAD_H
#define EXPLORATION_INFORMEES_THREAD_H

#include <QThread>
#include <QVector>
#include <QtMath>

#include "entite_simulation.h"
#include "salle_manoir.h"

class Exploration_informees_thread : public QThread
{
    Q_OBJECT
public:
    void run();
    Entite_simulation* entite;
    QVector<QVector<Salle_manoir>> tableau;

signals:
    void fin_exploration_informees(Entite_simulation* entite, QVector<int> action_resulta_exploration);

};

#endif // EXPLORATION_INFORMEES_THREAD_H
