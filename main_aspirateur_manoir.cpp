#include "main_aspirateur_manoir.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    main_windows_aspirateur_manoir w;
//    w.show();

    QVector<int> taille_manoir;
    //On fixe la taille en X
    taille_manoir.push_back(25);
    //On fixe la taille en Y
    taille_manoir.push_back(25);

    Environnement_manoir* manoir_1 = new Environnement_manoir(taille_manoir);
    Aspirateur_agent* aspirateur = new Aspirateur_agent(0, 0, manoir_1);
    Aspirateur_agent* aspirateur2 = new Aspirateur_agent(2, 1, manoir_1);
    Fenetre_affichage_manoir* fenetre_manoir_1 = new Fenetre_affichage_manoir(manoir_1);

//    Deplacement_thread* test_deplacement = new Deplacement_thread;
//    test_deplacement->entite = aspirateur;
//    test_deplacement->position_arriver_x = 1;
//    test_deplacement->position_arriver_y = 0;
//    test_deplacement->temps_attente_ms = 2500;

//    QObject::connect(test_deplacement, &Deplacement_thread::fin_deplacement, manoir_1, &Environnement_manoir::deplacement_entite);
//    QObject::connect(manoir_1, &Environnement_manoir::rafraichissement_image, fenetre_manoir_1, &Fenetre_affichage_manoir::rafraichissement_image);
//    test_deplacement->start();

    fenetre_manoir_1->show();
//    test_deplacement->wait();
    qDebug() << "C'est fini";
    return a.exec();
}
