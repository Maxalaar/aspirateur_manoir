#include "aspirateur_agent.h"

Aspirateur_agent::Aspirateur_agent(int position_initial_x, int position_initial_y, Environnement_manoir* manoir)
{
    position_x = position_initial_x;
    position_y = position_initial_y;
    type_entite = "aspirateur";
    this->manoir = manoir;
    manoir->placer_entite(position_x, position_y, this);
    this->tableau = manoir->get_tableau();
//    qDebug() << "la position de la salle fonction : " << this->tableau[0][0].position_x;

    //On connecte les fonctions de mouvement
    QObject::connect(this, &Aspirateur_agent::deplacement_haut, manoir, &Environnement_manoir::deplacement_haut_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_bas, manoir, &Environnement_manoir::deplacement_bas_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_gauche, manoir, &Environnement_manoir::deplacement_gauche_entite);
    QObject::connect(this, &Aspirateur_agent::deplacement_droite, manoir, &Environnement_manoir::deplacement_droite_entite);

    //On connecte la détection de la fin de l'action de mouvement
    QObject::connect(manoir, &Environnement_manoir::fin_action, this, &Aspirateur_agent::fonction_action);

    //On connecte la vision de l'agent aspirateur
    QObject::connect(this, &Aspirateur_agent::voir_manoire, manoir, &Environnement_manoir::mise_jour_manoire_init);
    QObject::connect(manoir, &Environnement_manoir::mise_jour_manoir, this, &Aspirateur_agent::mise_jour_manoire);

    //On connecte le ramassage de l'agent aspirateur
    QObject::connect(this, &Aspirateur_agent::ramasser_objet, manoir, &Environnement_manoir::ramassage_init);

    //On connecte l'aspiration de l'agent aspirateur
    QObject::connect(this, &Aspirateur_agent::aspirer_salle, manoir, &Environnement_manoir::aspiration_init);

    this->exploration_non_informees(this->tableau);
}

void Aspirateur_agent::fonction_action(Entite_simulation* entite)
{
    if(entite == this)
    {
        if(liste_action.size() > 0 /*&& compteur_vision < sycro_vision*/)
        {
            switch(liste_action[0])
            {
                case action_type::deplacement_haut :
                    emit deplacement_haut(this);
                    break;

                case action_type::deplacement_bas :
                    emit deplacement_bas(this);
                    break;

                case action_type::deplacement_gauche :
                    emit deplacement_gauche(this);
                    break;

                case action_type::deplacement_droite :
                    emit deplacement_droite(this);
                    break;

                case action_type::voir :
                    qDebug() << "Markeur 5 : ";
                    emit voir_manoire(this);
                    break;

                case action_type::ramasser :
                    emit ramasser_objet(this);
                    break;

                case action_type::aspirer :
                    emit aspirer_salle(this);
                    break;
            }
            liste_action.remove(0);
            compteur_vision = compteur_vision + 1;
        }
//        else
//        {
//            compteur_vision = 0;
//            emit voir_manoire(this);
//        }
    }
}

void Aspirateur_agent::mise_jour_manoire(Entite_simulation* entite, QVector<QVector<Salle_manoir>> tableau)
{
    if(entite == this)
    {
        this->tableau = tableau;
        this->exploration_non_informees(this->tableau);
        qDebug() << "Markeur 2 : ";
    }
}

