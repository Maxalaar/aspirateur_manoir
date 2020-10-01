#ifndef SALLE_MANOIR_H
#define SALLE_MANOIR_H

#include <QVector>

#include "entite_simulation.h"

class Salle_manoir
{
public:
    Salle_manoir();
    int position_x;
    int position_y;
    QVector<Entite_simulation*> liste_entite;
};

#endif // SALLE_MANOIR_H
