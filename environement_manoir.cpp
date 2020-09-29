#include "environement_manoir.h"

Environnement_manoir::Environnement_manoir(QVector<int> taille_manoir)
{
    for(int i = 0; i < taille_manoir[1]; i++)
    {
        QVector<Salle_manoir> ligne_salle_prov;

        for(int j = 0; j < taille_manoir[0]; j++)
        {
            Salle_manoir salle_manoir_prov;
            ligne_salle_prov.push_back(salle_manoir_prov);
        }

        this->tableau.push_back(ligne_salle_prov);
    }
}

QVector<QVector<Salle_manoir>> Environnement_manoir::get_tableau()
{
    return tableau;
}

void Environnement_manoir::placer_entite(int positon_x, int positon_y, Entite_simulation* entite)
{
    tableau[positon_x][positon_y].liste_entite.push_back(entite);
}

//void Environnement_manoir::run()
//{
    
//}

void Environnement_manoir::deplacement_entite(Entite_simulation* entite, int position_x, int position_y)
{
    for(int i = 0; i < tableau[entite->position_x][entite->position_y].liste_entite.size(); i++)
    {
        if(tableau[entite->position_x][entite->position_y].liste_entite[i] == entite)
        {
            tableau[entite->position_x][entite->position_y].liste_entite.remove(i);
        }
    }

    entite->position_x = position_x;
    entite->position_y = position_y;

    this->placer_entite(position_x, position_y, entite);
    emit rafraichissement_image();
}

void Environnement_manoir::deplacement_haut_entite(Entite_simulation* entite)
{
    Deplacement_thread* deplacement = new Deplacement_thread;
    QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
    deplacement->entite = entite;
    deplacement->position_arriver_x = entite->position_x + 1;
    deplacement->position_arriver_y = entite->position_y;
    deplacement->temps_attente_ms = temps_deplacement_ms;
    deplacement->start();
//    qDebug() << "Markeur 2 : " << thread()->currentThreadId();
}

void Environnement_manoir::deplacement_bas_entite(Entite_simulation* entite)
{
    Deplacement_thread* deplacement = new Deplacement_thread;
    QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
    deplacement->entite = entite;
    deplacement->position_arriver_x = entite->position_x - 1;
    deplacement->position_arriver_y = entite->position_y;
    deplacement->temps_attente_ms = temps_deplacement_ms;
}

void Environnement_manoir::deplacement_gauche_entite(Entite_simulation* entite)
{
    Deplacement_thread* deplacement = new Deplacement_thread;
    QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
    deplacement->entite = entite;
    deplacement->position_arriver_x = entite->position_x;
    deplacement->position_arriver_y = entite->position_y - 1;
    deplacement->temps_attente_ms = temps_deplacement_ms;
}

void Environnement_manoir::deplacement_droite_entite(Entite_simulation* entite)
{
    Deplacement_thread* deplacement = new Deplacement_thread;
    QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
    deplacement->entite = entite;
    deplacement->position_arriver_x = entite->position_x;
    deplacement->position_arriver_y = entite->position_y + 1;
    deplacement->temps_attente_ms = temps_deplacement_ms;
}