void Aspirateur_agent::exploration_non_informees(QVector<QVector<Salle_manoir>> tableau)
{
    Exploration_non_informees_thread* exploration_non_informees_thread = new Exploration_non_informees_thread;
    qRegisterMetaType<QVector<int> >("QVector<int>");

    qDebug() << "Markeur 1 : ";

    QObject::connect(exploration_non_informees_thread, &Exploration_non_informees_thread::fin_exploration_non_informees, this, &Aspirateur_agent::mise_jour_liste_action);
    exploration_non_informees_thread->entite = this;
    exploration_non_informees_thread->tableau = tableau;
    exploration_non_informees_thread->start();

//    QVector<Salle_manoir*> salle_historique;
//    QVector<Salle_manoir*> salle_front_exploration_liste;
//    QVector<int> cout_front_exploration_liste;
//    QVector<QVector<action_type>> action_front_exploration_liste;

//    QVector<action_type> action_resulta_exploration;

//    //On cherche dans quelle salle se trouve l'aspirateur
//    Salle_manoir* salle_initial;
//    for(int i = 0; i < tableau[0].size(); i++)
//    {
//        for(int j = 0; j < tableau.size(); j++)
//        {
//            for(int k = 0; k <tableau[i][j].liste_entite.size(); k++)
//            {
//                if(tableau[i][j].liste_entite[k] == this)
//                {
//                    salle_initial = &tableau[i][j];
//                }
//            }
//        }
//    }

//    //On ajoute les données où ce trouve l'aspirateur
//    salle_front_exploration_liste.push_back(salle_initial);
//    cout_front_exploration_liste.push_back(0);
//    QVector<action_type> action_salle_initial;
//    action_front_exploration_liste.push_back(action_salle_initial);

//    bool continuer_exploration = true;

//    while(continuer_exploration && salle_front_exploration_liste.size() > 0)
//    {

//        //On cherche l'indice du sommet avec le plus faible cout
//        int cout_faible_valeur = std::numeric_limits<int>::max();
//        int cout_faible_indice = -1;

//        for(int i = 0; i < cout_front_exploration_liste.size(); i++)
//        {
//            if(cout_front_exploration_liste[i] < cout_faible_valeur)
//            {
//                cout_faible_indice = i;
//                cout_faible_valeur = cout_front_exploration_liste[i];
//            }
//        }

//        //On cherche si il y a de la poussiere dans cette salle
//        for(int i = 0; i < salle_front_exploration_liste[cout_faible_indice]->liste_entite.size(); i++)
//        {
//            if(salle_front_exploration_liste[cout_faible_indice]->liste_entite[i]->type_entite == "poussiere")
//            {
//                continuer_exploration = false;
//                action_front_exploration_liste[cout_faible_indice].push_back(action_type::aspirer);
//                action_resulta_exploration = action_front_exploration_liste[cout_faible_indice];
//            }
//        }

//        //On cherche si il y a un bijou dans cette salle
//        for(int i = 0; i < salle_front_exploration_liste[cout_faible_indice]->liste_entite.size(); i++)
//        {
//            if(salle_front_exploration_liste[cout_faible_indice]->liste_entite[i]->type_entite == "bijou")
//            {
//                continuer_exploration = false;
//                action_front_exploration_liste[cout_faible_indice].push_back(action_type::ramasser);
//                action_resulta_exploration = action_front_exploration_liste[cout_faible_indice];
//            }
//        }

//        //Si on trouve rien on develope les salles adjacente;
//        if(continuer_exploration == true)
//        {
//            //On develope la salle du haut si possible
//            if(salle_front_exploration_liste[cout_faible_indice]->position_y + 1 < tableau.size())
//            {
//                //On verifie que la salle est pas déja dans l'historique
//                bool salle_deja_vue = false;
//                for(int i = 0; i < salle_historique.size(); i++)
//                {
//                    if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]))
//                    {
//                        salle_deja_vue = true;
//                    }
//                }

//                if(salle_deja_vue == false)
//                {
//                    //On note cette salle comme vue
//                    salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]));

//                    //On trouve le chemin pour avoir la salle du haut
//                    QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
//                    action_salle_prov.push_back(action_type::deplacement_haut);
//                    action_front_exploration_liste.push_back(action_salle_prov);

//                    //On ajoute le cout
//                    cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1);

//                    //On ajoute la salle dans le front
//                    salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]));
//                }
//            }

//            //On develope la salle du bas si possible
//            if(salle_front_exploration_liste[cout_faible_indice]->position_y - 1 >= 0)
//            {
//                //On verifie que la salle est pas déja dans l'historique
//                bool salle_deja_vue = false;
//                for(int i = 0; i < salle_historique.size(); i++)
//                {
//                    if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]))
//                    {
//                        salle_deja_vue = true;
//                    }
//                }

//                if(salle_deja_vue == false)
//                {
//                    //On note cette salle comme vue
//                    salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]));

//                    //On trouve le chemin pour avoir la salle du bas
//                    QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
//                    action_salle_prov.push_back(action_type::deplacement_bas);
//                    action_front_exploration_liste.push_back(action_salle_prov);

//                    //On ajoute le cout
//                    cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1);

//                    //On ajoute la salle dans le front
//                    salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]));
//                }
//            }

//            //On develope la salle de gauche si possible
//            if(salle_front_exploration_liste[cout_faible_indice]->position_x - 1 >= 0)
//            {
//                //On verifie que la salle est pas déja dans l'historique
//                bool salle_deja_vue = false;
//                for(int i = 0; i < salle_historique.size(); i++)
//                {
//                    if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]))
//                    {
//                        salle_deja_vue = true;
//                    }
//                }

//                if(salle_deja_vue == false)
//                {
//                    //On note cette salle comme vue
//                    salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));

//                    //On trouve le chemin pour avoir la salle du bas
//                    QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
//                    action_salle_prov.push_back(action_type::deplacement_gauche);
//                    action_front_exploration_liste.push_back(action_salle_prov);

//                    //On ajoute le cout
//                    cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1);

//                    //On ajoute la salle dans le front
//                    salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));
//                }
//            }

//            //On develope la salle de droite si possible
//            if(salle_front_exploration_liste[cout_faible_indice]->position_x + 1 < tableau[0].size())
//            {
//                //On verifie que la salle est pas déja dans l'historique
//                bool salle_deja_vue = false;
//                for(int i = 0; i < salle_historique.size(); i++)
//                {
//                    if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]))
//                    {
//                        salle_deja_vue = true;
//                    }
//                }

//                if(salle_deja_vue == false)
//                {
//                    //On note cette salle comme vue
//                    salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));

//                    //On trouve le chemin pour avoir la salle du bas
//                    QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
//                    action_salle_prov.push_back(action_type::deplacement_droite);
//                    action_front_exploration_liste.push_back(action_salle_prov);

//                    //On ajoute le cout
//                    cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1);

//                    //On ajoute la salle dans le front
//                    salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));
//                }
//            }
//        }

//        //Et pour finir on suprime la salle actuelle du front
//        salle_front_exploration_liste.remove(cout_faible_indice);
//        cout_front_exploration_liste.remove(cout_faible_indice);
//        action_front_exploration_liste.remove(cout_faible_indice);
//    }

//    action_resulta_exploration.push_back(action_type::voir);
//    return action_resulta_exploration;
}

void Aspirateur_agent::mise_jour_liste_action(Entite_simulation* entite, QVector<int> liste_action)
{
    if(entite == this)
    {
        //On convertie les int en actions
        QVector<action_type> resultat_conversion;

        for(int i = 0; i < liste_action.size(); i++)
        {
            switch(liste_action[i])
            {
                case 0 :
                    resultat_conversion.push_back(action_type::deplacement_haut);
                    break;

                case 1 :
                    resultat_conversion.push_back(action_type::deplacement_bas);
                    break;

                case 2 :
                    resultat_conversion.push_back(action_type::deplacement_gauche);
                    break;

                case 3 :
                    resultat_conversion.push_back(action_type::deplacement_droite);
                    break;

                case 4 :
                    resultat_conversion.push_back(action_type::voir);
                    break;

                case 5 :
                    resultat_conversion.push_back(action_type::ramasser);
                    break;

                case 6 :
                    resultat_conversion.push_back(action_type::aspirer);
                    break;
            }
        }

        this->liste_action = resultat_conversion;
        this->fonction_action(entite);
    }
}
