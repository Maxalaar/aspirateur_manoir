#ifndef ENTITE_SIMULATION_H
#define ENTITE_SIMULATION_H

#include <QString>
#include <QThread>
#include <QObject>
#include <QVector>

enum class action_type
{
    deplacement_haut,
    deplacement_bas,
    deplacement_gauche,
    deplacement_droite,
    voir,
    ramasser,
    aspirer
};

class Entite_simulation : public QThread
{
    Q_OBJECT
public:
    Entite_simulation();
    QString type_entite;
    int position_x;
    int position_y;
};

#endif // ENTITE_SIMULATION_H
