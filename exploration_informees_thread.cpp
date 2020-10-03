#include "exploration_informees_thread.h"

void Exploration_informees_thread::run()
{
    QVector<Salle_manoir*> salle_historique;
    QVector<Salle_manoir*> salle_front_exploration_liste;
    QVector<double> cout_front_exploration_liste;
    QVector<QVector<action_type>> action_front_exploration_liste;

    QVector<action_type> action_resulta_exploration;

    //On cherche tout les poussier et bijou du manoire
    QVector<int> position_x_salle_interet;
    QVector<int> position_y_salle_interet;

    //On crée le tableau des cout heuristique
    QVector<QVector<double>> tableau_cout_heuristique;
    for(int i = 0; i < tableau.size(); i++)
    {
        QVector<double> ligne_cout_prov;

        for(int j = 0; j < tableau[0].size(); j++)
        {
            ligne_cout_prov.push_back(0);
        }

        tableau_cout_heuristique.push_back(ligne_cout_prov);
    }

    for(int i = 0; i < tableau[0].size(); i++)
    {
        for(int j = 0; j < tableau.size(); j++)
        {
            for(int k = 0; k <tableau[i][j].liste_entite.size(); k++)
            {
                if(tableau[i][j].liste_entite[k]->type_entite == "bijou" || tableau[i][j].liste_entite[k]->type_entite == "poussiere")
                {
                     position_x_salle_interet.push_back(i);
                     position_y_salle_interet.push_back(j);
                }
            }
        }
    }

    if(position_x_salle_interet.size() > 0)
    {
        //On calcule la distance entre une salle et la poussier ou le bijou le plus proche

        //On cherche le cout le plus faible pour chaque salle
        for(int i = 0; i < tableau[0].size(); i++)
        {
            for(int j = 0; j < tableau.size(); j++)
            {
                double cout_faible_prov = std::numeric_limits<double>::max();
                for(int k = 0; k <position_x_salle_interet.size(); k++)
                {
                    double calcul_cout_heuristique = qSqrt(qPow(position_x_salle_interet[k] - (double)i, 2) + qPow(position_y_salle_interet[k] - (double)j, 2));
                    if(calcul_cout_heuristique < cout_faible_prov)
                    {
                        cout_faible_prov = calcul_cout_heuristique;
                    }
                }
                tableau_cout_heuristique[i][j] = cout_faible_prov;
            }
        }
    }

        //On cherche dans quelle salle se trouve l'aspirateur
        Salle_manoir* salle_initial;
        for(int i = 0; i < tableau[0].size(); i++)
        {
            for(int j = 0; j < tableau.size(); j++)
            {
                for(int k = 0; k <tableau[i][j].liste_entite.size(); k++)
                {
                    if(tableau[i][j].liste_entite[k] == this->entite)
                    {
                        salle_initial = &tableau[i][j];
                    }
                }
            }
        }

        //On ajoute les données où ce trouve l'aspirateur
        salle_front_exploration_liste.push_back(salle_initial);
        cout_front_exploration_liste.push_back(0);
        QVector<action_type> action_salle_initial;
        action_front_exploration_liste.push_back(action_salle_initial);

        bool continuer_exploration = true;

        while(continuer_exploration && salle_front_exploration_liste.size() > 0)
        {

            //On cherche l'indice du sommet avec le plus faible cout
            int cout_faible_valeur = std::numeric_limits<int>::max();
            int cout_faible_indice = -1;

            for(int i = 0; i < cout_front_exploration_liste.size(); i++)
            {
                if(cout_front_exploration_liste[i] < cout_faible_valeur)
                {
                    cout_faible_indice = i;
                    cout_faible_valeur = cout_front_exploration_liste[i];
                }
            }

            //On cherche si il y a de la poussiere dans cette salle
            for(int i = 0; i < salle_front_exploration_liste[cout_faible_indice]->liste_entite.size(); i++)
            {
                if(salle_front_exploration_liste[cout_faible_indice]->liste_entite[i]->type_entite == "poussiere")
                {
                    continuer_exploration = false;
                    action_front_exploration_liste[cout_faible_indice].push_back(action_type::aspirer);
                    action_resulta_exploration = action_front_exploration_liste[cout_faible_indice];
                }
            }

            //On cherche si il y a un bijou dans cette salle
            for(int i = 0; i < salle_front_exploration_liste[cout_faible_indice]->liste_entite.size(); i++)
            {
                if(salle_front_exploration_liste[cout_faible_indice]->liste_entite[i]->type_entite == "bijou")
                {
                    continuer_exploration = false;
                    action_front_exploration_liste[cout_faible_indice].push_back(action_type::ramasser);
                    action_resulta_exploration = action_front_exploration_liste[cout_faible_indice];
                }
            }

            //Si on trouve rien on develope les salles adjacente;
            if(continuer_exploration == true)
            {
                //On develope la salle du haut si possible
                if(salle_front_exploration_liste[cout_faible_indice]->position_y + 1 < tableau.size())
                {
                    //On verifie que la salle est pas déja dans l'historique
                    bool salle_deja_vue = false;
                    for(int i = 0; i < salle_historique.size(); i++)
                    {
                        if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]))
                        {
                            salle_deja_vue = true;
                        }
                    }

                    if(salle_deja_vue == false)
                    {
                        //On note cette salle comme vue
                        salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]));

                        //On trouve le chemin pour avoir la salle du haut
                        QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
                        action_salle_prov.push_back(action_type::deplacement_haut);
                        action_front_exploration_liste.push_back(action_salle_prov);

                        //On ajoute le cout
                        cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1 + tableau_cout_heuristique[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]);

                        //On ajoute la salle dans le front
                        salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y + 1]));
                    }
                }

                //On develope la salle du bas si possible
                if(salle_front_exploration_liste[cout_faible_indice]->position_y - 1 >= 0)
                {
                    //On verifie que la salle est pas déja dans l'historique
                    bool salle_deja_vue = false;
                    for(int i = 0; i < salle_historique.size(); i++)
                    {
                        if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]))
                        {
                            salle_deja_vue = true;
                        }
                    }

                    if(salle_deja_vue == false)
                    {
                        //On note cette salle comme vue
                        salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]));

                        //On trouve le chemin pour avoir la salle du bas
                        QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
                        action_salle_prov.push_back(action_type::deplacement_bas);
                        action_front_exploration_liste.push_back(action_salle_prov);

                        //On ajoute le cout
                        cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1 + tableau_cout_heuristique[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]);

                        //On ajoute la salle dans le front
                        salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x][salle_front_exploration_liste[cout_faible_indice]->position_y - 1]));
                    }
                }

                //On develope la salle de gauche si possible
                if(salle_front_exploration_liste[cout_faible_indice]->position_x - 1 >= 0)
                {
                    //On verifie que la salle est pas déja dans l'historique
                    bool salle_deja_vue = false;
                    for(int i = 0; i < salle_historique.size(); i++)
                    {
                        if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]))
                        {
                            salle_deja_vue = true;
                        }
                    }

                    if(salle_deja_vue == false)
                    {
                        //On note cette salle comme vue
                        salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));

                        //On trouve le chemin pour avoir la salle du bas
                        QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
                        action_salle_prov.push_back(action_type::deplacement_gauche);
                        action_front_exploration_liste.push_back(action_salle_prov);

                        //On ajoute le cout
                        cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1 + tableau_cout_heuristique[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]);

                        //On ajoute la salle dans le front
                        salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x - 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));
                    }
                }

                //On develope la salle de droite si possible
                if(salle_front_exploration_liste[cout_faible_indice]->position_x + 1 < tableau[0].size())
                {
                    //On verifie que la salle est pas déja dans l'historique
                    bool salle_deja_vue = false;
                    for(int i = 0; i < salle_historique.size(); i++)
                    {
                        if(salle_historique[i] == &(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]))
                        {
                            salle_deja_vue = true;
                        }
                    }

                    if(salle_deja_vue == false)
                    {
                        //On note cette salle comme vue
                        salle_historique.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));

                        //On trouve le chemin pour avoir la salle du bas
                        QVector<action_type> action_salle_prov = action_front_exploration_liste[cout_faible_indice];
                        action_salle_prov.push_back(action_type::deplacement_droite);
                        action_front_exploration_liste.push_back(action_salle_prov);

                        //On ajoute le cout
                        cout_front_exploration_liste.push_back(cout_front_exploration_liste[cout_faible_indice] + 1 + + tableau_cout_heuristique[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]);

                        //On ajoute la salle dans le front
                        salle_front_exploration_liste.push_back(&(tableau[salle_front_exploration_liste[cout_faible_indice]->position_x + 1][salle_front_exploration_liste[cout_faible_indice]->position_y]));
                    }
                }
            }

            //Et pour finir on suprime la salle actuelle du front
            salle_front_exploration_liste.remove(cout_faible_indice);
            cout_front_exploration_liste.remove(cout_faible_indice);
            action_front_exploration_liste.remove(cout_faible_indice);
        }

//    action_resulta_exploration.push_back(action_type::voir);

    //On convertie les actions en int
    QVector<int> resultat_conversion;

    for(int i = 0; i < action_resulta_exploration.size(); i++)
    {
        switch(action_resulta_exploration[i])
        {
            case action_type::deplacement_haut :
                resultat_conversion.push_back(0);
                break;

            case action_type::deplacement_bas :
                resultat_conversion.push_back(1);
                break;

            case action_type::deplacement_gauche :
                resultat_conversion.push_back(2);
                break;

            case action_type::deplacement_droite :
                resultat_conversion.push_back(3);
                break;

            case action_type::voir :
                resultat_conversion.push_back(4);
                break;

            case action_type::ramasser :
                resultat_conversion.push_back(5);
                break;

            case action_type::aspirer :
                resultat_conversion.push_back(6);
                break;
        }
    }

    emit fin_exploration_informees(entite, resultat_conversion);

}
