#include "environement_manoir.h"

Environnement_manoir::Environnement_manoir(QVector<int> taille_manoir)
{
    //On crée les salles
    for(int i = 0; i < taille_manoir[1]; i++)
    {
        QVector<Salle_manoir> ligne_salle_prov;

        for(int j = 0; j < taille_manoir[0]; j++)
        {
            Salle_manoir salle_manoir_prov;
            salle_manoir_prov.position_x = i;
            salle_manoir_prov.position_y = j;
            ligne_salle_prov.push_back(salle_manoir_prov);
        }

        this->tableau.push_back(ligne_salle_prov);
    }

    //On crée et on place les poussieres
    for(int i = 0; i < nombre_poussiere_initiale ; i++)
    {
        Entite_simulation* poussiere = new Entite_simulation();
        poussiere->position_x = QRandomGenerator::global()->bounded(tableau[0].size());
        poussiere->position_y = QRandomGenerator::global()->bounded(tableau.size());
        poussiere->type_entite = "poussiere";
        this->placer_entite(poussiere->position_x, poussiere->position_y, poussiere);
    }

    //On crée et on place les bijoux
    for(int i = 0; i < nombre_bijou_initiale ; i++)
    {
        Entite_simulation* bijou = new Entite_simulation();
        bijou->position_x = QRandomGenerator::global()->bounded(tableau[0].size());
        bijou->position_y = QRandomGenerator::global()->bounded(tableau.size());
        bijou->type_entite = "bijou";
        this->placer_entite(bijou->position_x, bijou->position_y, bijou);
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

void Environnement_manoir::deplacement_entite(Entite_simulation* entite, int position_x, int position_y)
{
    for(int i = 0; i < tableau[entite->position_x][entite->position_y].liste_entite.size(); i++)
    {
        if(tableau[entite->position_x][entite->position_y].liste_entite[i] == entite && entite->type_entite == "aspirateur")
        {
            tableau[entite->position_x][entite->position_y].liste_entite.remove(i);
        }
    }

    entite->position_x = position_x;
    entite->position_y = position_y;

    this->placer_entite(position_x, position_y, entite);
    emit rafraichissement_image();
    emit fin_action(entite);
}

void Environnement_manoir::deplacement_droite_entite(Entite_simulation* entite)
{
    if(0 <= entite->position_x + 1 && entite->position_x + 1 < tableau[0].size() && 0 <= entite->position_y && entite->position_y < tableau.size())
    {
        Deplacement_thread* deplacement = new Deplacement_thread;
        QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
        deplacement->entite = entite;
        deplacement->position_arriver_x = entite->position_x + 1;
        deplacement->position_arriver_y = entite->position_y;
        deplacement->temps_attente_ms = temps_deplacement_ms;
        deplacement->start();
    }
}

void Environnement_manoir::deplacement_gauche_entite(Entite_simulation* entite)
{
    if(0 <= entite->position_x - 1 && entite->position_x - 1 < tableau[0].size() && 0 <= entite->position_y && entite->position_y < tableau.size())
    {
        Deplacement_thread* deplacement = new Deplacement_thread;
        QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
        deplacement->entite = entite;
        deplacement->position_arriver_x = entite->position_x - 1;
        deplacement->position_arriver_y = entite->position_y;
        deplacement->temps_attente_ms = temps_deplacement_ms;
        deplacement->start();
    }
}

void Environnement_manoir::deplacement_bas_entite(Entite_simulation* entite)
{
    if(0 <= entite->position_x && entite->position_x < tableau[0].size() && 0 <= entite->position_y - 1 && entite->position_y - 1 < tableau.size())
    {
        Deplacement_thread* deplacement = new Deplacement_thread;
        QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
        deplacement->entite = entite;
        deplacement->position_arriver_x = entite->position_x;
        deplacement->position_arriver_y = entite->position_y - 1;
        deplacement->temps_attente_ms = temps_deplacement_ms;
        deplacement->start();
    }
}

void Environnement_manoir::deplacement_haut_entite(Entite_simulation* entite)
{
    if(0 <= entite->position_x && entite->position_x < tableau[0].size() && 0 <= entite->position_y + 1 && entite->position_y + 1 < tableau.size())
    {
        Deplacement_thread* deplacement = new Deplacement_thread;
        QObject::connect(deplacement, &Deplacement_thread::fin_deplacement, this, &Environnement_manoir::deplacement_entite);
        deplacement->entite = entite;
        deplacement->position_arriver_x = entite->position_x;
        deplacement->position_arriver_y = entite->position_y + 1;
        deplacement->temps_attente_ms = temps_deplacement_ms;
        deplacement->start();
    }
}

//Gestion de la vision des agents
void Environnement_manoir::mise_jour_manoire_init(Entite_simulation* entite)
{
    Vision_thread* vision = new Vision_thread;
    QObject::connect(vision, &Vision_thread::fin_vision, this, &Environnement_manoir::mise_jour_manoire);
    vision->entite = entite;
    vision->temps_attente_ms = temps_vision_ms;
    vision->start();
}

void Environnement_manoir::mise_jour_manoire(Entite_simulation* entite)
{
    emit mise_jour_manoir(entite, this->tableau);
    emit fin_action(entite);
}

//Gestion du ramassage des agents
void Environnement_manoir::ramassage_init(Entite_simulation* entite)
{
    Ramassage_thread* ramassage = new Ramassage_thread;
    QObject::connect(ramassage, &Ramassage_thread::fin_ramassage, this, &Environnement_manoir::ramassage);
    ramassage->entite = entite;
    ramassage->temps_attente_ms = temps_vision_ms;
    ramassage->start();
}

void Environnement_manoir::ramassage(Entite_simulation* entite)
{
    for(int i = 0; i < tableau[entite->position_x][entite->position_y].liste_entite.size(); i++)
    {
        if(tableau[entite->position_x][entite->position_y].liste_entite[i]->type_entite == "bijou")
        {
            tableau[entite->position_x][entite->position_y].liste_entite.remove(i);
        }
    }
    emit fin_action(entite);
}

void Environnement_manoir::aspiration_init(Entite_simulation* entite)
{
    Aspiration_thread* aspiration = new Aspiration_thread;
    QObject::connect(aspiration, &Aspiration_thread::fin_aspiration, this, &Environnement_manoir::aspiration);
    aspiration->entite = entite;
    aspiration->temps_attente_ms = temps_vision_ms;
    aspiration->start();
}

void Environnement_manoir::aspiration(Entite_simulation* entite)
{
    for(int i = 0; i < tableau[entite->position_x][entite->position_y].liste_entite.size(); i++)
    {
        if(tableau[entite->position_x][entite->position_y].liste_entite[i]->type_entite == "poussiere" || tableau[entite->position_x][entite->position_y].liste_entite[i]->type_entite == "bijou")
        {
            tableau[entite->position_x][entite->position_y].liste_entite.remove(i);
        }
    }
    emit fin_action(entite);
}
