#include "aspirateur_agent.h"

Aspirateur_agent::Aspirateur_agent(int position_initial_x, int position_initial_y, Environnement_manoir* manoir)
{
    position_x = position_initial_x;
    position_y = position_initial_y;
    type_entite = "aspirateur";
    this->manoir = manoir;
    manoir->placer_entite(position_x, position_y, this);

    //On connecte les fonctions de mouvement
    QObject::connect(this, &Aspirateur_agent::deplacement_haut, manoir, &Environnement_manoir::deplacement_haut_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_bas, manoir, &Environnement_manoir::deplacement_bas_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_gauche, manoir, &Environnement_manoir::deplacement_gauche_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_droite, manoir, &Environnement_manoir::deplacement_droite_entite);

    //On connecte la détection de la fin de l'action de mouvement
    QObject::connect(manoir, &Environnement_manoir::fin_action, this, &Aspirateur_agent::fonction_planification);

    //On connecte la vision de l'agent aspirateur
    QObject::connect(this, &Aspirateur_agent::voir_manoire, manoir, &Environnement_manoir::mise_jour_manoire);
    QObject::connect(manoir, &Environnement_manoir::mise_jour_manoir, this, &Aspirateur_agent::mise_jour_manoire);

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

void Aspirateur_agent::mise_jour_manoire(Entite_simulation* entite, QVector<QVector<Salle_manoir>> tableau)
{
    if(entite == this)
    {
        this->tableau = tableau;
    }
}
