#ifndef ASPIRATEUR_AGENT_H
#define ASPIRATEUR_AGENT_H

#include "entite_simulation.h"
#include "environement_manoir.h"
#include "salle_manoir.h"

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

class Aspirateur_agent : public Entite_simulation
{
    Q_OBJECT
public:
    Aspirateur_agent(int position_initial_x, int position_initial_y, Environnement_manoir* manoir);

private:
    Environnement_manoir* manoir;
    QVector<QVector<Salle_manoir>> tableau;
    int sycro_vision = 30;
    int compteur_vision = 0;
    QVector<action_type> liste_action;
    QVector<action_type> exploration_non_informees(QVector<QVector<Salle_manoir>> tableau);

public slots:
    void fonction_action(Entite_simulation* entite);
    void mise_jour_manoire(Entite_simulation* entite, QVector<QVector<Salle_manoir>> tableau);

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
