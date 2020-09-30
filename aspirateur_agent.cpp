#include "aspirateur_agent.h"

Aspirateur_agent::Aspirateur_agent(int position_initial_x, int position_initial_y, Environnement_manoir* manoir)
{
    position_x = position_initial_x;
    position_y = position_initial_y;
    type_entite = "aspirateur";
    this->manoir = manoir;
    manoir->placer_entite(position_x, position_y, this);
    QObject::connect(this, &Aspirateur_agent::deplacement_haut, manoir, &Environnement_manoir::deplacement_haut_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_bas, manoir, &Environnement_manoir::deplacement_bas_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_gauche, manoir, &Environnement_manoir::deplacement_gauche_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_droite, manoir, &Environnement_manoir::deplacement_droite_entite);

    QObject::connect(manoir, &Environnement_manoir::fin_deplacement, this, &Aspirateur_agent::fonction_planification);

    emit deplacement_haut(this);
//    qDebug() << "Markeur 1 : " << thread()->currentThreadId();
}

void Aspirateur_agent::fonction_planification(Entite_simulation* entite)
{
    if(entite == this)
    {
        emit deplacement_haut(this);
    }
}
