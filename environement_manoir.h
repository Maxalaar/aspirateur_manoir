#ifndef ENVIRONNEMENT_MANOIR_H
#define ENVIRONNEMENT_MANOIR_H

#include <QVector>
#include <QThread>
#include <QRandomGenerator>

#include "salle_manoir.h"
#include "entite_simulation.h"
#include "deplacement_thread.h"
#include "vision_thread.h"
#include "ramassage_thread.h"
#include "aspiration_thread.h"

class Environnement_manoir : public QObject/* : public QThread*/
{
    Q_OBJECT
public:
    Environnement_manoir(QVector<int> taille_manoir, int nombre_poussiere_initiale, int nombre_bijou_initiale);
    QVector<QVector<Salle_manoir>> get_tableau();
    void placer_entite(int positon_x, int positon_y, Entite_simulation* entite);
    int temps_deplacement_ms = 80;
    int temps_vision_ms = 100;
    int temps_recuperation_ms = 120;
    int temps_aspiration_ms = 120;
    int nombre_poussiere_initiale;
    int nombre_bijou_initiale;

//    void run() override;

private:
    QVector<QVector<Salle_manoir>> tableau;
    QVector<Entite_simulation> liste_aspirateur;
    
public slots:
    void deplacement_entite(Entite_simulation* entite, int position_x, int position_y);

    //Gestion du deplacement
    void deplacement_haut_entite(Entite_simulation* entite);
    void deplacement_bas_entite(Entite_simulation* entite);
    void deplacement_gauche_entite(Entite_simulation* entite);
    void deplacement_droite_entite(Entite_simulation* entite);

    //Gestion de la vision
    void mise_jour_manoire_init(Entite_simulation* entite);
    void mise_jour_manoire(Entite_simulation* entite);

    //Gestion du ramassage
    void ramassage_init(Entite_simulation* entite);
    void ramassage(Entite_simulation* entite);

    //Gestion aspiration
    void aspiration_init(Entite_simulation* entite);
    void aspiration(Entite_simulation* entite);

signals:
    void rafraichissement_image(void);
    void fin_action(Entite_simulation* entite);

    //Gestion de la vision
    void mise_jour_manoir(Entite_simulation* entite, QVector<QVector<Salle_manoir>> tableau);
};

#endif // ENVIRONNEMENT_MANOIR_H
