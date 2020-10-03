#include "aspirateur_agent.h"

Aspirateur_agent::Aspirateur_agent(int position_initial_x, int position_initial_y, Environnement_manoir* manoir, int sycro_vision, bool exploration_informees)
{
    this->sycro_vision = sycro_vision;
    this->exploration_informees_bool = exploration_informees;
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

    this->fonction_action(this);
//    this->exploration_non_informees(this->tableau);
}

void Aspirateur_agent::fonction_action(Entite_simulation* entite)
{
    if(entite == this)
    {
        if(liste_action.size() > 0 && compteur_vision < sycro_vision && recherche_en_cours != true)
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
        else
        {
            if(recherche_en_cours == false)
            {
                recherche_en_cours = true;
                compteur_vision = 0;
                emit voir_manoire(this);
            }
        }
    }
}

void Aspirateur_agent::mise_jour_manoire(Entite_simulation* entite, QVector<QVector<Salle_manoir>> tableau)
{
    if(entite == this)
    {
        this->tableau = tableau;
        if(exploration_informees_bool == true)
        {
            this->exploration_informees(this->tableau);
        }
        else
        {
            this->exploration_non_informees(this->tableau);
        }
    }
}

void Aspirateur_agent::exploration_non_informees(QVector<QVector<Salle_manoir>> tableau)
{
    Exploration_non_informees_thread* exploration_non_informees_thread = new Exploration_non_informees_thread;
    qRegisterMetaType<QVector<int> >("QVector<int>");

    QObject::connect(exploration_non_informees_thread, &Exploration_non_informees_thread::fin_exploration_non_informees, this, &Aspirateur_agent::mise_jour_liste_action);
    exploration_non_informees_thread->entite = this;
    exploration_non_informees_thread->tableau = tableau;
    exploration_non_informees_thread->start();
}

void Aspirateur_agent::exploration_informees(QVector<QVector<Salle_manoir>> tableau)
{
    Exploration_informees_thread* exploration_informees_thread = new Exploration_informees_thread;
    qRegisterMetaType<QVector<int> >("QVector<int>");

    QObject::connect(exploration_informees_thread, &Exploration_informees_thread::fin_exploration_informees, this, &Aspirateur_agent::mise_jour_liste_action);
    exploration_informees_thread->entite = this;
    exploration_informees_thread->tableau = tableau;
    exploration_informees_thread->start();
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
        this->recherche_en_cours = false;
        this->fonction_action(entite);
    }
}
