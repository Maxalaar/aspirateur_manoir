#ifndef ASPIRATEUR_AGENT_H
#define ASPIRATEUR_AGENT_H

#include "entite_simulation.h"
#include "environement_manoir.h"
#include "salle_manoir.h"
#include "exploration_non_informees_thread.h"
#include "exploration_informees_thread.h"

class Aspirateur_agent : public Entite_simulation
{
    Q_OBJECT
public:
    Aspirateur_agent(int position_initial_x, int position_initial_y, Environnement_manoir* manoir, int sycro_vision, bool exploration_informees);

private:
    Environnement_manoir* manoir;
    QVector<QVector<Salle_manoir>> tableau;
    int sycro_vision;
    int compteur_vision = 0;
    QVector<action_type> liste_action;
    void exploration_non_informees(QVector<QVector<Salle_manoir>> tableau);
    void exploration_informees(QVector<QVector<Salle_manoir>> tableau);
    bool recherche_en_cours = false;
    bool exploration_informees_bool;

public slots:
    void fonction_action(Entite_simulation* entite);
    void mise_jour_manoire(Entite_simulation* entite, QVector<QVector<Salle_manoir>> tableau);
    void mise_jour_liste_action(Entite_simulation* entite, QVector<int> liste_action);

signals:
    void deplacement_haut(Entite_simulation* entite);
    void deplacement_bas(Entite_simulation* entite);
    void deplacement_gauche(Entite_simulation* entite);
    void deplacement_droite(Entite_simulation* entite);

    void voir_manoire(Entite_simulation* entite);
    void ramasser_objet(Entite_simulation* entite);
    void aspirer_salle(Entite_simulation* entite);
};

#endif // ASPIRATEUR_AGENT_H
